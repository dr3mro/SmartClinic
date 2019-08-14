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
