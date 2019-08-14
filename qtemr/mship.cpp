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
    QtConcurrent::run(worker,&wm_mShip::work);
}
