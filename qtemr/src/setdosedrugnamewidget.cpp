// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "setdosedrugnamewidget.h"

setDoseDrugNameWidget::setDoseDrugNameWidget(QWidget *parent)
    : QLabel(parent) {}

void setDoseDrugNameWidget::mousePressEvent(QMouseEvent *event) {
  switch (event->button()) {
    case Qt::LeftButton:
      emit leftMouseButtonClicked();
      break;
    case Qt::RightButton:
      emit rightMouseButtonClicked();
      break;
    default:
      QLabel::mousePressEvent(event);
      break;
  }
}
