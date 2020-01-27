#include "ClientConnection.h"

/**
 * This class should represent client connections. Each object should
 * contain identifying data for that client and it's relationship to the server.
 */

ClientConnection::ClientConnection(int socketFd) {
    socketFileDescriptor = socketFd;
}

/**
 * The main send/receive loop between the connected client and server
 */
void ClientConnection::mainClientServerLoop() {

}
