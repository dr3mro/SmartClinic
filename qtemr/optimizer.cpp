// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "optimizer.h"

optimizer::optimizer(QObject *parent) : QObject(parent)
{
    sqlextra = new sqlExtra(this,"qt_sql_extra_Optimizer_connection",false);
    sqlbase = new sqlBase(this,"qt_sql_base_Optimizer_connection",false);
    sqlcoreIndex = new sqlCore(DRUGSINDEXPATH,this,"qt_sql_coreIndex_Optimizer_connection");
    sqlcoreEye = new sqlCore(DRUGEYEPATH,this,"qt_sql_coreEye_Optimizer_connection");
}

optimizer::~optimizer()
{
    sqlextra->optimize();
    delete sqlextra;
    sqlbase->optimize();
    delete sqlbase;
    sqlcoreIndex->optimize();
    delete sqlcoreIndex;
    sqlcoreEye->optimize();
    delete sqlcoreEye;
    QSqlDatabase::removeDatabase("qt_sql_extra_Optimizer_connection");
    QSqlDatabase::removeDatabase("qt_sql_base_Optimizer_connection");
    QSqlDatabase::removeDatabase("qt_sql_coreIndex_Optimizer_connection");
    QSqlDatabase::removeDatabase("qt_sql_coreEye_Optimizer_connection");
}

void optimizer::integrityCheck()
{
    emit toggleProgress(true);
    if ( db_patients && !abort)
        emit status ("patients.db",sqlbase->integrityCheck(quick));

    if ( db_core && !abort)
        emit status ("core.db",sqlextra->integrityCheck(quick));

    if ( db_drugsindex && !abort){
        emit status ("drugs.db",sqlcoreIndex->integrityCheck(quick));
        emit status ("drugEye.db",sqlcoreEye->integrityCheck(quick));
    }
    emit toggleProgress(false);
}

void optimizer::vacuum()
{
    emit toggleProgress(true);
    if ( db_patients && !abort)
        emit status ("[vacuum]:patients.db",sqlbase->vacuum());

    if ( db_core && !abort)
        emit status ("[vacuum]:core.db",sqlextra->vacuum());

    if ( db_drugsindex && !abort){
        emit status ("[vacuum]:drugs.db",sqlcoreIndex->vacuum());
        emit status ("[vacuum]:drugEye.db",sqlcoreEye->vacuum());
    }
    emit toggleProgress(false);
}

void optimizer::setDatabases(const bool &patients, const bool &core, const bool &drugs)
{
    db_patients = patients;
    db_core = core;
    db_drugsindex = drugs;
}

void optimizer::setQuick(const bool &c)
{
    quick = c;
}

void optimizer::WAL_CheckPoint(QString Mode)
{
    sqlbase->WAL_CheckPoint(Mode);
    sqlextra->WAL_CheckPoint(Mode);
    sqlcoreIndex->WAL_CheckPoint(Mode);
    sqlcoreEye->WAL_CheckPoint(Mode);
}

void optimizer::terminate(bool flag)
{
    abort=flag;
}
