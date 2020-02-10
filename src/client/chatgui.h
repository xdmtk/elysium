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

private:
    Ui::chatGui *ui;
};

#endif // CHATGUI_H
