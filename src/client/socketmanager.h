#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H
#include <QTcpSocket>

class SocketManager
{
public:
    SocketManager();
    QTcpSocket tcpSocket;
};

#endif // SOCKETMANAGER_H
