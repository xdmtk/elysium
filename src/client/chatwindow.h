#ifndef CHATWINDOW_H
#define CHATWINDOW_H
#include <QMainWindow>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QTimer>
#include "socketmanager.h"
#include "../core/CoreSettings.h"


class CommandManager;
namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);

    QString getUsername() {return username;}
    void setUsername(QString u);
    void display(QString msg);
    void setUsersTypingLabel(CoreSettings::Protocol indicator, std::string user);

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
    QString username;
    QVector<QString> usersTyping;
    QString getUpdatedTypingPrompt(CoreSettings::Protocol, std::string);


};

#endif // CHATWINDOW_H
