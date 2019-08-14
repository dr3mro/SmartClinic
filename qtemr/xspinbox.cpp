#include "xspinbox.h"

xSpinBox::xSpinBox(QWidget *parent)
{
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeReadWrite(bool)));
}

void xSpinBox::makeReadWrite(bool rw)
{
    setReadOnly(!rw);
}
