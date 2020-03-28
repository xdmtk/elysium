#include "DatabaseManager.h"
#include <fstream>
#include <vector>

DatabaseManager::DatabaseManager(Server *s) {
    server = s;
}


bool DatabaseManager::authenticateClient(std::string username, std::string password) {


}

std::string DatabaseManager::getEnvironmentValue(std::string key) {
    std::string line;
    std::vector<std::string> lines;
    std::ifstream envLines (ENV_PATH);
    if (envLines.is_open()) {
        while ( getline (envLines, line) ) {
            lines.emplace_back(line);
        }
        envLines.close();
    }
    for (auto entry : lines) {
        if (entry.find(key) != -1) {
            return (entry.substr(entry.find("=")));
        }
    }
    return NULL;
}
