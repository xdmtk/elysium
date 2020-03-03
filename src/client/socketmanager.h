#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H
#include <QTcpSocket>

class SocketManager
{
public:
    SocketManager();
private:
    friend class ChatWindow;
    QTcpSocket tcpSocket;
};

#endif // SOCKETMANAGER_H
