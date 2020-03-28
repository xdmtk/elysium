#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "commandmanager.h"
#include "notificationmanager.h"

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

    socket = new SocketManager(this);
    commandManager = new CommandManager(this, socket);
    notificationManager = new NotificationManager(this);

    connect(socket->getSocket(), &QTcpSocket::readyRead,this, &ChatWindow::activateCommandManager);
}

void ChatWindow::setUsername(QString u) {
    username = u;
    socket->setUsernameOnServer(username);
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
}


/*
 * Slot function:
 * This slot is emmited when there is data avaible to be
 * read from the server. It reads the data and then displays
 * it to the ChatWindow GUI
 */
void ChatWindow::display(QString msg) {
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
    ui->friendsDisplay->clear();
    if ((userlist.size()-1)== 1) {
        ui->peopleHereLabel->setText("<b>1 person here</b>");
    }
    else {
        ui->peopleHereLabel->setText("<b>"+QString::number(userlist.size()-1)+" people here</b>");
    }
    for (auto user : userlist) {
        ui->friendsDisplay->append(user);
    }
}
