// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef PRINTDIALOGTAB_H
#define PRINTDIALOGTAB_H

#include <QObject>
#include <QWidget>
//#include "switch.h"

class printDialogTab : public QWidget
{
    Q_OBJECT
public:
    explicit printDialogTab(QWidget *parent = nullptr);

signals:
    void refresh();

public slots:
    void refreshView();
    void refreshView(int);
    void refreshView(const QString&);
};

#endif // PRINTDIALOGTAB_H
