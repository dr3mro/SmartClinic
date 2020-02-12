#include "favouritedrugseditor.h"
#include "ui_favouritedrugseditor.h"

favouriteDrugsEditor::favouriteDrugsEditor(QWidget *parent) :
    mDialog(parent),
    ui(new Ui::favouriteDrugsEditor)
{
    ui->setupUi(this);
    setModal(true);
    sqlextra = new sqlExtra(this,"favourites_editor",false);
    doseDelegate = new favouriteDoseDelegate(ui->tableView);
    model = sqlextra->readStandardDoses();
    proxy_model = new QSortFilterProxyModel(this);
    proxy_model->setFilterKeyColumn(0);
    proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_model->setSourceModel(model);
    ui->tableView->setModel(proxy_model);
    ui->tableView->setColumnWidth(0,320);
    ui->tableView->setItemDelegate(doseDelegate);
    connect ( ui->tradeName,SIGNAL(textChanged(QString)),this,SLOT(addButtonToggler(QString)));
    connect ( ui->dose,SIGNAL(textChanged(QString)),this,SLOT(addButtonToggler(QString)));
    connect ( ui->tradeName,SIGNAL(textChanged(QString)),this,SLOT(setFilter(QString)));
    connect ( ui->closeButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect ( ui->dose,SIGNAL(returnPressed()),this,SLOT(on_ButtonNew_clicked()));
    connect ( model,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(dataChanged(QModelIndex,QModelIndex,QVector<int>)));
    emit loadCompleters();
    while(model->canFetchMore())
        model->fetchMore();
    ui->rowsCount->setText(QString::number(model->rowCount()));
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

favouriteDrugsEditor::~favouriteDrugsEditor()
{
    sqlextra->optimize();
    delete sqlextra;
    QSqlDatabase::removeDatabase("favourites_editor");
    delete doseDelegate;
    delete proxy_model;
    delete ui;
}

void favouriteDrugsEditor::on_ButtonDel_clicked()
{
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    int row = index.row();
    QString selectedDrug = ui->tableView->model()->data(index.sibling(row,0),Qt::DisplayRole).toString();
    sqlextra->deleteDefaultDrugDose(selectedDrug);
    model->select();
    while (model->canFetchMore())
        model->fetchMore();
    ui->ButtonDel->setEnabled(false);
    emit reloadCompleter();
    ui->rowsCount->setText(QString::number(model->rowCount()));
}

void favouriteDrugsEditor::on_tableView_clicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    ui->ButtonDel->setEnabled(true);
}

void favouriteDrugsEditor::addButtonToggler(QString arg1)
{
    Q_UNUSED(arg1)
    QString tradename = ui->tradeName->text().simplified();
    QString dose = ui->dose->text().simplified();
    ui->ButtonNew->setDisabled( (tradename.length() < 2 || dose.length() < 2 ));
    ui->dose->setDisabled((tradename.length() < 2));
}


void favouriteDrugsEditor::on_ButtonNew_clicked()
{
    QString tradeName = ui->tradeName->text().simplified();
    QString dose = ui->dose->text().simplified();
    ui->tradeName->clear();
    ui->dose->clear();

    QStringList list;
    int rows = model->rowCount();
    for ( int row=0; row<rows; row++)
    {
        list << model->data(model->index(row,0)).toString();
    }
    QMessageBox msgbox;

    if ( list.contains(tradeName,Qt::CaseInsensitive))
    {
        msgbox.information(nullptr,"Error","Error adding this item, alreay exisits!");
        return;
    }
    else
    {
        if (!sqlextra->addDefaultDrugDose(tradeName,dose))
        {
            msgbox.information(nullptr,"Error","Error adding this item, unknown Error!");
            return;
        }
        else
        {
            model->select();
            sqlextra->addToAutoComplete("doses",dose);
            sqlextra->addToAutoComplete("drugs",tradeName);
            while (model->canFetchMore())
                model->fetchMore();
            emit reloadCompleter();
            ui->rowsCount->setText(QString::number(model->rowCount()));
        }

    }
    ui->tradeName->setFocus(Qt::OtherFocusReason);
    ui->tableView->scrollToBottom();
}

void favouriteDrugsEditor::dataChanged(QModelIndex topLeft, QModelIndex bottomRight, QVector<int> vect)
{
    Q_UNUSED(bottomRight)
    Q_UNUSED(vect)
    QMessageBox msgbox;
    QString modifiedString = topLeft.data(Qt::DisplayRole).toString();
    int length = modifiedString.length();
    if (length < 2)
    {
        msgbox.information(nullptr,"Error","Error modifying this item, insufficient length!");
        model->revertAll();
    }
    else
    {
        model->submitAll();
    }
    model->select();
    ui->rowsCount->setText(QString::number(model->rowCount()));
}

void favouriteDrugsEditor::setFilter(QString arg1)
{
    proxy_model->setFilterWildcard(arg1);
}

