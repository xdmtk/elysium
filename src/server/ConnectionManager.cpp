#include "ConnectionManager.h"

ConnectionManager::ConnectionManager(Server * s) {
    server = s;
    listenForClientConnections();
}

void ConnectionManager::listenForClientConnections() {

}