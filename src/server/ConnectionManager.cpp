#include <cstring>
#include <cerrno>

#include <netinet/in.h>
#include <sys/socket.h>

#include "ConnectionManager.h"
#include "Logger.h"

ConnectionManager::ConnectionManager(Server * s) {
    server = s;
    setConnectionManagerConfiguration();
}

void ConnectionManager::setConnectionManagerConfiguration() {

    bindPort = 6692;
    connectionBacklogMaxLimit = 10;
};

void ConnectionManager::listenForClientConnections() {

    int bind_socket, option_value;
    struct sockaddr_in address;

    setupSocket(&bind_socket, &option_value);
    setAddressOptions(&address);
    bindAndListen(&bind_socket, &address);
}

void ConnectionManager::setupSocket(int * bindSocket, int * optionValue) {

    /* Produce a file descriptor for the listener socket */
    if ((*bindSocket = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
        Logger::fatal("Could not generate socket file descriptor! "
                      + (errno ? "Errno: " + std::string(strerror(errno)) : ""));
    }

    if (setsockopt(*bindSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &(*optionValue = 1), sizeof(*optionValue))) {
        Logger::fatal("Could not set socket options on socket! "
                      + (errno ? "Errno: " + std::string(strerror(errno)) : ""));

    }
}

void ConnectionManager::setAddressOptions(struct sockaddr_in * address) {

    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(bindPort);
}

void ConnectionManager::bindAndListen(int * bindSocket, struct sockaddr_in * address) {

    if (bind(*bindSocket, (struct sockaddr *)address, sizeof(*address)) < 0) {
        Logger::fatal("Could not bind to port " + std::to_string(address->sin_port) + "! "
                      + (errno ? "Errno: " + std::string(strerror(errno)) : ""));
    }
    if (listen(*bindSocket, connectionBacklogMaxLimit) < 0) {
        Logger::fatal("Call to listen() failed! " + (errno ? "Errno: " + std::string(strerror(errno)) : ""));
    }
}