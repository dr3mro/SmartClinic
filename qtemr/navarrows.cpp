// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "navarrows.h"

navArrows::navArrows(QWidget *parent):QToolButton(parent)
{
    connect(this,SIGNAL(leftButtonClicked()),parent->window(),SLOT(navButtonsLeftClicked()));
    connect(this,SIGNAL(rightButtonClicked()),parent->window(),SLOT(navButtonsRightClicked()));
    connect(this,SIGNAL(pressed()),parent->window(),SLOT(navButtonsLeftClicked()));
}

void navArrows::mousePressEvent(QMouseEvent *event)
{

    if ( event->button() == Qt::RightButton )
    {
        emit rightButtonClicked();
        return;
    }
    else if (event->button() == Qt::LeftButton )
    {
        emit leftButtonClicked();
        return;
    }
    QToolButton::mousePressEvent(event);
}
