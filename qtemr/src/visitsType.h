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


    t_visitsType _Requests;
    _Requests.id = Requests;
    _Requests.name ="Requests";
    _Requests.price = 0;

    t_visitsType _Follow1;
    _Follow1.id = Follow1;
    _Follow1.name ="Follow1";
    _Follow1.price = prices.followUp1;

    t_visitsType _Follow2;
    _Follow2.id = Follow2;
    _Follow2.name ="Follow2";
    _Follow2.price = prices.followUp2;

    t_visitsType _Follow3;
    _Follow3.id = Follow3;
    _Follow3.name ="Follow3";
    _Follow3.price = prices.followUp3;

    t_visitsType _Follow4;
    _Follow4.id = Follow4;
    _Follow4.name ="Follow4";
    _Follow4.price = prices.followUp4;

    t_visitsType _Free;
    _Free.id = Free;
    _Free.name ="Free";
    _Free.price = 0;

    t_visitsType _Undefined;
    _Undefined.id = Undefined;
    _Undefined.name ="Undefined";
    _Undefined.price = 0;

    mVisitTypes << _NewVisit << _Requests << _Follow1 << _Follow2 << _Follow3 << _Follow4 << _Free << _Undefined;
    return  mVisitTypes;
}

inline QString getVisitType(int _vt){
    QList<t_visitsType> vistsList = getVisitTypes();
    for(const t_visitsType vt:vistsList){
        if(vt.id == _vt)
            return vt.name;
    }
    return getVisitType(Undefined);
}

inline double getVisitPrice(int _vt){
    QList<t_visitsType> vistsList = getVisitTypes();
    for(const t_visitsType vt:vistsList){
        if(vt.id == _vt)
            return vt.price;
    }
    return getVisitPrice(Undefined);
}

inline n_visitsType advance(int _vt){

    mSettings &vt_settings = mSettings::instance();
    int maxFollowUps = vt_settings.getMaxFollowUps();
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

        if(maxFollowUpsPerProblem == _vt ){
            return autoSetNewAfterMaxIsReached? NewVisit:(n_visitsType)maxFollowUps;
        }else{
            return (n_visitsType) _vt++;
        }
        break;
    default:
        return Undefined;
        break;
    }
    return Undefined;
}
}

#endif // VISITSTYPE_H
