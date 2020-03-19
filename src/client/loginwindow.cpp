#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "chatwindow.h"
#include <QMessageBox>
#include "../core/CoreSettings.h"
/*
 * Constructor:
 * Constructs the object for use
 */
LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->horizontalLayout_4;

    /* List of the strigns to be put into the server box drop down menu */
    QStringList Ports = {"Josh V-Host - - (josh.elysium-project.net", "Sebastian V-Host - - (sebastian.elysium-project.net)",
                         "Nick V-Host - - (nick.elysium-project.net)", "Erick V-Host - - (erick.elysium-project.net)",
                         "Daniel V-Host - - (daniel.elysium-project.net)", "Production Server - - (elysium-project.net)"};
    /* Add Qlist to the server boc and set the color and background of the box */
    ui->ServerBox->addItems(Ports);
    ui->ServerBox->setStyleSheet("background: rgb(80,80,80);"
                                     "color:white;");
}
/*
 * Destructor:
 * Delete the object
 */
LoginWindow::~LoginWindow(){
    delete ui;
}

/*<<<<<<< HEAD

=======*/
/*
 * Slot function:
 * When the enter button is pressed on the
 * LoginWindow GUI it checks that username
 * and password match and then will open
 * ChatWindow upon success
 */
/*>>>>>>> 3298ba63fdebfa08d4cd73de36330c254c8589d4*/
void LoginWindow::on_pushButton_clicked(){
    int serverIndex;

    /* Need to enter a username to initiate connection to server */
    if (ui->lineEdit_username->text().length()) {
        serverIndex = ui->ServerBox->currentIndex();

        /* Instantiate ChatWindow */
        chatGui = new ChatWindow(this);

        /* Sets username locally - Sends protocol msg to server to set username
         * remotely */
        chatGui->setUsername(ui->lineEdit_username->text());

        /* Show the Chatwindow */
        chatGui->show();

        /* Use hide() instead of close() to keep lifespan of instantiated objects */
        this->hide();
    }
    else {

        /* Append red border style sheet indicating error */
        ui->lineEdit_username->setStyleSheet(ui->lineEdit_username->styleSheet()
                                             + "border: 1px solid red;");

        /* Show a message box alerting user to set their username */
        QMessageBox alert;
        alert.setText("Please set a username!");
        alert.exec();
    }



}

/*returns the struct holdiong the port info*/
portInfo LoginWindow::getPortInfo(){
  return p;
}


/* This struct functions returns a struct that holds the port information that was chosen
   it will return both the port number and the*/
void LoginWindow::retrieveNewPort(int port) {
    CoreSettings::ConfigEnvironment env;

  /*Based on the index passed in when the button is clicked*/
    switch (port) {
        case 0:
            env = CoreSettings::ConfigEnvironment::JoshDev; break;
        case 1:
            env = CoreSettings::ConfigEnvironment::SebastianDev; break;
        case 2:
            env = CoreSettings::ConfigEnvironment::NickDev; break;
        case 3:
            env = CoreSettings::ConfigEnvironment::ErickDev; break;
        case 4:
            env = CoreSettings::ConfigEnvironment::DanielDev; break;
        case 5:
            env = CoreSettings::ConfigEnvironment::Production;
    }

    /*instense of core settings class to call nonstatic functions*/
    CoreSettings c;
    c.setConfigEnvironments(env);

    /*holds port that was chosen*/
    p.portNumber = c.getPortNumber();
    p.hostName = QString::fromStdString(c.getHostName());
}



