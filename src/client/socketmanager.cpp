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

    /* Set a pointer back to the ChatWindow */
    chatWindow = cw;
    connectedToServer = false;

    /* Attempt to connect to the server */
    tcpSocket.connectToHost("elysium-project.net",6692);
    if(tcpSocket.waitForConnected(1000)){
        qDebug() << "Connected!";
        connectedToServer = true;
    }
    else{

        /* TODO: Should probably either close or disable the ChatWindow if 
         * there is a connection failure.. or even possibly instantiate the SocketManager
         * from the LoginWindow class before showing the ChatWindow */
        qDebug() << "Not Connected-->" + tcpSocket.errorString();
        qDebug() << tcpSocket.error();
    }
}

SocketManager::SocketManager(portInfo pass, ChatWindow * cw) {

    /* Set a pointer back to the ChatWindow */
    chatWindow = cw;
    connectedToServer = false;


    /* Attempt to connect to the server */
    /*Uses info for server instance chosen at login*/
    tcpSocket.connectToHost(pass.hostName, pass.portNumber);
    if(tcpSocket.waitForConnected(2000)){
        qDebug() << "Connected!";
        connectedToServer = true;

    }
    else{

        /* TODO: Should probably either close or disable the ChatWindow if
         * there is a connection failure.. or even possibly instantiate the SocketManager
         * from the LoginWindow class before showing the ChatWindow */
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

    /* Do the const char * casting here instead of from the ChatWindow class */
    tcpSocket.write(data.toStdString().c_str());
}


/**
 * Sets the username on the server for this client by appending 
 * a CoreSettings::Protocol enum as the first byte of the message 
 * 
 * @param - username - Username string to set on the server
 */
void SocketManager::setUsernameOnServer(QString username) {

    QString msgToSend;

    /* Append the Protocol indicator  */
    msgToSend.append(CoreSettings::Protocol::ServerSetUsername);

    /* Append the username (The server knows that the username comes directly
     * after the Protocol indicator */
    msgToSend.append(username);

    /* Send the raw QString to the server */
    writeToServer(msgToSend);
}
/*
 * Write function:
 * Gets the protocol that someone is typing and sends
 * off to server
 */
void SocketManager::sendTypingIndicator()
{
    QString msgToSend = "";
    msgToSend.append(CoreSettings::Protocol::TypingIndicator);
    writeToServer(msgToSend);


}

void SocketManager::sendNoTypingIndicator()
{
    QTimer::singleShot(250, [&](){
        QString msgToSend ="";
        msgToSend.append(CoreSettings::Protocol::NoTyping);
        writeToServer(msgToSend);
    });
}


/**
 * Sets the username on the server for this client by appending 
 * a CoreSettings::Protocol enum as the first byte of the message 
 * 
 * @param - username - Username string to set on the server
 */
void SocketManager::sendBasicChatMessage(QString msg) {
    
   QString msgToSend;
   if(msg.size() != 0){
       /* Append the Protocol indicator  */
       msgToSend.append(CoreSettings::Protocol::ServerBroadcastMessage);
       /* Append the message (The server knows that the message comes directly
        * after the protocol indicator */
       msgToSend.append(msg);
       /* Send the raw QString to the server */
       writeToServer(msgToSend);
   }

}

/**
 * Sends the Protocol enumeration for the Server to respond
 * with a list of usernames currently logged into the server
 */
void SocketManager::requestOnlineUserlist() {

    QString msgToSend;
    msgToSend.append(CoreSettings::Protocol::ServerRequestOnlineStatus);
    writeToServer(msgToSend);
}


/*
 * Get function:
 * Returns the member variable tcpSocket
 */
QTcpSocket *SocketManager::getSocket(){
    return &tcpSocket;
}


