
#include "clickablelabel.h"

clickablelabel::clickablelabel(QWidget* parent)
    : QLabel(parent)
{
    setCursor(Qt::PointingHandCursor);
}

void clickablelabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }

    QLabel::mousePressEvent(event);
}
