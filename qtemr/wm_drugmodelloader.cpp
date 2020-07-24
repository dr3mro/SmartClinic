#include "wm_drugmodelloader.h"

wm_drugModelLoader::wm_drugModelLoader(QObject *parent) : QObject(parent)
{
    connectionName = QString("qt_sql_base_drugsModel_%1_%2")
            .arg(qrand())
            .arg(qrand());
    sqlbase = new sqlBase(this,connectionName,false);
}

void wm_drugModelLoader::setDrugsModel(DrugsItemModel *drugsModel)
{
    model = drugsModel;
}

void wm_drugModelLoader::setIDJulianDate(int mID, int mJulianDate)
{
    ID = mID;
    julianDate = mJulianDate;
}

wm_drugModelLoader::~wm_drugModelLoader()
{
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase(connectionName);
}

DrugsItemModel* wm_drugModelLoader::Work()
{
    return sqlbase->readDrugs(ID,julianDate,model);
}

