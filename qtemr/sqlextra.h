#ifndef SQLEXTRA_H
#define SQLEXTRA_H

#include <QObject>
#include <QtSql>
#include <QApplication>
#include <QStringListModel>
#include "sqlcore.h"
#include "servicemodel.h"
#include "msql.h"
#include <QRandomGenerator>
class sqlExtra : public msql
{
    Q_OBJECT
public:
    explicit sqlExtra(QObject *parent = nullptr,QString connectioName="qt_sql_extra_connection",bool cTable=true);
    ~sqlExtra();
    bool createTables();
    bool createTable(QString tableName);
    bool addToAutoComplete(QString table, QString phrase, bool bypassCheck = false);
    bool addDefaultDrugDose(QString tradeName, QString dose);
    bool deleteDefaultDrugDose(QString tradeName);
    QString getDefaultDrugDose(QString tradeName);
    QStringList getFavourites();
    bool removeFromAutoComplete(QString table,QString phrase);
    bool executeQuery(QString queryStatement);
    QStringList getAutoCompleteList(QString table);
    bool doesCustomDrugsTableExists();
    void closeDataBase();
    bool resetDrugsTable();
    bool createServicesTable();
    bool addService(QString service);
    bool deleteSrvice(QString service);
    void updateServiceModel();
    QSqlTableModel *readServicesModel();
    QSqlTableModel *GetDietsModel();
    QSqlTableModel *readStandardDoses();
    QStringList getPaidServicesList();
    double getPaidServicePrice(QString service);
    void fixDatabase();
    bool createExpanderTable();
    bool addNewExpand(QString name);
    bool saveExpand(QString name,QString expand);
    bool deleteExapnd(QString name);
    QStringList getExpandList();
    QString getExpand(QString name);
    bool isExpandExists(QString name);
    bool isDefaultDoseExists(QString name);
    QStringList getDietList();
    QString getDiet(QString diet);

private:
    QSqlTableModel *tableModel;
    QSqlTableModel *stdDosesModel;
    QRandomGenerator generator;
signals:
private slots:
    void tableModelUpdateValidator(QModelIndex index, QModelIndex);
public slots:

};

#endif // SQLEXTRA_H
