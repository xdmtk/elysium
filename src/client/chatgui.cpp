#include "chatgui.h"
#include "ui_chatgui.h"

chatGui::chatGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatGui)
{
    ui->setupUi(this);
}

chatGui::~chatGui()
{
    delete ui;
}
