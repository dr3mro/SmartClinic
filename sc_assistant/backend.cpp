#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent),
    bcl(new broadcastListener(serverIP,this))
{
    QDir::setCurrent(QDir::homePath());
    serverIP = settings.value("ip").toString();
    net.setIP(serverIP);
}

BackEnd::~BackEnd()
{
    settings.setValue("ip", serverIP);
}

void BackEnd::setName(const QString &_name)
{
    name = _name;
}

void BackEnd::setID(const QString &_id)
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

void BackEnd::setServerIP(const QString &ip)
{
    serverIP = ip;
    net.setIP(serverIP);
}


QString BackEnd::getName() const
{
    return name;
}

QString BackEnd::getID() const
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

QString BackEnd::getServerIP()
{
    return serverIP;
}
void BackEnd::loadVisitor(const int &index)
{
    QJsonDocument doc = getJsonDocument();
    QList<QVariant> list = doc.toVariant().toList();
    QMap<QString, QVariant> map = list[index].toMap();
    name        = map["Name"].toString();
    ID          = map["ID"].toString();
    marital     = map["Marital"].toInt();
    age         = map["Age"].toInt();
    sex         = map["Sex"].toInt();
    residence   = map["Residence"].toString();
    placeofbirth= map["placeofbirth"].toString();
    job         = map["job"].toString();
    tel         = map["tel"].toString();
    visitType   = map["visitType"].toInt();
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

void BackEnd::deleteAll()
{
    QFile file;
    file.setFileName("visitors.json");
    file.remove();
}

QStringList  BackEnd::getPeopleList()
{
    QStringList people;
    QJsonDocument doc = getJsonDocument();
    QJsonArray array = doc.array();

    foreach (const QJsonValue & v, array)
    {
        QJsonObject obj = v.toObject();
        people << obj.value("Name").toString();
    }
    return people;
}

void BackEnd::send()
{
    net.send("visitors.json");
}

QJsonDocument BackEnd::getJsonDocument()
{
    QFile file;
    file.setFileName("visitors.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonRaw = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonRaw);
    file.close();
    return doc;
}

void BackEnd::saveJson(const QJsonDocument &doc)
{
    QFile file;
    file.setFileName("visitors.json");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.resize(0);
    file.write(doc.toJson());
    file.close();
}

