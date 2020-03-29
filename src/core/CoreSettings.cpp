#include "CoreSettings.h"
#include "../server/Server.h"
#include "../client/loginwindow.h"

CoreSettings::CoreSettings(Server * s){
    server = s;
    setConfigEnvironment();
}

CoreSettings::CoreSettings(){
    setConfigEnvironment();
}

/**
 * To make vhost deployment easier, the server can use the username
 * running the process to determine its configuration environment.
 */
void CoreSettings::setConfigEnvironment() {

#ifdef __linux__
    // If we're running on the EC2 instance, get the username running the process
    std::string user = getenv("USER");
    if (user == "erick") env = ConfigEnvironment::ErickDev;
    else if (user == "josh") env = ConfigEnvironment::JoshDev;
    else if (user == "nick") env = ConfigEnvironment::NickDev;
    else if (user == "daniel") env = ConfigEnvironment::DanielDev;
    else if (user == "sebastian") env = ConfigEnvironment::SebastianDev;
    else env = ConfigEnvironment::Production;
    return;
#endif

    // If we are running the client locally, start out in production mode
    // and let the client manually change the env
    env = ConfigEnvironment::Production;
}


void CoreSettings::setConfigEnvironments(ConfigEnvironment e) {
    env = e;
}

/**
 * The client will need to call this when determining which endpoint to
 * connect to.
 *
 * @return - Returns the hostname to connect to
 */
std::string CoreSettings::getHostName() {

    std::string hostName;
    switch (env) {
        case ConfigEnvironment::DanielDev:
            hostName = "daniel."; break;
        case ConfigEnvironment::ErickDev:
            hostName = "erick."; break;
        case ConfigEnvironment::SebastianDev:
            hostName = "sebastian."; break;
        case ConfigEnvironment::NickDev:
            hostName = "nick."; break;
        case ConfigEnvironment::JoshDev:
            hostName = "josh."; break;
        case ConfigEnvironment::Production:
        default:
            hostName = ""; break;
    }

    return "https://" + hostName + "elysium-project.net";
}


std::string CoreSettings::getHostName2() {

    std::string hostName;
    switch (env) {
        case ConfigEnvironment::DanielDev:
            hostName = "daniel."; break;
        case ConfigEnvironment::ErickDev:
            hostName = "erick."; break;
        case ConfigEnvironment::SebastianDev:
            hostName = "sebastian."; break;
        case ConfigEnvironment::NickDev:
            hostName = "nick."; break;
        case ConfigEnvironment::JoshDev:
            hostName = "josh."; break;
        case ConfigEnvironment::Production:
        default:
            hostName = ""; break;
    }

    return hostName + "elysium-project.net";
}

/**
 * Arbitrary port numbers for each given Vhost and production environment
 *
 * @return
 */
int CoreSettings::getPortNumber() {

    int portNumber;
    switch (env) {
        case ConfigEnvironment::DanielDev:
            portNumber = 6883; break;
        case ConfigEnvironment::ErickDev:
            portNumber = 6884; break;
        case ConfigEnvironment::SebastianDev:
            portNumber = 6885; break;
        case ConfigEnvironment::NickDev:
            portNumber = 6886; break;
        case ConfigEnvironment::JoshDev:
            portNumber = 6887; break;
        case ConfigEnvironment::Production:
        default:
            portNumber = 6692; break;
    }
    return portNumber;
}

