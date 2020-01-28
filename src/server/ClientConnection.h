#ifndef ELYSIUM_SERVER_CLIENTCONNECTION_H
#define ELYSIUM_SERVER_CLIENTCONNECTION_H
#define C_BUFFER_SIZE 4096

class ClientConnection {
public:
    ClientConnection(int socketFd);
    void mainClientServerLoop();
private:
    int socketFileDescriptor, bufferSize;

    void setClientConnectionConfiguration();
};


#endif //ELYSIUM_SERVER_CLIENTCONNECTION_H
