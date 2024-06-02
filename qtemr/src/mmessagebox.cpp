// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mmessagebox.h"

mMessageBox::mMessageBox(QWidget *parent) : QMessageBox(parent) {
  mpFadeIn = new QPropertyAnimation(this, "windowOpacity");
  mpFadeIn->setDuration(350);
  mpFadeIn->setStartValue(0.0);
  mpFadeIn->setEndValue(1.0);
  mpFadeIn->setEasingCurve(QEasingCurve::OutSine);

  mpFadeOut = new QPropertyAnimation(this, "windowOpacity");
  mpFadeOut->setDuration(180);
  mpFadeOut->setStartValue(1.0);
  mpFadeOut->setEndValue(0.0);
  mpFadeOut->setEasingCurve(QEasingCurve::OutSine);

  connect(mpFadeOut, SIGNAL(finished()), this, SLOT(onFadeOutFinished()));
}

// void mMessageBox::toggleVisualEffects(bool b)
//{
//     enableVisualEffects = b;
// }

// bool mMessageBox::getVisualEffectStatus()
//{
//     return enableVisualEffects;
// }

int mMessageBox::exec() {
  if (enableVisualEffects)
    mpFadeIn->start();
  else
    setWindowOpacity(1.00);
  return QMessageBox::exec();
}

mMessageBox::~mMessageBox() {
  delete mpFadeIn;
  delete mpFadeOut;
}

void mMessageBox::done(int result) {
  mResult = result;
  if (!enableVisualEffects)
    QMessageBox::done(mResult);
  else
    mpFadeOut->start();
}

void mMessageBox::show() {
  if (!enableVisualEffects) {
    QMessageBox::show();
    setWindowOpacity(1.00);
  } else {
    QMessageBox::show();
    mpFadeIn->start();
  }
}

void mMessageBox::onFadeOutFinished() { QMessageBox::done(mResult); }

void mMessageBox::closeEvent(QCloseEvent *e) {
  if (enableVisualEffects) {
    mpFadeOut->start();
    e->ignore();
  }
}
