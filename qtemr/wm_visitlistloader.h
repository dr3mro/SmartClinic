#ifndef WM_VISITLISTLOADER_H
#define WM_VISITLISTLOADER_H

#include <QObject>
#include "sqlbase.h"
#include <QRandomGenerator>
class wm_visitListLoader : public QObject
{
    Q_OBJECT
public:
    explicit wm_visitListLoader(QObject *parent = nullptr);
    ~wm_visitListLoader();
    void setID(int id);
private:
    sqlBase *sqlbase;
    int ID;
    QString connectionName;
    QRandomGenerator generator;

public slots:
    QVector<sqlBase::visitItem> Work();

};

#endif // WM_VISITLISTLOADER_H
