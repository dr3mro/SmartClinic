// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef WM_PATIENTNAMESCOMPLETERLOADER_H
#define WM_PATIENTNAMESCOMPLETERLOADER_H

#include <QObject>
#include <QRandomGenerator>
#include "sqlbase.h"

class wm_patientnamesCompleterLoader : public QObject
{
    Q_OBJECT
public:
    explicit wm_patientnamesCompleterLoader(QObject *parent = nullptr);
    ~wm_patientnamesCompleterLoader();
public slots:
    QStringList Work();
private:
    sqlBase *sqlbase;
    QString connectionName;
    
signals:

public slots:
};

#endif // WM_PATIENTNAMESCOMPLETERLOADER_H
