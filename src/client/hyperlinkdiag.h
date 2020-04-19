#ifndef HYPERLINKDIAG_H
#define HYPERLINKDIAG_H

#include <QDialog>

namespace Ui {
class hyperlinkDiag;
}

class hyperlinkDiag : public QDialog
{
    Q_OBJECT

public:
    explicit hyperlinkDiag(QWidget *parent = nullptr);
    ~hyperlinkDiag();

private:
    Ui::hyperlinkDiag *ui;
};

#endif // HYPERLINKDIAG_H
