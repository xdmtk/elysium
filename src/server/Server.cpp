#include "../core/CoreSettings.h"
#include "ConnectionManager.h"
#include "DatabaseManager.h"
#include "Logger.h"
#include "SignalManager.h"

Server::Server(){

    Logger::info("Starting server");
    Logger::info("Latest build commit: " + Logger::getLatestBuildCommit());

    coreSettings = new CoreSettings(this);
    signalManager = new SignalManager(this);
    connectionManager = new ConnectionManager(this);
    databaseManager = new DatabaseManager(this);
}

void Server::start() {
    connectionManager->listenForClientConnections();
}


void Server::broadcastMessage(std::string msg) {
    connectionManager->broadcastMessageToClients(msg);
}

/**
 * Expose the SignalManager for the server
 * @return - Pointer to the SignalManager
 */
SignalManager * Server::getSignalManager() {
    return signalManager;
}

/**
 * Expose the ConnectionManager for the server
 * @return - Pointer to the ConnectionManager
 */
ConnectionManager * Server::getConnectionManager() {
    return connectionManager;
}


CoreSettings * Server::getCoreSettings() {
    return coreSettings;
}


DatabaseManager * Server::getDatabaseManager() {
    return databaseManager;
}
