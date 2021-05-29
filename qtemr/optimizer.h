// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <QObject>
#include "sqlbase.h"
#include "sqlcore.h"
#include "sqlextra.h"

class optimizer : public QObject
{
    Q_OBJECT
public:
    explicit optimizer(QObject *parent = nullptr);
    ~optimizer();
    void integrityCheck();
    void vacuum();
    void setDatabases(const bool &patients, const bool &core, const bool &drugs);
    void setQuick(const bool &c);
    void WAL_CheckPoint(QString Mode);
    void terminate(bool flag);
signals:
    void status(QString,bool);
    void toggleProgress(bool);
private:
    sqlExtra *sqlextra;
    sqlBase *sqlbase;
    sqlCore *sqlcoreIndex;
    sqlCore *sqlcoreEye;
    bool db_patients;
    bool db_core;
    bool db_drugsindex;
    bool quick;
    bool abort;
public slots:
};

#endif // OPTIMIZER_H
