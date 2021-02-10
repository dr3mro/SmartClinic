// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef INTERNET_H
#define INTERNET_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
class internet : public QObject
{
    Q_OBJECT
    QTcpSocket *tcpSocket;

public:
    explicit internet(QObject *parent = nullptr);
    ~internet();

signals:
    void connected();
    void disconnected();

public slots:
    void checkOnline();

private slots:
    void socketConnected();
    void socketDisconnected();
    void timeout(QAbstractSocket::SocketError);

};

#endif // INTERNET_H
