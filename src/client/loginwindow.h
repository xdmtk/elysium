#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class ChatWindow;
class CoreSettings;
class LoginWindow : public QDialog
{
    Q_OBJECT


public:
    explicit LoginWindow(QWidget *parent = nullptr);
    struct hostPortCombo {
        QString hostname;
        int port;
    };
    ~LoginWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginWindow *ui;
    ChatWindow *chatGui;
    CoreSettings * coreSettings;
    struct hostPortCombo demoConnectToServer();

};

#endif // LOGINWINDOW_H
