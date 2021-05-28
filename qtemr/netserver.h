// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef NETSERVER_H
#define NETSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QFile>


class NetServer : public QObject
{
    Q_OBJECT
public:
    explicit NetServer(QObject *parent = nullptr);
    ~NetServer();
private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);
    void readSocket();
signals:
    void loadVisitors();
private:
    QTcpServer* m_server;
    QSet<QTcpSocket*> connection_set;
};

#endif // NETSERVER_H