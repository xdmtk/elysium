#ifndef ELYSIUM_SERVER_CLIENTCONNECTION_H
#define ELYSIUM_SERVER_CLIENTCONNECTION_H

#define C_BUFFER_SIZE 4096

class Server;
class ClientConnection {
public:
    ClientConnection(int socketFd, Server *s);

    void relayMessage(std::string msg);
    void mainClientServerLoop();
    bool isAlive();
private:

    int socketFileDescriptor, bufferSize, alive;
    Server * server;

    void setClientConnectionConfiguration();
    void terminateConnection();

};


#endif //ELYSIUM_SERVER_CLIENTCONNECTION_H
