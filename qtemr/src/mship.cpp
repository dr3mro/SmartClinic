// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mship.h"

mShip::mShip(QObject *parent) : QObject(parent),
    timer(new QTimer(this)),
    inet (new internet(this)),
    mail (new email(this)),
    worker(new wm_mShip)
{
    connect(timer,SIGNAL(timeout()),inet,SLOT(checkOnline()));
    connect(inet,SIGNAL(connected()),this,SLOT(work()));
    connect(inet,SIGNAL(connected()),timer,SLOT(stop()));
    connect(worker,SIGNAL(showHelloPirate()),this,SIGNAL(showHelloPirate()));
    connect(worker,SIGNAL(sendMail(QString,QString)),this,SLOT(sendMail(QString,QString)));
    connect(mail,SIGNAL(messageSent()),worker,SLOT(activateMailSent()));
}

mShip::~mShip()
{
    delete worker;
    delete timer;
    delete inet;
    delete mail;
}

void mShip::run()
{
	timer->start(200);
}

void mShip::sendMail(QString subject, QString body)
{
    mail->sendEmail(subject,body);
}

void mShip::work()
{
#if QT_VERSION >= 0x060000
    auto f = QtConcurrent::run(&wm_mShip::work,worker);
#else
    auto f = QtConcurrent::run(worker,&wm_mShip::work);
#endif

}
