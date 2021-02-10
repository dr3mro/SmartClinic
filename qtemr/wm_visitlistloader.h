// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
