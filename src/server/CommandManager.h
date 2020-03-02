#ifndef ELYSIUM_SERVER_COMMANDMANAGER_H
#define ELYSIUM_SERVER_COMMANDMANAGER_H
#include <string>
#include <map>

class Server;
class CommandManager {
public:
    CommandManager(Server * s);
    void handleMessageAndResponse(std::string msg);
    enum ServerResponse {BroadcastMessage, ExampleResponse1, ExampleResponse2};

private:
    Server * server;
    std::string incomingMessage;
    ServerResponse determineServerResponse();
    void sendNormalMessageToAllClients();

};


#endif //ELYSIUM_SERVER_COMMANDMANAGER_H
