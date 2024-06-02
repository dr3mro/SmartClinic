// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef XSPINBOX_H
#define XSPINBOX_H

#include <QObject>
#include <QSpinBox>

class xSpinBox : public QSpinBox {
  Q_OBJECT
 public:
  explicit xSpinBox(QWidget *parent = nullptr);
 public slots:
  void makeReadWrite(bool rw);
};

#endif  // XSPINBOX_H
