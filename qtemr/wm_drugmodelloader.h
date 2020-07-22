#ifndef WM_DRUGMODELLOADER_H
#define WM_DRUGMODELLOADER_H

#include <QObject>
#include "drugsitemmodel.h"
#include "sqlbase.h"
#include <QRandomGenerator>
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
    QRandomGenerator generator;
public slots:
    DrugsItemModel *Work();
};

#endif // WM_DRUGMODELLOADER_H
