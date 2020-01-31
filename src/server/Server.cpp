#include "ConnectionManager.h"
#include "Logger.h"
#include "Server.h"
#include "SignalManager.h"

Server::Server(){
    Logger::info("Starting server");
    signalManager = new SignalManager(this);
    connectionManager = new ConnectionManager(this);
}

void Server::start() {
    connectionManager->listenForClientConnections();
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
