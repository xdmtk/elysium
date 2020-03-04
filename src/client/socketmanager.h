#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H
#include <QTcpSocket>

class SocketManager
{
public:
    SocketManager();
    std::string readServerData();
    void writeToServer(const char *data);
    QTcpSocket *getSocket();

private:
    QTcpSocket tcpSocket;
};

#endif // SOCKETMANAGER_H
