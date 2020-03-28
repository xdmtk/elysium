#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#include <QString>
class ChatWindow;
class SocketManager;
class SoundManager;
class CommandManager
{
public:
    CommandManager(ChatWindow * cw, SocketManager * socket, SoundManager * sm);

    void handleIncomingMessage();
    void updateSoundSettings(bool onOff);

private:
    ChatWindow * chatWindow;
    SocketManager * socket;
    SoundManager * soundManager;
    void addIncomingMessageToChat(QString msg);
    void updateOnlineUserlist(QString userlist);

};

#endif // COMMANDMANAGER_H
