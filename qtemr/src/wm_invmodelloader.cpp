// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "wm_invmodelloader.h"

wm_invModelLoader::wm_invModelLoader(QObject *parent) : QObject(parent)
{
    r = QRandomGenerator::global()->bounded(0,9999999);
    connectionName = QString("qt_sql_base_investigations_%1").arg(r);
    sqlbase = new sqlBase(this,connectionName,false);
}

void wm_invModelLoader::setIdJulianDate(int id, int jdate)
{
    visitJulianDate = jdate;
    ID = id;
}

void wm_invModelLoader::setInvestigationsModel(InvestModel *investModel)
{
    model = investModel;
}

wm_invModelLoader::~wm_invModelLoader()
{
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase(connectionName);
}

InvestModel* wm_invModelLoader::Work()
{
    return sqlbase->getInvestigationsModel(model,ID,visitJulianDate);
}

