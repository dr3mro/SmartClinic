// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "sqlextra.h"

sqlExtra::sqlExtra(QObject *parent, QString connectionName, bool cTable) :
    msql(parent)
{
    QString path = QString("./data/coreComponents.db");
    if ( !createConnection(connectionName,path))
    {
        mDebug() << "Failed to connect to core components database";
    }

    if(cTable)
    {
        createServicesTable();
        createExpanderTable();
        createTables();
    }

    if ( !doesCustomDrugsTableExists())
    {
        QString coreconName = QString("qt_sql_core_coreDrugList_%1").arg(qrand());
        sqlCore *sqlcore = new sqlCore(this,coreconName);
        db.transaction();
        createTable("drugs");
        foreach ( QString drug , sqlcore->getCoreDrugList())
        {
            addToAutoComplete("drugs",drug,true);
        }
        sqlcore->optimize();
        delete sqlcore;
        QSqlDatabase::removeDatabase(coreconName);
        db.commit();
    }
    stdDosesModel = new QSqlTableModel(this,db);
}

sqlExtra::~sqlExtra()
{
    delete stdDosesModel;
}

bool sqlExtra::createTables()
{

    QStringList tables =
            QStringList() << "placeOfBirth" << "allergies"
                          << "diagnoses" << "dictionary"
                          << "doses" << "surgeries"
                          << "investigations" << "jobs"
                          << "places"  << "complaints";
    bool a = false ,b = false, c=false,d=false;
    a = executeQuery("CREATE TABLE IF NOT EXISTS defaultDoses ( tradeName varchar UNIQUE, dose varchar )");
    if ( !a )
    {
        mDebug() << "error creating default doses table";
    }

    foreach (QString table, tables)
    {
        b = executeQuery(QString("CREATE TABLE IF NOT EXISTS %1 ( STRING varchar UNIQUE )").arg(table));
        if (!b)
        {
            break;
        }

    }  
    c = executeQuery("CREATE TABLE IF NOT EXISTS diet ( diet varchar UNIQUE, description varchar )");
    if ( !c )
    {
        mDebug() << "error creating diets table";
    }
    d = createExpanderTable();

    if (!a||!b||!c||!d)
        return false;

    return true;
}

bool sqlExtra::createTable(QString tableName)
{
    return executeQuery(QString("CREATE TABLE IF NOT EXISTS %1 ( STRING varchar UNIQUE )").arg(tableName));
}

bool sqlExtra::addToAutoComplete(QString table, QString phrase , bool bypassCheck)
{

    if ( !bypassCheck && phrase.length() > 2 )
    {
        if ( ! getAutoCompleteList(table).contains(phrase,Qt::CaseInsensitive) )
            return executeQuery(QString("INSERT INTO '%1' (STRING) VALUES(\"%2\")").arg(table).arg(phrase.simplified()));
    }
    if ( bypassCheck )
    {
        return executeQuery(QString("INSERT INTO '%1' (STRING) VALUES(\"%2\")").arg(table).arg(phrase.simplified()));
    }

    return false;

}

bool sqlExtra::addDefaultDrugDose(QString tradeName, QString dose)
{
    bool q = executeQuery(QString("INSERT INTO defaultDoses (tradeName, dose) VALUES (\"%1\",\"%2\")").arg(tradeName).arg(dose));
    if ( !q )
    {
        mDebug() << " ERROR ADDING DEFAULT DOSE";
    }
    return q;
}

bool sqlExtra::deleteDefaultDrugDose(QString tradeName)
{
    bool q = executeQuery(QString("DELETE FROM defaultDoses WHERE tradeName=\"%1\"").arg(tradeName));
    if ( !q )
    {
        mDebug() << " ERROR DELETE DEFAULT DOSE";
    }
    return q;
}

QString sqlExtra::getDefaultDrugDose(QString tradeName)
{
    QString defaultDose;
    query->clear();
    bool q = query->exec(QString("SELECT dose FROM defaultDoses WHERE tradeName = \"%1\"").arg(tradeName));
    if ( !q )
    {
        mDebug()  << "Failed to fetch default drug dose";
    }

    while(query->next())
    {
        defaultDose = query->value(0).toString();
    }
    query->finish();
    return defaultDose;
}

