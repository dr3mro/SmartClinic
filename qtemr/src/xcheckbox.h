// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef XCHECKBOX_H
#define XCHECKBOX_H

#include <QCheckBox>
#include <QObject>

class xCheckBox : public QCheckBox {
  Q_OBJECT
 public:
  explicit xCheckBox(QWidget *parent = nullptr);
 public slots:
  void makeEditable(bool b);
};

#endif  // XCHECKBOX_H
