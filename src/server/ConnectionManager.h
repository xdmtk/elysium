#ifndef ELYSIUM_SERVER_CONNECTIONMANAGER_H
#define ELYSIUM_SERVER_CONNECTIONMANAGER_H

#include <vector>
#include <thread>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
class Server;
class ClientConnection;
class ConnectionManager {
public:
    ConnectionManager(Server *);
    void listenForClientConnections();
    void updateConnectionList();
    void killAllConnections();
    void broadcastMessageToClients(std::string msg);
    std::string getConnectedUserListCSV();

private:
    Server * server;
    std::vector<ClientConnection *> connectedClientList;
    int bindPort, connectionBacklogMaxLimit;

    void setupSocket(int *bindSocket, int *optionValue, struct sockaddr_in *address);
    void setAddressOptions(sockaddr_in *address);
    void bindAndListen(int *bindSocket, sockaddr_in *address);
    void setConnectionManagerConfiguration();

};

#endif //ELYSIUM_SERVER_CONNECTIONMANAGER_H
