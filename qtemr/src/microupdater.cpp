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
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    QString ignoredVersion = reg.value("skip_update").toString();
    if (info.length() < 7 )
        return false;
    latestVersion = QString(info.at(0)).toUtf8();

    if ( latestVersion != ignoredVersion && QVersionNumber::fromString(latestVersion) > QVersionNumber::fromString(APPVERSION) )
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
        QMessageBox msgBox;

        msgBox.setText(QString("New Update is available to version: %1, Do you want to update now?")
                          .arg(latestVersion));

        QAbstractButton* pButtonYes    =  msgBox.addButton(tr("Yes"), QMessageBox::YesRole);
        QAbstractButton* pButtonNo     =  msgBox.addButton(tr("No"), QMessageBox::NoRole);
        QAbstractButton* pButtonIgnore =  msgBox.addButton(tr("Skip"),QMessageBox::RejectRole);

        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes)
           emit launchMiniUpdater();
        else if (msgBox.clickedButton()==pButtonNo)
            return;
        else if (msgBox.clickedButton()==pButtonIgnore)
            skipUpdate(latestVersion);
    }
    emit deleteMe();
}

void microUpdater::skipUpdate(QString version)
{
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    reg.setValue("skip_update",version);
}
