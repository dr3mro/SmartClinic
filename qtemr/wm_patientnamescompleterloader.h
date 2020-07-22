#ifndef WM_PATIENTNAMESCOMPLETERLOADER_H
#define WM_PATIENTNAMESCOMPLETERLOADER_H

#include <QObject>
#include "sqlbase.h"
#include <QRandomGenerator>
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
    QRandomGenerator generator;
signals:

public slots:
};

#endif // WM_PATIENTNAMESCOMPLETERLOADER_H
