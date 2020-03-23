#include "notificationmanager.h"
#include "chatwindow.h"

NotificationManager::NotificationManager(ChatWindow *cw) {
    chatWindow = cw;
    projectIcon = new QIcon(":/icons/resources/keyboard-key-e.png");
    systemTrayIcon = new QSystemTrayIcon(*projectIcon);
    systemTrayIcon->show();
}

void NotificationManager::detectUserMention(const QString& msg) {
    QStringList tokens = msg.split(" ");
    for (auto token : tokens) {
        if (token.indexOf("@") != 0) continue;
        if (token.mid(1) == chatWindow->getUsername()) {
            fireUserMentionNotification(msg);
        }
    }
}

void NotificationManager::fireUserMentionNotification(const QString& msg) {
    systemTrayIcon->showMessage("User Mention", msg, *projectIcon, 3000);
}





