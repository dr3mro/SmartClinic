// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "printdialogtab.h"

printDialogTab::printDialogTab(QWidget *parent) : QWidget(parent)
{}

void printDialogTab::refreshView()
{
    //    Switch *sw = dynamic_cast<Switch*>(sender());
    //    if(sw->hasFocus())
    //
        emit refresh();
}

void printDialogTab::refreshView(int )
{
    emit refresh();
}

void printDialogTab::refreshView(const QString &)
{
    emit refresh();
}
