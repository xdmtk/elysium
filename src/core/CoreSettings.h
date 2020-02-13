//
// Created by xdmtk on 2/7/20.
//

#ifndef ELYSIUM_SERVER_CORESETTINGS_H
#define ELYSIUM_SERVER_CORESETTINGS_H


#include "../server/Server.h"

class CoreSettings {
public:

    CoreSettings(Server *s);
    CoreSettings();

    enum ConfigEnvironment {
        DanielDev, ErickDev, JoshDev, NickDev, SebastianDev, Production
    };

    std::string getHostName();
    int getPortNumber();
    void setConfigEnvironment(ConfigEnvironment);

private:
    Server * server;
    ConfigEnvironment env;

    void setConfigEnvironment();
};


#endif //ELYSIUM_SERVER_CORESETTINGS_H
