#include "hyperlinkdiag.h"
#include "ui_hyperlinkdiag.h"
#include <QDebug>
hyperlinkDiag::hyperlinkDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hyperlinkDiag)
{
    ui->setupUi(this);
}
void hyperlinkDiag::on_okButton_clicked(){
    linkText = ui->linktext->text();
    link = ui->linkedit->text();
    qDebug()<<linkText;
}
void hyperlinkDiag::on_cancelButton_clicked(){
    ui->linkedit->clear();
    ui->linktext->clear();
    this->hide();
}
QString hyperlinkDiag:: sendLinkMsg(){
    QString msg = " <a href = \"" + link + "\">" + linkText + "</a>";
    return msg;
}
hyperlinkDiag::~hyperlinkDiag()
{
    delete ui;
}
