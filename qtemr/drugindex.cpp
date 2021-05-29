// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "drugindex.h"
#include "ui_drugindex.h"

drugIndex::drugIndex(QWidget *parent) :
    mDialog(parent),
    ui(new Ui::drugIndex)
{
    ui->setupUi(this);
    drugsdb = msettings.getDefaultDrugsDatabase();
    sqlcoreIndex = new sqlCore(DRUGSINDEXPATH,this,"qt_sql_coreIndex_drugsIndex");
    sqlcoreEye = new sqlCore(DRUGEYEPATH,this,"qt_sql_coreEye_drugsIndex");
    QLocale locale("en_US");
    ui->updated->setText(locale.toString(QDate::fromString(QString::number(sqlcoreIndex->getDrugsDatabaseVersion()),"yyMMdd"),"MMMM,yy"));
    proxy_model = new mSortFilterProxyModel(this);
    QTimer::singleShot(0,this,SLOT(load()));
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    ui->DrugsDatabase->setCurrentIndex(drugsdb);
}

drugIndex::~drugIndex()
{
    sqlcoreIndex->optimize();
    sqlcoreEye->optimize();
    delete sqlcoreIndex;
    delete sqlcoreEye;
    QSqlDatabase::removeDatabase("qt_sql_coreIndex_drugsIndex");
    QSqlDatabase::removeDatabase("qt_sql_coreEye_drugsIndex");
    delete proxy_model;
    delete ui;
}


void drugIndex::on_closeButton_clicked()
{
    this->close();
}

void drugIndex::on_search_textChanged(const QString &arg1)
{
    //proxy_model->setFilterRegExp(arg1);
    proxy_model->setFilterWildcard(arg1);
}

void drugIndex::on_tradeName_clicked(bool status)
{
    ui->search->setFocus(Qt::OtherFocusReason);
    if ( status)
    {
        filterColumn = 0;
        proxy_model->setFilterKeyColumn(filterColumn);
    }
}


void drugIndex::on_genericName_clicked(bool status)
{
    ui->search->setFocus(Qt::OtherFocusReason);
    if ( status)
    {
        filterColumn = 1;
        proxy_model->setFilterKeyColumn(filterColumn);
    }

}

void drugIndex::on_indication_clicked(bool status)
{
    ui->search->setFocus(Qt::OtherFocusReason);
    if ( status)
    {
        filterColumn = 3;
        proxy_model->setFilterKeyColumn(filterColumn);
    }
}

void drugIndex::setCategory(QString category)
{
    proxy_model->setCategory(category);
    proxy_model->setFilterFixedString(ui->search->text());
    toggleResetButton();
}

void drugIndex::setManufacturer(QString manufacturer)
{
    proxy_model->setManufacturer(manufacturer);
    proxy_model->setFilterFixedString(ui->search->text());
    toggleResetButton();
}

void drugIndex::setForm(QString form)
{
    proxy_model->setForm(form);
    proxy_model->setFilterFixedString(ui->search->text());
    toggleResetButton();
}

void drugIndex::setResultsCount(QModelIndex,int,int)
{
     ui->resultsCount->setText(QString("<b>%1</b>").arg(proxy_model->rowCount()));
}



void drugIndex::on_resetButton_clicked()
{
    ui->categories->setCurrentIndex(0);
    ui->form->setCurrentIndex(0);
    ui->manufacturer->setCurrentIndex(0);
}

void drugIndex::toggleResetButton()
{
    ui->search->setFocus(Qt::OtherFocusReason);
    bool c = ( ui->categories->currentIndex() != 0 ) ? true:false ;
    bool f = ( ui->form->currentIndex() != 0 ) ? true:false ;
    bool m = ( ui->manufacturer->currentIndex() != 0 ) ? true:false ;
    ui->resetButton->setEnabled(( m | c | f ));
}

void drugIndex::setFilters()
{
    ui->categories->insertItem(0,"All Drugs");
    ui->manufacturer->insertItem(0,"All Companies");
    ui->form->insertItem(0,"All Forms");

    sqlCore::filters f;
    if(drugsdb == mSettings::Database::Standard)
        f = sqlcoreIndex->getFilters();
    else if (drugsdb == mSettings::Database::drugEye)
        f = sqlcoreEye->getFilters();

    ui->categories->insertItems(1,f.categories);
    ui->manufacturer->insertItems(1,f.companies);
    ui->form->insertItems(1,f.forms);
    ui->resultsCount->setText(QString("<b>%1</b>").arg(proxy_model->rowCount()));
}

void drugIndex::load()
{
    loadComplete = false;
    if(drugsdb != mSettings::Database::drugEye)
        model = sqlcoreIndex->getDrugsIndexModel();
    else
        model = sqlcoreEye->getDrugsIndexModel();

    ui->tradeName->setChecked(true);
    ui->indexTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->indexTable->horizontalHeader()->setStretchLastSection( true );
    ui->indexTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->indexTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->indexTable->setSelectionBehavior(QAbstractItemView::SelectRows );
    filterColumn = 0;
    model->setSortRole(Qt::EditRole);
    proxy_model->setFilterKeyColumn(filterColumn);
    proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_model->setSourceModel(model);
    proxy_model->setCategory("All Drugs");
    proxy_model->setManufacturer("All Companies");
    proxy_model->setForm("All Forms");
    ui->indexTable->setModel(proxy_model);
    ui->indexTable->setColumnWidth(0,300);
    ui->indexTable->setColumnWidth(1,250);
    ui->indexTable->sortByColumn(0,Qt::AscendingOrder);
    ui->indexTable->hideColumn(3);
    ui->indexTable->hideColumn(4);
    ui->indexTable->hideColumn(5);
    ui->indexTable->setWordWrap(false);
    ui->indexTable->setItemDelegate(new DrugsIndexPriceItemDelegate(this));
    connect(ui->categories,SIGNAL(currentIndexChanged(QString)),this,SLOT(setCategory(QString)));
    connect(ui->manufacturer,SIGNAL(currentIndexChanged(QString)),this,SLOT(setManufacturer(QString)));
    connect(ui->form,SIGNAL(currentIndexChanged(QString)),this,SLOT(setForm(QString)));
    connect(proxy_model,SIGNAL(rowsRemoved(QModelIndex,int,int)),this,SLOT(setResultsCount(QModelIndex,int,int)));
    connect(proxy_model,SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(setResultsCount(QModelIndex,int,int)));
    toggleResetButton();
    setFilters();
    loadComplete = true;
}

void drugIndex::on_DrugsDatabase_currentIndexChanged(int index)
{
    if(!loadComplete || drugsdb == index)
        return;

    drugsdb = (mSettings::Database) index;
    model->clear();
    ui->form->clear();
    ui->manufacturer->clear();
    ui->categories->clear();
    load();
}
