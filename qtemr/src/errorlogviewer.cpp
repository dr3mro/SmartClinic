// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "errorlogviewer.h"
#include "ui_errorlogviewer.h"

errorLogViewer::errorLogViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::errorLogViewer)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);
    vScrollBar = ui->plainTextEdit->verticalScrollBar();
    fsWatcher.addPath(logFile);
    connect(&fsWatcher,SIGNAL(fileChanged(QString)),this,SLOT(loadLog()));
    connect(&mail,SIGNAL(messageSent()),this,SLOT(messageSent()));
    connect(&mail,SIGNAL(messageFailed()),this,SLOT(messageFailed()));
    connect(&watcher, SIGNAL(finished()), this, SLOT(loadFromLogFile()));
    connect(&mail,&email::mDisconnected,this,&errorLogViewer::onDisconnect);
}

errorLogViewer::~errorLogViewer()
{
    delete ui;
}

void errorLogViewer::loadLog()
{
    if (pause)
        return;

    readLogFromDiskThread();
}

void errorLogViewer::on_delButton_clicked()
{
    dataIOhelper::saveFile("error.log",QByteArray());
    ui->plainTextEdit->clear();
}

void errorLogViewer::keyPressEvent(QKeyEvent *e)
{
    if ( e->key() == Qt::Key_F12 || e->key() == Qt::Key_Escape )
        close();

    QWidget::keyPressEvent(e);
}

void errorLogViewer::showEvent(QShowEvent *event)
{
    readLogFromDiskThread();
    QWidget::showEvent(event);
}

void errorLogViewer::on_playPause_clicked()
{
    pause = !pause;
    QIcon icon;

    if(!pause)
    {
        icon = QIcon(":/ionicons/pause");
        ui->playPause->setToolTip("Pause");
    }
    else
    {
        icon = QIcon(":/ionicons/play");
        ui->playPause->setToolTip("Resume");
    }
    ui->refresh->setEnabled(pause);
    ui->playPause->setIcon(icon);
}

void errorLogViewer::on_refresh_clicked()
{
    readLogFromDiskThread();
}

void errorLogViewer::loadFromLogFile()
{
    QString log = future.result();

    int logLength = log.length();

    ui->plainTextEdit->setPlainText(log);

    vScrollBar->triggerAction(QScrollBar::SliderToMaximum);

    if (logLength != 0 && !sending)
    {
        ui->sendReport->setEnabled(true);
        ui->delButton->setEnabled(true);
    }
    else if (!sending )
    {
        ui->sendReport->setEnabled(false);
        ui->delButton->setEnabled(false);
    }
}

QString errorLogViewer::readLogFromDisk()
{
    return dataIOhelper::readFile("error.log");
}

void errorLogViewer::readLogFromDiskThread()
{
    if(future.isRunning())
        return;

    future = QtConcurrent::run(this,&errorLogViewer::readLogFromDisk);
    watcher.setFuture(future);
}

void errorLogViewer::onDisconnect()
{
    ui->status->setText("");
    ui->sendReport->setEnabled(true);
    if(this->isVisible())
        QMessageBox::information(this,"Message","Looks like you are offline!. check your internet connection");

}

void errorLogViewer::on_sendReport_clicked()
{
    sending = true;
    ui->sendReport->setEnabled(false);
    QString report = ui->plainTextEdit->toPlainText();

    report.insert(0,QString("Device ID  : %1 \n\nError log Contents:\n").arg(rApp.genDeviceID()));

    if (report.length() != 0)
    {
        ui->status->setText("Sending...");
        mail.sendEmail("Error",report);
    }
    else
    {
        ui->sendReport->setEnabled(true);
        QMessageBox::information(0,"Message","Nothing to send!",QMessageBox::Ok);
    }
}

void errorLogViewer::messageSent()
{
    QMessageBox::information(0,"Message","Message with complete log was sent to the developer, Thank you!",QMessageBox::Ok);
    ui->status->setText("");
    ui->sendReport->setEnabled(true);
    dataIOhelper::saveFile("error.log",QByteArray());
    ui->plainTextEdit->clear();
    sending = false;

}

void errorLogViewer::messageFailed()
{
    QMessageBox::information(0,"Message","Failed to send log to developer, Please retry later and check your internet connection!");
    ui->status->setText("");
    ui->sendReport->setEnabled(true);
    sending = false;
}