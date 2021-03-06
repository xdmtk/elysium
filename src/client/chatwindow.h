#ifndef CHATWINDOW_H
#define CHATWINDOW_H
#include <QMainWindow>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QTimer>
#include <QListWidgetItem>
#include "socketmanager.h"
#include "../core/CoreSettings.h"
#include "portInfo.h"
#include "hyperlinkdiag.h"
#include "ui_hyperlinkdiag.h"
class CommandManager;
class NotificationManager;
class SoundManager;
class profile;
namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ChatWindow(portInfo pass, QWidget *parent = nullptr);

    QString getUsername() {return username;}
    void setLocalUsername(QString u);
    void display(QString msg);
    void setUsersTypingLabel(CoreSettings::Protocol indicator, std::string user);
    void setOnlineUserList(QStringList userlist);
    bool isConnected() {return socket->isConnectedToServer();}

    SocketManager * getSocketManager() {return socket;}
    NotificationManager * getNotificationManager() {return notificationManager;}
    CommandManager * getCommandManager() {return commandManager;}
    SoundManager * getSoundManager() {return soundManager;}
    bool areFriends(QString userName);
    void grabFriendsList(QString userName);


    ~ChatWindow();

private slots:
    void on_inputDisplay_returnPressed();
    void on_actionLight_mode_triggered();
    void on_actionDark_mode_triggered();
    void on_inputDisplay_cursorPositionChanged(int arg1, int arg2);
    void on_actionSound_on_triggered();
    void on_actionSound_off_triggered();
    void activateCommandManager();
    void on_hyperLinkButton_clicked();
    void on_emojisButton_clicked();
    void on_emojiList_itemClicked(QListWidgetItem *item);
    void on_friendsDisplay_itemClicked(QListWidgetItem *item);
    void ShowContextMenu(const QPoint& pos);
    void on_FriendsList_itemClicked(QListWidgetItem *item);

    void on_profilePushButton_clicked();

    void on_actionOnline_triggered();

    void on_actionDon_t_Disturb_triggered();

private:
    Ui::ChatWindow *ui;
    hyperlinkDiag * hyperlink;
    SocketManager * socket;
    CommandManager * commandManager;
    NotificationManager * notificationManager;
    QString username;
    QVector<QString> usersTyping;
    QString getUpdatedTypingPrompt(CoreSettings::Protocol, std::string);

    portInfo p;
    SoundManager * soundManager;
    profile * profilegui;
    bool sound = true;
    bool dark = false;
    bool online = true;
    bool showProfile = false;
    bool showEmoji = false;
    bool hasSelect = false;
    int selectionLength = 0;
    int selectionStart = 0;
    int usersOnline = 0;
    int count = 0;
};

#endif // CHATWINDOW_H
