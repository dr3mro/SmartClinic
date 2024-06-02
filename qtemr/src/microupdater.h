// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MICROUPDATER_H
#define MICROUPDATER_H

#include <QMessageBox>
#include <QObject>
#include <QTime>
#include <QTimer>
#include <QVersionNumber>

#include "filegrabber.h"
#include "globalvariables.h"
#include "internet.h"
class microUpdater : public QObject {
  Q_OBJECT
 public:
  explicit microUpdater(QObject *parent = nullptr);
  bool isUpdateAvailable(QByteArray ba);
  ~microUpdater();

 signals:
  void isConnected();
  void isDisconnected();
  void viewDownloadedData(QByteArray);
  void launchMiniUpdater();
  void deleteMe();
 public slots:
  void connected();
  void disconnected();

 private slots:
  void notifyUser(QByteArray ba);

 private:
  void skipUpdate(QString version);
  internet *inet;
  QTimer *timer;
  fileGrabber *updateInfoGraber;
  QString latestVersion;
};

#endif  // MICROUPDATER_H
