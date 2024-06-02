// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "internet.h"

internet::internet(QObject *parent)
    : QObject(parent), tcpSocket(new QTcpSocket(nullptr)) {
  // qRegisterMetaType<QAbstractSocket::SocketState>();
  // connect(tcpSocket,
  // SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(timeout(QAbstractSocket::SocketError)));
  connect(tcpSocket, &QTcpSocket::errorOccurred, this, &internet::timeout);
  // connect(tcpSocket, SIGNAL(connected()), this,
  // SLOT(socketConnected()),Qt::QueuedConnection);
  connect(tcpSocket, &QTcpSocket::connected, this, &internet::socketConnected);
  // connect(tcpSocket, SIGNAL(disconnected()), this,
  // SLOT(socketDisconnected()),Qt::QueuedConnection);
  connect(tcpSocket, &QTcpSocket::disconnected, this,
          &internet::socketDisconnected);
}

void internet::checkOnline() {
  if (tcpSocket->state() == QAbstractSocket::UnconnectedState) {
    tcpSocket->connectToHost("www.dropbox.com", 80, QIODevice::ReadWrite);
    // mDebug() << "Connecting...!";
  }
}

internet::~internet() { delete tcpSocket; }

void internet::socketConnected() {
  emit connected();
  // mDebug() << "Connected!";
}

void internet::socketDisconnected() {
  emit disconnected();
  // mDebug() << "Disconnected!";
}

void internet::timeout(QAbstractSocket::SocketError) {
  tcpSocket->disconnectFromHost();
  tcpSocket->close();
  // mDebug() << "TimedOut!";
}
