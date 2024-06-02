// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mcalendarwidget.h"

mCalendarWidget::mCalendarWidget(QWidget *parent) : QCalendarWidget(parent) {
  setFirstDayOfWeek(Qt::Saturday);
  setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
  setGridVisible(true);
}
