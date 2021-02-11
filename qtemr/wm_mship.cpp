// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "wm_mship.h"

wm_mShip::wm_mShip(QObject *parent) : QObject(parent),
  whitelistgraber(new fileGrabber(false,QUrl(whiteListUrl),nullptr))
{
    connect(whitelistgraber,SIGNAL(returnDownloadedData(QByteArray)),this,SLOT(downloadedWhiteList(QByteArray)));
}

wm_mShip::~wm_mShip()
{
    emit finished();
    delete whitelistgraber;
}

void wm_mShip::work()
{
    whitelistgraber->run();
    if ( !rApp.compare_reg_data())
        return;

    if ( !settings.isDeviceActivated() && !rApp.check_eval_copy() )
    {
        emit sendMail("New Device Registered",QString("%1 %2").arg(rApp.genDeviceID()).arg(rApp.read_reg_data()));
    }
}

void wm_mShip::start()
{
    //mDebug() << "mShip Starting ... ";
}

void wm_mShip::activateMailSent()
{
    QSettings reg(blockregPath,QSettings::NativeFormat);
    reg.setValue(activateRegKey,true);
}

void wm_mShip::downloadedWhiteList(QByteArray ba)
{
    if (!isWhiteListed(ba) && !rApp.check_eval_copy())
    {
        blockDevice();
        emit showHelloPirate();
    }
    else
    {
        rApp.toggleBlock(false);
    }
}

bool wm_mShip::isWhiteListed(QByteArray ba)
{
    QString savedReg = rApp.read_reg_data();
    QString rawData = QString(ba);
    QStringList wList = rawData.simplified().split(" ");

    if (wList.at(0) != "smartClinicWhiteList")
    {
        return true;
    }

    if (savedReg == rApp.trialCrypted() || savedReg.isEmpty())
    {
        return true;
    }

    foreach(QString s,wList)
    {
        if( s == savedReg )
        {
            return  true;
        }
    }

    return false;
}

void wm_mShip::blockDevice()
{
    rApp.toggleBlock(true);
    emit sendMail("Block Message",QString("A new device ( %1 ) has been blocked").arg(rApp.genDeviceID()));
}
