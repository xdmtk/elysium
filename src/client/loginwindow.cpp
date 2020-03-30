#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "chatwindow.h"
#include <QMessageBox>
#include "../core/CoreSettings.h"
#include <QRegExpValidator>

/*
 * Constructor:
 * Constructs the object for use
 */
LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
//    ui->horizontalLayout_4;

    /* List of the strigns to be put into the server box drop down menu */
    QStringList Ports = {"Production Server - - (elysium-project.net)", "Sebastian V-Host - - (sebastian.elysium-project.net)",
                         "Nick V-Host - - (nick.elysium-project.net)", "Erick V-Host - - (erick.elysium-project.net)",
                         "Daniel V-Host - - (daniel.elysium-project.net)", "Josh V-Host - - (josh.elysium-project.net"};

    /* Add Qlist to the server boc and set the color and background of the box */
    ui->ServerBox->addItems(Ports);
    ui->ServerBox->setStyleSheet("background: rgb(80,80,80);"
                                     "color:white;");

    this->setWindowIcon(QIcon(":/icons/resources/keyboard-key-e.png"));
    /* Only allow alphanumeric characters, dashes and underscores in the
     * username field */
    usernameRegex = new QRegExp("[A-Za-z0-9_-]+");
    regex = new QRegExpValidator(*usernameRegex);
    ui->lineEdit_username->setValidator(regex);
}


/*
 * Destructor:
 * Delete the object
 */
LoginWindow::~LoginWindow(){
    delete ui;
}


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
    if (validateUsername()) {
        serverIndex = ui->ServerBox->currentIndex();
        retrieveNewPort(serverIndex);
        qDebug()  << serverIndex;
        /* Instantiate ChatWindow */
        chatGui = new ChatWindow(p, this);

        /* Sets username locally - Sends protocol msg to server to set username
         * remotely */
        chatGui->setUsername(ui->lineEdit_username->text());
        
        /* Wait a second before retrieving the userlist (reason being the timing
         * of messages is still a bit wonky. TODO: May need to implement a message
         * delimiter) */
        QTimer::singleShot(1000, [&]{

            /* On successful connection, get the online userlist */
            if (chatGui->isConnected()) {
                chatGui->getSocketManager()->requestOnlineUserlist();
            }

            /* If the connection failed, close the ChatWindow, clear out the username
             * field, and show a message box alerting the user of the connection failure */
            else {
                chatGui->close();
                ui->lineEdit_username->clear();
                this->show();

                QMessageBox alert;
                alert.setText("Failed to connect to server!");
                alert.exec();
            }
        });

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


/* This struct functions returns a struct that holds the port information that was chosen
   it will return both the port number and the*/
void LoginWindow::retrieveNewPort(int port) {
    CoreSettings::ConfigEnvironment env;

  /*Based on the index passed in when the button is clicked*/
    switch (port) {
        case 0:
            env = CoreSettings::ConfigEnvironment::Production ;break;
        case 1:
            env = CoreSettings::ConfigEnvironment::SebastianDev; break;
        case 2:
            env = CoreSettings::ConfigEnvironment::NickDev; break;
        case 3:
            env = CoreSettings::ConfigEnvironment::ErickDev; break;
        case 4:
            env = CoreSettings::ConfigEnvironment::DanielDev; break;
        case 5:
           env = CoreSettings::ConfigEnvironment::JoshDev;
    }

    /*instense of core settings class to call nonstatic functions*/
    CoreSettings c;
    c.setConfigEnvironments(env);

    /*holds port that was chosen*/
    p.portNumber = c.getPortNumber();
    p.hostName = QString::fromStdString(c.getHostName2());
    qDebug() << p. portNumber << p.hostName;

}



bool LoginWindow::validateUsername() {
    return ui->lineEdit_username->text().length();
}

void LoginWindow::on_lineEdit_username_editingFinished() {
}
