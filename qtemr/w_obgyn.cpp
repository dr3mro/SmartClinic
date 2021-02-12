// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "w_obgyn.h"
#include "ui_w_obgyn.h"

w_obGyn::w_obGyn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::w_obGyn)
{
    ui->setupUi(this);
    sqlbase = new sqlBase(this,"w_ObGyn",false);
    ui->LMP->setDate(QDate::currentDate());
    connect (ui->checkBoxMenoPause,SIGNAL(toggled(bool)),this,SLOT(toggleLMPdateBox(bool)));
}

void w_obGyn::clear()
{
    ui->gpa->clear();
    ui->fpal->clear();
    ui->menarche->clear();
    ui->cycle->setCurrentIndex(0);
    ui->checkBoxCyclePain->setChecked(false);
    ui->lastsfor->clear();
    ui->every->clear();
    ui->LMP->setDate(QDate::currentDate());
    ui->checkBoxMenoPause->setChecked(false);
    ui->husband->clear();
    ui->siblings->clear();
}

QStandardItemModel *w_obGyn::getSiblingsModel()
{
    return ui->siblings->getModel();
}

QString w_obGyn::getFPAL()
{
    return ui->fpal->text();
}

void w_obGyn::toggleEditMode(bool pEditMODE)
{
    ui->addSiblings->setEnabled(pEditMODE);
    ui->removeSiblings->setEnabled((ui->siblings->selectionModel()->currentIndex().row() >= 0 ) ? pEditMODE:false);
    ui->LMP->setEnabled(pEditMODE ? !ui->checkBoxMenoPause->isChecked():false);
    ui->fpalCalButton->setEnabled(pEditMODE);
    pEditingMode = pEditMODE;
}

void w_obGyn::toggleHeaders(bool state)
{
    if (state)
    {
        ui->siblings->horizontalHeader()->show();
        ui->siblings->verticalHeader()->show();
    }
    else
    {
        ui->siblings->horizontalHeader()->hide();
        ui->siblings->verticalHeader()->hide();
    }
}

sqlBase::obGyn w_obGyn::getObgyne(int id)
{
    sqlBase::obGyn og;

    og.ID = id;
    og.husband = ui->husband->toHtml();
    og.GPA = ui->gpa->text();
    og.FPAL = ui->fpal->text();
    og.menarche = ui->menarche->text();
    og.cycle = ui->cycle->currentIndex();
    og.cyclePain = ui->checkBoxCyclePain->isChecked();
    og.lastFor = ui->lastsfor->text();
    og.every = ui->every->text();
    og.LMP = ui->LMP->date().toJulianDay();
    og.menoPause = ui->checkBoxMenoPause->isChecked();

    this->ID = id;
    return og;
}

void w_obGyn::load(int _ID)
{
    sqlBase::obGyn og = sqlbase->getObGyn(_ID);
    ui->gpa->setText(og.GPA);
    ui->fpal->setText(og.FPAL);
    ui->menarche->setText(og.menarche);
    ui->cycle->setCurrentIndex(og.cycle);
    ui->lastsfor->setText(og.lastFor);
    ui->every->setText(og.every);
    ui->checkBoxCyclePain->setChecked(og.cyclePain);
    ui->LMP->setDate(QDate::fromJulianDay(og.LMP));
    ui->checkBoxMenoPause->setChecked(og.menoPause);
    ui->husband->setHtml(og.husband);
    ui->siblings->populateSiblings(_ID);
    this->ID = _ID;
}

bool w_obGyn::isObGynModified()
{
    sqlBase::obGyn savedObGyn = sqlbase->getObGyn(ID);
    sqlBase::obGyn visibleObGyn = getObgyne(ID);
    bool husbandModified = ui->husband->document()->isModified();
    return((savedObGyn!=visibleObGyn)||husbandModified);
}

void w_obGyn::setID(int id)
{
    ID = id;
}

QString w_obGyn::getHusbandHtml()
{
    return ui->husband->toHtml();
}

w_obGyn::~w_obGyn()
{
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase("w_ObGyn");
    delete ui;
}

void w_obGyn::syncLMPDateWithVisit(QDate date)
{
    int LMP = date.toJulianDay();
    sqlbase->updateLMP(ID,LMP);
    ui->LMP->setDate(date);
}

void w_obGyn::toggleLMPdateBox(bool checked)
{
    ui->LMP->setEnabled(!checked);
}

void w_obGyn::on_addSiblings_clicked()
{
    addSiblings addsiblings(ui->siblings->getSelectedRow(),ui->siblings->getSelectedRowContent(),this,false);
    connect (&addsiblings,SIGNAL(addSibling(const sqlBase::Sibling&)),ui->siblings,SLOT(appendRow(const sqlBase::Sibling&)));
    addsiblings.exec();
}

void w_obGyn::on_removeSiblings_clicked()
{
    int currentSelectedRow = ui->siblings->currentIndex().row();
    if( currentSelectedRow == -1 )
        return;
    else
        ui->siblings->removeRow(currentSelectedRow);

    ui->removeSiblings->setEnabled((ui->siblings->getRowCount() > 0));
    ui->editSiblingButton->setEnabled((ui->siblings->getRowCount() > 0));
}

void w_obGyn::on_fpalCalButton_clicked()
{
    ui->fpal->setText(ui->siblings->calculateFPAL());
    ui->gpa->setText(ui->siblings->calculateGPA());
}

void w_obGyn::on_siblings_clicked(const QModelIndex &index)
{
    if (index.row() >= 0 )
    {
        ui->removeSiblings->setEnabled(pEditingMode);
        ui->editSiblingButton->setEnabled(pEditingMode);
    }
}

void w_obGyn::on_editSiblingButton_clicked()
{
    addSiblings addsiblings(ui->siblings->getSelectedRow(),ui->siblings->getSelectedRowContent(),this,true);
    connect (&addsiblings,SIGNAL(editSibling(int,const sqlBase::Sibling&)),ui->siblings,SLOT(editRow(int,const sqlBase::Sibling&)));
    addsiblings.exec();
}
