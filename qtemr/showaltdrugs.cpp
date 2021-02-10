// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "showaltdrugs.h"
#include "ui_showaltdrugs.h"

showAltDrugs::showAltDrugs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showAltDrugs)
{
    ui->setupUi(this);
    resize(680,480);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    proxy_model = new QSortFilterProxyModel(this);
    proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_model->setFilterKeyColumn(0);
}

void showAltDrugs::setSelectedDrugName(QString name)
{
    drugsTableCurrentSelectedDrugName = name;
}

showAltDrugs::~showAltDrugs()
{
    delete ui;
    delete proxy_model;
}

void showAltDrugs::setModel(QStandardItemModel *model)
{
    proxy_model->setSourceModel(model);
    ui->tableView->setModel(proxy_model);
    ui->tableView->setColumnWidth(0,280);
    ui->tableView->setColumnWidth(1,50);
    ui->lineEdit->clear();
    ui->lineEdit->setFocus(Qt::OtherFocusReason);
}

void showAltDrugs::setLabel(QString label)
{
    ui->filters->setText(label);
}

void showAltDrugs::on_tableView_activated(const QModelIndex &index)
{
    QString tradeName = index.sibling(index.row(),0).data(Qt::DisplayRole).toString();
    QMessageBox msgbox;
    int reply = msgbox.question(this,"Confirmation",QString("Are you sure you want to replace <b> %1 </b> with <b> %2 </b>").arg(drugsTableCurrentSelectedDrugName).arg(tradeName),QMessageBox::Yes,QMessageBox::No);
    switch ( reply )
    {
    case QMessageBox::No:
        return;
        break;
    case QMessageBox::Yes:
        emit replaceDrug(tradeName);
        close();
        break;
    default:
       break;
    }  
}

void showAltDrugs::on_lineEdit_textChanged(const QString &arg1)
{
    proxy_model->setFilterWildcard(arg1);
}

void showAltDrugs::keyPressEvent(QKeyEvent *keyevent)
{
    if(keyevent->key() == Qt::Key_Escape)
        close();
    QWidget::keyReleaseEvent(keyevent);
}
