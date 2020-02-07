//
// Created by xdmtk on 2/7/20.
//

#ifndef ELYSIUM_SERVER_CORESETTINGS_H
#define ELYSIUM_SERVER_CORESETTINGS_H


class CoreSettings {
public:

    enum ConfigEnvironment {
        DanielDev, ErickDev, JoshDev, NickDev, SebastianDev, Production
    };

    CoreSettings();
    ConfigEnvironment getConfigEnvironment();

};


#endif //ELYSIUM_SERVER_CORESETTINGS_H
