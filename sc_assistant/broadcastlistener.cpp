#include "broadcastlistener.h"

broadcastListener::broadcastListener(QString &ip_address, QObject *parent) : QObject(parent),
    udpSocket(new QUdpSocket(this)),
    m_ip_address(ip_address)
{
    udpSocket->bind(QHostAddress::AnyIPv4, 45454, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(QHostAddress::AnyIPv4);


    connect(udpSocket, &QUdpSocket::readyRead,
            this, &broadcastListener::processPendingDatagrams);
}

broadcastListener::~broadcastListener()
{
    delete udpSocket;
}

void broadcastListener::processPendingDatagrams()
{
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        m_ip_address = QString(datagram.constData());
        qDebug() << m_ip_address;
    }
}


