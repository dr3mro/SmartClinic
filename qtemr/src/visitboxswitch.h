// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef VISITBOXSWITCH_H
#define VISITBOXSWITCH_H

#include <QObject>
#include <QWidget>

#include "switch.h"

class visitBoxSwitch : public Switch {
  Q_OBJECT
 public:
  explicit visitBoxSwitch(QWidget *parent = nullptr);
 public slots:
  void makeEditable(bool b);
};

#endif  // VISITBOXSWITCH_H
