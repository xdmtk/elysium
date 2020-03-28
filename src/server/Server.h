#ifndef ELYSIUM_SERVER_SERVER_H
#define ELYSIUM_SERVER_SERVER_H
#include <string>
class SignalManager;
class ConnectionManager;
class CoreSettings;
class DatabaseManager;
class Server {

public:
    Server();
    void start();
    void broadcastMessage(std::string);
    SignalManager * getSignalManager();
    ConnectionManager * getConnectionManager();
    CoreSettings * getCoreSettings();
    DatabaseManager * getDatabaseManager();

private:
    SignalManager * signalManager;
    ConnectionManager * connectionManager;
    CoreSettings * coreSettings;
    DatabaseManager * databaseManager;

};
#endif //ELYSIUM_SERVER_SERVER_H
