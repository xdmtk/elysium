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
    std::string verifyUserScriptLocation = Logger::getDBScriptsDirectory() + "verify_user.php";
    std::string result_str = Logger::execShellCommand(("php " + verifyUserScriptLocation +
            " " + username + " " + password).c_str());
    Logger::debug(result_str);
    if (result_str.substr(0, result_str.find(",")) == "true") {
        return true;
    }
    setFailureReason(result_str.substr(result_str.find(",")+1));
    return false;
}


bool DatabaseManager::verifyEnvironmentValues() {
    return !DB_HOST.empty() &&
            !DB_NAME.empty() &&
            !DB_TABLE.empty() &&
            !DB_USER.empty() &&
            !DB_PASS.empty();
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
