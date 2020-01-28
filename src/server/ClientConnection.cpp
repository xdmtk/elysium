#include <netinet/in.h>
#include <sys/socket.h>

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
    alive = true;
    socketFileDescriptor = socketFd;
    server = s;
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

    // TODO: This is where the main conversation between client and server should happen
    // Need to implement functions to respond to client messages
    while (recv(socketFileDescriptor, buffer, sizeof(buffer), 0) != -1
        && !server->getSignalManager()->trappedSignal(SIGPIPE)) {       // TODO: Do not rely on SIGPIPE, or at the very least
                                                                        // figure out how to identify the offending thread at the signalmanager

        // Test code!
        send(socketFileDescriptor, "hi", sizeof("hi"), 0 );
    }
    terminateConnection();
}

void ClientConnection::terminateConnection() {

    // Set alive flag, and tell the server to update its connection list
    Logger::warn("Thread is about to die");
    alive = false;
    server->getConnectionManager()->updateConnectionList();
}

bool ClientConnection::isAlive() {
    return alive;
}
