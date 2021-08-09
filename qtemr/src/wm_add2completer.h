// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef WM_ADD2COMPLETER_H
#define WM_ADD2COMPLETER_H

#include <QObject>
#include <QRandomGenerator>
#include "sqlextra.h"
#include "datahelper.h"
#include "sqlbase.h"

class wm_add2Completer : public QObject
{
    Q_OBJECT
public:
    explicit wm_add2Completer(QObject *parent = nullptr);
    ~wm_add2Completer();
    void setVisitData(const sqlBase::Visit &v);
    void setPatientData(const sqlBase::Patient &p);
    void setHusband(QString h);
    void setMode(bool b);
    void save2Dict(QStringList dict);
signals:
    void finished();
public slots:
    void vWork();
    void pWork();
private:
    int r;
    sqlBase::Visit visit;
    sqlBase::Patient patient;
    bool autocompletebyword;
    void saveDicts(QStringList dicts);
    QStringList splitDict(QString &dict);
    QString connectionName;
    sqlExtra *sqlextra;
    QString husband;
};

#endif // WM_ADD2COMPLETER_H
