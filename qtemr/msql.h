#ifndef MSQL_H
#define MSQL_H

#include <QObject>
#include <QtSql>
#include "mdebug.h"
#include "msettings.h"
class msql : public QObject
{
    Q_OBJECT
public:
    explicit msql(QObject *parent = nullptr);
    QString sqlExec(QString sqlCmd);
    bool createConnection(QString connectionName, QString path);
    bool integrityCheck(bool quick);
    bool vacuum();
    bool optimize();
    void shrinkMem();
    void WAL_CheckPoint(QString Mode);
    virtual ~msql();

signals:
    void progress(QString pro,bool stat=true);
public slots:
    void killLoopFlag(bool flag=true);

private:
    mSettings::dbOptions options;

protected:
    bool killLoopFlag_=false;
    void setPragmas();
    QSqlDatabase db;
    QSqlQuery *query;
    QString ConnectionName;
    mSettings& settings=mSettings::instance();

};

#endif // MSQL_H
