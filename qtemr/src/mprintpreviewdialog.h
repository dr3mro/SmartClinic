// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MPRINTPREVIEWDIALOG_H
#define MPRINTPREVIEWDIALOG_H

#include <QObject>
#include <QShortcut>
#include <QToolBar>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrinter>

#include "mdebug.h"

class mPrintPreviewDialog : public QPrintPreviewDialog {
  Q_OBJECT
 public:
  explicit mPrintPreviewDialog(QWidget *parent = nullptr);
  //    void setPageOrientation(const QPrinter::Orientation &_orientation);
  ~mPrintPreviewDialog();

 private:
  QShortcut *printShortcut;
  QAction *portrait;
  QAction *landscape;
};

#endif  // MPRINTPREVIEWDIALOG_H
