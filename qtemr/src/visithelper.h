#ifndef VISITHELPER_H
#define VISITHELPER_H

#include <QObject>
#include <QDate>
#include "visittypes.h"
#include "sqlbase.h"

class VisitHelper : public QObject
{
    Q_OBJECT
public:

   enum WorkDay{
       Monday    = 1 << 1,
       Tuesday   = 1 << 2,
       Wednesday = 1 << 3,
       Thrusday  = 1 << 4,
       Friday    = 1 << 5,
       Saturday  = 1 << 6,
       Sunday    = 1 << 7,

    };

    Q_DECLARE_FLAGS(WorkDays,WorkDay)
    explicit VisitHelper(QObject *parent = nullptr);
   static QDate VisitDate(const QDate & lastFollowDate,
                QDate &lastSelectedFollowDate,
                bool isAutoSet,
                const VisitTypes::n_visitsType visitType,
                const WorkDays &wd,
                const int maxFollowupsDay,
                sqlBase *sqlbase,
                const int ID);

    static QDate makeFollowDate(const QDate & lastFollowDate,
                         QDate &lastSelectedFollowDate,
                         bool isAutoSet,
                         const VisitTypes::n_visitsType visitType,
                         const WorkDays &wd,
                         const int maxFollowupsDay,
                         sqlBase *sqlbase,
                         const int ID);


signals:

};

Q_DECLARE_OPERATORS_FOR_FLAGS (VisitHelper::WorkDays)
#endif // VISITHELPER_H
