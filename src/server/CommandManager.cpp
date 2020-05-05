#include "CommandManager.h"
#include "ClientConnection.h"
#include "ConnectionManager.h"
#include "DatabaseManager.h"
#include "../core/CoreSettings.h"
#include "Logger.h"
#include <utility>
#include "Server.h"
#include <string.h>

CommandManager::CommandManager(Server *s, ClientConnection *c) {
    server = s;
    clientConnection = c;
    databaseManager = server->getDatabaseManager();
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
        case CoreSettings::Protocol::ServerRequestAuthentication:
            authenticateClient();
            Logger::info("Received ServerRequestAuthentication");
            break;
        case CoreSettings::Protocol::VerifyFriendStatus:
            verifyFriend();
            Logger::info("Received VerifyFriendStatus");
            break;
        case CoreSettings::Protocol::AddFriend:
          addFriend();
          Logger::info("Received VerifyFriendStatus");
          break;
        case CoreSettings::Protocol::RemoveFriend:
          removeFriend();
          Logger::info("Received VerifyFriendStatus");
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
std::string protocol;

  if(incomingMessage[0] != '~'){
    /* Pluck the first character of the message and use the byte value
     * to index into the CoreSettings::Protocol enumeration to determine
     * the intended effect of the message */
    auto messageProtocolIdentifier = static_cast<CoreSettings::Protocol>(incomingMessage[0]);
    /* Strip that character from the message */
    incomingMessage = incomingMessage.substr(1);
    return messageProtocolIdentifier;
    }
  else{
      /* Pluck the second and third characters of the message and use the byte value
       * to index into the CoreSettings::Protocol enumeration to determine
       * the intended effect of the message */
      protocol = incomingMessage.substr(1,2);
      auto messageProtocolIdentifier = static_cast<CoreSettings::Protocol>(std::stoi(protocol));
      /* Strip ~ and the characters from the message */
      incomingMessage = incomingMessage.substr(3);
      return messageProtocolIdentifier;
    }

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
    sendOnlineStatusList();
    announceEntranceOrExit(true);
}


/**
 * Broadcasts a "username has entered/left the chat" message to the chatroom
 * @param entering - Boolean determining whether the client is entering or exiting the chat
 */
void CommandManager::announceEntranceOrExit(bool entering) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    incomingMessage = CoreSettings::Protocol::ServerBroadcastMessage;
    incomingMessage.append("<b>" + clientConnection->getUsername() + " has " +
                                   (entering ? "entered" : "left") + " the chat</b>");
    server->broadcastMessage(incomingMessage);
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


/**
 * When NoTypingIndicator protocol is received this sends a message
 * via server to ConnectionManager which in turn uses broadcast
 * message to clients.
 */
void CommandManager::sendNoTypingIndicator() {
    Logger::info("Sending no type indicator");
    incomingMessage = CoreSettings::Protocol::NoTyping;
    incomingMessage.append(clientConnection->getUsername());
    server->broadcastMessage(incomingMessage);
}

/**
 * Sends to the client the ClientReceiveOnlineStatus procotol enum,
 * followed by a comma separated list of usernames of currently
 * connected clients
 */
void CommandManager::sendOnlineStatusList() {
    Logger::info("Sending online status list");
    incomingMessage = CoreSettings::Protocol::ClientReceiveOnlineStatus;
    incomingMessage.append(server->getConnectionManager()->getConnectedUserListCSV());
    server->broadcastMessage(incomingMessage);
}


/**
 * Called when the Client requests the server to authenticate an
 * incoming username/password combo.
 *
 * On success, a ClientAcceptAuthentication protocol indicator is
 * sent back to the Client.
 *
 * On failure, a ClientRejectAuthentication protocol indicator
 * is sent back to the Client and the connection is then terminated
 */
void CommandManager::authenticateClient() {

    bool authSuccess;
    std::string username, password;

    /* Split the user/pass by comma delimited */
    password = incomingMessage.substr(incomingMessage.find(",")+1);
    username = incomingMessage.substr(0, incomingMessage.find(","));

    /* Call on the Database manager to verify client credentials */
    if (databaseManager->authenticateClient(username, password)) {
        incomingMessage = CoreSettings::Protocol::ClientAcceptAuthentication;
        authSuccess = true;
    }
    else {
        incomingMessage = CoreSettings::Protocol::ClientRejectAuthentication;
        incomingMessage.append("," + databaseManager->getFailureReason());
        authSuccess = false;
    }

    /* Send back the correct Protocol indicator based on Authentication success
     * or failure */
    clientConnection->sendMessageToClient(incomingMessage);

    /* On failure, terminate the connection */
    if (!authSuccess) {
        clientConnection->terminateConnection();
    }
}


/**
 * Called when the Client requests the server to authenticate an
 * incoming username/password combo.
 *
 * On success, a ClientAcceptAuthentication protocol indicator is
 * sent back to the Client.
 *
 * On failure, a ClientRejectAuthentication protocol indicator
 * is sent back to the Client and the connection is then terminated
 */
void CommandManager::verifyFriend() {
    std::string username, friendUsername;

    /* Split the user/pass by comma delimited */
    username = incomingMessage.substr(incomingMessage.find(",")+1);
    friendUsername = incomingMessage.substr(0, incomingMessage.find(","));

    /* Call on the Database manager to verify client credentials */
    if (databaseManager->verifyFriend(username, friendUsername)) {
        incomingMessage = '~' + CoreSettings::Protocol::AreFriends;
    }
    else {
        incomingMessage = '~' + CoreSettings::Protocol::AreNotFriends;
    }

    /* Send back the correct Protocol indicator based on Authentication success
     * or failure */
    clientConnection->sendMessageToClient(incomingMessage);


}

void CommandManager::addFriend() {
  std::string username, friendUsername;

  /* Split the user/pass by comma delimited */
  username = incomingMessage.substr(incomingMessage.find(",")+1);
  friendUsername = incomingMessage.substr(0, incomingMessage.find(","));

  /* Call on the Database manager to verify client credentials */
  databaseManager->addFriend(username, friendUsername);
}

void CommandManager::removeFriend() {
  std::string username, friendUsername;

  /* Split the user/pass by comma delimited */
  username = incomingMessage.substr(incomingMessage.find(",")+1);
  friendUsername = incomingMessage.substr(0, incomingMessage.find(","));

  /* Call on the Database manager to verify client credentials */
  databaseManager->removeFriend(username, friendUsername);

}

