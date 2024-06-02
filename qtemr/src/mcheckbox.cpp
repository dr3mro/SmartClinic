// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mcheckbox.h"

mCheckBox::mCheckBox(QWidget *parent) : QCheckBox(parent) {
  connect(this, SIGNAL(sendCheckBoxName(QString)), parent->window(),
          SLOT(appendCheckBoxTextToPastHx(QString)));
  connect(parent->window(), SIGNAL(setReadWrite(bool)), this,
          SLOT(makeEditable(bool)));
  connect(this, SIGNAL(clicked(bool)), this, SLOT(sendCheckBoxName(bool)));
}
void mCheckBox::makeEditable(bool b) { setEnabled(b); }

void mCheckBox::sendCheckBoxName(bool) { emit sendCheckBoxName(text()); }
