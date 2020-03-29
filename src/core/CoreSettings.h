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

    /* This enumeration can contain a maximum of 256 possible 
     * flags/indicators to use in communicating special operations to/from
     * the server
     */
    enum Protocol {
        NoOperation,
        ServerBroadcastMessage,
        ClientNormalMessage,
        ServerSetUsername,
        TypingIndicator,
        NoTyping
    };
    std::string getHostName();
    std::string getHostName2();

    int getPortNumber();
    void setConfigEnvironments(ConfigEnvironment e);




private:
    Server * server;
    ConfigEnvironment env;

    void setConfigEnvironment();
};


#endif //ELYSIUM_SERVER_CORESETTINGS_H
