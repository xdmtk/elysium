#ifndef ELYSIUM_SERVER_COMMANDMANAGER_H
#define ELYSIUM_SERVER_COMMANDMANAGER_H
#include "../core/CoreSettings.h"
#include <string>
#include <map>

class Server;
class ClientConnection;
class CommandManager {
public:
    CommandManager(Server *s, ClientConnection *c);
    void handleMessageAndResponse(std::string msg);

private:
    Server * server;
    ClientConnection * clientConnection;
    std::string incomingMessage;
    CoreSettings::Protocol determineServerResponse();
    void sendNormalMessageToAllClients();

    void setClientUsername();
};


#endif //ELYSIUM_SERVER_COMMANDMANAGER_H
