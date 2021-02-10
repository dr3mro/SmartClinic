// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "wm_completerloader.h"

wm_CompleterLoader::wm_CompleterLoader(QObject *parent) : QObject(parent)
{
    r = qrand();
}

QStringList wm_CompleterLoader::Work()
{
    QStringList list;
    connectionName = QString("qt_sql_extra_%1_%2_%3").arg(tableName).arg(r).arg(QTime::currentTime().msecsSinceStartOfDay());
    sqlextra = new sqlExtra(nullptr,connectionName,false);
    if (tableName == "expander")
        list = sqlextra->getExpandList();
    else if (tableName == "favourites")
        list = sqlextra->getFavourites();
    else
        list = sqlextra->getAutoCompleteList(tableName);

    sqlextra->optimize();
    delete sqlextra;
    QSqlDatabase::removeDatabase(connectionName);
    return list;
}

void wm_CompleterLoader::setTable(QString table)
{
    tableName = table;
}
