#include <algorithm>
#include <cstring>
#include <cerrno>
#include <netinet/in.h>
#include <sys/socket.h>

#include "../core/CoreSettings.h"
#include "ConnectionManager.h"
#include "ClientConnection.h"
#include "Logger.h"

ConnectionManager::ConnectionManager(Server * s) {
    server = s;
    setConnectionManagerConfiguration();
}

/**
 * Set configuration options for the server.
 */
void ConnectionManager::setConnectionManagerConfiguration() {

    bindPort = server->getCoreSettings()->getPortNumber();
    connectionBacklogMaxLimit = 10;
};

/**
 * Master function to setup listener socket and accept incoming
 * client connections.
 */
void ConnectionManager::listenForClientConnections() {

    int bindSocket, incomingSocket, optionValue;
    struct sockaddr_in address;

    setupSocket(&bindSocket, &optionValue, &address);

    /* On new client connection, get the socket fd, and detatch a thread dedicated to communicating
     * with the client */
    while (incomingSocket = accept(bindSocket,NULL,NULL)) {

        Logger::info("Got new connection on socket fd: " + std::to_string(incomingSocket));

        // If accept() returns negative, errno is set. Print the error
        if (incomingSocket < 0) {
            Logger::error("Socket fd returned is negative! Errno:" + std::string(strerror(errno)));
            continue;
        }
        std::thread([&] {
            // Push the client onto the connectedClientList and begin send/receive loop
            connectedClientList.emplace_back(new ClientConnection(incomingSocket, server));
            connectedClientList.back()->mainClientServerLoop();
        }).detach();
    }
}

/**
 * Gets the socket file descriptor and calls setsockopt for
 * ipv4 options
 * @param bindSocket - Socket file descriptor
 * @param optionValue -
 */
void ConnectionManager::setupSocket(int *bindSocket, int *optionValue, struct sockaddr_in *address) {

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
    setAddressOptions(address);
    bindAndListen(bindSocket, address);
}

/**
 * Operates on the sockaddr_in structure to set IPV4 address binding
 * and allows the call to bind to utilize all potential IP address of the host
 *
 * @param address - Pointer to structure containing address/port data
 */
void ConnectionManager::setAddressOptions(struct sockaddr_in * address) {

    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(bindPort);
}

/**
 * Wrapper around bind() and listen() against the socket file descriptor
 *
 * @param bindSocket - Socket file descriptor
 * @param address - Address structure
 */
void ConnectionManager::bindAndListen(int * bindSocket, struct sockaddr_in * address) {

    if (bind(*bindSocket, reinterpret_cast<struct sockaddr *>(address), sizeof(*address)) < 0) {
        Logger::fatal("Could not bind to port " + std::to_string(address->sin_port) + "! "
                      + (errno ? "Errno: " + std::string(strerror(errno)) : ""));
    }
    if (listen(*bindSocket, connectionBacklogMaxLimit) < 0) {
        Logger::fatal("Call to listen() failed! " + (errno ? "Errno: " + std::string(strerror(errno)) : ""));
    }
    else  {
        Logger::info("Binding to port " + std::to_string(bindPort) + " has been successful. ");
    }

}

/**
 * Iterates through the current connection list and checks the `alive` flag
 * of each thread. Removes the ClientConnection if isAlive() fails
 */
void ConnectionManager::updateConnectionList() {
    auto it = connectedClientList.begin();
    while (it != connectedClientList.end()) {
        if (!(*it)->isAlive()) {
            it = connectedClientList.erase(it);
        }
        else {
            it++;
        }
    }
}

/**
 * ConnectionManager function called by the server when a thread
 * receive a message to relay to other threads
 * @param msg
 */
void ConnectionManager::broadcastMessageToClients(std::string msg) {

    // Iterate through the connected client list and send out the message
    for (auto client : connectedClientList)  {
        client->sendMessageToClient(msg);
    }
}

/**
 *  Eliminate all sockets current managed through the connectedClientList
 */
void ConnectionManager::killAllConnections() {
    connectedClientList.clear();
}

/**
 * Iterates the list of currently connected clients, retrieves
 * the username of each client and appends them to a comma
 * separated list
 *
 * @return string of comma separated usernames
 */
std::string ConnectionManager::getConnectedUserListCSV() {

    std::string clientListCSV;
    for (auto client : connectedClientList) {
        clientListCSV.append(client->getUsername() + ",");
    }

    /* Strip the last comma appended if there were usernames in the list */
    if (!clientListCSV.empty()) {
        clientListCSV.substr(0, clientListCSV.size() - 1);
    }

    return clientListCSV;
}
