#include "xlineedit.h"

xLineEdit::xLineEdit(QWidget *parent)
{
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeReadWrite(bool)));
}

void xLineEdit::makeReadWrite(bool rw)
{
    setReadOnly(!rw);
}
