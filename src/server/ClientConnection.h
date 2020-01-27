#ifndef ELYSIUM_SERVER_CLIENTCONNECTION_H
#define ELYSIUM_SERVER_CLIENTCONNECTION_H


class ClientConnection {
public:
    ClientConnection(int socketFd);
    void mainClientServerLoop();
private:
    int socketFileDescriptor;

};


#endif //ELYSIUM_SERVER_CLIENTCONNECTION_H
