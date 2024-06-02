// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "m_ClickableLabel.h"

m_ClickableLabel::m_ClickableLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f) {}

m_ClickableLabel::m_ClickableLabel(const QString &text, QWidget *parent,
                                   Qt::WindowFlags f)
    : QLabel(text, parent, f) {}

void m_ClickableLabel::setPhoneNumber(const QString &p) { phoneNumber = p; }

QString m_ClickableLabel::getPhoneNumber() { return phoneNumber; }

void m_ClickableLabel::mousePressEvent(QMouseEvent *event) {
  switch (event->button()) {
    case Qt::LeftButton:
      emit leftMouseButtonClicked();
      break;
    default:
      QLabel::mousePressEvent(event);
      break;
  }
}

void m_ClickableLabel::enterEvent(QEvent *event) {
  Q_UNUSED(event)
  emit setFontBold(true);
}

void m_ClickableLabel::leaveEvent(QEvent *event) {
  Q_UNUSED(event)
  emit setFontBold(false);
}
