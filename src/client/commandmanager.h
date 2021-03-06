#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#include <QString>
#include <QMainWindow>
#include "../core/CoreSettings.h"

class ChatWindow;
class SocketManager;
class SoundManager;
class CommandManager
{

public:

    void handleIncomingMessage();
    void authReplyReceivedAndSet();
    QString getAuthReply() {return authReply;};
    bool getAuthSuccess() {return authSuccess;};
    bool getAreFriends() {return areFriends;};
    QList<std::string> getFriendsList() {return friendsList;};
    void addFriend(std::string name);
    void removeFriend(std::string name);
    CommandManager(ChatWindow * cw, SocketManager * socket, SoundManager * sm);
    void updateSoundSettings(bool onOff);

private:
    ChatWindow * chatWindow;
    SocketManager * socket;
    QString authReply;
    QList<std::string> friendsList;
    bool authSuccess;
    bool areFriends;
    void addIncomingMessageToChat(QString msg);
    void updateOnlineUserlist(QString userlist);
    void setAuthReply(QString reply, bool val);
    void handleAuthReply(QString reply, CoreSettings::Protocol protocol);
    SoundManager * soundManager;
    void setAreFriends(bool val);
    void setFriendsList(std::string list);


};

#endif // COMMANDMANAGER_H
