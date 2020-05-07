#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>

namespace Ui {
class profile;
}

class profile : public QWidget
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr);
    ~profile();
    void setUsername(QString username);
    void setDark(bool dark);
    void setSound(bool sound);
    void setStatus(bool online);
    void setNumberOfFriends(int num);

private slots:
    void on_exitPushButton_clicked();

private:
    Ui::profile *ui;
};

#endif // PROFILE_H
