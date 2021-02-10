// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "dieteditor.h"
#include "ui_dieteditor.h"

DietEditor::DietEditor(QWidget *parent) :
    mDialog(parent),
    sqlextra (new sqlExtra(this,"qt_sql_extra_dietEditor_connection",false)),
    ui(new Ui::DietEditor)
{
    ui->setupUi(this);
    emit loadCompleters();

    dietModel = sqlextra->GetDietsModel();

    ui->dietList->setModel(dietModel);
    ui->dietList->hideColumn(1);
    ui->dietList->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->lineEdit->setHidden(true);
    setEditable(false);
    ui->buttonEdit->setEnabled(false);
    ui->buttonDelete->setEnabled(false);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

}

DietEditor::~DietEditor()
{
    delete dietModel;
    sqlextra->optimize();
    delete sqlextra;
    QSqlDatabase::removeDatabase("qt_sql_extra_dietEditor_connection");
    delete ui;
}

void DietEditor::on_dietList_clicked(const QModelIndex &index)
{
    ui->dietEdit->setHtml( dietModel->data(index.sibling(index.row(),1)).toString());
    ui->buttonDelete->setEnabled(index.row() >= 0);
    ui->buttonEdit->setEnabled(index.row() >= 0);
}

void DietEditor::on_buttonAdd_clicked()
{
    if (ui->lineEdit->isVisible())
        ui->lineEdit->hide();
    else
        ui->lineEdit->show();

    ui->lineEdit->setFocus(Qt::OtherFocusReason);

}

void DietEditor::on_lineEdit_editingFinished()
{
    ui->lineEdit->hide();
}


void DietEditor::on_buttonEdit_toggled(bool checked)
{
    setEditable(checked);
}

void DietEditor::on_ButtonSave_clicked()
{
    QString text = ui->dietEdit->toHtml();
    QModelIndex index = ui->dietList->selectionModel()->currentIndex();
    int row = index.row();
    dietModel->setData(index.sibling(row,1),QVariant(text));
    ui->buttonEdit->toggle();
}

void DietEditor::on_buttonDelete_clicked()
{
    int reply = QMessageBox::question(0,"Confirm","Are you sure you want to delete the selected diet?",
                                      QMessageBox::Yes,QMessageBox::No);
    if (reply == QMessageBox::No)
        return;

    QModelIndex index = ui->dietList->selectionModel()->currentIndex();
    int row = index.row();
    dietModel->removeRow(row);
    dietModel->select();
}

void DietEditor::on_lineEdit_returnPressed()
{
    QSqlRecord rec (dietModel->record());
    QString diet = ui->lineEdit->text().simplified();
    rec.setValue(0,QVariant(diet));
    rec.setValue(1,QVariant(diet));
    dietModel->insertRecord(-1,rec);
    dietModel->submitAll();
}

void DietEditor::setEditable(bool state)
{
    ui->dietList->setEnabled(!state);
    ui->dietEdit->setReadOnly(!state);
    ui->buttonAdd->setEnabled(!state);
    ui->buttonDelete->setEnabled(!state);
    ui->ButtonSave->setEnabled(state);
    //ui->dietList->clearSelection();
}

void DietEditor::on_closeButton_clicked()
{
    close();
}
