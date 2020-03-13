#include "CommandManager.h"
#include "ClientConnection.h"
#include "Logger.h"
#include <utility>
#include "Server.h"

CommandManager::CommandManager(Server *s, ClientConnection *c) {
    server = s;
    clientConnection = c;
}


/**
 * This function should handle all incoming messages from the client and
 * determine the correct response to send back.
 */
void CommandManager::handleMessageAndResponse(std::string msg) {

    /* Store the incoming client message to class member variable */
    incomingMessage = std::move(msg);

    /* Analyze the message to determine the correct server response */
    CoreSettings::Protocol response = determineServerResponse();

    /* Use this switch to form and send the correct server response */
    switch (response) {
        case CoreSettings::Protocol::ServerBroadcastMessage:
            Logger::info("Received ServerBroadcastMessage protocol indicator");
            sendNormalMessageToAllClients();
            break;
        case CoreSettings::Protocol::ServerSetUsername:
            Logger::info("Received ServerSetUsername protocol indicator");
            setClientUsername();
            break;
        case CoreSettings::Protocol::NoOperation:
            Logger::info("Received NoOperation protocol indicator");
            break;
        default:
            Logger::warn("Could not identify protocol indicator - Defaulting to Noop");
            break;
    }
}


/**
 *
 * Called to operate on the raw incoming message from the client. Analyzes
 * the first byte in the message, strips it from the message, and 
 * returns that byte casted into a Protocol enumeration 
 *
 */
CoreSettings::Protocol CommandManager::determineServerResponse() {

    /* Pluck the first character of the message and use the byte value
     * to index into the CoreSettings::Protocol enumeration to determine
     * the intended effect of the message */
    auto messageProtocolIdentifier = static_cast<CoreSettings::Protocol>(incomingMessage[0]);

    /* Strip that character from the message */
    incomingMessage = incomingMessage.substr(1);

    return messageProtocolIdentifier;
}


/**
 * A response function called when the Protocol indicator is 
 * Protocol::ServerBroadcastMessage. 
 *
 * Prepends the username for this particular client and calls server->BroadcastMessage()
 * to send out a "Username: Message" style message to all connected clients 
 */
void CommandManager::sendNormalMessageToAllClients() {
    incomingMessage = clientConnection->getUsername() + ": " + incomingMessage;
    server->broadcastMessage(incomingMessage);
}


/**
 * A response function called when the Protocol indicator is 
 * Protocol::ServerSetUsername
 *
 * After the Protocol indicator has been stripped, the only string left in
 * incomingMessage is the username the client intends to set itself to. 
 *
 * Calls clientConnection->setUsername to modify the username class variable
 */
void CommandManager::setClientUsername() {
    Logger::info("Setting client username from " + clientConnection->getUsername() +
        " to " + incomingMessage);
    clientConnection->setUsername(incomingMessage);
}
