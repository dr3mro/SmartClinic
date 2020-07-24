#include "wm_patientnamescompleterloader.h"

wm_patientnamesCompleterLoader::wm_patientnamesCompleterLoader(QObject *parent) : QObject(parent)
{
    connectionName = QString("qt_sql_base_%1_%2_%3")
            .arg(QString("patientNames"))
            .arg(qrand())
            .arg(QTime::currentTime().msecsSinceStartOfDay());
    sqlbase = new sqlBase(nullptr,connectionName,false);
}

wm_patientnamesCompleterLoader::~wm_patientnamesCompleterLoader()
{
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase(connectionName);
}

QStringList wm_patientnamesCompleterLoader::Work()
{
    return sqlbase->getPatientNameList();
}
