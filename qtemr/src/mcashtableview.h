// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MCASHTABLEVIEW_H
#define MCASHTABLEVIEW_H

#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QObject>
#include <QTableView>

class mCashTableView : public QTableView {
  Q_OBJECT
 public:
  explicit mCashTableView(QWidget *parent = nullptr);

 protected:
  bool eventFilter(QObject *o, QEvent *e);
 signals:
  void doCalculations();
};

#endif  // MCASHTABLEVIEW_H
