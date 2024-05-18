#include "sqlcore.h"
#include "globalvariables.h"


sqlCore::sqlCore(QObject *parent,QString connectionName) : msql(parent),
    model(new QStandardItemModel(parent)),
    drugModel(new QStringListModel(parent))
{
    QString path = QString("./data/drugs.db");
    if ( ! createConnection(connectionName,path) )
        mDebug() << "Failed to connect to drugs index data base";
}

QStandardItemModel *sqlCore::getDrugsIndexModel()
{
    query->clear();
    QStringList  labels;
    labels << "Trade Name" << "Generic Name" << "Price" << "Category" << "Form" << "Manufacturer";
    model->setHorizontalHeaderLabels(labels);
    bool q = query->exec("SELECT  DISTINCT(name) as name,active,price,company,description,dosage_form  FROM druglist ");
    if ( !q )
    {
        mDebug() << query->lastError().text();
    }
    int x=0;
    while (query->next())
    {
        QString tradeName = query->value(0).toString();
        QString genericName = query->value(1).toString();
        QString price = query->value(2).toString();
        QString manufacturer = query->value(3).toString();
        QString category = query->value(4).toString();
        QString form = query->value(5).toString();
        QString manufactorer = query->value(6).toString();

        QStandardItem *tradeitem = new QStandardItem (tradeName);
        tradeitem->setToolTip(category);

        QStandardItem *genericitem = new QStandardItem (genericName);
        genericitem->setToolTip(QString("<p align=left > %1 </p>").arg(genericName));

        QStandardItem *priceitem = new QStandardItem();
        priceitem->setData(QVariant(price.toDouble()),Qt::DisplayRole);

        QStandardItem *categoryitem = new QStandardItem(category);
        priceitem->setToolTip(manufacturer);

        QStandardItem *formitem = new QStandardItem(form);

        QStandardItem *manufactureritem = new QStandardItem(manufacturer);

        model->setItem(x, 0,tradeitem);
        model->setItem(x, 1,genericitem);
        model->setItem(x, 2,priceitem);
        model->setItem(x, 3,categoryitem);
        model->setItem(x, 4,formitem);
        model->setItem(x, 5,manufactureritem);

        x++;
    }
    query->finish();
    return model;
}

QStandardItemModel *sqlCore::getFindDrugsModel(QStandardItemModel *fmodel, QString col, QStringList filters)
{
    fmodel->clear();
    query->clear();
    QStringList  labels;
    labels << "Trade Name" << "Price" << "Manufacturer";
    fmodel->setHorizontalHeaderLabels(labels);
    QString cmd = QString("SELECT name,active,price,company FROM druglist WHERE ");
    int filtersLength = filters.length();
    int fx = 1 ;

    foreach (QString filter, filters)
    {
        cmd.append(QString("%1 LIKE '%%2%' ").arg(col).arg(filter));
        if ( fx < filtersLength)
        {
            cmd.append("AND ");
            fx++;
        }
    }

    bool q = query->exec(cmd);

    if ( !q )
    {
        mDebug() << query->lastError().text();
    }
    int x=0;
    while (query->next())
    {
        QString tradeName = query->value(0).toString();
        QString genericName = query->value(1).toString();
        double price = query->value(2).toDouble();
        QString manufacturer = query->value(3).toString();

        QStandardItem *tradeitem = new QStandardItem (tradeName);
        tradeitem->setToolTip(QString("<p align=left > %1 </p>").arg(genericName));
        QStandardItem *priceitem = new QStandardItem();
        priceitem->setData(QVariant(price), Qt::DisplayRole);
        QStandardItem *manufactureritem = new QStandardItem(manufacturer);

        fmodel->setItem(x, 0,tradeitem);
        fmodel->setItem(x, 1,priceitem);
        fmodel->setItem(x, 2,manufactureritem);
        x+=1;
    }
    query->finish();
    return fmodel;

}

QStringListModel *sqlCore::getCoreDrugListModel()
{
    query->clear();
    bool q = query->exec("SELECT DISTINCT name FROM drugslist");
    if (!q)
    {
        mDebug() << query->lastError().text();
    }


    while (query->next())
    {
        drugModel->setData(drugModel->index(drugModel->rowCount()-1), query->value(0).toString());
    }
    query->finish();
    drugModel->sort(0,Qt::AscendingOrder);
    return drugModel;
}

QStringList sqlCore::getCoreDrugList()
{
    query->clear();
    bool q = query->exec("SELECT DISTINCT name FROM druglist");
    if (!q)
    {
        mDebug() << query->lastError().text();
    }
    QStringList drugs;

    while (query->next())
    {
        //drugs <<  crypto.decryptToString(query->value(0).toString());
        drugs <<  query->value(0).toString();
    }
    std::sort(drugs.begin(),drugs.end());
    query->finish();
    return drugs;
}

QString sqlCore::getDrugDetail(QString tradeName, QString column)
{
    query->clear();
    QString drugDetail;
    bool q = query->exec(QString("SELECT %1 FROM druglist WHERE name=\"%2\"").arg(column).arg(tradeName));
    if (!q)
    {
        mDebug() << "ERROR GET DRUG DETAILS" << query->lastError().text();
    }
    //mDebug() << query->executedQuery();
    while (query->next())
    {
            drugDetail = query->value(0).toString();
    }
    query->finish();
    return drugDetail;
}

