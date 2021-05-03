// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "netserver.h"

NetServer::NetServer(QObject *parent) : QObject(parent),m_server(new QTcpServer)
{
    if(m_server->listen(QHostAddress::Any, 8080))
    {
       connect(m_server, &QTcpServer::newConnection, this, &NetServer::newConnection);
       //qDebug() <<"Server is listening...";
    }
    else
    {
       // qDebug() << QString("Unable to start the server: %1.").arg(m_server->errorString());
    }
}

NetServer::~NetServer()
{
    foreach (QTcpSocket* socket, connection_set)
    {
        socket->close();
        socket->deleteLater();
    }

    m_server->close();
    delete m_server;
}

void NetServer::newConnection()
{
    while (m_server->hasPendingConnections())
        appendToSocketList(m_server->nextPendingConnection());
}


void NetServer::appendToSocketList(QTcpSocket *socket)
{
    connection_set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &NetServer::readSocket);

    qDebug() <<QString::number(socket->socketDescriptor());
    qDebug() << QString("INFO :: Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor());
}

void NetServer::readSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray buffer;
    QFile file;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    socketStream.startTransaction();
    socketStream >> buffer;

    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128);

    if(fileType=="attachment"){
        QString fileName = header.split(",")[1].split(":")[1];
        //QString ext = fileName.split(".")[1];
        //QString size = header.split(",")[2].split(":")[1].split(";")[0];
        QString filePath = "visitors.json";
        file.setFileName(fileName);
        if(file.open(QIODevice::WriteOnly)){
                file.write(buffer);
                file.close();
                emit loadVisitors();
                qDebug() <<  QString("INFO :: Attachment from sd:%1 successfully stored on disk under the path %2").arg(socket->socketDescriptor()).arg(QString(filePath));
            }else
                qDebug() <<  "QTCPServer" << "An error occurred while trying to write the attachment.";
        }else{
            qDebug() <<   QString("INFO :: Attachment from sd:%1 discarded").arg(socket->socketDescriptor());
    }
}
