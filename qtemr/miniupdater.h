#ifndef MINIUPDATER_H
#define MINIUPDATER_H

#include <QDialog>
#include <QTimer>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QTime>
#include <QMessageBox>
#include <QVersionNumber>
#include "globalvariables.h"
#include "build.h"
#include "filegrabber.h"
#include "datahelper.h"
#include "dataiohelper.h"
#include "squeeze.h"
#include "microupdater.h"

namespace Ui {
class miniUpdater;
}

class miniUpdater : public QDialog
{
    Q_OBJECT

public:
    explicit miniUpdater(QWidget *parent = nullptr);
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

public slots:
    void verifyUpdate(QString path);
private:
    Ui::miniUpdater *ui;
    QTimer *timeOut;
    QTime clock;
    microUpdater *microupdater;
    fileGrabber *updateFileGraber;
    QString updateUrl,updateMD5,latestVersion,latestBuildNo,latestBuildDate,latestBuildTime,updateMessage;
    bool downloading=false;
    void displayVersionInfo();
    void applyUpdate();
    QString humanizeUpdateData(QByteArray ba);
    QString updatePath;
    void enableUpdating(bool b);
    void closeEvent(QCloseEvent *e);
    void keyPressEvent(QKeyEvent *e);

};

#endif // MINIUPDATER_H
