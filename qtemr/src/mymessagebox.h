// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QCheckBox>
#include <QObject>

#include "dataiohelper.h"
#include "mmessagebox.h"
#include "msettings.h"

class myMessageBox : public mMessageBox {
  Q_OBJECT
 public:
  explicit myMessageBox(QWidget *parent = nullptr);
  mMessageBox *messagebox;
  int question(QWidget *parent, const QString &title, const QString &text,
               const StandardButton button0, const StandardButton button1,
               bool DefaultNo = false);
  int question(QWidget *parent, const QString &title, const QString &text,
               const StandardButton button0, const StandardButton button1,
               const StandardButton button2);
  int information(QWidget *parent, const QString &title, const QString &text);
 signals:

 public slots:
};

#endif  // MYMESSAGEBOX_H
