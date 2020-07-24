#include "msql.h"

msql::msql(QObject *parent) : QObject(parent)
{
     options = settings.readDbOptions();
}

QString msql::sqlExec(QString sqlCmd)
{
    query->clear();
    QString value;

    if (!query->exec(sqlCmd))
    {
        mDebug() << sqlCmd << query->lastError().text();

    }
    else if (!query->first())
    {
//        mDebug() << "not valid query: " << sqlCmd << query->isSelect();
//        mDebug() << query->lastError().text();
        return "";
    }
    else
    {
        value = query->value(0).toString();
    }
    query->finish();
    return value;
}

msql::~msql()
{
   // mDebug() << "stop:" <<ConnectionName;
    query->finish();
    db.commit();
    db.close();
    delete query;
}

void msql::killLoopFlag(bool flag)
{
    killLoopFlag_=flag;
}

void msql::setPragmas()
{  
    sqlExec(QString("PRAGMA cache_size = %1;").arg(options.cache_size));
    sqlExec(QString("PRAGMA page_size = %1;").arg(options.page_size));
    sqlExec(QString("PRAGMA auto_vacuum = %1").arg(options.autovacuum));
    sqlExec(QString("PRAGMA temp_store = %1;").arg(options.temp_store));
    sqlExec(QString("PRAGMA synchronous = %1").arg(options.synchronous));
    sqlExec(QString("PRAGMA journal_mode = %1").arg(options.journal_mode));
    sqlExec(QString("PRAGMA locking_mode = %1").arg(options.locking_mode));
    sqlExec(QString("PRAGMA cache = %1").arg(options.shared_cache));
    WAL_CheckPoint(options.WAL_CheckPoint);

}

bool msql::createConnection(QString connectionName, QString path)
{
    ConnectionName = connectionName;
    //mDebug() << "start:"<< ConnectionName;
    if ( QSqlDatabase::contains(connectionName))
    {
        db = QSqlDatabase::database(connectionName);
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE",connectionName);
    }
    db.setHostName("127.0.0.1");
    db.setDatabaseName(path);
    bool b =  db.open();

    query = new QSqlQuery(db);
    setPragmas();
    return b;
}

bool msql::integrityCheck(bool quick)
{
    QString cmd;
    if (quick)
        cmd = "PRAGMA quick_check;";
    else
        cmd = "PRAGMA integrity_check;";

    return ( sqlExec(cmd) == "ok" );
}

bool msql::vacuum()
{
    bool result;
    query->clear();
    result = query->exec("VACUUM;");
    query->finish();
    return result;
}

bool msql::optimize()
{
    if(!options.optimize)
        return false;

    query->clear();
    bool r = query->exec("PRAGMA optimize;");
    query->finish();
    shrinkMem(); // to be called after connectio close with optimize
    return r;
}

void msql::shrinkMem()
{
    if(!options.shrinkMem)
        return;

    query->clear();
    query->exec("PRAGMA shrink_memory");
    query->finish();
}

void msql::WAL_CheckPoint(QString Mode)
{
    if(Mode=="OFF")
        return;
    else if(Mode=="DEFAULT")
        query->exec("PRAGMA wal_checkpoint;");
    else
        query->exec(QString("PRAGMA wal_checkpoint(%1);").arg(Mode));
}
