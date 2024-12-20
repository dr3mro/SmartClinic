// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "toast.h"

#include <QScreen>

toast::toast(QWidget *parent)
    : QLabel(parent), centerPos(0), horizontalPos(0), verticalPos(0) {
  setText("This is a notification");
  setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  setWindowModality(Qt::WindowModal);
  miTimer.setInterval(30);
  moTimer.setInterval(30);
  connect(&wait, SIGNAL(timeout()), &moTimer, SLOT(start()));
  connect(&moTimer, SIGNAL(timeout()), &wait, SLOT(stop()));
  connect(&miTimer, SIGNAL(timeout()), this, SLOT(moveToastin()));
  connect(&moTimer, SIGNAL(timeout()), this, SLOT(moveToastout()));
  setStyleSheet("background-color: lightgreen;border:1px solid grey;");
}

void toast::setCenterPos(int pos) {
  centerPos = pos;
  horizontalPos.store(centerPos);
}

void toast::setMessage(QString title, QString msg) {
  // verticalPos.store(0);
  setMessageType(title);
  setText(msg);
  wait.setInterval(msg.length() * 170);
  adjustSize();
  horizontalPos = centerPos - width() / 2;
  effect.play();
  // this to prevent close if message changed & adjust size if msg length
  // changed
  if (wait.isActive()) {
    wait.start();
    QRect scr = getScreenRect();
    move(horizontalPos + scr.left(), verticalPos + scr.top());
  } else if (moTimer.isActive()) {
    moTimer.stop();
    miTimer.start();
  }
}

void toast::setMessageType(QString title) {
  QString c;
  if (!QString::compare("Message", title, Qt::CaseInsensitive)) {
    c = "Aliceblue";
    effect.setSource(QUrl("qrc:/Audio/Notify"));
  } else if (!QString::compare("Done", title, Qt::CaseInsensitive)) {
    c = "lightgreen";
    effect.setSource(QUrl("qrc:/Audio/default"));
  } else if (!QString::compare("Error", title, Qt::CaseInsensitive)) {
    c = "tomato";
    effect.setSource(QUrl("qrc:/Audio/blocked"));
  } else if (!QString::compare("Warning", title, Qt::CaseInsensitive)) {
    c = "LemonChiffon";
    effect.setSource(QUrl("qrc:/Audio/cal"));
  } else if (!QString::compare("Information", title, Qt::CaseInsensitive)) {
    c = "GhostWhite";
    effect.setSource(QUrl("qrc:/Audio/info"));
  } else {
    c = "Orange";
    effect.setSource(QUrl("qrc:/Audio/print"));
  }
  setStyleSheet(QString("background-color:%1;border:1px solid grey;").arg(c));
}

void toast::moveToastin() {
  verticalPos++;
  QRect scr = getScreenRect();
  move(horizontalPos + scr.left(), verticalPos + scr.top());
  if (verticalPos > 0) {
    miTimer.stop();
    wait.start();
  }
}

void toast::moveToastout() {
  verticalPos--;
  QRect scr = getScreenRect();
  move(horizontalPos + scr.left(), verticalPos + scr.top());
  if (verticalPos < -height()) {
    moTimer.stop();
    QLabel::hide();
  }
}

void toast::moveCenter() {
  verticalPos = -height();
  QRect scr = getScreenRect();
  move(horizontalPos + scr.left(), verticalPos + scr.top());
}

QRect toast::getScreenRect() { return qApp->primaryScreen()->geometry(); }

void toast::mousePressEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton) moTimer.start();
  QLabel::mousePressEvent(e);
}

void toast::showEvent(QShowEvent *e) {
  moTimer.stop();
  wait.stop();
  moveCenter();
  QLabel::showEvent(e);
  effect.play();
  miTimer.start();
}
