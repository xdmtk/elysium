#include "CommandManager.h"

#include <utility>
#include "Server.h"

CommandManager::CommandManager(Server * s) {
    server = s;
}


/**
 * This function should handle all incoming messages from the client and
 * determine the correct response to send back.
 */
void CommandManager::handleMessageAndResponse(std::string msg) {

    /* Store the incoming client message to class member variable */
    incomingMessage = std::move(msg);

    /* Analyze the message to determine the correct server response */
    ServerResponse response = determineServerResponse();

    /* Use this switch to form and send the correct server response */
    switch (response) {
        case ExampleResponse1:
        case ExampleResponse2:
        case BroadcastMessage:

            /* Defaults to basic repeater/relay behavior */
            sendNormalMessageToAllClients();
    }
}

CommandManager::ServerResponse CommandManager::determineServerResponse() {
    /*
     * Here ideally we'd have some logic to analyze a portion of the message
     * and determine whether the client is requesting some particular action
     * or response from the server.
     *
     * Also we would want to strip out whatever the indicator for the command
     * was from the message.
     *
     * But for now, since we haven't yet gotten client/server communication working
     * yet, this section of code will just continue to send out the incoming message
     * to all connected clients.
     */
    return BroadcastMessage;
}


void CommandManager::sendNormalMessageToAllClients() {
    server->broadcastMessage(incomingMessage);
}

