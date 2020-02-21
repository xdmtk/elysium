#ifndef CHATWINDOW_H
#define CHATWINDOW_H
#include <QMainWindow>
#include <QtDebug>
#include "socketmanager.h"

//class SocketManager;

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
  //  friend class SocketManager;
    ~ChatWindow();

private slots:
    void on_inputDisplay_returnPressed();
    void on_actionLight_mode_triggered();
    void on_actionDark_mode_triggered();
private:
    Ui::ChatWindow *ui;
    SocketManager socket;
};

#endif // CHATWINDOW_H
