#ifndef WM_VISITLISTLOADER_H
#define WM_VISITLISTLOADER_H

#include <QObject>
#include "sqlbase.h"

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
    

public slots:
    QVector<sqlBase::visitItem> Work();

};

#endif // WM_VISITLISTLOADER_H
