#include "connectionprogresswindow.h"
#include "ui_connectionprogresswindow.h"

ConnectionProgressWindow::ConnectionProgressWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionProgessWindow) {

    ui->setupUi(this);
}

ConnectionProgressWindow::~ConnectionProgressWindow() {
    delete ui;
}

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


