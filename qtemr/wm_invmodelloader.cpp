#include "wm_invmodelloader.h"

wm_invModelLoader::wm_invModelLoader(QObject *parent) : QObject(parent)
{
    r = generator.generate();
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

