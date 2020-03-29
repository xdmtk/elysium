#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "chatwindow.h"
#include "commandmanager.h"
#include "connectionprogresswindow.h"
#include <csignal>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QCryptographicHash>
#include <QThread>
#include <QTime>



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


/**
 * @brief LoginWindow::on_pushButton_clicked
 *
 * Event handlers for the "Sign-on" button at the
 * Login Window. Initiates the connection process by
 * connecting to the server, authenticating the client,
 * and launching the ChatWindow
 */
void LoginWindow::on_pushButton_clicked(){

    /* Need to enter at least a username and password to
     * initiate connection to server */
    if (validateUsername() && validatePassword()) {

        /* Instantiate ChatWindow */
        chatGui = new ChatWindow(this);

        /* Instantiate ConnectionProgressWindow */
        cpw = new ConnectionProgressWindow();

        /* Hide the login window and show the connection progress window */
        this->hide();
        cpw->show();
        cpw->updateConnectionStateUI(ConnectionProgressWindow::ConnectionProgress::StartState);


        /* Wait a second before checking the server connection status to
         * be mindful of any potential network delays */
        QTimer::singleShot(1000, [&]{

            /* On successful connection, initiate authentication request */
            if (chatGui->isConnected()) {

                /* Update the Connection Progress Window to show authentication steps */
                cpw->updateConnectionStateUI(ConnectionProgressWindow::ConnectionProgress::ConnectedToServer);

                /* Fire authentication check */
                if (sendAuthenticationRequest()) {

                    /* If authentication checks out, set username supplied both locally
                     * and remotely */
                    cpw->updateConnectionStateUI(ConnectionProgressWindow::ConnectionProgress::Authenticated);
                    chatGui->getSocketManager()->setUsernameOnServer(ui->lineEdit_username->text().trimmed());
                    chatGui->setLocalUsername(ui->lineEdit_username->text().trimmed());

                    /* Again, delay the messages so they don't stack. Ask here in
                     * 1 second for the current online status of the chatroom users */
                    QTimer::singleShot(1000, [&] {
                        /* Show the Chatwindow */
                        chatGui->getSocketManager()->requestOnlineUserlist();
                        chatGui->show();
                        cpw->hide();
                    });
                }

                /* If the authentication failed, hide the Connection Progress Window
                 * but show the Login Window again */
                else {
                    cpw->hide();
                    this->show();
                }

            }
            /* If the connection failed, close the ChatWindow, clear out the username
             * field, and show a message box alerting the user of the connection failure */
            else {
                chatGui->close();
                ui->lineEdit_username->clear();
                this->show();
                cpw->hide();

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
        /* Append red border style sheet indicating error */
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

/**
 * @brief LoginWindow::sendAuthenticationRequest
 * This function hashes the supplied password and calls the SocketManager
 * directly to fire the Authentication request.
 *
 * After firing the request, it blocks (but while continuing to
 * process signals/slots) for 1 second, giving the server (hopefully)
 * enough time to validate the credentials and respond to the
 * client
 *
 * The client will pick up the response and set a flag in the
 * CommandManager, which this function will use to determine whether
 * there was an issue with the authentication
 *
 * @return - True on auth success, False on auth failure
 */
bool LoginWindow::sendAuthenticationRequest() {
    QEventLoop loop;
    QString passwordHash = QCryptographicHash::hash(ui->lineEdit_password->text().toUtf8(),
                                                    QCryptographicHash::Sha1).toHex();
    chatGui->getSocketManager()->sendAuthenticationRequest(
                ui->lineEdit_username->text(),
                passwordHash
                );

    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    if (chatGui->getCommandManager()->getAuthSuccess()) {
        return true;
    }
    else {
        QMessageBox alert;
        alert.setText("Authentication failed! Reason: " + chatGui->getCommandManager()
                      ->getAuthReply());
        alert.exec();
        return false;
    }
}


bool LoginWindow::validateUsername() {
    return ui->lineEdit_username->text().length();
}


bool LoginWindow::validatePassword() {
    return ui->lineEdit_password->text().length();
}

void LoginWindow::on_lineEdit_username_editingFinished() {
}