QStringList sqlExtra::getFavourites()
{
    query->clear();
    bool p = query->exec("SELECT tradeName FROM defaultDoses");
    if ( !p )
    {
        mDebug() << "ERROR WHILE CREATING AUTOCOMPLETE LIST FVOURITES: " << query->lastError().text();
        mDebug() << query->lastQuery();
    }
    QStringList sList ;
    while(query->next())
    {
        sList << query->value(0).toString();
    }
    return sList;
}

bool sqlExtra::removeFromAutoComplete(QString table, QString phrase)
{
    QString query;
    if ( table == "favourites")
        query = QString("DELETE FROM defaultDoses WHERE TradeName = \"%1\";").arg(phrase);
    else
        query = QString("DELETE FROM '%1' WHERE STRING = \"%2\";").arg(table).arg(phrase);
    return executeQuery(query);
}

bool sqlExtra::executeQuery(QString queryStatement)
{
    query->clear();
    bool q = query->exec(queryStatement);
    if ( !q )
    {
        mDebug() << "ERROR WHILE Executing : " << queryStatement
                 << " : " << query->lastError().text();
    }
    query->finish();
    return q;
}

QStringList sqlExtra::getAutoCompleteList(QString table)
{
    query->clear();
    bool p = query->exec(QString("SELECT STRING FROM %1").arg(table));
    if ( !p )
    {
        mDebug() << "ERROR WHILE CREATING AUTOCOMPLETE LIST : " << query->lastError().text();
        mDebug() << query->lastQuery();
    }
    QStringList sList ;
    while(query->next())
    {
        sList << query->value(0).toString();
    }
    return sList;
}

bool sqlExtra::doesCustomDrugsTableExists()
{
    query->clear();
    QString value;
    if (!query->exec("SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND name='drugs'") || !query->first())
    {
        mDebug() << query->lastError().text();
    }
    else
    {
        value = query->value(0).toString();
    }
    query->finish();
    return bool(value.toInt());
}

void sqlExtra::closeDataBase()
{
    query->finish();
    //db.commit();
    db.close();
}

bool sqlExtra::resetDrugsTable()
{
    sqlCore sqlcore(this,"qt_sql_core_resetDrugs");
    bool x = executeQuery("DROP TABLE drugs");
    if ( !x )
    {
        mDebug() << "FAILED TO DELETE DRUGS TABLE";
    }
    else
    {
        if (!createTable("drugs"))
        {
            return false;
        }
            

        db.transaction();

        foreach ( QString drug , sqlcore.getCoreDrugList())
            addToAutoComplete("drugs",drug,true);

        foreach ( QString exp , getExpandList())
            addToAutoComplete("drugs",exp,true);

        db.commit();
    }
    sqlcore.optimize();
    return x;
}

bool sqlExtra::createServicesTable()
{
    query->clear();
    bool x = query->exec("CREATE TABLE IF NOT EXISTS SERVICES (service varchar UNIQUE, price integer)");
    if (!x)
    {
        mDebug() << "Failed to create services table : ?" << query->lastError().text();
    }

    query->finish();
    return x;
}

bool sqlExtra::addService(QString service)
{
    query->clear();
    bool x = query->exec(QString("INSERT INTO SERVICES (service) VALUES (\"%1\")").arg(service));
    if (!x)
    {
        mDebug() << "Failed to create services table : ?" << query->lastError().text();
    }

    query->finish();

    return x? addToAutoComplete("investigations",service):x;
}

bool sqlExtra::deleteSrvice(QString service)
{
    query->clear();
    bool x = query->exec(QString("DELETE FROM SERVICES WHERE service=\"%1\"").arg(service));
    if (!x)
    {
        mDebug() << "Failed to delete service from services table : ?" << query->lastError().text();
    }

    query->finish();
    return x;
}

void sqlExtra::updateServiceModel()
{
    tableModel->select();
}


QSqlTableModel *sqlExtra::readServicesModel()
{
    tableModel = new serviceModel(this,db) ;
    connect(tableModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(tableModelUpdateValidator(QModelIndex,QModelIndex)));
    tableModel->setTable("SERVICES");
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    tableModel->select();
    tableModel->setHeaderData(0,Qt::Horizontal,"Service");
    tableModel->setHeaderData(1,Qt::Horizontal,"Price");
    return tableModel;
}

QSqlTableModel *sqlExtra::GetDietsModel()
{
    QSqlTableModel *dietModel = new QSqlTableModel(this,db) ;
    dietModel->setTable("diet");
    dietModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    dietModel->select();
    dietModel->setHeaderData(0,Qt::Horizontal,"diet");
    dietModel->setHeaderData(1,Qt::Horizontal,"description");

    return dietModel;
}

