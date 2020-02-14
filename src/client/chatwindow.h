#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QTcpSocket>
#include "loginwindow.h"

namespace Ui {
class ChatWindow;
}
class LoginWindow;
class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    void setHostPortCombo(LoginWindow::hostPortCombo hp);
    ~ChatWindow();

private slots:
    void on_inputDisplay_returnPressed();
    void on_actionLight_mode_triggered();
    void on_actionDark_mode_triggered();
private:
    Ui::ChatWindow *ui;
    QString hostname;
    int port;
    QTcpSocket * sock;
    QThread * thread;
};

#endif // CHATWINDOW_H
