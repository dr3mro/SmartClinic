// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MSQL_H
#define MSQL_H

#include <QObject>
#include <QtSql/QtSql>
#include "mdebug.h"
#include "msettings.h"
class msql : public QObject
{
    Q_OBJECT
public:
    explicit msql(QObject *parent = nullptr);
    inline QString sqlExec(const QString & sqlCmd,bool alt=false);
    bool createConnection(const QString & connectionName, QString path);
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
    QSqlQuery *query2;
    QString ConnectionName;
    mSettings& settings=mSettings::instance();

};

#endif // MSQL_H
