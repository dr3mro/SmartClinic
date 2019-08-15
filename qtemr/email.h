#ifndef EMAIL_H
#define EMAIL_H

#include <QObject>
#include "3rdparty/smtp/smtp.h"
#include "globalvariables.h"

class email : public QObject
{
    Q_OBJECT

public:
    explicit email(QObject *parent = nullptr);
    void sendEmail(QString subject , QString body );
    Smtp *smtp;
    ~email();

signals:
    void messageSent();
    void messageFailed();
public slots:
    void mailSent(QString status);
};

#endif // EMAIL_H
