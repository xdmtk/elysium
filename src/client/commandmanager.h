#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

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
};

#endif // COMMANDMANAGER_H
