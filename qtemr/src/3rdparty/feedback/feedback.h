/*
  Copyright (c) 2011 - Tőkés Attila

  This file is part of SmtpClient for Qt.

  SmtpClient for Qt is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  SmtpClient for Qt is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY.

  See the LICENCE file for more details.
*/

#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QWidget>
#include <QSettings>

#include <QListWidget>
#include "3rdparty/simple-email/SimpleMail"
#include "globalvariables.h"

namespace Ui {
    class FeedBack;
}

namespace SimpleMail {
class Server;
}

using namespace SimpleMail;

class FeedBack : public QWidget
{
    Q_OBJECT

public:
    explicit FeedBack(QWidget *parent = nullptr);
    void clear();
    const bool & get_isBusy();
    ~FeedBack();

private Q_SLOTS:
    void on_addAttachment_clicked();
    void on_sendEmail_clicked();
    void sendMailAsync(const MimeMessage &msg);
    void on_attachments_itemClicked(QListWidgetItem *item);
    void on_deleteButton_clicked();

private:
    std::vector<Server *> m_aServers;
    Ui::FeedBack *ui;
    void errorMessage(const QString & message);
    bool isBusy=false;
};

#endif // FEEDBACK_H
