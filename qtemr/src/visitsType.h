#ifndef VISITSTYPE_H
#define VISITSTYPE_H

#include <QString>
#include <QList>
#include "msettings.h"

namespace VisitsType {

enum n_visitsType{
    NewVisit=0,
    Follow1=1,
    Follow2=2,
    Follow3=3,
    Follow4=4,
    Free=5,
    Requests=6,
    Undefined=-1
};

struct t_visitsType{
    n_visitsType id;
    QString name;
    double price;
    QBrush color;
    QString symbole;
    QIcon icon;
};

inline QList<t_visitsType> getVisitTypes(){

    QList<t_visitsType> mVisitTypes;
    double price = 0;
    mSettings &vt_settings = mSettings::instance();
    mSettings::clinicPrices prices = vt_settings.getClinicPrices();


    t_visitsType _NewVisit;
    _NewVisit.id = NewVisit;
    _NewVisit.name ="NewVisit";
    _NewVisit.price = prices.newVisit;
    _NewVisit.color = QBrush(QColor::fromRgb(204,229,255));
    _NewVisit.symbole = "Ⓝ";
    _NewVisit.icon = QIcon(":/Graphics/newvisit");


    t_visitsType _Requests;
    _Requests.id = Requests;
    _Requests.name ="Requests";
    _Requests.price = 0;
    _Requests.color = QBrush(QColor::fromRgb(229,204,255));
    _Requests.symbole = "Ⓡ";
    _Requests.icon = QIcon(":/Graphics/fvisit");

    t_visitsType _Follow1;
    _Follow1.id = Follow1;
    _Follow1.name ="Follow 1";
    _Follow1.price = prices.followUp1;
    _Follow1.color = QBrush(QColor::fromRgb(255,255,204));
    _Follow1.symbole = "①";
    _Follow1.icon = QIcon(":/Graphics/fvisit");

    t_visitsType _Follow2;
    _Follow2.id = Follow2;
    _Follow2.name ="Follow 2";
    _Follow2.price = prices.followUp2;
    _Follow2.color = QBrush(QColor::fromRgb(229,255,204));
    _Follow2.symbole = "②";
    _Follow2.icon = QIcon(":/Graphics/fvisit");

    t_visitsType _Follow3;
    _Follow3.id = Follow3;
    _Follow3.name ="Follow 3";
    _Follow3.price = prices.followUp3;
    _Follow3.color = QBrush(QColor::fromRgb(204,255,204));
    _Follow3.symbole = "③";
    _Follow3.icon = QIcon(":/Graphics/fvisit");

    t_visitsType _Follow4;
    _Follow4.id = Follow4;
    _Follow4.name ="Follow 4";
    _Follow4.price = prices.followUp4;
    _Follow4.color = QBrush(QColor::fromRgb(204,255,229));
    _Follow4.symbole = "④";
    _Follow4.icon = QIcon(":/Graphics/fvisit");

    t_visitsType _Free;
    _Free.id = Free;
    _Free.name ="Free";
    _Free.price = 0;
    _Free.color = QBrush(QColor::fromRgb(255,255,255));
    _Free.symbole = "Ⓕ";
    _Free.icon = QIcon(":/Graphics/free");

    t_visitsType _Undefined;
    _Undefined.id = Undefined;
    _Undefined.name ="Undefined";
    _Undefined.price = 0;
    _Undefined.color = QBrush(QColor::fromRgb(255,255,255));
    _Undefined.symbole = "◯";
    _Undefined.icon = QIcon(":/Graphics/free");

    mVisitTypes << _NewVisit << _Requests << _Follow1 << _Follow2 << _Follow3 << _Follow4 << _Free << _Undefined;
    return  mVisitTypes;
}

inline QString getVisitType(const int & _vt){
    QList<t_visitsType> vistsList = getVisitTypes();
    for(const t_visitsType vt:vistsList){
        if(vt.id == _vt)
            return vt.name;
    }
    return getVisitType(Undefined);
}

inline int getVisitTypeIndex(const int & _vt){
    QList<t_visitsType> vistsList = getVisitTypes();
    int index = -1;
    for(const t_visitsType vt:vistsList){
        if(vt.id == _vt)
            return ++index;
        else
            index++;
    }
    return getVisitTypeIndex(Undefined);
}


inline double getVisitPrice(const int & _vt){
    QList<t_visitsType> vistsList = getVisitTypes();
    for(const t_visitsType vt:vistsList){
        if(vt.id == _vt)
            return vt.price;
    }
    return getVisitPrice(Undefined);
}

inline QBrush getVisitColor(const int & _vt){
    QList<t_visitsType> vistsList = getVisitTypes();
    for(const t_visitsType vt:vistsList){
        if(vt.id == _vt)
            return vt.color;
    }
    return getVisitColor(Undefined);
}

inline n_visitsType advance(int _vt){

    mSettings &vt_settings = mSettings::instance();
    int maxFollowUpsPerProblem = vt_settings.getMaxFollowUpsPerProblem();
    bool autoSetNewAfterMaxIsReached = vt_settings.autoSetNewAfterMaxFollowUpsPerProblem();

    switch (_vt) {
    case Free:
        return Free;
        break;

    case NewVisit:
    case Requests:
        return Follow1;
        break;

    case Follow1:
    case Follow2:
    case Follow3:
    case Follow4:

        if(_vt == maxFollowUpsPerProblem){
            return autoSetNewAfterMaxIsReached? NewVisit:(n_visitsType)maxFollowUpsPerProblem;
        }else{
            return (n_visitsType) ++_vt;
        }
        break;
    default:
        return Undefined;
        break;
    }
    return Undefined;
}

inline QString getVisitSymbole(const int & _vt){
    QList<t_visitsType> vistsList = getVisitTypes();
    for(const t_visitsType vt:vistsList){
        if(vt.id == _vt)
            return vt.symbole;
    }
    return getVisitSymbole(Undefined);
}

inline QString getVisitSymbole(const int & _i,const bool &isCaseClosed,const bool & noNextDateSpecified){
    VisitsType::n_visitsType vt;

    if(isCaseClosed || noNextDateSpecified)
        vt = NewVisit;
    else
        vt = VisitsType::advance(getVisitTypes().at(_i).id);

    //mDebug() << vt << " " << _i << " " << getVisitTypes().at(_i).id;
    return VisitsType::getVisitSymbole(vt);
}

inline QIcon getVisitIcon(const int & _vt)
{
    QList<t_visitsType> vistsList = getVisitTypes();
    for(const t_visitsType vt:vistsList){
        if(vt.id == _vt)
            return vt.icon;
    }
    return getVisitIcon(Undefined);
}

}

#endif // VISITSTYPE_H
