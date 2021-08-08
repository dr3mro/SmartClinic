// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef SQLCORE_H
#define SQLCORE_H

#include <QObject>
#include <QtSql/QtSql>
#include <QStandardItemModel>
#include <QStringList>
#include "mdebug.h"
#include "msql.h"

class sqlCore : public msql
{
    Q_OBJECT
public:
    struct filters{QStringList categories;QStringList companies;QStringList forms;};
    explicit sqlCore(QObject *parent=nullptr, QString connectionName="qt_sql_core_connection");
    QStandardItemModel *getDrugsIndexModel();
    QStandardItemModel *getFindDrugsModel(QStandardItemModel *model, QString col, QStringList filters);
    QStringListModel *getCoreDrugListModel();
    QStringList getCoreDrugList();
    QString getDrugDetail(QString tradeName, QString column);
    int getDrugsDatabaseVersion();
    filters getFilters();
    void closeDataBase();
    ~sqlCore();

private:
    QStandardItemModel *model;
    QStringListModel *drugModel;
};

#endif // SQLCORE_H
