#ifndef CHATGUI_H
#define CHATGUI_H

#include <QDialog>

namespace Ui {
class chatGui;
}

class chatGui : public QDialog
{
    Q_OBJECT

public:
    explicit chatGui(QWidget *parent = nullptr);
    ~chatGui();


private slots:
   // void on_inputDisplay_returnPressed();

    void on_inputDisplay_returnPressed();

private:
    Ui::chatGui *ui;
    bool enterPressed;

};

#endif // CHATGUI_H
