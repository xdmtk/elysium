#ifndef ELYSIUM_SERVER_DATABASEMANAGER_H
#define ELYSIUM_SERVER_DATABASEMANAGER_H
#define ENV_PATH "/var/www/private.env"
#include <string>

class Server;
class DatabaseManager {

public:
    DatabaseManager(Server * s);
    bool authenticateClient(std::string username, std::string password);
private:

    Server * server;
    std::string getEnvironmentValue(std::string key);
    bool verifyEnvironmentValues();

    const std::string DB_HOST = getEnvironmentValue("DB_HOST");
    const std::string DB_NAME = getEnvironmentValue("DB_NAME");
    const std::string DB_TABLE = getEnvironmentValue("DB_TABLE");
    const std::string DB_USER = getEnvironmentValue("DB_USER");
    const std::string DB_PASS = getEnvironmentValue("DB_PASS");


};


#endif //ELYSIUM_SERVER_DATABASEMANAGER_H
