#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QDialog>
#include <QRegExpValidator>

class ChatWindow;
class ConnectionProgressWindow;

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
private slots:
    void on_pushButton_clicked();
    void on_lineEdit_username_editingFinished();

private:
    Ui::LoginWindow *ui;
    ChatWindow *chatGui;
    ConnectionProgressWindow *cpw;
    QRegExp * usernameRegex;
    QRegExpValidator * regex;
    bool validateUsername();
    bool validatePassword();
    bool sendAuthenticationRequest();
};

#endif // LOGINWINDOW_H
