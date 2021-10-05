// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MSQL_H
#define MSQL_H

#if defined __GNUC__
#define GNUINLINE __attribute__((__always_inline__))
#elif defined _MSC_VER
#define GNUINLINE
#endif

#include <QObject>
#include <QtSql/QtSql>
#include "mdebug.h"
#include "msettings.h"
class msql : public QObject
{
    Q_OBJECT
public:
    explicit msql(QObject *parent = nullptr);   
    bool createConnection(const QString & connectionName, QString path);
    bool integrityCheck(bool quick);
    bool vacuum();
    bool optimize();
    void shrinkMem();
    void WAL_CheckPoint(QString Mode);
    virtual ~msql();
    inline QString sqlExec(const QString & sqlCmd,bool alt=false) GNUINLINE{
        QSqlQuery* q;

        if(alt)
            q = query2;
        else
            q = query;

        q->clear();
        QString value;

        if (!q->exec(sqlCmd))
        {
            mDebug() << sqlCmd << q->lastError().text();

        }
        else if (!q->first())
        {
    //        mDebug() << "not valid query: " << sqlCmd << q->isSelect();
    //        mDebug() << q->lastError().text();
            return "";
        }
        else
        {
            value = q->value(0).toString();
        }
        q->finish();
        return value;
    }

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
