#ifndef FILEGRABBER_H
#define FILEGRABBER_H

#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QTimer>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QSslError>

#include "mdebug.h"

class fileGrabber : public QObject {
  Q_OBJECT
 public:
  explicit fileGrabber(bool save, QUrl url = QUrl(), QObject *parent = nullptr);
  void doDownload(const QUrl &url);
  QString saveFileName(const QUrl &url);
  bool closeFile();
  void openFile(const QString &filename);
  void run();
  void abort();
  void setURL(const QUrl &_url);
  ~fileGrabber();
 public slots:
  void execute();
  void downloadFinished(QNetworkReply *reply);
  void sslErrors(const QList<QSslError> &errors);
  void processData();
 signals:
  void returnDownloadedData(QByteArray data);
  void downloadSaved(double s);
  void downloadProgress(qint64, qint64);
  void verifyFile(QString path);
  void finished();

 private:
  QUrl url;
  bool save;
  QNetworkAccessManager manager;
  QNetworkReply *reply;
  QFile file;
  QTimer t;
};

#endif  // FILEGRABBER_H
