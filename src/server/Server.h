#ifndef ELYSIUM_SERVER_SERVER_H
#define ELYSIUM_SERVER_SERVER_H

class SignalManager;
class ConnectionManager;
class Server {

public:
    Server();
    void start();
    SignalManager * getSignalManager();
    ConnectionManager * getConnectionManager();

private:
    SignalManager * signalManager;
    ConnectionManager * connectionManager;

};
#endif //ELYSIUM_SERVER_SERVER_H
