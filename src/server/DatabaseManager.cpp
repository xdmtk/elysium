#include "DatabaseManager.h"
#include "Logger.h"
#include <fstream>
#include <vector>

DatabaseManager::DatabaseManager(Server *s) {
    server = s;
    if (!verifyEnvironmentValues())  {
        Logger::fatal("Could not parse values from Environment file! Server cannot continue");
    }
}


bool DatabaseManager::authenticateClient(std::string username, std::string password) {


}

bool DatabaseManager::verifyEnvironmentValues() {
    return DB_HOST != "" &&
            DB_NAME != "" &&
            DB_TABLE != "" &&
            DB_USER != "" &&
            DB_PASS != "";
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
    for (const auto& entry : lines) {
        if (entry.find(key) != -1) {
            return (entry.substr(entry.find("=")+1));
        }
    }
    return "";
}
