#include "visithelper.h"


QDate VisitHelper::makeFollowDate(const QDate &fd, QDate &lastSelected, bool isAutoSet, const VisitTypes::n_visitsType visitType,
                                  const WorkDays &wd, const int maxFollowupsDay, sqlBase *sqlbase, const int ID, bool manual)
{
    if(manual){
        while (true){
            if( (( 1 << lastSelected.dayOfWeek() ) & wd)  && (sqlbase->getFollowUpsCountForThisDate(lastSelected,ID) < maxFollowupsDay) ){
                return lastSelected;
            }else{
                lastSelected = lastSelected.addDays(1);
            }
        }
    }

    if(visitType == VisitTypes::n_visitsType::Requests){
        return fd;
    }

    if(!isAutoSet){
        return QDate::currentDate();

    }
    if(visitType == VisitTypes::n_visitsType::NewVisit){

        while (true){
            if( (( 1 << lastSelected.dayOfWeek() ) & wd)  && (sqlbase->getFollowUpsCountForThisDate(lastSelected,ID) < maxFollowupsDay) ){
                return lastSelected;
            }else{
                lastSelected = lastSelected.addDays(1);
            }
        }
    }
    return QDate::currentDate();
}
