#include "wm_texteditcompleterloader.h"

wm_texteditCompleterLoader::wm_texteditCompleterLoader(QObject *parent) : QObject(parent)
{
    connectionName = QString("qt_sql_extra_%1_%2_%3")
            .arg(QString("dictionary"))
            .arg(generator.generate())
            .arg(QTime::currentTime().msecsSinceStartOfDay());
    sqlextra = new sqlExtra(this,connectionName,false);


}

wm_texteditCompleterLoader::~wm_texteditCompleterLoader()
{
    sqlextra->optimize();
    delete sqlextra;
    QSqlDatabase::removeDatabase(connectionName);
}

QStringList wm_texteditCompleterLoader::work()
{
    return sqlextra->getAutoCompleteList(QString("dictionary"));
}
