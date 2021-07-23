#include "netclient.h"

netClient::netClient(QObject *parent) : QObject(parent),
    socket(new QTcpSocket(this))
{
    socket->connectToHost(m_ServerIP,8080);
    connect(&t,&QTimer::timeout,this,&netClient::reconnect);

    t.start();
    t.setInterval(5000);

    if(socket->waitForConnected(1000)){
        qDebug() << "Connected to Server" << m_ServerIP;
        isConnected = true;
        emit connectionStateChanged();
    }
    else{
        qDebug() << "QTCPClient"<< QString("The following error occurred: %1.").arg(socket->errorString());
        isConnected = false;
        emit connectionStateChanged();
    }
}

netClient::~netClient()
{
    socket->close();
    delete  socket;
}

void netClient::send(const QString &filePath)
{
    if(!isDataModified(fileChecksum(filePath,QCryptographicHash::Md5)))
        return;

    if(socket)
    {
        if(socket->isOpen())
        {
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
    m_ServerIP = ip;
}

QString & netClient::getIP()
{
    return m_ServerIP;
}

bool &netClient::getIsConnected()
{
    return isConnected;
}

void netClient::reconnect()
{
    if(socket->waitForConnected(900) && qApp->applicationState() == Qt::ApplicationState::ApplicationActive){
        qDebug() << "Connected to Server" << m_ServerIP;
        isConnected = true;
        emit connectionStateChanged();
        return;
    }
    else if ( qApp->applicationState() == Qt::ApplicationState::ApplicationActive) {
        qDebug() << "QTCPClient"<< QString("The following error occurred: %1:%2.").arg(socket->errorString(),m_ServerIP);
        isConnected = false;
        emit connectionStateChanged();
        socket->connectToHost(m_ServerIP,8080);
    }
}

QByteArray netClient::fileChecksum(const QString &fileName,QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile f(fileName);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f)) {
            return hash.result();
        }
    }
    return QByteArray();
}

bool netClient::isDataModified(const QByteArray &hash)
{
    static QByteArray lastHash;

    bool status  = (lastHash != hash);

    lastHash = hash;

    qDebug() << status;
    return  status;
}
