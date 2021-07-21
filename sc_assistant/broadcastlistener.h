#ifndef BROADCASTLISTENER_H
#define BROADCASTLISTENER_H

#include <QObject>
#include <QUdpSocket>

class broadcastListener : public QObject
{
    Q_OBJECT
public:
    explicit broadcastListener(QString & ip_address,QObject *parent = nullptr);
    ~broadcastListener();

private slots:
    void processPendingDatagrams();

signals:

private:
    QUdpSocket *udpSocket;
    QString & m_ip_address;

};

#endif // BROADCASTLISTENER_H
