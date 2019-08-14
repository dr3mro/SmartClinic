#include "setdosedrugnamewidget.h"

setDoseDrugNameWidget::setDoseDrugNameWidget(QWidget *parent) : QLabel(parent)
{

}

void setDoseDrugNameWidget::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:
        emit leftMouseButtonClicked();
        break;
    case Qt::RightButton:
        emit rightMouseButtonClicked();
        break;
    default:
        QLabel::mousePressEvent(event);
        break;
    }
}
