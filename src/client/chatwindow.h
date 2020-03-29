#ifndef CHATWINDOW_H
#define CHATWINDOW_H
#include <QMainWindow>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QTimer>
#include "socketmanager.h"
#include "../core/CoreSettings.h"
#include <portInfo.h>


class CommandManager;
class NotificationManager;
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
    void setUsername(QString u);
    void display(QString msg);
    void setUsersTypingLabel(CoreSettings::Protocol indicator, std::string user);
    void setOnlineUserList(QStringList userlist);
    bool isConnected() {return socket->isConnectedToServer();}
    SocketManager * getSocketManager() {return socket;}
    NotificationManager * getNotificationManager() {return notificationManager;}

    ~ChatWindow();
private slots:
    void on_inputDisplay_returnPressed();
    void on_actionLight_mode_triggered();
    void on_actionDark_mode_triggered();
    void on_inputDisplay_cursorPositionChanged(int arg1, int arg2);
    void activateCommandManager();

private:
    Ui::ChatWindow *ui;
    SocketManager * socket;
    CommandManager * commandManager;
    NotificationManager * notificationManager;
    QString username;
    QVector<QString> usersTyping;
    QString updateUsersTyping(CoreSettings::Protocol,std::string);
    QString getUpdatedTypingPrompt(CoreSettings::Protocol, std::string);
    portInfo p;

};

#endif // CHATWINDOW_H
