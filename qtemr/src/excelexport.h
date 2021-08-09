// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef EXCELEXPORT_H
#define EXCELEXPORT_H

#include <QObject>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "mdebug.h"



class excelExport : public QObject
{
    Q_OBJECT
public:
    explicit excelExport(QObject *parent = nullptr);
    bool createXLS(QString excelFilePath);
    bool addRow(QString ID,QString Name,QString Mobile);
    void closeFile();
    ~excelExport();
private:
    QSqlDatabase db;
    QSqlQuery *query;
signals:

public slots:
};

#endif // EXCELEXPORT_H
