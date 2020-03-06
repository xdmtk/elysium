#ifndef ELYSIUM_SERVER_CLIENTCONNECTION_H
#define ELYSIUM_SERVER_CLIENTCONNECTION_H

#define C_BUFFER_SIZE 4096

class Server;
class CommandManager;
class ClientConnection {
public:
    ClientConnection(int socketFd, Server *s);

    void sendMessageToClient(std::string msg);
    void mainClientServerLoop();
    void setUsername(std::string u);
    bool isAlive();
private:

    int socketFileDescriptor, bufferSize, alive;
    std::string username;

    Server * server;
    CommandManager * commandManager;

    void setClientConnectionConfiguration();
    void terminateConnection();

    void clearReceiveBuffer(char *buffer);
};


#endif //ELYSIUM_SERVER_CLIENTCONNECTION_H
