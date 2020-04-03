#include "connectionprogresswindow.h"
#include "ui_connectionprogresswindow.h"

/**
 * @brief ConnectionProgressWindow::ConnectionProgressWindow
 * Basic constructor for a Form class that shows the state
 * of the initial server connection process
 *
 * @param parent
 */
ConnectionProgressWindow::ConnectionProgressWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionProgessWindow) {

    ui->setupUi(this);
}


/**
 * @brief ConnectionProgressWindow::~ConnectionProgressWindow
 * Basic destructor for the class
 */
ConnectionProgressWindow::~ConnectionProgressWindow() {
    delete ui;
}


/**
 * @brief ConnectionProgressWindow::updateConnectionStateUI
 * Called continuously during the initial Server connection process
 * and updates the UI based on the current state of the connection
 * process
 *
 * @param state - An enum representing progress in the connection process
 */
void ConnectionProgressWindow::updateConnectionStateUI(ConnectionProgress state) {
    switch (state) {
        case ConnectionProgress::StartState:
            ui->stepOneAction->setVisible(true);
            ui->stepTwoAction->setVisible(false);
            ui->stepThreeAction->setVisible(false);
            break;
        case ConnectionProgress::ConnectedToServer:
            ui->stepTwoAction->setVisible(true);
            ui->progressTextLabel->setText("Step 2: Authenticating Username and Password with Server");
            break;
        case ConnectionProgress::Authenticated:
            ui->stepThreeAction->setVisible(true);
            ui->progressTextLabel->setText("Step 3: Connected! Initializing Chat Window");
            break;
    }
}


