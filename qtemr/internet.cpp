#include "internet.h"

internet::internet(QObject *parent) : QObject(parent),
    tcpSocket(new QTcpSocket(nullptr))
{
    qRegisterMetaType<QAbstractSocket::SocketState>();
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(timeout(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(socketConnected()),Qt::QueuedConnection);
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()),Qt::QueuedConnection);

}

void internet::checkOnline()
{
    if ( tcpSocket->state() == QAbstractSocket::UnconnectedState )
    {
        tcpSocket->connectToHost("www.dropbox.com",80,QIODevice::ReadWrite);
        //mDebug() << "Connecting...!";
    }
}

internet::~internet()
{
    delete tcpSocket;
}

void internet::socketConnected()
{
    emit connected();
    //mDebug() << "Connected!";
}

void internet::socketDisconnected()
{
    emit disconnected();
    //mDebug() << "Disconnected!";
}

void internet::timeout(QAbstractSocket::SocketError )
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    //mDebug() << "TimedOut!";
}
