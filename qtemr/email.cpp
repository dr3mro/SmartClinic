#include "email.h"

email::email(QObject *parent) : QObject(parent)
{
    smtp = new Smtp("smartclinic22@gmail.com","my1stlov","smtp.gmail.com",465);
    connect (smtp,SIGNAL(status(QString)),this,SLOT(mailSent(QString)));
}

void email::sendEmail(QString subject, QString body)
{
    smtp->sendMail(selfEmail,devEmail,subject,body);
}

email::~email()
{
    delete smtp;
}

void email::mailSent(QString status)
{
    if ( status == tr( "Message sent" ))
        emit messageSent();
    else if ( status == tr("Failed to send message"))
        emit messageFailed();
}

