// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MLABELMSG_H
#define MLABELMSG_H

#include <QObject>
#include <QLabel>
#include <QDesktopWidget>
#include <QString>
#include <QFont>
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include "windowmanager.h"

class mLabelMsg : public QLabel
{
    Q_OBJECT
public:
    explicit mLabelMsg(QWidget *parent=nullptr);
    ~mLabelMsg();
    void show();
    void setMessage(QString msg);
private:
    QDesktopWidget *desktop;
    QGraphicsDropShadowEffect *effect;
    WindowManager wm;
};

#endif // MLABELMSG_H
