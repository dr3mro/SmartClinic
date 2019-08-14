#include "psspinbox.h"

psSpinBox::psSpinBox(QWidget *parent):QSpinBox(parent)
{
    connect(this,SIGNAL(valueChanged(int)),this,SLOT(onValueChanged()));
    connect(this,SIGNAL(refreshView()),parent->window(),SLOT(refreshView()));
}

void psSpinBox::onValueChanged()
{
    if(hasFocus())
        emit refreshView();
}
