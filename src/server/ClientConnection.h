#ifndef ELYSIUM_SERVER_CLIENTCONNECTION_H
#define ELYSIUM_SERVER_CLIENTCONNECTION_H

#include "Server.h"

#define C_BUFFER_SIZE 4096

class ClientConnection {
public:
    ClientConnection(int socketFd, Server *s);
    void mainClientServerLoop();
    bool isAlive();
private:
    int socketFileDescriptor, bufferSize, alive;
    Server * server;

    void setClientConnectionConfiguration();

    void terminateConnection();
};


#endif //ELYSIUM_SERVER_CLIENTCONNECTION_H
