#include "mlabelmsg.h"

mLabelMsg::mLabelMsg (QWidget *parent)
    : QLabel (parent), effect (new QGraphicsDropShadowEffect (this))
{

  effect->setColor (Qt::gray);
  effect->setBlurRadius(5);
  effect->setXOffset(2);
  effect->setYOffset(2);
  QString l = "<b>Please wait ...</b>";
  QFont f;
  f.setPointSize(16);
  setText(l);
  setFont(f);
  resize(250, 50);
  setAlignment(Qt::AlignCenter);
  setWindowModality(Qt::ApplicationModal);
  setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
  setWindowOpacity(0.8);
  setStyleSheet(
      QString("background-color: rgb(0, 0, 0);"
              "color: rgb(170, 255, 127);"));
}

mLabelMsg::~mLabelMsg () { delete effect; }

void mLabelMsg::show() {
  wm.centerOnScreen(this);
  setGraphicsEffect(effect);
  QWidget::show();
}

void
mLabelMsg::setMessage (QString msg)
{
  setText(msg);
  resize(msg.length() * 11, 50);
  setFocus (Qt::OtherFocusReason);
}
