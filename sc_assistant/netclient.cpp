#include "netclient.h"

netClient::netClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    socket->connectToHost(addr,8080);
    connect(&t,&QTimer::timeout,this,&netClient::reconnect);

    t.start();
    t.setInterval(5000);

    if(socket->waitForConnected(1000))
        qDebug() << "Connected to Server";
    else{
        qDebug() << "QTCPClient"<< QString("The following error occurred: %1.").arg(socket->errorString());

    }
}

void netClient::send(const QString &file)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QString filePath = file;

            QFile file(filePath);
            if(file.open(QIODevice::ReadOnly)){

                QFileInfo fileInfo(file.fileName());
                QString fileName(fileInfo.fileName());

                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_15);

                QByteArray header;
                header.prepend(QString("fileType:attachment,fileName:%1,fileSize:%2;").arg(fileName).arg(file.size()).toUtf8());
                header.resize(128);

                QByteArray byteArray = file.readAll();
                byteArray.prepend(header);

                socketStream.setVersion(QDataStream::Qt_5_15);
                socketStream << byteArray;
            }else
                qDebug() << "Attachment is not readable!";
        }
        else
            qDebug()  << "Socket doesn't seem to be opened";
    }
    else
        qDebug() <<"Not connected";
}

void netClient::setIP(const QString &ip)
{
    addr = ip;
}

QString netClient::getIP()
{
    return addr;
}

void netClient::reconnect()
{
    if(socket->waitForConnected(900) && qApp->applicationState() == Qt::ApplicationState::ApplicationActive){
        qDebug() << "Connected to Server" << addr;
        return;
    }
    else if ( qApp->applicationState() == Qt::ApplicationState::ApplicationActive) {
        qDebug() << "QTCPClient"<< QString("The following error occurred: %1:%2.").arg(socket->errorString(),addr);
        socket->connectToHost(addr,8080);
    }
}