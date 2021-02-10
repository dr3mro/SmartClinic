// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "xdatetimeedit.h"

xDateTimeEdit::xDateTimeEdit(QWidget *parent)
{
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeReadWrite(bool)));
}

void xDateTimeEdit::makeReadWrite(bool rw)
{
    setReadOnly(!rw);
}
