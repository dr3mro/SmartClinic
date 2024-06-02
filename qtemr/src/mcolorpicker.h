// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MCOLORPICKER_H
#define MCOLORPICKER_H

#include <QObject>
#include <QWidget>

#include "colorbutton.h"

class mColorPicker : public colorButton {
  Q_OBJECT
 public:
  explicit mColorPicker(QWidget *parent = nullptr);
};

#endif  // MCOLORPICKER_H