QSqlTableModel *sqlExtra::readStandardDoses()
{
    stdDosesModel->clear();
    stdDosesModel->setTable("defaultDoses");
   //stdDosesModel->setSort(0,Qt::AscendingOrder);
    stdDosesModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    stdDosesModel->select();
    stdDosesModel->setHeaderData(0,Qt::Horizontal,"Trade Name");
    stdDosesModel->setHeaderData(1,Qt::Horizontal,"Default Dose");
    return stdDosesModel;
}

//QSqlTableModel *sqlExtra::getSqlTable(QString table, QString col1, QString col2)
//{
//    serviceModel *m = new serviceModel(this,db) ;
//    dietModel->setTable("diet");
//    dietModel->setEditStrategy(QSqlTableModel::OnFieldChange);

//    dietModel->select();
//    dietModel->setHeaderData(0,Qt::Horizontal,"diet");
//    dietModel->setHeaderData(1,Qt::Horizontal,"description");

//    return dietModel;
//}

QStringList sqlExtra::getPaidServicesList()
{
    QStringList list;
    query->clear();
    bool x = query->exec("SELECT service FROM SERVICES");
    if (!x)
    {
        mDebug() << "Failed to GET LIST OF service from services table : ?" << query->lastError().text();
    }
    while(query->next())
    {
        list << query->value(0).toString();
    }
    query->finish();
    return list;
}

double sqlExtra::getPaidServicePrice(QString service)
{
    double price=0;
    query->clear();
    bool x = query->exec(QString("SELECT price FROM SERVICES WHERE service=\"%1\"").arg(service));
    if (!x)
    {
        mDebug() << "Failed to GET  service Price from services table : ?" << query->lastError().text();
    }
    while(query->next())
    {
        price= query->value(0).toDouble();
    }
    query->finish();
    return price;
}

void sqlExtra::fixDatabase()
{
    QStringList tables = db.tables(QSql::AllTables);

    foreach (QString table, tables)
    {
        QApplication::processEvents();
        executeQuery(QString("VACUUM `%1`").arg(table));
    }

}

bool sqlExtra::createExpanderTable()
{
    bool c = executeQuery("CREATE TABLE IF NOT EXISTS expander ( name varchar UNIQUE, string varchar )");
    if ( !c )
    {
        mDebug() << "error creating expander table";
    }
    return c;
}

bool sqlExtra::addNewExpand(QString name)
{
    if (getAutoCompleteList("drugs").contains(name))
        return false;

    bool b = executeQuery(QString("INSERT INTO expander (name) VALUES (\"%1\")").arg(name));
    if ( !b )
    {
        mDebug() << "error add expander item";
    }
    if (b)
    {
        addToAutoComplete("drugs",name);
    }
    return b;
}

bool sqlExtra::saveExpand(QString name, QString expand)
{
    query->clear();
    query->prepare(QString("UPDATE expander SET string=:string where name=\"%1\"").arg(name));
    query->bindValue(":string",expand);
    bool b = query->exec();
    query->finish();
    return b;
}

bool sqlExtra::deleteExapnd(QString name)
{
    bool c = executeQuery(QString("DELETE FROM expander Where name=\"%1\"").arg(name));
    if (c)
        executeQuery(QString("DELETE FROM drugs Where STRING=\"%1\"").arg(name));
    if ( !c )
    {
        mDebug() << "error delete expander item";
    }
    return c;
}

QStringList sqlExtra::getExpandList()
{
    query->clear();
    bool p = query->exec("SELECT name FROM expander");
    if ( !p )
    {
        mDebug() << "ERROR WHILE CREATING EXAPNDER LIST : " << query->lastError().text();
    }
    QStringList sList ;
    while(query->next())
    {
        sList << query->value(0).toString();
    }
    return sList;
}

QString sqlExtra::getExpand(QString name)
{
    QString expander;
    query->clear();
    bool x = query->exec(QString("SELECT string FROM expander WHERE name=\"%1\"").arg(name));
    if (!x)
    {
        mDebug() << "Failed to GET expander from expander table : ?" << query->lastError().text();
    }
    while(query->next())
    {
        expander= query->value(0).toString();
    }

    query->finish();
    return expander;
}

