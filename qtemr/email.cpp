// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "email.h"

email::email(QObject *parent) : QObject(parent)//,
    //server(std::make_unique<SimpleMail::Server>())
{

}

void email::sendEmail(QString subject, QString messageText)
{
    //auto server = std::make_unique<SimpleMail::Server>();
    SimpleMail::Server *server = new SimpleMail::Server(this);
    connect(server,&SimpleMail::Server::itsOver,this,&email::messageFailed);
    server->setHost("smtp.gmail.com");
    server->setPort(465);
    server->setConnectionType(SimpleMail::Server::SslConnection);
    server->setUsername(selfEmail);
    server->setPassword("my1stlov");

    auto text(new SimpleMail::MimeText);
    SimpleMail::MimeMessage message;
    message.setSender(SimpleMail::EmailAddress(selfEmail, "Smart Clinic App"));
    message.addTo(SimpleMail::EmailAddress(QString("Dr. Amr Osman <%1>").arg(devEmail)));
    message.setSubject(subject);
    text->setText(messageText);
    message.addPart(text);

    SimpleMail::ServerReply *reply = server->sendMail(message);

    connect(reply, &SimpleMail::ServerReply::finished,reply,[=]{
        if ( !reply->error())
            emit messageSent();

        reply->deleteLater();
    });

}

