#ifndef CHATGUI_H
#define CHATGUI_H

#include <QDialog>

namespace Ui {
class chatGui;
}

class ChatGui : public QDialog
{
    Q_OBJECT

public:
    explicit ChatGui(QWidget *parent = nullptr);
    ~ChatGui();

private slots:
    void on_inputDisplay_returnPressed();

private:
    Ui::chatGui *ui;

};

#endif // CHATGUI_H
