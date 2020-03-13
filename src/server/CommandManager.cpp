#include "CommandManager.h"
#include "ClientConnection.h"
#include "ConnectionManager.h"
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
        case CoreSettings::Protocol::TypingIndicator:
            Logger::info("Received TypingIndicator protocol indicator");
            sendTypingIndicator();
            break;
        case CoreSettings::Protocol::NoTyping:
            Logger::info("Received NoTyping protocol indicator");
            sendNoTypingIndicator();
            break;
        case CoreSettings::Protocol::ServerRequestOnlineStatus:
            sendOnlineStatusList();
            Logger::info("Received ServerRequestOnlineStatus indicator");
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
    std::string msg = incomingMessage;
    incomingMessage = CoreSettings::Protocol::ServerBroadcastMessage;
    incomingMessage.append(clientConnection->getUsername() + ": " + msg);
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

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    sendOnlineStatusList();
}


/**
 * When TypingIndicator protocol is received this sends a message
 * via server to ConnectionManager which in turn uses broadcast
 * message to clients.
 */
void CommandManager::sendTypingIndicator(){
    incomingMessage = CoreSettings::Protocol::TypingIndicator;
    incomingMessage.append(clientConnection->getUsername());
    Logger::info("Sending typing indicator");
    server->broadcastMessage(incomingMessage);

}


void CommandManager::sendNoTypingIndicator() {
    Logger::info("Sending no type indicator");
    incomingMessage = CoreSettings::Protocol::NoTyping;
    incomingMessage.append(clientConnection->getUsername());
    server->broadcastMessage(incomingMessage);
}


void CommandManager::sendOnlineStatusList() {
    Logger::info("Sending online status list");
    incomingMessage = CoreSettings::Protocol::ClientReceiveOnlineStatus;
    incomingMessage.append(server->getConnectionManager()->getConnectedUserListCSV());
    server->broadcastMessage(incomingMessage);
}
