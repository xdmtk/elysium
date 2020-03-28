#ifndef CONNECTIONPROGESSWINDOW_H
#define CONNECTIONPROGESSWINDOW_H

#include <QDialog>

namespace Ui {
class ConnectionProgessWindow;
}

class ConnectionProgressWindow : public QDialog
{
    Q_OBJECT


public:
    enum ConnectionProgress {
        StartState, ConnectedToServer, Authenticated
    };

    explicit ConnectionProgressWindow(QWidget *parent = nullptr);
    ~ConnectionProgressWindow();
    void updateConnectionStateUI(ConnectionProgress state);

private:
    Ui::ConnectionProgessWindow *ui;
};

#endif // CONNECTIONPROGESSWINDOW_H
