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
