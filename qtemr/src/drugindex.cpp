#include "drugindex.h"
#include "ui_drugindex.h"

drugIndex::drugIndex(QWidget *parent) :
    mDialog(parent),
    ui(new Ui::drugIndex)
{
    ui->setupUi(this);
    sqlcore = new sqlCore(this,"qt_sql_core_drugsIndex");
    QLocale locale("en_US");
    ui->updated->setText(locale.toString(QDate::fromString(QString::number(sqlcore->getDrugsDatabaseVersion()),"yyMMdd").addYears(100),"dd-MMMM-yyyy"));
    proxy_model = new mSortFilterProxyModel(this);
    QTimer::singleShot(0,this,SLOT(load()));
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    connect(sqlcore,&sqlCore::drugsDatabaseUpdateFinished,this,&drugIndex::onDrugsDatabaseChange);
    connect(sqlcore,&sqlCore::progress,this,&drugIndex::setMessageText);
    message.setMessage("<b> Please wait... </b>");
}

drugIndex::~drugIndex()
{
    sqlcore->optimize();
    delete sqlcore;
    QSqlDatabase::removeDatabase("qt_sql_core_drugsIndex");
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

    sqlCore::filters f = sqlcore->getFilters();
    ui->categories->insertItems(1,f.categories);
    ui->manufacturer->insertItems(1,f.companies);
    ui->form->insertItems(1,f.forms);
    ui->resultsCount->setText(QString("<b>%1</b>").arg(proxy_model->rowCount()));
}

void drugIndex::load()
{
    model = sqlcore->getDrugsIndexModel();
    ui->tradeName->setChecked(true);

    filterColumn = 0;
    model->setSortRole(Qt::EditRole);
    proxy_model->setFilterKeyColumn(filterColumn);
    proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_model->setSourceModel(model);
    proxy_model->setCategory("All Drugs");
    proxy_model->setManufacturer("All Companies");
    proxy_model->setForm("All Forms");
    ui->indexTable->setModel(proxy_model);
    // ui->indexTable->setColumnWidth(0,300);
    // ui->indexTable->setColumnWidth(1,250);

    connect(ui->categories,SIGNAL(currentTextChanged(QString)),this,SLOT(setCategory(QString)));
    connect(ui->manufacturer,SIGNAL(currentTextChanged(QString)),this,SLOT(setManufacturer(QString)));
    connect(ui->form,SIGNAL(currentTextChanged(QString)),this,SLOT(setForm(QString)));
    connect(proxy_model,SIGNAL(rowsRemoved(QModelIndex,int,int)),this,SLOT(setResultsCount(QModelIndex,int,int)));
    connect(proxy_model,SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(setResultsCount(QModelIndex,int,int)));
    toggleResetButton();
    setFilters();

    ui->indexTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->indexTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->indexTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    // ui->indexTable->horizontalHeader()->setStretchLastSection( true );
    ui->indexTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    ui->indexTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->indexTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->indexTable->setSelectionBehavior(QAbstractItemView::SelectRows );
    ui->indexTable->sortByColumn(0,Qt::AscendingOrder);
    ui->indexTable->hideColumn(3);
    ui->indexTable->hideColumn(4);
    ui->indexTable->hideColumn(5);
    ui->indexTable->setWordWrap(false);
    ui->indexTable->setItemDelegate(new DrugsIndexPriceItemDelegate(this));
}



void drugIndex::on_updateButton_clicked()
{
    QTcpSocket sock;
    sock.connectToHost("www.google.com", 80);
    bool connected = sock.waitForConnected(1000);//ms

    if (!connected)
    {
        QMessageBox::information(nullptr,"Error",QString("%1 cannot access the internet, Please check your connection.").arg(APPNAME));
        sock.abort();
        return;
    }
    sock.close();

    int reply  = QMessageBox::question(nullptr,"Upadating drugs database","Are you sure that you want to update drugs index database?",QMessageBox::Button::Yes,QMessageBox::Button::No);
    if(reply == QMessageBox::Button::No)
        return;
    message.show();
    sqlcore->updateDrugsDatabase();
}


void drugIndex::on_resetDatabaseButton_clicked()
{
    int reply  = QMessageBox::question(nullptr,"Reseting drugs database","Are you sure that you want to reset the drugs database to factory version?",QMessageBox::Button::Yes,QMessageBox::Button::No);
    if(reply == QMessageBox::Button::No)
        return;

    message.show();
    QFile resDrugsdb(":/databases/db");
    QFile drugsdb("./data/drugs.db");
    resDrugsdb.open(QIODevice::ReadOnly);
    QByteArray dbArray = resDrugsdb.readAll();
    drugsdb.open(QIODevice::WriteOnly);
    drugsdb.write(dbArray);
    drugsdb.close();
    resDrugsdb.close();
    onDrugsDatabaseChange(true);
}

void drugIndex::onDrugsDatabaseChange(bool success)
{
    if(success){
        QMessageBox::information(nullptr,"Done",QString("%1 will now quit to reload the new changes of drugs index.").arg(APPNAME));
        qApp->quit();
    }else{
        QMessageBox::information(nullptr,"Done","Updating drugs index Database failed! Try Again later.");
    }
    message.hide();
}

void drugIndex::setMessageText(const QString &status)
{
    message.setMessage(status);
}


