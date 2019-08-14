#include "visitboxswitch.h"

visitBoxSwitch::visitBoxSwitch(QWidget *parent):Switch(parent)
{
    connect (parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeEditable(bool)));
}

void visitBoxSwitch::makeEditable(bool b)
{
    setEnabled(b);
}
