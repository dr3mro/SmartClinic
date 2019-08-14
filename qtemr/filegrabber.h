#ifndef FILEGRABBER_H
#define FILEGRABBER_H

#include <QApplication>
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <QTimer>
#include <QUrl>
#include "mdebug.h"

class fileGrabber : public QObject
{
    Q_OBJECT
public:
    explicit fileGrabber(bool save, QUrl url,QObject *parent = nullptr);
    void doDownload(const QUrl &url);
    QString saveFileName(const QUrl &url);
    bool closeFile();
    void openFile(const QString &filename);
    void run();
    void abort();
    ~fileGrabber();
public slots:
    void execute();
    void downloadFinished(QNetworkReply *reply);
    void sslErrors(const QList<QSslError> &errors);
    void processData();
signals:
    void returnDownloadedData(QByteArray data);
    void downloadSaved(double s);
    void downloadProgress(qint64,qint64);
    void verifyFile(QString path);
    void finished();
private:
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    QFile file;
    QTimer t;
    QUrl url;
    bool save;
};

#endif // FILEGRABBER_H
