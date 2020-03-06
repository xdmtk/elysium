#ifndef ELYSIUM_SERVER_COMMANDMANAGER_H
#define ELYSIUM_SERVER_COMMANDMANAGER_H
#include "../core/CoreSettings.h"
#include <string>
#include <map>

class Server;
class CommandManager {
public:
    CommandManager(Server * s);
    void handleMessageAndResponse(std::string msg);

private:
    Server * server;
    std::string incomingMessage;
    CoreSettings::Protocol determineServerResponse();
    void sendNormalMessageToAllClients();

};


#endif //ELYSIUM_SERVER_COMMANDMANAGER_H
