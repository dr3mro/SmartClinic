#ifndef MCOLORPICKER_H
#define MCOLORPICKER_H

#include <QObject>
#include <QWidget>
#include "colorbutton.h"

class mColorPicker : public colorButton
{
    Q_OBJECT
public:
    explicit mColorPicker(QWidget *parent=nullptr);
};

#endif // MCOLORPICKER_H
