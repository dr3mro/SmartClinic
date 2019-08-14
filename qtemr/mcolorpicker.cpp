#include "mcolorpicker.h"

mColorPicker::mColorPicker(QWidget *parent):colorButton(parent)
{
    connect(this,SIGNAL(newColorSelected(QColor)),parent,SIGNAL(newColor(QColor)));
    connect(this,SIGNAL(clicked(bool)),parent,SLOT(hide()));
    connect(this,SIGNAL(clicked(bool)),this,SLOT(colorSelected()));
    colorPicker = true;
}
