#include "vprintbutton.h"

vPrintButton::vPrintButton(QWidget *parent):QPushButton(parent)
{

}

void vPrintButton::mousePressEvent(QMouseEvent *e)
{
    switch (e->button())
    {
    case Qt::LeftButton:
        emit leftButtonClicked();
        break;
    case Qt::MiddleButton:
        emit middleButtonClicked();
        break;
    case Qt::RightButton:
        emit rightButtonClicked();
        break;
    default:
        break;
    }
    QPushButton::mousePressEvent(e);
}
