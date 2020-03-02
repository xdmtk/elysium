#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    socket = new QTcpSocket();
    ui->setupUi(this);
    ui->friendsDisplay->setReadOnly(1);
    ui->outputDisplay->setReadOnly(1);
    ui->inputDisplay->setPlaceholderText("Type here");
    ui->friendsDisplay->setPlaceholderText("Friends list");

    ui->outputDisplay->setStyleSheet("background: rgb(80,80,80);"
                                     "color:white;");
    ui->inputDisplay->setStyleSheet("background: rgb(80,80,80);"
                                    "color:white;"
                                    "border: 1px solid black;");
    ui->friendsDisplay->setStyleSheet("background: rgb(80,80,80);"
                                      "color:white;");

    socket->connectToHost("elysium-project.net",6692);
    connect(socket, &QTcpSocket::readyRead,this,&ChatWindow::display);
}

ChatWindow::~ChatWindow(){
    delete ui;
}

void ChatWindow::on_inputDisplay_returnPressed(){
   QString hosts[5] = {"daniel","erick","sebastian","nick","josh"};
   QString userInput;
   ui->outputDisplay->append(hosts[2] + ": ");
   userInput = ui->inputDisplay->text();
   ui->inputDisplay->clear();
   ui->outputDisplay->insertPlainText(userInput);
   //std::string toServer = userInput.toStdString();
   //socket->write(toServer.c_str());
}

void ChatWindow::on_actionLight_mode_triggered(){
    ui->outputDisplay->setStyleSheet("background: white;"
                                     "color:black;");
    ui->inputDisplay->setStyleSheet("background: white;"
                                    "color:black;"
                                    "border: 1px solid black;");
    ui->friendsDisplay->setStyleSheet("background: white;"
                                      "color:black;");

}

void ChatWindow::on_actionDark_mode_triggered()
{
    ui->outputDisplay->setStyleSheet("background: rgb(80,80,80);"
                                     "color:white;");
    ui->inputDisplay->setStyleSheet("background: rgb(80,80,80);"
                                    "color:white;"
                                    "border: 1px solid black;");
    ui->friendsDisplay->setStyleSheet("background: rgb(80,80,80);"
                                      "color:white;");
}

void ChatWindow::display()
{
    std::string holder;
    QString qInput;
    holder = socket->readAll().toStdString();
    qInput = QString::fromUtf8(holder.c_str());
    ui->outputDisplay->append(qInput);
}
