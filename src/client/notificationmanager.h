#ifndef ELYSIUM_NOTIFICATIONMANAGER_H
#define ELYSIUM_NOTIFICATIONMANAGER_H

#include <QSystemTrayIcon>

class ChatWindow;
class NotificationManager {

    public:
        NotificationManager(ChatWindow * cw);
        void detectUserMention(QString msg);

    private:
        ChatWindow * chatWindow;
        QSystemTrayIcon * systemTrayIcon;

};
#endif //ELYSIUM_NOTIFICATIONMANAGER_H
