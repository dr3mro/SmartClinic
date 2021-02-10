// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mcashtableview.h"

mCashTableView::mCashTableView(QWidget *parent):QTableView (parent)
{
    viewport()->installEventFilter(this);
}

bool mCashTableView::eventFilter(QObject *o, QEvent *e)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *> (e);
    QKeyEvent *keyEvent = static_cast<QKeyEvent *> (e);

    QModelIndex cell =  indexAt(viewport()->mapFromGlobal(QCursor::pos()));

    bool isShift = keyEvent->modifiers().testFlag(Qt::KeyboardModifier::ShiftModifier);
    bool isCtrl = keyEvent->modifiers().testFlag(Qt::KeyboardModifier::ControlModifier);


    if ( o == this->viewport() && mouseEvent->type() == QEvent::MouseButtonRelease){
        if(isShift || isCtrl ){
            if(mouseEvent->button() == Qt::LeftButton && cell.isValid() )
                emit doCalculations();
        }else{
            emit clearSelection();
            emit doCalculations();
        }
    }

    return QTableView::eventFilter(o,e);
}
