#ifndef MICROUPDATER_H
#define MICROUPDATER_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QVersionNumber>
#include <QMessageBox>
#include "internet.h"
#include "globalvariables.h"
#include "filegrabber.h"
class microUpdater : public QObject
{
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
    internet *inet;
    QTimer *timer;
    fileGrabber *updateInfoGraber;
    QString latestVersion;

};

#endif // MICROUPDATER_H
