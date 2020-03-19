#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QDialog>

class ChatWindow;

namespace Ui {
class LoginWindow;
}

struct portInfo {
        QString hostName;
        int portNumber;
    };

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    portInfo getPortInfo();


    ~LoginWindow();
private slots:
    void on_pushButton_clicked();
private:
    Ui::LoginWindow *ui;
    ChatWindow *chatGui;
    portInfo p;
    portInfo retrieveNewPort(int port);
};


#endif // LOGINWINDOW_H
