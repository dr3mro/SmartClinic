// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MINIUPDATER_H
#define MINIUPDATER_H

#include <QCloseEvent>
#include <QDialog>
#include <QElapsedTimer>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QVersionNumber>

#include "build.h"
#include "datahelper.h"
#include "dataiohelper.h"
#include "filegrabber.h"
#include "globalvariables.h"
#include "microupdater.h"
#include "squeeze.h"

namespace Ui {
class miniUpdater;
}

class miniUpdater : public QDialog {
  Q_OBJECT

 public:
  explicit miniUpdater(QWidget *parent = nullptr, bool autoupdate = false);
  ~miniUpdater();
 private slots:
  void connected();
  void disconnected();
  void on_doButton_clicked();
  void viewDownloadedData(QByteArray ba);
  void downloadingFinished(double size);
  void downloadProgress(qint64 x, qint64 t);
  void on_closeButton_clicked();
  void connectionTimeOut();

  void on_restartButton_clicked();

 public slots:
  void verifyUpdate(QString path);

 private:
  Ui::miniUpdater *ui;
  QTimer *timeOut;
  QElapsedTimer clock;
  microUpdater *microupdater;
  fileGrabber *updateFileGraber;
  QString updateUrl, updateMD5, latestVersion, latestBuildNo, latestBuildDate,
      latestBuildTime, updateMessage;
  bool downloading = false;
  void displayVersionInfo();
  void applyUpdate();
  QString humanizeUpdateData(QByteArray ba);
  QString updatePath;
  void enableUpdating(bool b);
  void closeEvent(QCloseEvent *e);
  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
  bool autoUpdate = false;
  bool updateAvailable = false;
};

#endif  // MINIUPDATER_H
