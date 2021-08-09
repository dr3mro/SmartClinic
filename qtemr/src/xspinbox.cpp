// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "xspinbox.h"

xSpinBox::xSpinBox(QWidget *parent)
{
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeReadWrite(bool)));
}

void xSpinBox::makeReadWrite(bool rw)
{
    setReadOnly(!rw);
}
