#include "loginwindow.h"
#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QTcpSocket>
#include <QDebug>
#include <QThread>
#include <iostream>
ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
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
}

ChatWindow::~ChatWindow(){
    delete ui;
}

void ChatWindow::setHostPortCombo(struct LoginWindow::hostPortCombo hp) {
    hostname = hp.hostname;
    port = hp.port;
    sock = new QTcpSocket();
    qDebug() << hostname << port;
    connect(sock, &QAbstractSocket::connected, [&] {
        qDebug() << "Connected";
        thread = QThread::create([&] {
            char buf[4096] = {'\0'};
            qDebug() << "Thread started";
            while(sock->waitForReadyRead()) {
                QString foo(sock->readAll());
                qDebug() << "Message: " << foo;
            }
            qDebug() << "Thread finished";
        });
        thread->start();

    } );
    connect(sock, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            [=](QAbstractSocket::SocketError socketError){qDebug() << sock->errorString();});
    sock->connectToHost(hostname, port);


}

void ChatWindow::on_inputDisplay_returnPressed(){
   QString hosts[5] = {"daniel","erick","sebastian","nick","josh"};
   QString userInput;
   ui->outputDisplay->append(hosts[2] + ": ");
   userInput = ui->inputDisplay->text();
   ui->inputDisplay->clear();
   ui->outputDisplay->insertPlainText(userInput);

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
