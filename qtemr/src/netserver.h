// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef NETSERVER_H
#define NETSERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkInterface>
#include <QTimer>
#include <QDebug>
#include <QDataStream>
#include <QFile>
#include "mdebug.h"


class NetServer : public QObject
{
    Q_OBJECT
public:
    explicit NetServer(QObject *parent = nullptr);
    ~NetServer();
public slots:

private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);
    void readSocket();
signals:
    void loadVisitors();
private:
    QTcpServer* m_server;
    QUdpSocket *m_udpBroadcastSocket;
    QTimer m_broadcastIPTimer;
    QSet<QTcpSocket*> connection_set;
    QString m_InterfaceName;
    QList<QHostAddress> broadcastAddresses;
    QList<QHostAddress> ipAddresses;
};

#endif // NETSERVER_H
