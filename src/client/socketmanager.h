#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H
#include <QTcpSocket>
#include <QtDebug>


class SocketManager{
public:
    SocketManager();
    friend class ChatWindow;

private:
     void connect();
    QTcpSocket *tcpSocket;

};

#endif // SOCKETMANAGER_H
