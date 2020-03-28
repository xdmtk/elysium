#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#include <QString>
#include "../core/CoreSettings.h"

class ChatWindow;
class SocketManager;
class CommandManager
{
public:
    CommandManager(ChatWindow * cw, SocketManager * socket);

    void handleIncomingMessage();
    void authReplyReceivedAndSet();
    QString getAuthReply() {return authReply;};
    bool getAuthSuccess() {return authSuccess;};

private:
    ChatWindow * chatWindow;
    SocketManager * socket;
    QString authReply;
    bool authSuccess;
    void addIncomingMessageToChat(QString msg);
    void updateOnlineUserlist(QString userlist);
    void setAuthReply(QString reply, bool val);
    void handleAuthReply(QString reply, CoreSettings::Protocol protocol);
};

#endif // COMMANDMANAGER_H
