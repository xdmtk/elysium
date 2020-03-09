#include "chatwindow.h"
#include "socketmanager.h"
#include "../core/CoreSettings.h"
#include <QString>

/*
 * Constructor:
 * Connects to host and displays message based on connection
 * waitForConnected parameter is in millieseconds
 */
SocketManager::SocketManager(ChatWindow * cw) {

    chatWindow = cw;
    tcpSocket.connectToHost("elysium-project.net",6885);
    if(tcpSocket.waitForConnected(2000)){
        qDebug() << "Connected!";
    }
    else{
        qDebug() << "Not Connected-->" + tcpSocket.errorString();
        qDebug() << tcpSocket.error();
    }
}

/*
 * Get function:
 * Returns the data from the server as a std::string
 */
std::string SocketManager::readServerData(){
    return tcpSocket.readAll().toStdString();
}

/*
 * Write function:
 * Gets data through parameter in which is then sent to server
 */
void SocketManager::writeToServer(QString data) {
    tcpSocket.write(data.toStdString().c_str());
}

void SocketManager::setUsernameOnServer(QString username) {
    QString msgToSend;
    msgToSend.append(CoreSettings::Protocol::ServerSetUsername);
    msgToSend.append(username);
    writeToServer(msgToSend);
}
/*
 * Write function:
 * Gets the protocol that someone is typing and sends
 * off to server
 */
void SocketManager::sendTypingIndicator()
{
    QString msgToSend;
    msgToSend.append(CoreSettings::Protocol::TypingIndicator);
    writeToServer(msgToSend);

}

void SocketManager::sendNoTypingIndicator()
{
 QString msgToSend;
 msgToSend.append(CoreSettings::Protocol::NoTyping);
 writeToServer(msgToSend);
}

void SocketManager::sendBasicChatMessage(QString msg) {

   QString msgToSend;
   msgToSend.append(CoreSettings::Protocol::ServerBroadcastMessage);
   msgToSend.append(msg);
   writeToServer(msgToSend);
}

/*
 * Get function:
 * Returns the member variable tcpSocket
 */
QTcpSocket *SocketManager::getSocket(){
    return &tcpSocket;
}


