#include "visittypes.h"

VisitTypes::VisitTypes()
{
    t_visitsType _NewVisit;
    _NewVisit.id = NewVisit;
    _NewVisit.name ="NewVisit";
    _NewVisit.price = prices.newVisit;
    _NewVisit.color = QBrush(QColor::fromRgb(204,229,255));
    _NewVisit.symbole = "Ⓝ";
    _NewVisit.icon = QIcon(":/alphaNums/alphaNum/014-n.png");


    t_visitsType _Requests;
    _Requests.id = Requests;
    _Requests.name ="Requests";
    _Requests.price = 0;
    _Requests.color = QBrush(QColor::fromRgb(229,204,255));
    _Requests.symbole = "Ⓡ";
    _Requests.icon = QIcon(":/alphaNums/alphaNum/018-r.png");

    t_visitsType _Follow1;
    _Follow1.id = Follow1;
    _Follow1.name ="Follow 1";
    _Follow1.price = prices.followUp1;
    _Follow1.color = QBrush(QColor::fromRgb(255,255,204));
    _Follow1.symbole = "①";
    _Follow1.icon = QIcon(":/alphaNums/alphaNum/028-1.png");

    t_visitsType _Follow2;
    _Follow2.id = Follow2;
    _Follow2.name ="Follow 2";
    _Follow2.price = prices.followUp2;
    _Follow2.color = QBrush(QColor::fromRgb(229,255,204));
    _Follow2.symbole = "②";
    _Follow2.icon = QIcon(":/alphaNums/alphaNum/029-2.png");

    t_visitsType _Follow3;
    _Follow3.id = Follow3;
    _Follow3.name ="Follow 3";
    _Follow3.price = prices.followUp3;
    _Follow3.color = QBrush(QColor::fromRgb(204,255,204));
    _Follow3.symbole = "③";
    _Follow3.icon = QIcon(":/alphaNums/alphaNum/030-3.png");

    t_visitsType _Follow4;
    _Follow4.id = Follow4;
    _Follow4.name ="Follow 4";
    _Follow4.price = prices.followUp4;
    _Follow4.color = QBrush(QColor::fromRgb(204,255,229));
    _Follow4.symbole = "④";
    _Follow4.icon = QIcon(":/alphaNums/alphaNum/031-4.png");

    t_visitsType _Free;
    _Free.id = Free;
    _Free.name ="Free";
    _Free.price = 0;
    _Free.color = QBrush(QColor::fromRgb(255,255,255));
    _Free.symbole = "Ⓕ";
    _Free.icon = QIcon(":/alphaNums/alphaNum/006-f.png");

    t_visitsType _Undefined;
    _Undefined.id = Undefined;
    _Undefined.name ="Undefined";
    _Undefined.price = 0;
    _Undefined.color = QBrush(QColor::fromRgb(255,255,255));
    _Undefined.symbole = "◯";
    _Undefined.icon = QIcon(":/alphaNums/alphaNum/021-u.png");

    ui_VisitTypes << _NewVisit << _Requests << _Follow1 << _Follow2 << _Follow3 << _Follow4 << _Free << _Undefined;
    algo_VisitTypes << _NewVisit <<  _Follow1 << _Follow2 << _Follow3 << _Follow4 << _Free << _Requests << _Undefined;

}

VisitTypes::~VisitTypes()
{

}

VisitTypes &VisitTypes::instance()
{
    static VisitTypes s_instance;
    return s_instance;
}

VisitTypes::n_visitsType VisitTypes::advance(int _vt) const
{
    int maxFollowUpsPerProblem = settings.getMaxFollowUpsPerProblem();
    bool autoSetNewAfterMaxIsReached = settings.autoSetNewAfterMaxFollowUpsPerProblem();

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

QList<VisitTypes::t_visitsType> &VisitTypes::getVisitTypesListByUiIndex()
{
    return ui_VisitTypes;
}

QList<VisitTypes::t_visitsType> &VisitTypes::getVisitTypesListByAlgoIndex()
{
    return algo_VisitTypes;
}

VisitTypes::t_visitsType & VisitTypes::getVisitTypesByUiIndex(const int &index) const
{
    return const_cast<VisitTypes::t_visitsType &>(ui_VisitTypes.at(index));
}

VisitTypes::t_visitsType & VisitTypes::getVisitTypesByAlgoIndex(const int &index) const
{
    return const_cast<VisitTypes::t_visitsType &>(algo_VisitTypes.at(index));
}

int VisitTypes::getVisitIndexFromId(const n_visitsType &id) const
{
    int index = -1;
    for(const t_visitsType & vt:ui_VisitTypes){
        if(vt.id == id)
            return ++index;
        else
            index++;
    }
    return getVisitIndexFromId(Undefined);
}

QString VisitTypes::getVisitSymbole(const int &_i, const bool &isCaseClosed, const bool &noNextDateSpecified) const
{
    n_visitsType vt;

    if(isCaseClosed || noNextDateSpecified){
        vt = NewVisit;
    }else{
        vt = advance(ui_VisitTypes.at(_i).id);
    }
    //mDebug() << vt << " " << _i << " " << getVisitTypes().at(_i).id;
    return algo_VisitTypes.at(vt).symbole;
}
