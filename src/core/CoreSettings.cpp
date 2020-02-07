#include<fstream>

#include "CoreSettings.h"

CoreSettings::CoreSettings(){

}

CoreSettings::ConfigEnvironment CoreSettings::getConfigEnvironment(){

#ifdef __linux__
    // If we're running on the EC2 instance, get the username running the process
    std::string user = getenv("USER");
    if (user == "erick") return ConfigEnvironment::ErickDev;
    if (user == "josh") return ConfigEnvironment::JoshDev;
    if (user == "nick") return ConfigEnvironment::NickDev;
    if (user == "daniel") return ConfigEnvironment::DanielDev;
    if (user == "sebastian") return ConfigEnvironment::SebastianDev;
    if (user == "ubuntu") return ConfigEnvironment ::Production;
#endif




}