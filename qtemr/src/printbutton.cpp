// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "printbutton.h"

printButton::printButton(QWidget *parent):QPushButton(parent)
{
    connect(this,SIGNAL(printDialog()),parent->window(),SLOT(showPrintDialog()));
    connect(this,SIGNAL(printPreview()),parent->window(),SLOT(showPrintPreviewDialog()));
    connect(this,SIGNAL(clicked()),parent->window(),SLOT(mPrint()));
}

void printButton::mousePressEvent(QMouseEvent *event)
{
    if ( event->modifiers() == Qt::SHIFT)
    {
        emit printDialog();
        return;
    }
    if ( event->modifiers() == Qt::CTRL)
    {
        emit printPreview();
        return;
    }
    QPushButton::mousePressEvent(event);
}
