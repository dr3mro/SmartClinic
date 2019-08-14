#include "wm_investtooltiploader.h"

wm_investTooltipLoader::wm_investTooltipLoader(QObject *parent) : QObject(parent)
{

}

void wm_investTooltipLoader::setInvestigationsModel(InvestModel *investModel)
{
    model = investModel;
}

void wm_investTooltipLoader::setScale(int &s)
{
    scale = s;
}


InvestModel *wm_investTooltipLoader::Work()
{
    int rows = model->rowCount();
    QString name,path,html;
    killloopFlag = false;
    for(int r=0;r<rows;r++)
    {
        name = model->item(r,1)->text();
        path = model->item(r,3)->text();
        html = invIconHelper::getInvestigationTooltip(path,name,scale);

        QCoreApplication::processEvents();
        if(killloopFlag)
        {
            return model;
        }
        else
        {
            if(model->hasIndex(r,1))
                model->item(r,1)->setToolTip(html);
        }
    }

    return model;
}

void wm_investTooltipLoader::killloop()
{
    killloopFlag = true;
}
