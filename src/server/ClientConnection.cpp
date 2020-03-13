#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>

#include "CommandManager.h"
#include "ConnectionManager.h"
#include "ClientConnection.h"
#include "Logger.h"
#include "Server.h"
#include "SignalManager.h"

/**
 * This class should represent client connections. Each object should
 * contain identifying data for that client and it's relationship to the server.
 */

ClientConnection::ClientConnection(int socketFd, Server *s) {

    commandManager = new CommandManager(s, this);
    server = s;

    username = "Anonymous";
    alive = true;
    socketFileDescriptor = socketFd;
    setClientConnectionConfiguration();

}


// TODO: Make buffer size configurable
void ClientConnection::setClientConnectionConfiguration() {
}

/**
 * The main send/receive loop between the connected client and server
 */
void ClientConnection::mainClientServerLoop() {

    char buffer[C_BUFFER_SIZE] = {'\0'};

    /* For this condition, receive the message, make sure the socket is open, and make sure the message
     * isnt empty */
    while (recv(socketFileDescriptor, buffer, sizeof(buffer), 0) != -1
        && !server->getSignalManager()->trappedSignal(SIGPIPE) && strlen(buffer)) {

        Logger::info("Received message from client: " + std::string(buffer));

        /* Pass message to CommandManager for further action for client */
        commandManager->handleMessageAndResponse(buffer);

        /* Clear out the buffer */
        clearReceiveBuffer(buffer);
    }

    /* If the message comes back blank, or the socket is closed, or recv() returns an error,
     * we can safely kill the connection */
    terminateConnection();
}

/**
 * Called by the Server class to relay a message from another connected client
 * 'Overrides' to mainClientServerLoop in a way
 */
void ClientConnection::sendMessageToClient(std::string msg) {
    Logger::info("Sending message " + msg);
    send(socketFileDescriptor, msg.c_str(), msg.size(), 0);
}

/**
 * This function sets a flag on the thread to alert the ConnectionManager
 * to drop this object from the ConnectedClientList. No more messages will be
 * relayed to a client after calling this
 */
void ClientConnection::terminateConnection() {

    // Set alive flag, and tell the server to update its connection list
    Logger::warn("Thread is about to die");
    alive = false;
    server->getConnectionManager()->updateConnectionList();

    commandManager->sendOnlineStatusList();
}


bool ClientConnection::isAlive() {
    return alive;
}

/**
 * Clears out the receive buffer used for recv() calls
 * @param buffer
 */
void ClientConnection::clearReceiveBuffer(char * buffer) {
    for (int i = 0; i < C_BUFFER_SIZE; ++i) buffer[i] = '\0';
}

/**
 * Set function for class variable username
 * @param u
 */
void ClientConnection::setUsername(std::string u) {
    username = u;
}

std::string ClientConnection::getUsername() {
    return username;
}
