#include "hyperlinkdiag.h"
#include "chatwindow.h"
#include "ui_hyperlinkdiag.h"
#include <QDebug>
hyperlinkDiag::hyperlinkDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hyperlinkDiag)
{
    ui->setupUi(this);
    /**
     Just a head's up, if you remove the http from any
     link, QTextbrowser acts funky and does not open
     external links..
     **/
    link="http://";
}
void hyperlinkDiag::on_okButton_clicked(){
    linkText = ui->linktext->text();
    link = link.append(ui->linkedit->text());
    cw->getSocketManager()->sendBasicChatMessage(sendLinkMsg());
}
void hyperlinkDiag::on_cancelButton_clicked(){
    ui->linkedit->clear();
    ui->linktext->clear();
    this->hide();
}
void hyperlinkDiag::setCw(ChatWindow * chat){
    cw = chat;
}
QString hyperlinkDiag:: sendLinkMsg(){
    QString msg = "<a href = \"" + link.trimmed() + "\">" + linkText.trimmed() + "</a>";
    return msg;
}
hyperlinkDiag::~hyperlinkDiag()
{
    delete ui;
}
