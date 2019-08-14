#include "sqlcore.h"

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
    bool q = query->exec("SELECT TRADENAME,GENERICNAME,PRICE,MANUFACTURER,CATEGORY,FORM FROM drugsIndex");
    if ( !q )
    {
        mDebug() << query->lastError().text();
    }
    int x=0;
    while (query->next())
    {
        QString category = query->value(4).toString();
        QString manufacturer = query->value(3).toString();
        QString form = query->value(5).toString();
        //QStandardItem *tradeitem = new QStandardItem (crypto.decryptToString(query->value(0).toString()));
        QStandardItem *tradeitem = new QStandardItem (query->value(0).toString());
        tradeitem->setToolTip(category);
        QStandardItem *genericitem = new QStandardItem (query->value(1).toString());
        genericitem->setToolTip(QString("<p align=left > %1 </p>").arg(query->value(1).toString()));
        QStandardItem *priceitem = new QStandardItem();
        priceitem->setData(QVariant(query->value(2).toDouble()),Qt::DisplayRole);
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
        x+=1;
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
    QString cmd = QString("SELECT TRADENAME,GENERICNAME,PRICE,MANUFACTURER FROM drugsIndex WHERE ");
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
    bool q = query->exec("SELECT TRADENAME FROM drugsIndex");
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
    bool q = query->exec("SELECT TRADENAME,FORM FROM drugsIndex");
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
    qSort(drugs.begin(),drugs.end());
    query->finish();
    return drugs;
}

QString sqlCore::getDrugDetail(QString tradeName, QString column)
{
    query->clear();
    QString drugDetail;
    bool q = query->exec(QString("SELECT %1 FROM drugsIndex WHERE TRADENAME=\"%2\"").arg(column).arg(tradeName));
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
    bool q = query->exec("SELECT MANUFACTURER,CATEGORY,FORM FROM drugsIndex");
    if ( !q )
    {
        mDebug() << query->lastError().text();
    }
    while (query->next())
    {
        QString company = query->value(0).toString();
        QString category = query->value(1).toString();
        QString form = query->value(2).toString();

        if (!f.companies.contains(company))
        {
            f.companies << company;
        }
        if (!f.categories.contains(category))
        {
            f.categories << category;
        }
        if (!f.forms.contains(form))
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


sqlCore::~sqlCore()
{
    model->removeRows(0,model->rowCount());
    delete model;
    drugModel->removeRows(0,drugModel->rowCount());
    delete drugModel;
}
