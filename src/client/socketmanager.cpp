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
        qDebug() << "Not Connected!";
    }
}
