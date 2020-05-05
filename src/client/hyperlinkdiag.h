#ifndef HYPERLINKDIAG_H
#define HYPERLINKDIAG_H

#include <QDialog>
class ChatWindow;
namespace Ui {
class hyperlinkDiag;
}

class hyperlinkDiag : public QDialog
{
    Q_OBJECT

public:
    explicit hyperlinkDiag(QWidget *parent = nullptr);
    QString sendLinkMsg();
    void setCw(ChatWindow * chat);
    ~hyperlinkDiag();
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
private:
    Ui::hyperlinkDiag *ui;
    QString linkText;
    QString link;
    ChatWindow * cw;
};

#endif // HYPERLINKDIAG_H
