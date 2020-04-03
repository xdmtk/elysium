#ifndef ELYSIUM_NOTIFICATIONMANAGER_H
#define ELYSIUM_NOTIFICATIONMANAGER_H

#include <QSystemTrayIcon>

class ChatWindow;
class NotificationManager {

    public:
        NotificationManager(ChatWindow * cw);
        void detectUserMention(const QString& msg);

    private:
        ChatWindow * chatWindow;
        QSystemTrayIcon * systemTrayIcon;
        QIcon * projectIcon;

    void fireUserMentionNotification(const QString& msg, const QString& sendingUser);
};
#endif //ELYSIUM_NOTIFICATIONMANAGER_H
