// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "excelexport.h"

excelExport::excelExport(QObject *parent) : QObject(parent)
{

}

bool excelExport::createXLS(QString excelFilePath)
{
    db = QSqlDatabase::addDatabase("QODBC3","excelExport");
    QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls)};DSN=''; FIRSTROWHASNAMES=1; READONLY=FALSE;CREATE_DB=\"%1\";DBQ=%2").
            arg(excelFilePath).arg(excelFilePath);

    db.setDatabaseName(dsn);

    if(!db.isValid())
    {
        mDebug() << "ExportExcelObject::export2Excel failed: QODBC not supported.";
        return false;
    }

    if(!db.open())
    {
        mDebug() << "Failed to Create XLS connection";
        mDebug() << db.lastError().text()<<"Get-OdbcDriver on powershell as admin";
        return false;
    }
    query = new QSqlQuery(db);
    if ( query->exec("CREATE TABLE PATIENTS(ID TEXT,NAME TEXT,MOBILE TEXT);"))
        return true;
    else
        return false;
}

bool excelExport::addRow(QString ID, QString Name, QString Mobile)
{
    query->clear();
    QString prepare = QString("INSERT INTO PATIENTS (ID,NAME,MOBILE)VALUES(:ID,:NAME,:MOBILE);");
    query->prepare(prepare);
    query->bindValue(":ID",ID);
    query->bindValue(":NAME",Name);
    query->bindValue(":MOBILE",Mobile);
    bool b = query->exec();
    query->finish();
    return b;
}

void excelExport::closeFile()
{
    delete query;
    db.close();
    db=QSqlDatabase();
    QSqlDatabase::removeDatabase("excelExport");
}

excelExport::~excelExport()
{

}

