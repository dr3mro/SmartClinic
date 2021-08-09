// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef WM_VISITSAVER_H
#define WM_VISITSAVER_H

#include <QObject>
#include <QRandomGenerator>
#include "sqlbase.h"

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
    

};

#endif // WM_VISITSAVER_H
