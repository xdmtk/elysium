#include "socketmanager.h"

/*
 * Constructor:
 * Connects to host and displays message based on connection
 * waitForConnected parameter is in millieseconds
 */
SocketManager::SocketManager()
{
    tcpSocket.connectToHost("elysium-project.net",6692);
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
void SocketManager::writeToServer(const char *data){
    tcpSocket.write(data);
}

/*
 * Get function:
 * Returns the member variable tcpSocket
 */
QTcpSocket *SocketManager::getSocket(){
    return &tcpSocket;
}


