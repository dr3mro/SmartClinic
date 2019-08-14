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
};

#endif // PRINTDIALOGTAB_H
