#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QtCore>
#include <qqml.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFile>
#include "netclient.h"

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY visitorChanged)
    Q_PROPERTY(QString ID   READ getID WRITE setID NOTIFY visitorChanged)
    Q_PROPERTY(int sex READ getSex WRITE setSex NOTIFY visitorChanged)
    Q_PROPERTY(int marital READ getMarital WRITE setMarital NOTIFY visitorChanged)
    Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY visitorChanged)
    Q_PROPERTY(QString residence READ getResidence WRITE setResidence NOTIFY visitorChanged)
    Q_PROPERTY(QString placeofbirth READ getPlaceofbirth WRITE setPlaceofbirth NOTIFY visitorChanged)
    Q_PROPERTY(QString job READ getJob WRITE setJob NOTIFY visitorChanged)
    Q_PROPERTY(QString tel READ getTel WRITE setTel NOTIFY visitorChanged)
    Q_PROPERTY(int visitType READ getVisitType WRITE setVisitType NOTIFY visitorChanged)
    Q_PROPERTY(bool finished READ getFinished WRITE setFinished NOTIFY visitorChanged)
    Q_PROPERTY(QString serverIP READ getServerIP WRITE setServerIP NOTIFY connectionStateChanged)
    Q_PROPERTY(bool isConnected READ getIsConnected NOTIFY connectionStateChanged)
    QML_ELEMENT
public:
    explicit BackEnd(QObject *parent = nullptr);
    ~BackEnd();
    void setName(const QString &_name);
    void setID(const QString &_id);
    void setSex(const int &_sex);
    void setMarital(const int &_marital);
    void setAge(const int &_age);
    void setResidence(const QString &_residence);
    void setPlaceofbirth(const QString &_placeofbirth);
    void setJob(const QString &_job);
    void setTel(const QString &_tel);
    void setVisitType(const int &_visitType);
    void setFinished(const bool & _finished);
    void setServerIP(const QString &ip);
    QString getName()const;
    QString getID()const;
    int getSex()const;
    int getMarital()const;
    int getAge()const;
    QString getResidence()const;
    QString getPlaceofbirth()const;
    QString getJob()const;
    QString getTel()const;
    int getVisitType()const;
    bool getFinished()const;
    QString getServerIP();
    bool getIsConnected();
    Q_INVOKABLE void loadVisitor(const int & index);
    Q_INVOKABLE void addNew(const int &index);
    Q_INVOKABLE void delVisitor(const int &index);
    Q_INVOKABLE void visitorSetFinishedState(const int &index, const bool &state);
    Q_INVOKABLE void deleteAll();
    Q_INVOKABLE QVariantList getPeopleList();
    Q_INVOKABLE void send();

    QJsonDocument getJsonDocument();
    void saveJson(const QJsonDocument &doc);
    QString pwd;



signals:
    Q_SIGNAL void visitorChanged();
    Q_SIGNAL void connectionStateChanged();

private:
    QString name="";
    QString ID="";
    int sex=-1;
    int marital=-1;
    int age=-1;
    QString residence="";
    QString placeofbirth="";
    QString job="";
    QString tel="";
    int visitType=-1;
    bool finished =false;
    netClient net;
    QString & serverIP;
    bool & isConnected;
    broadcastListener *bcl;
    QTimer sendTimer;

};

#endif // BACKEND_H
