#ifndef ELYSIUM_NOTIFICATIONMANAGER_H
#define ELYSIUM_NOTIFICATIONMANAGER_H

#include <QSystemTrayIcon>
#include <QListWidget>

class ChatWindow;
class NotificationManager {

    public:
        NotificationManager(ChatWindow * cw);
        void detectUserMention(const QString& msg);
        void detectFriendOnline(int usersOnline, int t, QListWidget* list);

    private:
        ChatWindow * chatWindow;
        QSystemTrayIcon * systemTrayIcon;
        QIcon * projectIcon;

    void fireUserMentionNotification(const QString& msg, const QString& sendingUser);
    void userOnlineNotification(QString userName);
};
#endif //ELYSIUM_NOTIFICATIONMANAGER_H
