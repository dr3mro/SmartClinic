// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "microupdater.h"

microUpdater::microUpdater(QObject *parent) : QObject(parent),
  inet(new internet(this)),
  timer(new QTimer(this)),
  updateInfoGraber(new fileGrabber(false,QUrl(updateInfo),this))
{
    timer->start(1000);

    connect(timer,SIGNAL(timeout()),inet,SLOT(checkOnline()));
    connect(inet,SIGNAL(connected()),this,SLOT(connected()));
    connect(inet,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(updateInfoGraber,SIGNAL(returnDownloadedData(QByteArray)),this,SLOT(notifyUser(QByteArray)));
}

bool microUpdater::isUpdateAvailable(QByteArray ba)
{
    QStringList info = QString(ba).split(";");
    if (info.length() < 7 )
        return false;
    latestVersion = QString(info.at(0)).toUtf8();
    if ( QVersionNumber::fromString(latestVersion) > QVersionNumber::fromString(APPVERSION) )
        return true;
    else
        return false;
}

microUpdater::~microUpdater()
{
    delete inet;
    delete timer;
    delete updateInfoGraber;
}

void microUpdater::connected()
{
    timer->stop();
    updateInfoGraber->run();
    emit isConnected();
}

void microUpdater::disconnected()
{
    //
}

void microUpdater::notifyUser(QByteArray ba)
{
    if (parent()->objectName() == "miniUpdater")
        emit viewDownloadedData(ba);

    if ( isUpdateAvailable(ba) && parent()->objectName() == "MainWindow")
    {
        int reply = QMessageBox::question(0,
                              "Update",
                              QString("New Update is available to version: %1, Do you want to update now?")
                              .arg(latestVersion)
                              ,QMessageBox::Yes,QMessageBox::No);
        if (reply == QMessageBox::Yes)
            emit launchMiniUpdater();
    }
    emit deleteMe();
}
