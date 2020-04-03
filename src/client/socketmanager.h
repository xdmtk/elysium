#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H
#include <QTcpSocket>
#include "loginwindow.h"
#include <portInfo.h>

class ChatWindow;
class SocketManager
{
public:
    SocketManager(ChatWindow * cw);
    SocketManager(portInfo pass, ChatWindow * cw);
    std::string readServerData();
    void sendBasicChatMessage(QString msg);
    void setUsernameOnServer(QString username);
    void sendTypingIndicator();
    void sendNoTypingIndicator();
    void requestOnlineUserlist();
    bool isConnectedToServer() {return connectedToServer;};
    QTcpSocket *getSocket();

private:
    QTcpSocket tcpSocket;
    ChatWindow * chatWindow;
    void writeToServer(QString data);
    bool connectedToServer;
};

#endif // SOCKETMANAGER_H
