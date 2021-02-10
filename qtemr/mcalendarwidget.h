// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MCALENDARWIDGET_H
#define MCALENDARWIDGET_H

#include <QObject>
#include <QCalendarWidget>
#include <QWidget>

class mCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit mCalendarWidget(QWidget *parent=nullptr);
};

#endif // MCALENDARWIDGET_H