int sqlCore::getDrugsDatabaseVersion()
{
    // this is for migration and will be removed later
    if (! db.tables().contains("metadata"))
    {
        query->clear();

        if (query->exec("CREATE TABLE IF NOT EXISTS metadata(var varchar,value INTEGER);"))
        {

            mDebug() << "CREATING METADATATABLE";

            query->prepare("INSERT INTO `metadata`(`var`,`value`) VALUES (:var,:value);");
            query->bindValue(":var","version");
            query->bindValue(":value",150920);

            if (!query->exec())
                mDebug() << "FILED INSERTING DRUGS DB VERSION" << query->lastError().text();
        }
        query->finish();
    }


    // end migration code

    query->clear();
    int drugsDatabaseVersion=0;
    bool q = query->exec("SELECT value FROM metadata WHERE var=\"version\"");
    if (!q)
    {
        mDebug() << "ERROR GET DRUG DATABASE VERSION" << query->lastError().text();
    }
    //mDebug() << query->executedQuery();
    while (query->next())
    {
            drugsDatabaseVersion = query->value(0).toInt();
    }
    query->finish();
    return drugsDatabaseVersion;
}

sqlCore::filters sqlCore::getFilters()
{
    query->clear();
    filters f;
    bool q = query->exec("SELECT company,description,dosage_form FROM druglist");
    if ( !q )
    {
        mDebug() << query->lastError().text();
    }
    while (query->next())
    {
        QString company = query->value(0).toString();
        QString category = query->value(1).toString();
        QString form = query->value(2).toString();

        if (!f.companies.contains(company) && !company.isEmpty())
        {
            f.companies << company;
        }
        if (!f.categories.contains(category) && !category.isEmpty())
        {
            f.categories << category;
        }
        if (!f.forms.contains(form) && !form.isEmpty())
        {
            f.forms << form;
        }
    }
    f.categories.sort(Qt::CaseInsensitive);
    f.companies.sort(Qt::CaseInsensitive);
    f.forms.sort(Qt::CaseInsensitive);
    query->finish();
    return f;
}


void sqlCore::closeDataBase()
{
    query->clear();
    db.close();
}

