#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "chatwindow.h"
#include <QMessageBox>
/*
 * Constructor:
 * Constructs the object for use
 */
LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
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
