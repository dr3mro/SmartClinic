// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "visitboxswitch.h"

visitBoxSwitch::visitBoxSwitch(QWidget *parent) : Switch(parent) {
  connect(parent->window(), SIGNAL(setReadWrite(bool)), this,
          SLOT(makeEditable(bool)));
}

void visitBoxSwitch::makeEditable(bool b) { setEnabled(b); }
