// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef TOAST_H
#define TOAST_H

#include <QApplication>
#include <QLabel>
#include <QMouseEvent>
#include <QObject>
#include <QShowEvent>
#include <QSoundEffect>
#include <QTimer>
#include <QWidget>
#include <QWindow>
#include <atomic>

class toast : public QLabel {
  Q_OBJECT
 public:
  explicit toast(QWidget *parent = nullptr);
  void setCenterPos(int pos);
  void setMessage(QString title, QString msg);
  void setMessageType(QString title);

 private slots:
  void moveToastin();
  void moveToastout();

 private:
  void moveCenter();
  QRect getScreenRect();
  std::atomic_int centerPos;
  std::atomic_int horizontalPos;
  std::atomic_int verticalPos;
  QTimer miTimer;
  QTimer moTimer;
  QTimer fTimer;
  QTimer wait;
  QSoundEffect effect;

 protected:
  void mousePressEvent(QMouseEvent *e);
  void showEvent(QShowEvent *e);
};

#endif  // TOAST_H
