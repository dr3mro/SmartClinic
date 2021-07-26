#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent),
    serverIP(net.getIP()),
    isConnected(net.getIsConnected()),
    bcl(new broadcastListener(serverIP,this))
{
    connect(&sendTimer,&QTimer::timeout,this,&BackEnd::send);
    connect(&net,&netClient::connectionStateChanged,this,&BackEnd::connectionStateChanged);
    sendTimer.start(3000);
    dataChangeWatcher.addPath(jsonFileName);

    connect(&dataChangeWatcher,&QFileSystemWatcher::fileChanged,this,[=](){
        sendTimer.start(3000);
    });

}

BackEnd::~BackEnd()
{
    delete bcl;
}

void BackEnd::setName(const QString &_name)
{
    name = _name;
}

void BackEnd::setID(const int &_id)
{
    ID =_id;
}

void BackEnd::setSex(const int &_sex)
{
    sex = _sex;
}

void BackEnd::setMarital(const int &_marital)
{
    marital = _marital;
}

void BackEnd::setAge(const int &_age)
{
    age = _age;
}

void BackEnd::setResidence(const QString &_residence)
{
    residence = _residence;
}

void BackEnd::setPlaceofbirth(const QString &_placeofbirth)
{
    placeofbirth = _placeofbirth;
}

void BackEnd::setJob(const QString &_job)
{
    job = _job;
}

void BackEnd::setTel(const QString &_tel)
{
    tel = _tel;
}

void BackEnd::setVisitType(const int &_visitType)
{
    visitType = _visitType;

}

void BackEnd::setFinished(const bool &_finished)
{
    finished = _finished;
}

void BackEnd::setServerIP(const QString &ip)
{
    serverIP = ip;
    //net.setIP(serverIP);
}


QString BackEnd::getName() const
{
    return name;
}

int BackEnd::getID() const
{
    return ID;
}

int BackEnd::getSex() const
{
    return sex;
}

int BackEnd::getMarital() const
{
    return marital;
}

int BackEnd::getAge() const
{
    return age;
}

QString BackEnd::getResidence() const
{
    return residence;
}

QString BackEnd::getPlaceofbirth() const
{
    return placeofbirth;
}

QString BackEnd::getJob() const
{
    return job;
}

QString BackEnd::getTel() const
{
    return tel;
}

int BackEnd::getVisitType() const
{
    return visitType;
}

bool BackEnd::getFinished() const
{
    return finished;
}

QString BackEnd::getServerIP()
{
    return serverIP;
}

bool BackEnd::getIsConnected()
{
    return isConnected;
}
void BackEnd::loadVisitor(const int &index)
{
    QJsonDocument doc = getJsonDocument();
    QList<QVariant> list = doc.toVariant().toList();
    QMap<QString, QVariant> map = list[index].toMap();
    name        = map["Name"].toString();
    ID          = map["ID"].toInt();
    marital     = map["Marital"].toInt();
    age         = map["Age"].toInt();
    sex         = map["Sex"].toInt();
    residence   = map["Residence"].toString();
    placeofbirth= map["placeofbirth"].toString();
    job         = map["job"].toString();
    tel         = map["tel"].toString();
    visitType   = map["visitType"].toInt();
    finished    = map["finished"].toBool();
    emit visitorChanged();
}


void BackEnd::addNew(const int &index)
{
    QJsonDocument doc = getJsonDocument();

    QJsonArray array = doc.array();
    QJsonObject json;

    json.insert("Name",name);
    json.insert("ID",ID);
    json.insert("Sex",sex);
    json.insert("Marital",marital);
    json.insert("Age",age);
    json.insert("Residence",residence);
    json.insert("placeofbirth",placeofbirth);
    json.insert("job",job);
    json.insert("tel",tel);
    json.insert("visitType",visitType);
    json.insert("finished",finished);
    if(index == -1)
        array.append(json);
    else
        array.insert(index,json);
    QJsonDocument finalDoc;
    finalDoc.setArray(array);
    saveJson(finalDoc);
}

void BackEnd::delVisitor(const int &index)
{
    QJsonDocument doc = getJsonDocument();

    QJsonArray array = doc.array();
    array.removeAt(index);

    QJsonDocument finalDoc;
    finalDoc.setArray(array);
    saveJson(finalDoc);

}

void BackEnd::visitorSetFinishedState(const int &index, const bool & state)
{
    QJsonDocument doc = getJsonDocument();

    QJsonArray array = doc.array();

    QJsonObject json = array.at(index).toObject();

    array.removeAt(index);

    auto x = json.find("finished");

    *x = state;

    array.insert(index,json);
    QJsonDocument finalDoc;
    finalDoc.setArray(array);
    saveJson(finalDoc);
}

void BackEnd::deleteAll()
{
    QFile file;
    file.setFileName(jsonFileName);
    file.remove();
}

QVariantList  BackEnd::getPeopleList()
{
    QVariantList people;


    QJsonDocument doc = getJsonDocument();
    QJsonArray array = doc.array();

    foreach (const QJsonValue & v, array)
    {
        QJsonObject obj = v.toObject();
        QVariantMap pair1;
        pair1.insert("name", obj.value("Name").toString());
        pair1.insert("state", obj.value("finished").toBool());
        people << pair1;
    }
    return people;
}

void BackEnd::send()
{
    if(net.send(jsonFileName))
        sendTimer.stop();
}

QJsonDocument BackEnd::getJsonDocument()
{
    QFile file;
    file.setFileName(jsonFileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonRaw = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonRaw);
    file.close();
    return doc;
}

void BackEnd::saveJson(const QJsonDocument &doc)
{
    QFile file;
    file.setFileName(jsonFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.resize(0);
    file.write(doc.toJson());
    file.close();
}

