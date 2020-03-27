#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "chatwindow.h"
#include <QMessageBox>
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
void LoginWindow::on_pushButton_clicked(){

    /* Need to enter a username to initiate connection to server */
    if (validateUsername()) {

        /* Instantiate ChatWindow */
        chatGui = new ChatWindow(this);

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


bool LoginWindow::validateUsername() {
    return ui->lineEdit_username->text().length();
}

void LoginWindow::on_lineEdit_username_editingFinished() {
}
