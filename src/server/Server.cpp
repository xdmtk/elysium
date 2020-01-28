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

SignalManager * Server::getSignalManager() {
    return signalManager;
}
