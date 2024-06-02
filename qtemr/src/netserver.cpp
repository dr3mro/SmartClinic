// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "netserver.h"

NetServer::NetServer(QObject *parent)
    : QObject(parent),
      m_server(new QTcpServer(this)),
      m_udpBroadcastSocket(new QUdpSocket(this)) {
  if (m_server->listen(QHostAddress::Any, 8080)) {
    connect(m_server, &QTcpServer::newConnection, this,
            &NetServer::newConnection);

    connect(m_server, &QTcpServer::newConnection, this,
            [=]() { m_broadcastIPTimer.stop(); });

    // qDebug() <<"Server is listening...";
  } else {
    // qDebug() << QString("Unable to start the server:
    // %1.").arg(m_server->errorString());
  }

  m_broadcastIPTimer.start(3000);
  connect(&m_broadcastIPTimer, &QTimer::timeout, this, [=]() {
    broadcastAddresses.clear();
    ipAddresses.clear();
    const QList<QNetworkInterface> interfaces =
        QNetworkInterface::allInterfaces();
    for (const QNetworkInterface &interface : interfaces) {
      QNetworkInterface::InterfaceFlags flags = interface.flags();
      if (((interface.type() == QNetworkInterface::Ethernet ||
            interface.type() == QNetworkInterface::Wifi) &&
           interface.type() != QNetworkInterface::Virtual) &&
          ((bool)(flags & QNetworkInterface::IsRunning) &&
           !(bool)(flags & QNetworkInterface::IsLoopBack) &&
           (bool)(flags & QNetworkInterface::IsUp) &&
           (bool)(flags & QNetworkInterface::CanBroadcast))) {
        const QList<QNetworkAddressEntry> entries = interface.addressEntries();
        for (const QNetworkAddressEntry &entry : entries) {
          QHostAddress broadcastAddress = entry.broadcast();
          if (broadcastAddress != QHostAddress::Null &&
              entry.ip() != QHostAddress::LocalHost) {
            broadcastAddresses << broadcastAddress;
            ipAddresses << entry.ip();
          }
        }
      }
    }
    for (const QHostAddress &address : qAsConst(broadcastAddresses)) {
      for (auto server : ipAddresses) {
        QByteArray datagram = "hello";  // server.toString().toUtf8();
        m_udpBroadcastSocket->writeDatagram(datagram, address, 45454);
        // mDebug() << server ;
      }
    }
  });
}

NetServer::~NetServer() {
  foreach (QTcpSocket *socket, connection_set) {
    socket->close();
    socket->deleteLater();
  }

  m_server->close();
  m_udpBroadcastSocket->close();
  delete m_server;
  delete m_udpBroadcastSocket;
}

void NetServer::newConnection() {
  while (m_server->hasPendingConnections())
    appendToSocketList(m_server->nextPendingConnection());
}

void NetServer::appendToSocketList(QTcpSocket *socket) {
  connection_set.insert(socket);
  connect(socket, &QTcpSocket::readyRead, this, &NetServer::readSocket);

  connect(socket, &QTcpSocket::disconnected, this,
          [=]() { m_broadcastIPTimer.start(3000); });

  connect(socket, &QTcpSocket::disconnected, this, [=]() {
    connection_set.remove(socket);
    delete socket;
  });

  mDebug() << "Socket count: " << connection_set.count();
  qDebug() << QString::number(socket->socketDescriptor());
  qDebug() << QString("INFO :: Client with sockd:%1 has just entered the room")
                  .arg(socket->socketDescriptor());
}

void NetServer::readSocket() {
  QTcpSocket *socket = reinterpret_cast<QTcpSocket *>(sender());

  QByteArray buffer;
  QFile file;
  QDataStream socketStream(socket);
  socketStream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

  socketStream.startTransaction();
  socketStream >> buffer;

  QString header = buffer.mid(0, 128);
  QString fileType = header.split(",")[0].split(":")[1];

  buffer = buffer.mid(128);

  if (fileType == "attachment") {
    QString fileName = header.split(",")[1].split(":")[1];
    // QString ext = fileName.split(".")[1];
    // QString size = header.split(",")[2].split(":")[1].split(";")[0];
    QString filePath = "visitors.json";
    file.setFileName(fileName);
    if (file.open(QIODevice::WriteOnly)) {
      file.write(buffer);
      file.close();
      emit loadVisitors();
      qDebug() << QString(
                      "INFO :: Attachment from sd:%1 successfully stored on "
                      "disk under the path %2")
                      .arg(socket->socketDescriptor())
                      .arg(QString(filePath));
    } else
      qDebug() << "QTCPServer"
               << "An error occurred while trying to write the attachment.";
  } else {
    qDebug() << QString("INFO :: Attachment from sd:%1 discarded")
                    .arg(socket->socketDescriptor());
  }
}
