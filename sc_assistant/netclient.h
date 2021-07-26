#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include <QAbstractSocket>
#include <QDebug>
#include <QHostAddress>
#include <QMetaType>
#include <QString>
#include <QStandardPaths>
#include <QTcpSocket>
#include <QDataStream>
#include <QFile>
#include <QFileInfo>
#include <QTimer>
#include <QApplication>
#include <QCryptographicHash>
#include "broadcastlistener.h"

class netClient : public QObject
{
    Q_OBJECT
public:
    explicit netClient(QObject *parent = nullptr);
    ~netClient();
    bool send(const QString & filePath);
    void setIP(const QString & ip);
    QString &getIP();
    bool &getIsConnected();
signals:
    void connectionStateChanged();

private slots:
    void mConnect();
private:
    QString m_ServerIP=QString("127.0.0.1");
    bool isConnected=false;
    QTcpSocket* socket;
    QTimer t;
//    QByteArray fileChecksum(const QString &fileName,QCryptographicHash::Algorithm hashAlgorithm);
//    bool isDataModified(const QByteArray &hash);

};

#endif // NETCLIENT_H
