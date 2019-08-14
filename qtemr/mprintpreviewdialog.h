#ifndef MPRINTPREVIEWDIALOG_H
#define MPRINTPREVIEWDIALOG_H

#include <QObject>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QToolBar>
#include <QShortcut>
#include "mdebug.h"


class mPrintPreviewDialog : public QPrintPreviewDialog
{
    Q_OBJECT
public:
    explicit mPrintPreviewDialog(QWidget *parent=nullptr);
    void setPageOrientation(QPrinter::Orientation _orientation);
    ~mPrintPreviewDialog();
private:
    QShortcut *printShortcut;
    QAction *portrait;
    QAction *landscape;
};

#endif // MPRINTPREVIEWDIALOG_H
