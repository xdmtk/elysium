#include "chatwindow.h"
#include "ui_chatwindow.h"


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
    ui->inputDisplay->focusWidget();

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
            ui->typingIndicator->setText(updateUsersTyping(response,temp));
            break;
        case CoreSettings::Protocol::NoTyping:
            ui->typingIndicator->setText(updateUsersTyping(response,temp));
            break;
    }
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
    if(arg2 == 0)
        socket->sendNoTypingIndicator();
    else if(arg1 == 0 || arg1 == -1)
        socket->sendTypingIndicator();
}

/**
 * Modifier function:
 * @param client protocol with the associated userName
 * This function updates the member QVector with the users
 * typing and then sends a prompt back with the updated list
 * @return QString with prompt of current users typing
 */
QString ChatWindow::updateUsersTyping(CoreSettings::Protocol type,
                                      std::string userName){
    QString typingPrompt = "";
    QByteArray currentUser(userName.c_str(), userName.length());
    int index = usersTyping.indexOf(currentUser);

    //1.Check for protocol and then either add or delete user from vector
    if(type == CoreSettings::Protocol::TypingIndicator && index == -1)
        usersTyping.push_front(currentUser);
    else if((type == CoreSettings::Protocol::NoTyping))
        usersTyping.remove(index);

    //2.If there is at least one user typing display prompt
    if(usersTyping.size() != 0){
        for(QVector<QString>::iterator it = usersTyping.begin(); it != usersTyping.end(); it++)
            typingPrompt += *it + ",";
        typingPrompt += " is typing ...";

    }
    return typingPrompt;

}
