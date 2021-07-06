// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef ERRORLOGVIEWER_H
#define ERRORLOGVIEWER_H

#include <QWidget>
#include <QTimer>
#include <QByteArray>
#include <QKeyEvent>
#include <QtConcurrentRun>
#include <QFutureWatcher>
#include <QScrollBar>
#include <QIcon>
#include <QMessageBox>
#include <QFileSystemWatcher>
#include "dataiohelper.h"
#include "email.h"
#include "regapp.h"

namespace Ui {
class errorLogViewer;
}

class errorLogViewer : public QWidget
{
    Q_OBJECT

public:
    explicit errorLogViewer(QWidget *parent = nullptr);
    ~errorLogViewer();
private slots:
    void loadLog();
    void on_delButton_clicked();
    void on_playPause_clicked();
    void on_refresh_clicked();
    void on_sendReport_clicked();
    void messageSent();
    void messageFailed();
    void loadFromLogFile();
    QString readLogFromDisk();
    void readLogFromDiskThread();
    void onDisconnect();
private:
    Ui::errorLogViewer *ui;
    QScrollBar *vScrollBar;
    bool pause=false;
    email mail;
    bool sending = false;
    regApp rApp;
    QFutureWatcher<QString> watcher;
    QFuture<QString> future;
    QFileSystemWatcher fsWatcher;
    QString logFile="error.log";
protected:
    void keyPressEvent(QKeyEvent *e);
    void showEvent(QShowEvent *event);
};

#endif // ERRORLOGVIEWER_H
