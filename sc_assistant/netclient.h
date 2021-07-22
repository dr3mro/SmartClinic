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
    ~netClient();
    void send(const QString & file);
    void setIP(const QString & ip);
    QString &getIP();
    bool &getIsConnected();
signals:
    void connectionStateChanged();
private:
    QTcpSocket* socket;
    QTimer t;
private slots:
    void reconnect();
private:
    QString m_ServerIP=QString("127.0.0.1");
    bool isConnected=false;

};

#endif // NETCLIENT_H
