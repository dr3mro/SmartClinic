// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef PRINTBUTTON_H
#define PRINTBUTTON_H

#include <QMouseEvent>
#include <QObject>
#include <QPushButton>

class printButton : public QPushButton {
  Q_OBJECT
 public:
  explicit printButton(QWidget *parent);

 protected:
  void mousePressEvent(QMouseEvent *event);
 signals:
  void printDialog();
  void printPreview();
};

#endif  // PRINTBUTTON_H