bool sqlExtra::isExpandExists(QString name)
{
    QString sqlCmd = QString("SELECT EXISTS(SELECT * FROM expander where name=\"%1\")").arg(name);
    query->clear();
    QString value;
    if (!query->exec(sqlCmd) || !query->first())
    {
        mDebug() << sqlCmd << query->lastError().text();
    }
    else
    {
        value = query->value(0).toString();
    }
    query->finish();
    return bool(value.toInt());
}

bool sqlExtra::isDefaultDoseExists(QString name)
{
    QString sqlCmd = QString("SELECT EXISTS(SELECT * FROM defaultDoses where tradeName=\"%1\")").arg(name);
    query->clear();
    QString value;
    if (!query->exec(sqlCmd) || !query->first())
    {
        mDebug() << sqlCmd << query->lastError().text();
    }
    else
    {
        value = query->value(0).toString();
    }
    query->finish();
    return bool(value.toInt());
}

QStringList sqlExtra::getDietList()
{
    query->clear();
    bool p = query->exec("SELECT diet FROM diet");
    if ( !p )
    {
        mDebug() << "ERROR WHILE READING DIET LIST: " << query->lastError().text();
        mDebug() << query->lastQuery();
    }
    QStringList sList = QStringList() << "-";
    while(query->next())
    {
        sList << query->value(0).toString();
    }
    return sList;
}

QString sqlExtra::getDiet(QString diet)
{
    query->clear();
    bool p = query->exec(QString("SELECT description FROM diet Where diet=\"%1\"").arg(diet));
    if ( !p )
    {
        mDebug() << "ERROR WHILE GETTING DIET DESCRIPTION: " << query->lastError().text();
        mDebug() << query->lastQuery();
    }
    QString dietDescription;
    while(query->next())
    {
        dietDescription = query->value(0).toString();
    }
//    QTextDocument doc;
//    doc.setHtml( dietDescription );

//    return doc.toPlainText();

    return dietDescription;
}

//void sqlExtra::clearDefaultDoseTable()
//{
//    executeQuery("DELETE FROM defaultDoses WHERE tradeName IS NULL OR trim(tradeName) = '';");
//    executeQuery("DELETE FROM defaultDoses WHERE dose IS NULL OR trim(dose) = '';");
//}


//bool sqlExtra::createConnection(QString connectionName)
//{
//    ConnectionName = connectionName;
//    //mDebug() << connectionName << " created";
//    QString path = QString("./data/coreComponents.db");

//    if ( QSqlDatabase::contains(connectionName))
//    {
//        db = QSqlDatabase::database(connectionName);
//    }
//    else
//    {
//        db = QSqlDatabase::addDatabase("QSQLITE",connectionName);
//    }
//    db.setHostName("127.0.0.1");
//    db.setDatabaseName(path);
//    bool b =  db.open();
//    if (!b)
//    {
//        mDebug() << "Failed to connect to drugsIndex database";
//    }
//    query = new QSqlQuery(db);
//    setPragmas();
//    return b;
//}

//void sqlExtra::setPragmas()
//{

//    executeQuery("PRAGMA auto_vacuum=0");
//    //executeQuery("PRAGMA default_cache_size=128000000;");
//    //executeQuery("PRAGMA cache_size=128000000;");
//    //executeQuery("PRAGMA page_size=10240000;");
//    executeQuery("PRAGMA temp_store = MEMORY;");
//    executeQuery("PRAGMA synchronous=OFF");
//    executeQuery("PRAGMA journal_mode=MEMORY");
//    executeQuery("PRAGMA locking_mode=NORMAL");
//}

//QString sqlExtra::sqlExec(QString sqlCmd)
//{
//    query->clear();
//    QString value;
//    if (!query->exec(sqlCmd))
//    {
//        mDebug() << sqlCmd << query->lastError().text();
//    }
//    else if (!query->first())
//    {
//        //mDebug() << "not valid query: " << sqlCmd << query->isSelect();
//        return "";
//    }
//    else
//    {
//        value = query->value(0).toString();
//    }
//    query->finish();
//    return value;
//}

void sqlExtra::tableModelUpdateValidator(QModelIndex index, QModelIndex)
{
    bool isDouble= false;
    bool isInt= false;
    QString cell = index.sibling(index.row(),1).data().toString();
    cell.toDouble(&isDouble);
    cell.toInt(&isInt);
    if ( isDouble || isInt )
    {
        return;
    }
    else
    {
        tableModel->revert();
    }
}
