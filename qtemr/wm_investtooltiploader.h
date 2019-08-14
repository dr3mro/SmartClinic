#ifndef WM_INVESTTOOLTIPLOADER_H
#define WM_INVESTTOOLTIPLOADER_H

#include <QObject>
#include <QCoreApplication>
#include "investmodel.h"
#include "inviconhelper.h"

class wm_investTooltipLoader : public QObject
{
    Q_OBJECT
public:
    explicit wm_investTooltipLoader(QObject *parent = nullptr);
    void setInvestigationsModel(InvestModel *investModel);
    void setScale(int &s);

signals:

public slots:
    InvestModel *Work();
    void killloop();
private:
    InvestModel *model;
    int scale;
    bool killloopFlag=false;

};

#endif // WM_INVESTTOOLTIPLOADER_H
