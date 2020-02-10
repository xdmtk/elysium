#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chatgui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_lineEdit_returnPressed();

    void on_Login_clicked();

private:
    Ui::MainWindow *ui;
    chatGui *Gui;
};
#endif // MAINWINDOW_H
