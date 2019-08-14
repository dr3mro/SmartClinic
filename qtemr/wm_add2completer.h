#ifndef WM_ADD2COMPLETER_H
#define WM_ADD2COMPLETER_H

#include <QObject>
#include "sqlextra.h"
#include "datahelper.h"
#include "sqlbase.h"

class wm_add2Completer : public QObject
{
    Q_OBJECT
public:
    explicit wm_add2Completer(QObject *parent = nullptr);
    ~wm_add2Completer();
    void setVisitData(sqlBase::Visit v);
    void setPatientData(sqlBase::Patient p);
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
    sqlExtra *sqlextra;
    QString connectionName;
    QString husband;
};

#endif // WM_ADD2COMPLETER_H
