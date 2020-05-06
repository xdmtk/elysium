#include "linkaction.h"

void LinkAction::mouseReleaseEvent(QMouseEvent *){
    emit clicked(this);
}
