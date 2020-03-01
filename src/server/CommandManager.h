#ifndef ELYSIUM_SERVER_COMMANDMANAGER_H
#define ELYSIUM_SERVER_COMMANDMANAGER_H
#include <string>

class Server;
class CommandManager {
public:
    CommandManager(Server * s);
    void handleMessage(std::string msg);

private:
    Server * server;
};


#endif //ELYSIUM_SERVER_COMMANDMANAGER_H
