#ifndef ELYSIUM_SERVER_CONNECTIONMANAGER_H
#define ELYSIUM_SERVER_CONNECTIONMANAGER_H

#include <vector>
#include <thread>

class Server;
class ClientConnection;
class ConnectionManager {
public:
   ConnectionManager(Server *);

private:
    Server * server;
    std::vector<ClientConnection *> connectedClientList;

    void listenForClientConnections();
};

#endif //ELYSIUM_SERVER_CONNECTIONMANAGER_H
