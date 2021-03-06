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
        NoTyping,
        ServerRequestOnlineStatus,
        ClientReceiveOnlineStatus,
        ServerRequestAuthentication,
        ClientAcceptAuthentication,
        ClientRejectAuthentication,
        VerifyFriendStatus,
        AreFriends,
        AreNotFriends,
        AddFriend,
        RemoveFriend,
        RetrieveFriends,
        HaveList
    };
    std::string getHostName();

    int getPortNumber();
    void setConfigEnvironment(ConfigEnvironment e);




private:
    Server * server;
    ConfigEnvironment env;

    void setConfigEnvironment();
};


#endif //ELYSIUM_SERVER_CORESETTINGS_H
