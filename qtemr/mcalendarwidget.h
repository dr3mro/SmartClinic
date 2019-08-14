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
