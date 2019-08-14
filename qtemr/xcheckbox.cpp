#include "xcheckbox.h"

xCheckBox::xCheckBox(QWidget *parent)
{
    connect (parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeEditable(bool)));
}

void xCheckBox::makeEditable(bool b)
{
    setEnabled(b);
}
