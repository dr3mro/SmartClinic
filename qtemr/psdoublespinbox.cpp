// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "psdoublespinbox.h"

psDoubleSpinBox::psDoubleSpinBox(QWidget *parent):QDoubleSpinBox(parent)
{   
    setMinimum(0.0);
    connect(this,SIGNAL(valueChanged(double)),this,SLOT(onValueChanged()));
    connect(this,SIGNAL(refreshView()),parent->window(),SLOT(refreshView()));
}

void psDoubleSpinBox::onValueChanged()
{
    if(hasFocus())
        emit refreshView();
}
