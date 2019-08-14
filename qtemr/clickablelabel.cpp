#include "clickablelabel.h"

clickableLabel::clickableLabel(QWidget *parent):QLabel(parent)
{
    setToolTip("Left Click to Search selected site\n"
               "Right Click to Search google.com");
}

void clickableLabel::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton)
        emit leftClicked();
    if ( event->button() == Qt::RightButton)
        emit rightClicked();
    QLabel::mousePressEvent(event);
}

void clickableLabel::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    QFont font;
    font.setBold(true);
    font.setUnderline(false);
    setFont(font);
}

void clickableLabel::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    QFont font;
    font.setBold(true);
    font.setUnderline(true);
    setFont(font);
}
