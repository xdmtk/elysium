#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "../core/CoreSettings.h"


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
    ui->friendsDisplay->setReadOnly(1);
    ui->outputDisplay->setReadOnly(1);
    ui->inputDisplay->setPlaceholderText("Type here");
    ui->friendsDisplay->setPlaceholderText("Friends list");

    ui->outputDisplay->setStyleSheet("background: rgb(80,80,80);"
                                     "color:white;");
    ui->inputDisplay->setStyleSheet("background: rgb(80,80,80);"
                                    "color:white;"
                                    "border: 1px solid black;");
    ui->friendsDisplay->setStyleSheet("background: rgb(80,80,80);"
                                      "color:white;");
    ui->typingIndicator->setStyleSheet("color:green");

    initUsersTyping();
    socket = new SocketManager(this);
    connect(socket->getSocket(), &QTcpSocket::readyRead,this, &ChatWindow::display);
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
void ChatWindow::display() {
    std::string temp;
    QString qInput,userName;

    temp = socket->readServerData();
    CoreSettings::Protocol response = static_cast<CoreSettings::Protocol>(temp[0]);
    temp = temp.substr(1);

    switch (response){
        case CoreSettings::Protocol::ServerBroadcastMessage:
            qInput = QString::fromUtf8(temp.c_str());
            ui->outputDisplay->append(qInput);
            ui->typingIndicator->setText("");
            break;
        case CoreSettings::Protocol::TypingIndicator:
              ui->typingIndicator->setText(updateUsersTyping(temp));
            break;
        case CoreSettings::Protocol::NoTyping:
            ui->typingIndicator->setText(updateUsersNotTyping(temp));
            break;
    }
}

/*
 * Slot function:
 * This slot is emited when someone changes cursor position
 * It is being used a notype indicator.
 * when cursorposition reaches 0 signal notype indicator
 */
//Its getting changed when enter key is pressed
void ChatWindow::on_inputDisplay_cursorPositionChanged(int arg1, int arg2){
    if(arg2 == 0 && arg1 != 0)
        socket->sendNoTypingIndicator();
    else if(arg1 == 0 )
        socket->sendTypingIndicator();
}
/*
 * Init function:
 * This function initalizes the the usersTyping map.The key being the
 * users name and the value as 0 to indicate user is not typing.
 */
void ChatWindow::initUsersTyping(){
    usersTyping.insert(std::pair<std::string,int>("eric",0));
    usersTyping.insert(std::pair<std::string,int>("daniel",0));
    usersTyping.insert(std::pair<std::string,int>("nick",0));
    usersTyping.insert(std::pair<std::string,int>("josh",0));
    usersTyping.insert(std::pair<std::string,int>("sebastian",0));
}
/**
 * modifier function:
 * @param current user who started typing
 * This function updates the map of users who are typing and then
 * builds a string with it which then is used as the
 * typing indicator
 * @return Qstring with the current users typing
 */
QString ChatWindow::updateUsersTyping(std::string userName){
    QString typingIndicatorPrompt;
    std::map<std::string,int>::iterator it = usersTyping.find(userName);
    userName ="";

    //1.Change current user status to typing
    if(it != usersTyping.end())
        it->second = 1;

    //2.Go through list and if user is currently typing add to output
    for(it = usersTyping.begin(); it != usersTyping.end(); it++)
        if(it->second == 1)
            userName += it->first + ",";

    userName += " is typing ...";

    return QString::fromUtf8(userName.c_str());
}

QString ChatWindow::updateUsersNotTyping(std::string userName){
    QString typingIndicatorPrompt;
    std::map<std::string,int>::iterator it = usersTyping.find(userName);
    userName ="";

    //1.Change current user status to not typing
    if(it != usersTyping.end())
        it->second = 0;

    //2.Go through list and if user is currently typing add to output
    for(it = usersTyping.begin(); it != usersTyping.end(); it++)
        if(it->second == 1)
            userName += it->first + ",";

    //3.Only display if there are people typing
    if(userName.length() != 0)
       userName += " is typing ...";

    return QString::fromUtf8(userName.c_str());
}
