// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "psspinbox.h"

psSpinBox::psSpinBox(QWidget *parent) : QSpinBox(parent) {
  connect(this, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged()));
  connect(this, SIGNAL(refreshView()), parent->window(), SLOT(refreshView()));
}

void psSpinBox::onValueChanged() {
  if (hasFocus()) emit refreshView();
}
