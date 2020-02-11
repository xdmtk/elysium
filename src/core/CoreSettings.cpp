#include "CoreSettings.h"
#include "../server/Server.h"

CoreSettings::CoreSettings(Server * s){
    server = s;
    setConfigEnvironment();
}

void CoreSettings::setConfigEnvironment() {

#ifdef __linux__
    // If we're running on the EC2 instance, get the username running the process
    std::string user = getenv("USER");
    if (user == "erick") env = ConfigEnvironment::ErickDev;
    if (user == "josh") env = ConfigEnvironment::JoshDev;
    if (user == "nick") env = ConfigEnvironment::NickDev;
    if (user == "daniel") env = ConfigEnvironment::DanielDev;
    if (user == "sebastian") env = ConfigEnvironment::SebastianDev;
    if (user == "ubuntu") env = ConfigEnvironment::Production;
#endif
    env = ConfigEnvironment::Production;
}

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