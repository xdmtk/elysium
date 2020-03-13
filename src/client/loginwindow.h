#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QDialog>
#include <QRegExpValidator>

class ChatWindow;

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
private:
    Ui::LoginWindow *ui;
    ChatWindow *chatGui;
    QRegExp * usernameRegex;
    QRegExpValidator * regex;
    bool validateUsername();

};

#endif // LOGINWINDOW_H
