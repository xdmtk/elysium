#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H
#include <QTcpSocket>
#include <QtDebug>


class SocketManager{
public:
    SocketManager();

private:
   friend class ChatWindow;
    void connect();
    QTcpSocket *tcpSocket;

};

#endif // SOCKETMANAGER_H
