// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "msurgicalnotes.h"

mSurgicalNotes::mSurgicalNotes(QWidget *)
{
    model = new QStandardItemModel(this);
    sqlbase = new sqlBase(this,"qt_sql_base_surgnotes",false);
}

void mSurgicalNotes::fillTable(int ID)
{
    model = sqlbase->readSurgNotes(ID,model);
    setModel(model);
    this->hideColumn(0);
    this->hideColumn(1);
    this->hideColumn(4);
    emit disableDeleteEditButton();
}


mSurgicalNotes::~mSurgicalNotes()
{
    delete model;
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase("qt_sql_base_surgnotes");
}
