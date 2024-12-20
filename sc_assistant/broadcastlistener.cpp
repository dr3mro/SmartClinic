#include "broadcastlistener.h"

broadcastListener::broadcastListener(QString &ip_address, QObject *parent) : QObject(parent),
    udpSocket(new QUdpSocket(this)),
    m_ip_address(ip_address)
{
    udpSocket->bind(QHostAddress::AnyIPv4,45454,QUdpSocket::ShareAddress);

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &broadcastListener::processPendingDatagrams);
}

broadcastListener::~broadcastListener()
{
    udpSocket->close();
    delete udpSocket;
}

void broadcastListener::processPendingDatagrams()
{
    QByteArray datagram;
    QHostAddress host;
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size(),&host);
        if(datagram == "hello")
            m_ip_address = host.toString();
        //qDebug() << m_ip_address;
    }
}


