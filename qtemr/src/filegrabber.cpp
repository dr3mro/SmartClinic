#include "filegrabber.h"

fileGrabber::fileGrabber(bool _save, QUrl _url, QObject *parent) : QObject(parent),
        url(_url),
        save(_save)
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)),SLOT(downloadFinished(QNetworkReply*)));

    t.setInterval(100);
    connect(&t,SIGNAL(timeout()),SLOT(processData()));
}

void fileGrabber::doDownload(const QUrl &_url)
{
    //mDebug() << "Download Starting..";

    QNetworkRequest request(_url);
    reply = manager.get(request);
    if (save)
    {
        reply->setReadBufferSize(4096000);
        connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SIGNAL(downloadProgress(qint64,qint64)));
        t.start();
    }
#ifndef QT_NO_SSL
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
#endif
}

QString fileGrabber::saveFileName(const QUrl &_url)
{
    QString path = _url.path();
    QString basename = QString("update/%1").arg(QFileInfo(path).fileName());
    //mDebug() << basename;
    if (basename.isEmpty())
        basename = "update/download.zip";
    return basename;
}

bool fileGrabber::closeFile()
{
    double size = file.size();
    file.close();

    emit downloadSaved(size);
    return true;
}

void fileGrabber::openFile(const QString &filename)
{
    file.setFileName(filename);
    if (! file.open(QIODevice::WriteOnly))
        mDebug() << "Failed to open update file .. ";

}

void fileGrabber::run()
{
    QTimer::singleShot(0,this,SLOT(execute()));
}

void fileGrabber::abort()
{
    reply->abort();
    emit finished();
}

void fileGrabber::setURL(const QUrl &_url)
{
    url = _url;
}

fileGrabber::~fileGrabber()
{
    if (file.isOpen())
        file.close();
}

void fileGrabber::execute()
{
    if (save)
        openFile(saveFileName(url));

    doDownload(url);
}

void fileGrabber::downloadFinished(QNetworkReply *_reply)
{
    if (_reply->error()) {
        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(_reply->errorString()));
    }
    else if (save)
    {
        processData();
        closeFile();
        emit verifyFile(saveFileName(url));
    }
    else
    {
        emit returnDownloadedData(_reply->readAll());
    }
    emit finished();
    //mDebug() << "Download finnished";
}

void fileGrabber::sslErrors(const QList<QSslError> &errors)
{
#ifndef QT_NO_SSL
    foreach (const QSslError &error, errors)
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
    Q_UNUSED(sslErrors);
#endif
}

void fileGrabber::processData()
{
    //mDebug() << "Data Processing";
    if (reply->bytesAvailable() > 0 )
        file.write(reply->read(reply->bytesAvailable()));
    file.flush();
    QApplication::processEvents();
}
