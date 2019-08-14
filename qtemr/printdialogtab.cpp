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
