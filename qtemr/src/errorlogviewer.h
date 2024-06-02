// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef ERRORLOGVIEWER_H
#define ERRORLOGVIEWER_H

#include <QByteArray>
#include <QFileSystemWatcher>
#include <QFutureWatcher>
#include <QIcon>
#include <QKeyEvent>
#include <QMessageBox>
#include <QScrollBar>
#include <QTimer>
#include <QWidget>
#include <QtConcurrent/QtConcurrentRun>

#include "dataiohelper.h"
#include "email.h"
#include "regapp.h"

namespace Ui {
class errorLogViewer;
}

class errorLogViewer : public QWidget {
  Q_OBJECT

 public:
  explicit errorLogViewer(QWidget *parent = nullptr);
  ~errorLogViewer();
 private slots:
  void loadLog();
  void onDelButton_clicked();
  void onPlayPause_clicked();
  void onRefresh_clicked();
  void onSendReport_clicked();
  void messageSent();
  void messageFailed();
  void loadFromLogFile();
  QString readLogFromDisk();
  void readLogFromDiskThread();
  void onDisconnect();

 private:
  Ui::errorLogViewer *ui;
  QScrollBar *vScrollBar;
  bool pause = false;
  email mail;
  bool sending = false;
  regApp rApp;
  QFutureWatcher<QString> watcher;
  QFuture<QString> future;
  QFileSystemWatcher fsWatcher;
  QString logFile = "error.log";

 protected:
  void keyPressEvent(QKeyEvent *e);
  void showEvent(QShowEvent *event);
};

#endif  // ERRORLOGVIEWER_H
