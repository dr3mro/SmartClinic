/*
  Copyright (c) 2011 - Tőkés Attila

  This file is part of SmtpClient for Qt.

  SmtpClient for Qt is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  SmtpClient for Qt is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY.

  See the LICENSE file for more details.
*/

#include "feedback.h"
#include "ui_feedback.h"

#include <QFileDialog>
#include <QErrorMessage>
#include <QMessageBox>

#include "..\simple-email\server.h"
#include "..\simple-email\serverreply.h"

using namespace SimpleMail;

FeedBack::FeedBack(QWidget *parent) : QWidget(parent)
  , ui(new Ui::FeedBack)
{
    ui->setupUi(this);
}

void FeedBack::clear()
{
    ui->attachments->clear();
    ui->subject->clear();
    ui->texteditor->clear();
    ui->attachments->addItem("error.log");
    ui->attachments->addItem("license.key");
    ui->attachments->addItem("settings.ini");
    ui->deleteButton->setEnabled(false);
    isBusy = false;
}

const bool &FeedBack::get_isBusy()
{
    return isBusy;
}

FeedBack::~FeedBack()
{
    delete ui;
}

void FeedBack::on_addAttachment_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec()) {
        ui->attachments->addItems(dialog.selectedFiles());
    }
}

void FeedBack::on_sendEmail_clicked()
{
    MimeMessage message;

    message.setSender(QString(selfEmail));
    message.setSubject(ui->subject->text());

    message.addTo(QString(devEmail));

    auto content = new MimeHtml;
    content->setHtml(ui->texteditor->toHtml());

    message.addPart(content);

    for (int i = 0; i < ui->attachments->count(); ++i) {
        message.addPart(new MimeAttachment(new QFile(ui->attachments->item(i)->text())));
    }
    sendMailAsync(message);
}

void FeedBack::sendMailAsync(const MimeMessage &msg)
{
    isBusy = true;
    const QString host = "smtp.gmail.com";
    const quint16 port(465);
    const Server::ConnectionType ct = SimpleMail::Server::SslConnection;

    Server *server = nullptr;
    for (auto srv : m_aServers) {
        if (srv->host() == host && srv->port() == port & srv->connectionType() == ct) {
            server = srv;
            break;
        }
    }

    if (!server) {
        server = new Server(this);
        server->setHost(host);
        server->setPort(port);
        server->setConnectionType(ct);
        m_aServers.push_back(server);
    }

    const QString user = selfEmail;
    if (!user.isEmpty()) {
        server->setAuthMethod(Server::AuthLogin);
        server->setUsername(user);
        server->setPassword(selfPass);
    }

    ServerReply *reply = server->sendMail(msg);
    connect(reply, &ServerReply::finished, this, [=] {
        //qDebug() << "ServerReply finished" << reply->error() << reply->responseText();
        reply->deleteLater();
        if (reply->error()) {
            errorMessage(QLatin1String("Mail sending failed:\n") + reply->responseText());
        } else {
            QMessageBox okMessage(this);
            okMessage.setText(QLatin1String("The email was succesfully sent:\n") + reply->responseText());
            okMessage.exec();
        }
        isBusy = false;
    });
    this->close();
}


void FeedBack::errorMessage(const QString &message)
{
    QErrorMessage err (this);

    err.showMessage(message);

    err.exec();
}

void FeedBack::on_attachments_itemClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    ui->deleteButton->setEnabled(true);
}


void FeedBack::on_deleteButton_clicked()
{
    if(ui->attachments->currentRow() != -1){
        ui->attachments->takeItem(ui->attachments->currentRow());
        ui->deleteButton->setEnabled(false);
    }
}

