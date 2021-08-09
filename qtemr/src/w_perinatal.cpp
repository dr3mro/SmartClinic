// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "w_perinatal.h"
#include "ui_w_perinatal.h"

w_perinatal::w_perinatal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::w_perinatal)
{
    ui->setupUi(this);
    sqlbase = new sqlBase(this,"w_perinatal",false);
}

void w_perinatal::clear()
{
    ui->pregLine->clear();
    ui->laborLine->clear();
    ui->NICUline->clear();
    ui->dietLine->clear();
    ui->GAline->clear();
    ui->Gline->clear();
    ui->Pline->clear();
    ui->Lline->clear();
}

void w_perinatal::load(int id)
{
    ID = id;
    sqlBase::perinatal pnatal = sqlbase->getPerinatal(id);
    ui->pregLine->setText(pnatal.pregLine);
    ui->laborLine->setText(pnatal.laborLine);
    ui->NICUline->setText(pnatal.NICULine);
    ui->dietLine->setText(pnatal.dietLine);
    ui->GAline->setText(pnatal.GALine);
    ui->Gline->setText(pnatal.GLine);
    ui->Pline->setText(pnatal.PLine);
    ui->Lline->setText(pnatal.LLine);
}

sqlBase::perinatal w_perinatal::getPerinatal(int id)
{
    sqlBase::perinatal pnatal;
    pnatal.ID = id;
    pnatal.pregLine = ui->pregLine->text().simplified();
    pnatal.laborLine = ui->laborLine->text().simplified();
    pnatal.NICULine = ui->NICUline->text().simplified();
    pnatal.dietLine = ui->dietLine->text().simplified();
    pnatal.GALine = ui->GAline->text().simplified();
    pnatal.GLine = ui->Gline->text().simplified();
    pnatal.PLine = ui->Pline->text().simplified();
    pnatal.LLine = ui->Lline->text().simplified();
    return pnatal;
}

bool w_perinatal::isPnatalModified()
{
    sqlBase::perinatal savedPnatal = sqlbase->getPerinatal(ID);
    sqlBase::perinatal visisblePnatal = getPerinatal(ID);
    return(savedPnatal!=visisblePnatal);
}

void w_perinatal::setID(int id)
{
    ID = id;
}

w_perinatal::~w_perinatal()
{
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase("w_perinatal");
    delete ui;
}
