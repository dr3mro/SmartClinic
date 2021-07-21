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
#include "broadcastlistener.h"

class netClient : public QObject
{
    Q_OBJECT
public:
    explicit netClient(QObject *parent = nullptr);
    void send(const QString & file);
    void setIP(const QString & ip);
    QString getIP();
signals:

private:
    QTcpSocket* socket;
    QTimer t;
private slots:
    void reconnect();
private:
    QString addr=QString("127.0.0.1");

};

#endif // NETCLIENT_H
