#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "../core/CoreSettings.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    coreSettings = new CoreSettings();
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


void LoginWindow::demoConnectToServer() {
    CoreSettings::ConfigEnvironment env;
    int currentIndex =ui->serverSelect->currentIndex();
    switch (currentIndex) {
        case 0:
            env = CoreSettings::ConfigEnvironment::Production; break;
        case 1:
            env = CoreSettings::ConfigEnvironment::NickDev; break;
        case 2:
            env = CoreSettings::ConfigEnvironment::SebastianDev; break;
        case 3:
            env = CoreSettings::ConfigEnvironment::JoshDev; break;
        case 4:
            env = CoreSettings::ConfigEnvironment::ErickDev; break;
        case 5:
            env = CoreSettings::ConfigEnvironment::DanielDev;
    }
    coreSettings->setConfigEnvironment(env);
    QString hostName = QString::fromStdString(coreSettings->getHostName());
    int port = coreSettings->getPortNumber();




}