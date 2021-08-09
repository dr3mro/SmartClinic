// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef WM_MSHIP_H
#define WM_MSHIP_H

#include <QObject>
#include <QSettings>
#include "globalvariables.h"
#include "filegrabber.h"
#include "regapp.h"
#include "msettings.h"

class wm_mShip : public QObject
{
    Q_OBJECT
public:
    explicit wm_mShip(QObject *parent = nullptr);
    ~wm_mShip();

signals:
    void finished();
    void showHelloPirate();
    void checkOnline();
    void connected();
    void sendMail(QString,QString);
public slots:
    void work();
    void start();
    void activateMailSent();
private slots:
    void downloadedWhiteList(QByteArray ba);
private:
    fileGrabber *whitelistgraber;
    regApp rApp;
    mSettings& settings=mSettings::instance();
    bool isWhiteListed(QByteArray ba);
    void blockDevice();
};

#endif // WM_MSHIP_H
