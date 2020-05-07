#ifndef ELYSIUM_SERVER_COMMANDMANAGER_H
#define ELYSIUM_SERVER_COMMANDMANAGER_H
#include "../core/CoreSettings.h"
#include <string>
#include <map>

class Server;
class ClientConnection;
class DatabaseManager;
class CommandManager {
public:
    CommandManager(Server *s, ClientConnection *c);
    void handleMessageAndResponse(std::string msg);
    void sendOnlineStatusList();
    void announceEntranceOrExit(bool entering);

private:
    Server * server;
    ClientConnection * clientConnection;
    DatabaseManager * databaseManager;

    std::string incomingMessage;
    CoreSettings::Protocol determineServerResponse();
    void sendNormalMessageToAllClients();
    void sendTypingIndicator();
    void sendNoTypingIndicator();
    void setClientUsername();
    void authenticateClient();
    void verifyFriend();
    void addFriend();
    void removeFriend();
    void retrieveFriends();

};


#endif //ELYSIUM_SERVER_COMMANDMANAGER_H
