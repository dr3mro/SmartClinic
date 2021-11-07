#include "visithelper.h"


QDate VisitHelper::makeFollowDate(const QDate &visitDate, const QDate &lastFollowDate, const QDate &currentFollowDate, QDate &lastSelectedFollowDate, bool isAutoSet, const VisitTypes::n_visitsType visitType,
                                  const WorkDays &wd, const int maxFollowupsDay, sqlBase *sqlbase, const int ID, bool manual)
{
    qDebug() << visitDate << lastFollowDate << currentFollowDate << lastSelectedFollowDate
             << isAutoSet << visitType << wd << maxFollowupsDay << ID << manual;

    if(manual){
        if(currentFollowDate == visitDate )
            return lastFollowDate;
        else
            return visitDate;
    }

    if(visitType == VisitTypes::n_visitsType::Requests)
        return lastFollowDate;

    if(!isAutoSet)
        return QDate::currentDate();

    if(visitType == VisitTypes::n_visitsType::NewVisit){
        while (true){
            if( (( 1 << lastSelectedFollowDate.dayOfWeek() ) & wd)  &&
                    (sqlbase->getFollowUpsCountForThisDate(lastSelectedFollowDate,ID) < maxFollowupsDay) ){
                return lastSelectedFollowDate;
            }else if (maxFollowupsDay > 0){
                lastSelectedFollowDate = lastSelectedFollowDate.addDays(1);
            } else {
                return QDate::currentDate();
            }
        }
    }
    return QDate::currentDate();
}
