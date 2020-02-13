#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow(){
    delete ui;
}

void LoginWindow::on_pushButton_clicked(){
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username == "test" && password == "test"){
        chatGui = new ChatWindow(this);
        this->close();
        chatGui->show();
    }
    else{
        QMessageBox::warning(this,"pushButton_login","Username and password is not correct");
    }
}