void sqlCore::processResponse(const QByteArray& response) {

    if (!query->exec("BEGIN TRANSACTION;")) {
        mDebug() << "Error executing SQL:" << query->lastError().text();
        return;
    }


    if (!query->exec("DROP table IF EXISTS druglist;")) {
        mDebug() << "Error executing SQL:" << query->lastError().text();
        return;
    }

    if (!query->exec("CREATE TABLE IF NOT EXISTS druglist ("
                    "id TEXT PRIMARY KEY, "
                    "name TEXT, "
                    "arabic TEXT, "
                    "oldprice TEXT, "
                    "price TEXT, "
                    "active TEXT, "
                    "description TEXT, "
                    "company TEXT, "
                    "dosage_form TEXT, "
                    "units TEXT, "
                    "barcode TEXT, "
                    "route TEXT, "
                    "pharmacology TEXT, "
                    "sold_times TEXT);")) {
        mDebug() << "Error executing SQL:" << query->lastError().text();
        return;
    }

    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonArray jsonArray = jsonResponse.array();

    for (const QJsonValue& value : jsonArray) {
        QJsonObject obj = value.toObject();
        QString id = obj["id"].toString();
        QString name = obj["name"].toString();
        QString arabic = obj["arabic"].toString();
        QString price = obj["price"].toString();
        QString active = obj["active"].toString();
        QString description = obj["description"].toString();
        QString company = obj["company"].toString();
        QString dosage_form = obj["dosage_form"].toString();
        QString units = obj["units"].toString();
        QString barcode = obj["barcode"].toString();
        QString route = obj["route"].toString();
        QString pharmacology = obj["pharmacology"].toString();
        QString sold_times = obj["sold_times"].toString();

        QString insertQuery = QString("INSERT INTO druglist "
                                      "(id, name, arabic, price, active, description, company, "
                                      "dosage_form, units, barcode, route, pharmacology, sold_times) "
                                      "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', "
                                      "'%9', '%10', '%11', '%12', '%13');")
                                  .arg(id, name, arabic, price, active, description, company,
                                       dosage_form, units, barcode, route, pharmacology, sold_times);

        if (!query->exec(insertQuery)) {
            mDebug() << "Error executing SQL:" << query->lastError().text();
            return;
        }
    }

    if (!query->exec("COMMIT;")) {
        mDebug() << "Error executing SQL:" << query->lastError().text();
    }

    query->exec("UPDATE druglist SET active = UPPER(active);");
    query->exec("UPDATE druglist SET description = trim(description);");
    query->exec("UPDATE druglist SET description = ltrim(description,'.');");
    query->exec("UPDATE druglist SET description = replace(description,'.',' - ');");
    query->exec("UPDATE druglist SET description = UPPER(description);");
    query->exec("UPDATE druglist SET dosage_form = trim(dosage_form);");
    query->exec("UPDATE druglist SET dosage_form = UPPER(dosage_form);");
    query->exec("UPDATE druglist SET company = trim(company);");
    query->exec("UPDATE druglist SET company = ltrim(company,'.');");
    query->exec("UPDATE druglist SET company = ltrim(company,'\"');");
    query->exec("UPDATE druglist SET company = UPPER(company);");

    query->exec("UPDATE druglist SET name = TRIM(name);");
    query->exec("UPDATE druglist SET name = UPPER(name);");
    query->exec("UPDATE druglist SET name = replace(name,'\"','');");

    query->exec("UPDATE druglist SET name = replace(name,' MG','MG');");
    query->exec("UPDATE druglist SET name = replace(name,' MCG','MCG');");
    query->exec("UPDATE druglist SET name = replace(name,' ML','ML');");

    query->exec("UPDATE druglist SET name = replace(name,' MG','MG');");
    query->exec("UPDATE druglist SET name = replace(name,' MCG','MCG');");
    query->exec("UPDATE druglist SET name = replace(name,' ML','ML');");

    query->exec("UPDATE druglist SET name = replace(name,' GRAM','GRAM');");
    query->exec("UPDATE druglist SET name = replace(name,' GM','GM');");

    query->exec("UPDATE druglist SET name = replace(name,' GRAM','GRAM');");
    query->exec("UPDATE druglist SET name = replace(name,' GM','GM');");

    query->exec("UPDATE druglist SET name = replace(name,'TABLET','TAB');");
    query->exec("UPDATE druglist SET name = replace(name,'CAPSULE','CAP');");

    query->exec("UPDATE druglist SET name = replace(name,'TABS','TAB');");
    query->exec("UPDATE druglist SET name = replace(name,'CAPS','CAP');");

    query->exec("UPDATE druglist SET name = replace(name,'...','.');");
    query->exec("UPDATE druglist SET name = replace(name,'..','.');");
    query->exec("UPDATE druglist SET name = rtrim(name,'.');");

    query->exec("UPDATE druglist SET name = replace(name,'AMPS','AMP');");
    query->exec("UPDATE druglist SET name = replace(name,'AMPSS','AMP');");
    query->exec("UPDATE druglist SET name = replace(name,'F.C.TAB','F.C. TAB');");

    //query->exec("UPDATE druglist SET name = replace(name,'EAR  DROPS','EAR DROPS');");

    query->exec("UPDATE druglist SET name = replace(name,'DISTAB','DIS. TAB');");
    query->exec("UPDATE druglist SET name = replace(name,'DISTABLETS','DIS. TAB');");

    query->exec("UPDATE druglist SET name = replace(name,' TABLES','TAB');");

    query->exec("UPDATE druglist SET name = replace(name,'   ',' ');");
    query->exec("UPDATE druglist SET name = replace(name,'  ',' ');");

    query->exec("UPDATE druglist SET name = replace(name,'1 2 3 (ONE TWO THREE)','123');");
    query->exec("UPDATE druglist SET name = replace(name,'1 2 3','123');");

    query->exec("UPDATE druglist SET name = TRIM(name);");

    query->exec("UPDATE druglist SET name='CIPROCORT EAR DROPS 10ML' WHERE name = 'CIPROCORT OTIC DROPS 10ML';");
    query->exec("UPDATE druglist SET dosage_form='EAR DROPS' WHERE name = 'CIPROCORT EAR DROPS 10ML';");
    query->exec("UPDATE druglist SET description = 'MULTIVITAMIN' WHERE name = 'REGNADEX 30 TAB';");

    query->exec("UPDATE druglist SET dosage_form = 'CAPSULE' WHERE dosage_form = 'CAPS';");
    query->exec("UPDATE druglist SET dosage_form = 'CREAM' WHERE dosage_form = 'CRE';");
    query->exec("UPDATE druglist SET dosage_form = 'POWDER' WHERE dosage_form = 'POWER';");
    query->exec("UPDATE druglist SET dosage_form = 'TABLET' WHERE dosage_form = 'TABS.' OR dosage_form = 'TABLETS' ;");

    query->exec("UPDATE druglist SET active = 'UNSPECIFIED' WHERE TRIM(active) = '';");
    query->exec(QString("UPDATE metadata SET value=%1 WHERE var='version'").arg(QDate::currentDate().toString("yyMMdd")));
    //SELECT name, COUNT(*) c FROM druglist GROUP BY name HAVING c > 1 AND TRIM(pharmacology) != '';

    query->exec("COMMIT;");

    db.close();
    emit drugsDatabaseUpdateFinished();
}

void sqlCore::updateDrugsDatabase()
{

    QNetworkRequest request(QUrl("https://dwaprices.com/api_dr88g/index.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QObject::connect(&networkManager, &QNetworkAccessManager::finished, [&](QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            processResponse(response);
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });
    networkManager.post(request, "updatesqlite=1");
}


sqlCore::~sqlCore()
{
    model->removeRows(0,model->rowCount());
    delete model;
    drugModel->removeRows(0,drugModel->rowCount());
    delete drugModel;
}
