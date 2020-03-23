#include "notificationmanager.h"

NotificationManager::NotificationManager(ChatWindow *cw) {
    chatWindow = cw;
    systemTrayIcon = new QSystemTrayIcon(QIcon(":/icons/resources/keyboard-key-e.png"));
    systemTrayIcon->show();
}

void NotificationManager::detectUserMention(QString msg) {



}





