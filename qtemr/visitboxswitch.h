#ifndef VISITBOXSWITCH_H
#define VISITBOXSWITCH_H

#include <QObject>
#include <QWidget>
#include "switch.h"


class visitBoxSwitch : public Switch
{
    Q_OBJECT
public:
    explicit visitBoxSwitch(QWidget *parent=nullptr);
public slots:
    void makeEditable(bool b);
};

#endif // VISITBOXSWITCH_H
