#ifndef VISITTYPES_H
#define VISITTYPES_H


#include "msettings.h"
#include <QList>

class VisitTypes
{
public:
    enum n_visitsType{
        NewVisit=0,
        Follow1=1,
        Follow2=2,
        Follow3=3,
        Follow4=4,
        Free=5,
        Requests=6,
        Undefined=7
    };
    struct t_visitsType{
        n_visitsType id;
        QString name;
        double price;
        QBrush color;
        QString symbole;
        QIcon icon;
    };

    static VisitTypes &instance();
    VisitTypes(const VisitTypes&) = delete;
    VisitTypes(VisitTypes&&) = delete;
    VisitTypes& operator=(const VisitTypes&) = delete;
    VisitTypes& operator=(VisitTypes&&) = delete;

    n_visitsType advance(int _vt) const;
    QList<t_visitsType> & getVisitTypesListByUiIndex();
    QList<t_visitsType> & getVisitTypesListByAlgoIndex();

    t_visitsType & getVisitTypesByUiIndex(const int &index) const;
    t_visitsType & getVisitTypesByAlgoIndex(const int &index) const;

    int getVisitIndexFromId(const n_visitsType &id) const;
    QString getVisitSymbole(const int & _i,const bool &isCaseClosed,const bool & noNextDateSpecified) const;

private:
    QList<t_visitsType> ui_VisitTypes;
    QList<t_visitsType> algo_VisitTypes;
    mSettings &settings = mSettings::instance();
    mSettings::clinicPrices prices = settings.getClinicPrices();

    VisitTypes();
    ~VisitTypes();
};
#endif // VISITTYPES_H
