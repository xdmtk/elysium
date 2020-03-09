#ifndef ELYSIUM_SERVER_SERVER_H
#define ELYSIUM_SERVER_SERVER_H
#include <string>
class SignalManager;
class ConnectionManager;
class CoreSettings;
class Server {

public:
    Server();
    void start();
    void broadcastMessage(std::string);
    void sendTypingIndicator();
    SignalManager * getSignalManager();
    ConnectionManager * getConnectionManager();
    CoreSettings * getCoreSettings();

private:
    SignalManager * signalManager;
    ConnectionManager * connectionManager;
    CoreSettings * coreSettings;

};
#endif //ELYSIUM_SERVER_SERVER_H
