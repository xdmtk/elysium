//
// Created by xdmtk on 2/7/20.
//

#ifndef ELYSIUM_SERVER_CORESETTINGS_H
#define ELYSIUM_SERVER_CORESETTINGS_H


#include "../server/Server.h"

class CoreSettings {
public:

    CoreSettings(Server *s);

    enum ConfigEnvironment {
        DanielDev, ErickDev, JoshDev, NickDev, SebastianDev, Production
    };
    enum Protocol {
        NoOperation,
        ServerBroadcastMessage,
        ClientNormalMessage
    };

    std::string getHostName();
    int getPortNumber();

private:
    Server * server;
    ConfigEnvironment env;

    void setConfigEnvironment();
};


#endif //ELYSIUM_SERVER_CORESETTINGS_H
