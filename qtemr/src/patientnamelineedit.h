// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef PATIENTNAMELINEEDIT_H
#define PATIENTNAMELINEEDIT_H

#include <QKeyEvent>
#include <QObject>

#include "mlineedit.h"
#include "wm_patientnamescompleterloader.h"

class patientNameLineEdit : public mLineEdit {
  Q_OBJECT
 public:
  explicit patientNameLineEdit(QWidget *parent = nullptr);
  ~patientNameLineEdit();
 private slots:
  void loadCompleter();
  void createCompleter();

 protected:
  void keyPressEvent(QKeyEvent *e);

 private:
  wm_patientnamesCompleterLoader *Worker;
};

#endif  // PATIENTNAMELINEEDIT_H
