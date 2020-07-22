#ifndef WM_VISITSAVER_H
#define WM_VISITSAVER_H

#include <QObject>
#include "sqlbase.h"
#include <QRandomGenerator>
class wm_visitSaver : public QObject
{
    Q_OBJECT
public:
    explicit wm_visitSaver(QObject *parent = nullptr);
    ~wm_visitSaver();
    void setVisitData(sqlBase::visitData &data);

signals:
    void finished();
    void finishedSavingState(bool);
public slots:
    void Work();
private:
    sqlBase::visitData visitData;
    QString tableName;
    sqlBase *sqlbase=nullptr;
    QString connectionName;
    QRandomGenerator generator;

};

#endif // WM_VISITSAVER_H
