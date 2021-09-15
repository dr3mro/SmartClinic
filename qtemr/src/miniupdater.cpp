// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "miniupdater.h"
#include "ui_miniupdater.h"

miniUpdater::miniUpdater(QWidget *parent,bool _autoUpate) :
    QDialog(parent),
    ui(new Ui::miniUpdater),
    timeOut(new QTimer(this)),
    autoUpdate(_autoUpate)
{
      ui->setupUi(this);
      setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
      setFixedSize(400,450);
      displayVersionInfo();
      ui->progressBar->hide();
      ui->speed->hide();
      ui->restartButton->hide();
      ui->doButton->setHidden(autoUpdate);
      ui->textEdit->append("Checking update server ...");
      microupdater = new microUpdater(this);
      connect(microupdater,SIGNAL(isConnected()),this,SLOT(connected()));
      connect(microupdater,SIGNAL(viewDownloadedData(QByteArray)),this,SLOT(viewDownloadedData(QByteArray)));
}


miniUpdater::~miniUpdater()
{
    delete ui;
}

void miniUpdater::connected()
{
    ui->textEdit->append("<html><p style='color:green;'><b>Connected to update server.</b></p></html>");
}

void miniUpdater::disconnected()
{
    //ui->textEdit->append("<html><p style='color:red;'><color:red><b>Connection to update server Lost.</b></p></html>");
    //timer->start();
}

void miniUpdater::on_doButton_clicked()
{
    ui->doButton->setEnabled(false);
    ui->closeButton->setText("Abort");
    updateFileGraber = new fileGrabber(true,QUrl(updateUrl),this);
    downloading = true;
    connect( updateFileGraber,SIGNAL(downloadSaved(double)),this,SLOT(downloadingFinished(double)));
    connect( updateFileGraber,SIGNAL(finished()),updateFileGraber,SLOT(deleteLater()) );
    connect( updateFileGraber,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProgress(qint64,qint64)));
    connect( updateFileGraber,SIGNAL(verifyFile(QString)),this,SLOT(verifyUpdate(QString)) );
    connect( timeOut,SIGNAL(timeout()),this,SLOT(connectionTimeOut()));
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    ui->speed->show();
    clock.start();
    timeOut->start(15000);
    updateFileGraber->run();
    ui->textEdit->append("<html><p style='color:blue;'><b>Downloading Update, Please Wait!</b></p></html>");
}

void miniUpdater::viewDownloadedData(QByteArray ba)
{
    ui->textEdit->append(humanizeUpdateData(ba));
    enableUpdating(microupdater->isUpdateAvailable(ba));
}

void miniUpdater::downloadingFinished(double size)
{
    downloading = false;
    ui->textEdit->append(QString("<html><p style='color:blue;'><b>Download finished.(%1) MiB </b></p></html>").arg(double(size/1000000)));
    ui->progressBar->hide();
    ui->speed->hide();
}

void miniUpdater::downloadProgress(qint64 x, qint64 t)
{
    ui->progressBar->setValue(x);
    ui->progressBar->setMaximum(t);
    QString speed = QString::number(x/clock.elapsed());
    ui->speed->setText(QString("%1 KiB/Sec").arg(speed));
    timeOut->start(15000);
}

void miniUpdater::displayVersionInfo()
{
    ui->textEdit->clear();
    ui->textEdit->append(QString("Current Version    : %1 \n"
                                 "Current Build No   : %2 \n"
                                 "Current Build Date : %3 \n"
                                 "Current Build Time : %4 \n")
                         .arg(APPVERSION)
                         .arg(BUILD)
                         .arg(BUILDDATE)
                         .arg(BUILDTIME));
}

void miniUpdater::applyUpdate()
{
    timeOut->stop();
    dataIOhelper::deleteFile(exeBackUp);
    dataIOhelper::renameFile(EXENAME,exeBackUp);
    squeeze::expand(updatePath,EXENAME);
    dataIOhelper::deleteFile(updatePath);
    ui->restartButton->setHidden(false);
    ui->doButton->setHidden(true);
    ui->textEdit->append(QString("<b>%1</b> was updated Successfully to Version (%2),"
                                 " you will enjoy the update at next restart!,please click restart now.").arg(APPNAME).arg(latestVersion));
    ui->closeButton->setText("Restart later");
}

QString miniUpdater::humanizeUpdateData(QByteArray ba)
{
    QStringList info = QString(ba).split(";");
    if (info.length() < 7 )
        return QString("Failed to Parse Update Info");
    latestVersion =info.at(0);
    latestBuildNo = info.at(1);
    latestBuildDate =info.at(2);
    latestBuildTime =info.at(3);
    updateUrl = info.at(4);
    updateMD5 = info.at(5);
    updateMessage=info.at(6);

    return QString("Latest Version    : %1 \n"
                   "Latest Build No   : %2 \n"
                   "Latest Build Date : %3 \n"
                   "Latest Build Time : %4 \n"
                   "Update Info : %5 \n")
                             .arg(latestVersion)
                             .arg(latestBuildNo)
                             .arg(latestBuildDate)
                             .arg(latestBuildTime)
                             .arg(updateMessage);


}

void miniUpdater::verifyUpdate(QString path)
{
    updatePath = path;
    QByteArray updatePkg =  dataIOhelper::readFile(path);
    QString downloadedMD5 = QString(QCryptographicHash::hash((updatePkg),QCryptographicHash::Md5).toHex());
    bool verified = (downloadedMD5 == updateMD5)? true:false;
    QString msg = (verified)? "<html><p style='color:blue;'><b>File Verification Success.</b></p></html>"
                                              :"<html><p style='color:red;'><b>File Verification Failed.</b></p></html>" ;
    ui->textEdit->append(msg);
    if (verified)
    {
        ui->textEdit->append("<html><p style='color:blue;'><b>Applying Update.</b></p></html>");
        applyUpdate();
    }
}

void miniUpdater::enableUpdating(bool b)
{
    QString msg = (b)? "<html><p style='color:green;'><b>New Update is available.</b></p></html>"
                     :"<html><p style='color:blue;'><b>Already uptodate.</b></p></html>";
    ui->textEdit->append(msg);
    ui->doButton->setEnabled(b);

    if(b && autoUpdate){
        on_doButton_clicked();
    }
}

void miniUpdater::closeEvent(QCloseEvent *e)
{
    if (downloading)
    {
        QMessageBox box;
        int reply = box.question(nullptr,"Confirmation","This will abort current update in progress, Are you sure?",
                                 QMessageBox::Yes,QMessageBox::No);
        if ( reply == QMessageBox::Yes)
        {
            delete updateFileGraber;
            downloading = false;
            e->accept();
        }
        else
        {
            e->ignore();
        }
    }
    else
        e->accept();
}

void miniUpdater::keyPressEvent(QKeyEvent *e)
{
    if ( e->key() == Qt::Key_Escape ||e->key() == Qt::ALT + Qt::Key_F4)
    {
        e->ignore();
        close();
    }
    else
        QWidget::keyPressEvent(e);
}


void miniUpdater::on_closeButton_clicked()
{
    close();
}

void miniUpdater::connectionTimeOut()
{
    ui->textEdit->append("<html><p style='color:red;'><b>Connection timed out, Update Failed, Please retry later.</b></p></html>");
    updateFileGraber->abort();
    timeOut->stop();
    ui->speed->hide();
    ui->progressBar->hide();
}

void miniUpdater::on_restartButton_clicked()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

