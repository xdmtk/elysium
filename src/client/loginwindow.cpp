#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "chatwindow.h"
#include "connectionprogresswindow.h"
#include <QMessageBox>
#include <QRegExpValidator>
#include <QCryptographicHash>
#include <QThread>



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
    if (validateUsername() && validatePassword()) {

        /* Instantiate ChatWindow */
        chatGui = new ChatWindow(this);
        cpw = new ConnectionProgressWindow();
        this->hide();
        cpw->show();
        cpw->updateConnectionStateUI(ConnectionProgressWindow::ConnectionProgress::StartState);

        QTimer::singleShot(1000, [&]{

            /* On successful connection, initiate authentication request */
            if (chatGui->isConnected()) {
                cpw->updateConnectionStateUI(ConnectionProgressWindow::ConnectionProgress::ConnectedToServer);

                if (sendAuthenticationRequest()) {
                    cpw->updateConnectionStateUI(ConnectionProgressWindow::ConnectionProgress::Authenticated);
                    chatGui->getSocketManager()->setUsernameOnServer(ui->lineEdit_username->text().trimmed());
                    chatGui->setLocalUsername(ui->lineEdit_username->text().trimmed());

                    QTimer::singleShot(1000, [&] {
                        /* Show the Chatwindow */
                        chatGui->getSocketManager()->requestOnlineUserlist();
                        chatGui->show();
                        cpw->hide();
                    });
                }

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
    }
    else {

        /* Append red border style sheet indicating error */
        if (!validateUsername()) {
            ui->lineEdit_username->setStyleSheet(ui->lineEdit_username->styleSheet()
                                                 + "border: 1px solid red;");
        }
        if (!validatePassword()) {
            ui->lineEdit_password->setStyleSheet(ui->lineEdit_password->styleSheet()
                                                 + "border: 1px solid red;");
        }

        /* Show a message box alerting user to set their username */
        QMessageBox alert;
        alert.setText("Missing username and/or password!");
        alert.exec();
    }

}


bool LoginWindow::sendAuthenticationRequest() {
    QString passwordHash = QCryptographicHash::hash(ui->lineEdit_password->text().toUtf8(),
                                                    QCryptographicHash::Sha1).toHex();

    return true;
}


bool LoginWindow::validateUsername() {
    return ui->lineEdit_username->text().length();
}


bool LoginWindow::validatePassword() {
    return ui->lineEdit_password->text().length();
}

void LoginWindow::on_lineEdit_username_editingFinished() {
}
