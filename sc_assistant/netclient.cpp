#include "netclient.h"

netClient::netClient(QObject *parent) : QObject(parent),
    socket(new QTcpSocket(this))
{
    connect(&t,&QTimer::timeout,this,&netClient::mConnect);

    connect(socket,&QTcpSocket::disconnected,this,[=](){
        t.start(5000);
    });
    connect(socket,&QTcpSocket::errorOccurred,this,[=](){
        t.start(5000);
    });
    connect(socket,&QTcpSocket::connected,this,[=](){
        t.stop();
    });

    t.start(5000);
}

netClient::~netClient()
{
    socket->close();
    delete  socket;
}

bool netClient::send(const QString &filePath)
{
//    if(!isDataModified(fileChecksum(filePath,QCryptographicHash::Md5)))
//        return false;

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
                return true;
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

void netClient::mConnect()
{
    if (qApp->applicationState() == Qt::ApplicationState::ApplicationActive){

        socket->connectToHost(m_ServerIP,8080);

        bool oldState = isConnected;

        isConnected = socket->waitForConnected(900);

        qDebug() << "Connections state is : " << isConnected << " to server: " << m_ServerIP;

        if(oldState != isConnected)
            emit connectionStateChanged();
    }
}

//QByteArray netClient::fileChecksum(const QString &fileName,QCryptographicHash::Algorithm hashAlgorithm)
//{
//    QFile f(fileName);
//    if (f.open(QFile::ReadOnly)) {
//        QCryptographicHash hash(hashAlgorithm);
//        if (hash.addData(&f)) {
//            return hash.result();
//        }
//    }
//    return QByteArray();
//}

//bool netClient::isDataModified(const QByteArray &hash)
//{
//    static QByteArray lastHash;

//    bool status  = (lastHash != hash);

//    lastHash = hash;

//    qDebug() << status;

//    return  status;
//}
