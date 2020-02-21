#include "socketmanager.h"

SocketManager::SocketManager()
{
    tcpSocket = new QTcpSocket();
}

void SocketManager::connect(){
    tcpSocket->connectToHost("elysium-project.net",6692);

    if(!tcpSocket->waitForConnected(1000)){
        qDebug() << "Error" << tcpSocket->errorString();
    }
    else{
        qDebug() << "connected";
    }
}
