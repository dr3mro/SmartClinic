// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef VPRINTBUTTON_H
#define VPRINTBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include "mdebug.h"

class vPrintButton : public QPushButton
{
    Q_OBJECT
public:
    explicit vPrintButton(QWidget *parent=nullptr);
protected:
    void mousePressEvent(QMouseEvent *e);
signals:
    void rightButtonClicked();
    void middleButtonClicked();
    void leftButtonClicked();

};

#endif // VPRINTBUTTON_H
