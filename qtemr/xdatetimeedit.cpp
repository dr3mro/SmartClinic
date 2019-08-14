#include "xdatetimeedit.h"

xDateTimeEdit::xDateTimeEdit(QWidget *parent)
{
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeReadWrite(bool)));
}

void xDateTimeEdit::makeReadWrite(bool rw)
{
    setReadOnly(!rw);
}
