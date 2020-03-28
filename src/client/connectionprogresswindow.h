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
    explicit ConnectionProgressWindow(QWidget *parent = nullptr);
    ~ConnectionProgressWindow();

private:
    Ui::ConnectionProgessWindow *ui;
};

#endif // CONNECTIONPROGESSWINDOW_H
