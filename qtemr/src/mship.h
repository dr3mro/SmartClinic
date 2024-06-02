// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MSHIP_H
#define MSHIP_H

#include <QObject>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

#include "email.h"
#include "internet.h"
#include "wm_mship.h"
class mShip : public QObject {
  Q_OBJECT
 public:
  explicit mShip(QObject *parent = nullptr);
  ~mShip();
 public slots:
  void run();

 signals:
  void showHelloPirate();

 private slots:
  void sendMail(QString subject, QString body);
  void work();

 private:
  QTimer *timer;
  internet *inet;
  email *mail;
  wm_mShip *worker;
};

#endif  // MSHIP_H
