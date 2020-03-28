#include "connectionprogresswindow.h"
#include "ui_connectionprogesswindow.h"

ConnectionProgressWindow::ConnectionProgressWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionProgessWindow)
{
    ui->setupUi(this);
}

ConnectionProgressWindow::~ConnectionProgressWindow()
{
    delete ui;
}
