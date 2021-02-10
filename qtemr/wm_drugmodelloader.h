// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef WM_DRUGMODELLOADER_H
#define WM_DRUGMODELLOADER_H

#include <QObject>
#include "drugsitemmodel.h"
#include "sqlbase.h"

class wm_drugModelLoader : public QObject
{
    Q_OBJECT
public:
    explicit wm_drugModelLoader(QObject *parent = nullptr);
    void setDrugsModel(DrugsItemModel *drugsModel);
    void setIDJulianDate(int mID,int mJulianDate);
    ~wm_drugModelLoader();

signals:

private:
    int ID;
    int julianDate;
    sqlBase *sqlbase;
    DrugsItemModel *model;
    QString connectionName;
    
public slots:
    DrugsItemModel *Work();
};

#endif // WM_DRUGMODELLOADER_H
