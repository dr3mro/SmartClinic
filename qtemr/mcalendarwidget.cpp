#include "mcalendarwidget.h"

mCalendarWidget::mCalendarWidget(QWidget *parent):QCalendarWidget(parent)
{
    setFirstDayOfWeek(Qt::Saturday);
    setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    setGridVisible(true);

}
