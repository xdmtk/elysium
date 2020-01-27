#ifndef ELYSIUM_SERVER_CONNECTIONMANAGER_H
#define ELYSIUM_SERVER_CONNECTIONMANAGER_H

#include <vector>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
class Server;
class ClientConnection;
class ConnectionManager {
public:
   ConnectionManager(Server *);
   void listenForClientConnections();

private:
    Server * server;
    std::vector<std::pair<ClientConnection *, std::thread>> connectedClientList;
    int bindPort, connectionBacklogMaxLimit;

    void setupSocket(int *bindSocket, int *optionValue, struct sockaddr_in *address);
    void setAddressOptions(sockaddr_in *address);
    void bindAndListen(int *bindSocket, sockaddr_in *address);
    void setConnectionManagerConfiguration();
};

#endif //ELYSIUM_SERVER_CONNECTIONMANAGER_H
