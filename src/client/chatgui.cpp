#include "chatgui.h"
#include "ui_chatgui.h"

ChatGui::ChatGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatGui)
{
    ui->setupUi(this);
    ui->friendsDisplay->setReadOnly(1);
    ui->outputDisplay->setReadOnly(1);
    ui->inputDisplay->setPlaceholderText("Type here");
    ui->friendsDisplay->setPlaceholderText("Friends list");
}
ChatGui::~ChatGui(){
    delete ui;
}
void ChatGui::on_inputDisplay_returnPressed(){

    QString userInput;
    userInput = ui->inputDisplay->text();
    ui->inputDisplay->clear();
    ui->outputDisplay->append(userInput);
}
