#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "commandmanager.h"
#include "notificationmanager.h"
#include "soundmanager.h"
#include <QTime>
#include "hyperlinkdiag.h"
#include "ui_hyperlinkdiag.h"

/*
 * Constructor:
 * Sets style of the ChatWindow up
 * while making a connection to the server
 */
ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    ui->inputDisplay->focusWidget();
    ui->emojiList->setVisible(showEmoji);

    ui->friendsDisplay->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->friendsDisplay, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));

    socket = new SocketManager(this);
    soundManager = new SoundManager();
    commandManager = new CommandManager(this, socket, soundManager);
    notificationManager = new NotificationManager(this);
    connect(socket->getSocket(), &QTcpSocket::readyRead,this, &ChatWindow::activateCommandManager);
}

ChatWindow::ChatWindow(portInfo pass, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    ui->inputDisplay->focusWidget();
    ui->emojiList->setVisible(showEmoji);

    ui->friendsDisplay->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->friendsDisplay, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));

    p = pass;

    socket = new SocketManager(p, this);
    soundManager = new SoundManager();
    commandManager = new CommandManager(this, socket, soundManager);
    notificationManager = new NotificationManager(this);


    connect(socket->getSocket(), &QTcpSocket::readyRead,this, &ChatWindow::activateCommandManager);
}

void ChatWindow::setLocalUsername(QString u) {
    username = u;
}

ChatWindow::~ChatWindow(){
    delete ui;
}
/*
 * Slot function:
 * After typing message in GUI and pressing enter this
 * function is emmited in which it sends the data
 * to the server
 */
void ChatWindow::on_inputDisplay_returnPressed(){
   socket->sendBasicChatMessage(ui->inputDisplay->text());
   soundManager->sendMessage();
   ui->inputDisplay->clear();
}


/*
 * Slot function:
 * This slot is emmited when the user clicks on light mode
 * for the menubar of the GUI
 */
void ChatWindow::on_actionLight_mode_triggered(){
    ui->outputDisplay->setStyleSheet("background: white;"
                                     "color:black;");
    ui->inputDisplay->setStyleSheet("background: white;"
                                    "color:black;"
                                    "border: 1px solid black;");
    ui->friendsDisplay->setStyleSheet("background: white;"
                                      "color:black;");

}


/*
 * Slot function:
 * This slot is emmited when the user clicks on dark mode
 * from the menubar of the GUI
 */
void ChatWindow::on_actionDark_mode_triggered() {
    ui->outputDisplay->setStyleSheet("background: rgb(80,80,80);"
                                     "color:white;");
    ui->inputDisplay->setStyleSheet("background: rgb(80,80,80);"
                                    "color:white;"
                                    "border: 1px solid black;");
    ui->friendsDisplay->setStyleSheet("background: rgb(80,80,80);"
                                      "color:white;");
    //ui->menuFile->setStyleSheet();
    //setStyleSheet("background-color: black;");
}




/*
 * Slot function:
 * This slot is emmited when there is data avaible to be
 * read from the server. It reads the data and then displays
 * it to the ChatWindow GUI
 * When using append, text inherits style from previous block, so span is needed
 * in order to prevent text to turn blue after a link has been added.
 * see:
 * https://stackoverflow.com/questions/44291816/qt-open-href-links
 */
void ChatWindow::display(QString msg) {
    if(msg[0] != "<"){
        QStringList u = msg.split(":");
        QString sender = u[0];
        if(sender != username)
            soundManager->incMessage();
    }
    msg = "<span> " + msg + "</span>" ;
    ui->outputDisplay->append(msg);
    ui->typingIndicator->setText("");
}


/**
 * Slot function:
 * @param arg1 = oldPosition, arg2 = newPosition
 * This slot is emited when someone changes cursor position
 * when arg1 is -1 its the first instance of typing since Chat has been open
 * when arg1 is 0 it means user is typing
 * when arg2 reaches 0 then user is not typing
 */
void ChatWindow::on_inputDisplay_cursorPositionChanged(int arg1, int arg2){
    if(arg2 == 0) {
        socket->sendNoTypingIndicator();
        ui->sendQLabel->setPixmap(QPixmap(":/resources/send_inactive.png"));
    }
    else if(arg1 == 0 || arg1 == -1) {
        socket->sendTypingIndicator();
        ui->sendQLabel->setPixmap(QPixmap(":/resources/send_active.png"));
    }
}
/**
 * Sound initially off, buttons toggle it on/off.
 */
void ChatWindow::on_actionSound_on_triggered(){
    commandManager->updateSoundSettings(true);
    ui->actionSound_off->setChecked(false);
    ui->actionSound_on->setChecked(true);
}
void ChatWindow::on_actionSound_off_triggered(){
    commandManager->updateSoundSettings(false);
    ui->actionSound_on->setChecked(false);
    ui->actionSound_off->setChecked(true);
}
void ChatWindow::on_hyperLinkButton_clicked(){
    hyperlink = new hyperlinkDiag(this);
    hyperlink->setCw(this);
    hyperlink->show();
}
/**
 * Modifier function:
 * @param client protocol with the associated userName
 * This function updates the member QVector with the users
 * typing and then sends a prompt back with the updated list
 * @return QString with prompt of current users typing
 */
