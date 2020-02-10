#include "chatgui.h"
#include "ui_chatgui.h"

chatGui::chatGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatGui)
{
    ui->setupUi(this);
    enterPressed = true;
    ui->friendsDisplay->setReadOnly(1);
    ui->outputDisplay->setReadOnly(1);
    ui->inputDisplay->setPlaceholderText("Type here");
    ui->friendsDisplay->setPlaceholderText("Friends list");
}
chatGui::~chatGui()
{
    delete ui;
}
void chatGui::on_inputDisplay_returnPressed()
{
        QString userInput;
        userInput = ui->inputDisplay->text();
        ui->inputDisplay->clear();
        ui->outputDisplay->append(userInput);

}
