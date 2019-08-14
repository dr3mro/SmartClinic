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
    void setDatabases(bool &patients, bool &core, bool &drugs);
    void setQuick(bool &c);
    void WAL_CheckPoint(QString Mode);
    void terminate(bool flag);
signals:
    void status(QString,bool);
    void toggleProgress(bool);
private:
    sqlExtra *sqlextra;
    sqlBase *sqlbase;
    sqlCore *sqlcore;
    bool db_patients;
    bool db_core;
    bool db_drugsindex;
    bool quick;
    bool abort;
public slots:
};

#endif // OPTIMIZER_H
