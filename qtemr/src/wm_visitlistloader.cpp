// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "wm_visitlistloader.h"

wm_visitListLoader::wm_visitListLoader(QObject *parent) : QObject(parent),
    connectionName ( QString("qt_sql_base_visitListLoader_%1").arg(QRandomGenerator::global()->bounded(0,9999999))),
    sqlbase ( new sqlBase(this,connectionName,false))
{

}

wm_visitListLoader::~wm_visitListLoader()
{
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase(connectionName);
}

void wm_visitListLoader::setID(int id)
{
    ID = id;
}

QVector<sqlBase::visitItem> wm_visitListLoader::Work()
{
    return sqlbase->getPatientVisits(ID);
}

