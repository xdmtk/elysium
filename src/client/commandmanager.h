#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#include <QString>

class ChatWindow;
class SocketManager;
class CommandManager
{
public:
    CommandManager(ChatWindow * cw, SocketManager * socket);

    void handleIncomingMessage();

private:
    ChatWindow * chatWindow;
    SocketManager * socket;
    void addIncomingMessageToChat(QString msg);
    void updateOnlineUserlist(QString userlist);
};

#endif // COMMANDMANAGER_H
