#include "socketmanager.h"

SocketManager::SocketManager()
{
    tcpSocket.connectToHost("elysium-project.net",6692);
    if(tcpSocket.waitForConnected(2000)){
        qDebug() << "Connected!";
    }
    else{
        qDebug() << "Not Connected!";
    }
}