QString ChatWindow::getUpdatedTypingPrompt(CoreSettings::Protocol type,
                                      std::string userName){
    QString typingPrompt = "";
    QByteArray currentUser(userName.c_str(), userName.length());
    int index = usersTyping.indexOf(currentUser);

    //1.Check for protocol and then either add or delete user from vector
    if(type == CoreSettings::Protocol::TypingIndicator && index == -1)
        usersTyping.push_front(currentUser);
    else if((type == CoreSettings::Protocol::NoTyping && index != -1))
        usersTyping.remove(index);

    //2.If there is at least one user typing display prompt
    if(usersTyping.size() != 0){
        for(QVector<QString>::iterator it = usersTyping.begin(); it != usersTyping.end(); it++)
            typingPrompt += *it + ", ";
        typingPrompt += " is typing ...";

    }
    return typingPrompt;

}

/**
 * Called by CommandManager when either a TypingIndicator or NoTyping
 * Protocol enumeratioin is received from the server. Sets the text
 * of the QLabel that shows whether a user is typing or not.
 *
 * @param indicator - Either Typing or NoTyping
 * @param user - Username string that broadcasted the typing indicator
 *
 */
void ChatWindow::setUsersTypingLabel(CoreSettings::Protocol indicator, std::string user) {
    ui->typingIndicator->setText(getUpdatedTypingPrompt(indicator, user));
}


/**
 * Slot function wrapper to make a call to handleIncomingMessage.
 * When calling connect() against a signal emitted by our socket object,
 * apparently the slot function needs to be a member of the class that
 * called connect()
 */
void ChatWindow::activateCommandManager() {
    commandManager->handleIncomingMessage();
}


/**
 * Iterates a QStringList of usernames currently logged into
 * the server. Called by the CommandManager when a 
 * ClientReceiveOnlineStatus Protocol enumeration is 
 * received from the server.
 */
void ChatWindow::setOnlineUserList(QStringList userlist) {
    QString u = QString::number(userlist.size()-1);
    qDebug()<< u;
    int t = u.toInt();
    ui->friendsDisplay->clear();
    if ((userlist.size()-1)== 1) {
        ui->peopleHereLabel->setText("<b>1 person here</b>");
    }
    else {
        ui->peopleHereLabel->setText("<b>"+QString::number(userlist.size()-1)+" people here</b>");
    }

    for (auto user : userlist) {
        if(user != "")
        ui->friendsDisplay->addItem(user);
        qDebug() << user;
    }
    if(t > usersOnline){
        soundManager->userEntersChat();
        /*if(usersOnline != 0){
          getNotificationManager()->detectFriendOnline(usersOnline, t, ui->friendsDisplay);
          }*/
      }
    qDebug()<<usersOnline;
    if(t < usersOnline)
    soundManager->userLeavesChat();
    usersOnline = t;

}

/*makes the emojiList widget visible or if the widget is already visible
then it is removed from view*/
void ChatWindow::on_emojisButton_clicked(){
  if(ui->inputDisplay->hasSelectedText()){
      selectionStart = ui->inputDisplay->selectionStart();
      selectionLength = ui->inputDisplay->selectionLength();
      hasSelect = true;
    }
  if(showEmoji == false)
    showEmoji = true;
  else
    showEmoji = false;
  ui->emojiList->setVisible(showEmoji);
}

/*inserts the selected emoji into the input Display*/
void ChatWindow::on_emojiList_itemClicked(QListWidgetItem *item){
  QString S = item->text();
  if(hasSelect)
  ui->inputDisplay->setSelection(selectionStart, selectionLength);
  ui->inputDisplay->insert(S);
  showEmoji = false;
  ui->emojiList->setVisible(showEmoji);
  ui->inputDisplay->deselect();
  hasSelect = false;
}

/*inserts an @call to user selected at the end of current available text.
 * Will not replace selected text*/
void ChatWindow::on_friendsDisplay_itemClicked(QListWidgetItem *item){
  QString S = " @" + item->text();
  ui->inputDisplay->end(false);
  ui->inputDisplay->insert(S);
}

void ChatWindow::ShowContextMenu(const QPoint& pos) // this is a slot
{
    // for most widgets
    QPoint globalPos = ui->friendsDisplay->mapToGlobal(pos);
  if(ui->friendsDisplay->itemAt(pos) != nullptr){
    QMenu myMenu;
    if(ui->friendsDisplay->itemAt(pos)->text() != getUsername()){
        if(areFriends(ui->friendsDisplay->itemAt(pos)->text())){
           myMenu.addAction("Remove Friend");
          }
        else{
           myMenu.addAction("Add Friend");
            }
      }
    myMenu.addAction("Block");
    // ...

    QAction* rightClickedItem = myMenu.exec(globalPos);
        if (rightClickedItem)
        {
            if(rightClickedItem->text().contains("Add Friend")){
                getSocketManager()->addFriend(getUsername(), ui->friendsDisplay->itemAt(pos)->text());
                  }
            else if(rightClickedItem->text().contains("Remove Friend")){
                getSocketManager()->deleteFriend(getUsername(), ui->friendsDisplay->itemAt(pos)->text());
                    }
            else if(rightClickedItem->text().contains("Block")){

              }
          }
        else
        {
        // nothing was chosen
        }

      }

}

/*return true if you are friends and false if you are not
calls socketmanager to check friend status*/
bool ChatWindow::areFriends(QString friendUserName){

getSocketManager()->verifyFriendStatus(getUsername(), friendUserName);
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

return getCommandManager()->getAreFriends();
}

