#include "DatabaseManager.h"
#include "Logger.h"
#include <fstream>
#include <vector>


/**
 * This class should handle all Database related operations.
 *
 * @param s - Pointer back to the Server
 */
DatabaseManager::DatabaseManager(Server *s) {
    server = s;

    if (!verifyEnvironmentValues())  {
        Logger::fatal("Could not parse values from Environment file! Server cannot continue");
    }
}


/**
 * Invokes the PHP interpreter against a quick PHP script to verify the
 * authentication status of the given username and password
 * @param username
 * @param password
 * @return
 */
bool DatabaseManager::authenticateClient(std::string username, std::string password) {

    std::string verifyUserScriptLocation = Logger::getDBScriptsDirectory() + "verify_user.php";
    std::string result_str = Logger::execShellCommand(("php " + verifyUserScriptLocation +
            " " + username + " " + password).c_str());


    if (result_str.substr(0, result_str.find(",")) == "true") {
        return true;
    }
    setFailureReason(result_str.substr(result_str.find(",")+1));
    return false;
}

/**
 * Invokes the PHP interpreter against a quick PHP script to verify the
 * authentication status of the given username and password
 * @param username
 * @param password
 * @return
 */
bool DatabaseManager::verifyFriend(std::string username, std::string friendUsername) {

    std::string verifyUserScriptLocation = Logger::getDBScriptsDirectory() + "verify_Friends.php";
    std::string result_str = Logger::execShellCommand(("php " + verifyUserScriptLocation +
            " " + username + " " + friendUsername).c_str());


    if (result_str == "true") {
        return true;
    }
    return false;
}

void DatabaseManager::addFriend(std::string username, std::string friendUsername) {

    std::string verifyUserScriptLocation = Logger::getDBScriptsDirectory() + "add_Friends.php";
    std::string result_str = Logger::execShellCommand(("php " + verifyUserScriptLocation +
            " " + username + " " + friendUsername).c_str());
}

void DatabaseManager::removeFriend(std::string username, std::string friendUsername) {

    std::string verifyUserScriptLocation = Logger::getDBScriptsDirectory() + "remove_Friend.php";
    std::string result_str = Logger::execShellCommand(("php " + verifyUserScriptLocation +
            " " + username + " " + friendUsername).c_str());
}


/**
 * Verifies the ENV values were parsed correctly
 * @return - True on successful parse, False when some credentials are missing
 */
bool DatabaseManager::verifyEnvironmentValues() {
    return !DB_HOST.empty() &&
            !DB_NAME.empty() &&
            !DB_TABLE.empty() &&
            !DB_USER.empty() &&
            !DB_PASS.empty();
}


/**
 * Quick function to pull the environment values from the given key
 * @param key - A key to get the associated value in the ENV file
 * @return - The value corresponding to the given key
 */
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
