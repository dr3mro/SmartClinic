// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mprintpreviewdialog.h"

mPrintPreviewDialog::mPrintPreviewDialog(QWidget *parent):QPrintPreviewDialog(parent)
{
    QList<QToolBar *> toolbarlist = findChildren<QToolBar *>();
    QToolBar *toolbar =toolbarlist.at(0);
    QList<QAction*> actionsList = toolbar->actions();
    QAction *print = actionsList.at(21);
    portrait = actionsList.at(7);
    landscape = actionsList.at(8);

    print->setShortcut(QKeySequence("CTRL+P"));

    printShortcut = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_P),this);
    connect ( printShortcut,SIGNAL(activated()),parent,SLOT(mPrint()));
    connect ( printShortcut,SIGNAL(activated()),this,SLOT(close()));
    setMinimumSize(800,600);
}

void mPrintPreviewDialog::setPageOrientation(const QPrinter::Orientation &_orientation)
{
    printer()->setOrientation(_orientation);
    if(_orientation ==  QPrinter::Portrait)
        portrait->setChecked(true);
    else if (_orientation ==  QPrinter::Landscape)
        landscape->setChecked(true);
}

mPrintPreviewDialog::~mPrintPreviewDialog()
{
    delete printShortcut;
}
