// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "remoteassist.h"
#include "ui_remoteassist.h"

remoteAssist::remoteAssist(QWidget *parent) :
    QDialog(parent),
    model(new QStandardItemModel),
    sqlbase (new sqlBase(this,QString("qt_sql_base_remoteAssistant_connection"),false)),
    ui(new Ui::remoteAssist)
{
    ui->setupUi(this);
    ui->visitorsTableView->setModel(model);
    connect(ui->searchByID,&QToolButton::clicked,this,&remoteAssist::searchByID);
    connect(ui->searchByName,&QToolButton::clicked,this,&remoteAssist::searchByName);
    connect(ui->searchByTel,&QToolButton::clicked,this,&remoteAssist::searchByTel);
    connect(ui->reload,&QToolButton::clicked,this,&remoteAssist::loadVisitors);
    connect(ui->visitorsTableView->selectionModel(),&QItemSelectionModel::currentRowChanged,this,&remoteAssist::showVisitor);




    loadVisitors();

}

remoteAssist::~remoteAssist()
{
    delete model;
    delete ui;
}

void remoteAssist::loadVisitors()
{
    while(model->rowCount() > 0)
        model->removeRow(0);


    QJsonDocument doc = getJsonDocument();
    QList<QVariant> list = doc.toVariant().toList();
    int row = 0;
    foreach (const QVariant &v, list) {
        QMap<QString, QVariant> map = v.toMap();

        QStandardItem *name = new QStandardItem(map["Name"].toString());
        QStandardItem *ID = new QStandardItem(map["ID"].toString());

        QStandardItem *marital = new QStandardItem();
        marital->setData(QVariant(map["Marital"].toInt()), Qt::DisplayRole);

        QStandardItem *age = new QStandardItem();
        age->setData(QVariant(map["Age"].toInt()), Qt::DisplayRole);

        QStandardItem *sex = new QStandardItem();
        sex->setData(QVariant(map["Sex"].toInt()), Qt::DisplayRole);

        QStandardItem *residence = new QStandardItem(map["Residence"].toString());
        QStandardItem *placeofbirth = new QStandardItem(map["placeofbirth"].toString());
        QStandardItem *job = new QStandardItem(map["job"].toString());
        QStandardItem *tel = new QStandardItem(map["tel"].toString());

        QStandardItem *visitType = new QStandardItem();
        visitType->setData(QVariant(map["visitType"].toInt()), Qt::DisplayRole);

        model->setItem(row,0,ID);
        model->setItem(row,1,name);
        model->setItem(row,2,marital);
        model->setItem(row,3,age);
        model->setItem(row,4,sex);
        model->setItem(row,5,residence);
        model->setItem(row,6,placeofbirth);
        model->setItem(row,7,job);
        model->setItem(row,8,tel);
        model->setItem(row,9,visitType);

        row++;
    }
    tweakTable();
}

QJsonDocument remoteAssist::getJsonDocument()
{
    QFile file;
    file.setFileName("visitors.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonRaw = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonRaw);
    file.close();
    return doc;
}

remoteAssist::Visitor remoteAssist::getVisitor(const int &row)
{
    Visitor visitor;
    if(model->rowCount() > 0) {
        visitor.ID = model->item(row,0)->text();
        visitor.name = model->item(row,1)->text();
        visitor.marital = model->item(row,2)->text().toInt();
        visitor.age = model->item(row,3)->text().toInt();
        visitor.sex = model->item(row,4)->text().toInt();
        visitor.residence = model->item(row,5)->text();
        visitor.placeofbirth = model->item(row,6)->text();
        visitor.job = model->item(row,7)->text();
        visitor.tel = model->item(row,8)->text();
        visitor.visitType = model->item(row,9)->text().toInt();
    }

    return  visitor;
}

void remoteAssist::showVisitor(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    if(current.row() < 0)
        return;

    Visitor visitor = getVisitor(current.row());
    ui->_id->setText(visitor.ID);
    ui->_name->setText(visitor.name);
    ui->_martital->setCurrentIndex(visitor.marital);
    ui->_age->setValue(visitor.age);
    ui->_sex->setCurrentIndex(visitor.sex);
    ui->_residence->setText(visitor.residence);
    ui->_pob->setText(visitor.placeofbirth);
    ui->_occu->setText(visitor.job);
    ui->_tel->setText(visitor.tel);
    ui->_visitType->setCurrentIndex(visitor.visitType);

    bool idExists= sqlbase->isPatientExists(visitor.ID.toInt());
    bool nameExists = sqlbase->isPatientNameUsed(visitor.name);
    bool nameIdMatch = sqlbase->haveSameNameWithSameID(visitor.ID.toInt(),visitor.name);


    if(nameIdMatch)
    {
        ui->id_check->setCheckState(Qt::CheckState::Checked);
        ui->name_check->setCheckState(Qt::CheckState::Checked);
        ui->loadID->setEnabled(true);
        ui->loadName->setEnabled(true);
    }
    else
    {
        if(idExists)
        {
            ui->id_check->setCheckState(Qt::CheckState::PartiallyChecked);
            ui->loadID->setEnabled(true);
        }
        else
        {
            ui->id_check->setCheckState(Qt::CheckState::Unchecked);
            ui->loadID->setEnabled(false);
        }
        if(nameExists)
        {
            ui->name_check->setCheckState(Qt::CheckState::PartiallyChecked);
            ui->loadName->setEnabled(true);
        }
        else
        {
            ui->name_check->setCheckState(Qt::CheckState::Unchecked);
            ui->loadName->setEnabled(false);
        }

    }




}

void remoteAssist::tweakTable()
{
    model->setHorizontalHeaderLabels( QStringList() << "ID" << "Name " );
    ui->visitorsTableView->setColumnHidden(2,true);
    ui->visitorsTableView->setColumnHidden(3,true);
    ui->visitorsTableView->setColumnHidden(4,true);
    ui->visitorsTableView->setColumnHidden(5,true);
    ui->visitorsTableView->setColumnHidden(6,true);
    ui->visitorsTableView->setColumnHidden(7,true);
    ui->visitorsTableView->setColumnHidden(8,true);
    ui->visitorsTableView->setColumnHidden(9,true);
    ui->visitorsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->visitorsTableView->horizontalHeader()->setStretchLastSection( true );
    ui->visitorsTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->visitorsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->visitorsTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->visitorsTableView->setSelectionBehavior(QAbstractItemView::SelectRows );

    ui->visitorsTableView->selectRow(0);

}

void remoteAssist::on_visitorsTableView_clicked(const QModelIndex &index)
{
    showVisitor(index,index);
}

void remoteAssist::searchByID()
{
    search(ui->_id->text());
}

void remoteAssist::searchByName()
{
    search(ui->_name->text());
}

void remoteAssist::searchByTel()
{
    search(ui->_tel->text());
}


void remoteAssist::on_visitorsTableView_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    Visitor visitor = getVisitor(row);
    createVisitor(visitor);
    close();
}

void remoteAssist::on_loadID_clicked()
{

}

void remoteAssist::on_loadName_clicked()
{

}
