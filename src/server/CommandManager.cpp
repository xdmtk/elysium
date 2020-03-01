#include "CommandManager.h"
#include "Server.h"

CommandManager::CommandManager(Server * s) {
    server = s;
}

void CommandManager::handleMessage(std::string msg) {
    server->broadcastMessage(msg);
}
