// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mcolorpicker.h"

mColorPicker::mColorPicker(QWidget *parent):colorButton(parent)
{
    connect(this,SIGNAL(newColorSelected(const QColor&)),parent,SIGNAL(newColor(const QColor&)));
    connect(this,SIGNAL(clicked(bool)),parent,SLOT(hide()));
    connect(this,SIGNAL(clicked(bool)),this,SLOT(colorSelected()));
    colorPicker = true;
}
