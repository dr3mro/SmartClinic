// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mergedlg.h"
#include "ui_mergedlg.h"

MergeDlg::MergeDlg(QWidget *parent) :
    mDialog(parent),
    ui(new Ui::MergeDlg)
{
    ui->setupUi(this);
    sqlbase = new sqlBase(this,"qt_sql_base_merge",false);
    this->setStyleSheet(settings.themeMaker());
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    connect(ui->cbAccept,SIGNAL(toggled(bool)),ui->btnApply,SLOT(setEnabled(bool)));

    int maxID = sqlbase->getPatientIndexLength()-1;
    valid = maxID>0;
    ui->cb_all->setChecked(true);

    ui->toID->setMaximum(maxID);
    ui->fromID->setMaximum(maxID);
}

MergeDlg::~MergeDlg()
{
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase("qt_sql_base_merge");
    delete ui;
}


void MergeDlg::on_closeButton_clicked()
{
    this->close();
}

void MergeDlg::on_btnApply_clicked()
{
    if(!valid)
    {
        ui->status->setText("Failed: Invalid patient ID.");
        return;
    }

    int fromID = ui->fromID->value();
    int toID = ui->toID->value();

    if(fromID==toID)
    {
        ui->status->setText("Failed: Cannot move visits of same ID.");
        return;
    }


    int reply = msgbox.question(this,"Message",
                                 "Are you Sure? <i>This Can't be undone!</i> ",
                                 QMessageBox::Yes,QMessageBox::No,true);


    if (reply == QMessageBox::No)
        return;


    bool state = sqlbase->copyVisit2ID(fromID,toID,getSelectedVisits());
    bool onSuccessDelete = ui->cb_delorigin->isChecked();
    bool deleteStatus=false;

    if(state && onSuccessDelete)
        deleteStatus = sqlbase->deletePatientRecord(fromID);

    ui->status->setText((state && deleteStatus)? "Success!":"Error!.");

    loadVisits();

    emit loadThisPatient(toID);
    emit reloadPatientsList();
    emit toggleEditMode(false);
}

void MergeDlg::on_cb_all_toggled(bool checked)
{
    ui->visits->setHidden(checked);
    adjustSize();
    wm.centerOnScreen(this);
    loadVisits();
}

QStringList MergeDlg::getSelectedVisits()
{
    QStringList _selectedVisits;
    QList<QListWidgetItem*> list;

    if(ui->cb_all->isChecked())
    {
        int rows = ui->visits->count();
        for(int r=0;r<rows;r++)
        {
            list.append(ui->visits->item(r));
        }
    }
    else
    {
        list = ui->visits->selectedItems();
    }


    foreach (QListWidgetItem *item, list) {
        _selectedVisits.append(item->text());
    }
    return _selectedVisits;
}

void MergeDlg::loadVisits()
{
    int fromID = ui->fromID->value();
    QList<QPair<QString, QString> > visitList = sqlbase->getListVisitsType(fromID);

    ui->visits->clear();

    QPair<QString,QString> visit;
    foreach (visit, visitList) {
        ui->visits->addItem(visit.first);
    }
}

void MergeDlg::on_fromID_valueChanged(int)
{
    loadVisits();
}
