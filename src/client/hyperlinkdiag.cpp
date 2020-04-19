#include "hyperlinkdiag.h"
#include "ui_hyperlinkdiag.h"

hyperlinkDiag::hyperlinkDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hyperlinkDiag)
{
    ui->setupUi(this);
}

hyperlinkDiag::~hyperlinkDiag()
{
    delete ui;
}
