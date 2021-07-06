// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef EMAIL_H
#define EMAIL_H

#include <QObject>
#include "3rdparty/simple-email/SimpleMail"
#include "globalvariables.h"
#include "memory"

class email : public QObject
{
    Q_OBJECT

public:
    explicit email(QObject *parent = nullptr);
    void sendEmail(QString subject , QString messageText );

signals:
    void messageSent();
    void messageFailed();
    void mDisconnected();
};

#endif // EMAIL_H
