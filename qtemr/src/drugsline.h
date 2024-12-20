// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef DRUGSLINE_H
#define DRUGSLINE_H

#include <QAction>
#include <QMouseEvent>
#include <QObject>
#include <QSettings>

#include "genericlineedit.h"

class drugsLine : public genericLineEdit {
  Q_OBJECT
 public:
  explicit drugsLine(QWidget *parent = nullptr);
 private slots:
  void loadCompleter();

 private:
  QAction *favAction;
  bool favouriteDrugs;

 protected:
  void mousePressEvent(QMouseEvent *e);
};

#endif  // DRUGSLINE_H
