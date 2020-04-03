#include "notificationmanager.h"
#include "chatwindow.h"


/**
 * Constructor the NotificationManager class. Sets the chatWindow pointer,
 * establishes a QIcon to use as the System Tray Icon, and displays the
 * System Tray Icon
 *
 * @param cw - Pointer to the ChatWindow instance
 */
NotificationManager::NotificationManager(ChatWindow *cw) {
    chatWindow = cw;
    projectIcon = new QIcon(":/icons/resources/keyboard-key-e.png");
    systemTrayIcon = new QSystemTrayIcon(*projectIcon);
    systemTrayIcon->show();
}


/**
 * Breaks an incoming message up into space delimited tokens, scans each
 * token for the '@' symbol at the beginning of the token, and checks whether
 * the username preceded by the '@' symbol is the username of the current user
 *
 * If it is, fireUserMentionNotification() is called to trigger a notification
 * on the System Tray Icon
 *
 * @param msg - Incoming chat message
 */
void NotificationManager::detectUserMention(const QString& msg) {
    QStringList tokens = msg.split(" ");
    QStringList u = tokens[0].split(":");
    QString sendingUser = u[0];
    qDebug()<<"Sending user: "<<sendingUser;
    for (auto token : tokens) {
        if (token.indexOf("@") != 0) continue;
        if (token.mid(1) == chatWindow->getUsername() || token.mid(1) == "here") {
            fireUserMentionNotification(msg, sendingUser);
        }
    }
}


/**
 * Simple wrapper call around QSystemTrayIcon's showMessage() function. Displays
 * the incoming chat message with a notification titled "User Mention"
 *
 * @param msg - Incoming chat message
 */
void NotificationManager::fireUserMentionNotification(const QString& msg, const QString & sendingUser) {
    if( sendingUser!= chatWindow->getUsername())
        systemTrayIcon->showMessage("User Mention", msg, *projectIcon, 3000);
}





