// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QObject>
#include <QWidget>

class clickableLabel : public QLabel {
  Q_OBJECT
 public:
  explicit clickableLabel(QWidget *parent = nullptr);

 signals:
  void rightClicked();
  void leftClicked();

 protected:
  void mousePressEvent(QMouseEvent *event);
  void leaveEvent(QEvent *event);
  void enterEvent(QEvent *event);
};

#endif  // CLICKABLELABEL_H
