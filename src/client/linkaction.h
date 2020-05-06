#ifndef LINKACTION_H
#define LINKACTION_H
#include <QWidget>
#include <QLabel>
#include "hyperlinkdiag.h"

class LinkAction: public QLabel{
    Q_OBJECT
public:
    LinkAction(QWidget *parent=0): QLabel(parent){};
signals:
    void clicked(LinkAction * click);
protected:
    void mouseReleaseEvent(QMouseEvent*);

};

#endif // LINKACTION_H
