#ifndef DATAHELPER_H
#define DATAHELPER_H

#include <QObject>
#include <QTextDocument>
#include <QDate>
#include <QCoreApplication>
#include <QEventLoop>
#include "mdebug.h"
#include "msettings.h"

class dataHelper : public QObject
{
    Q_OBJECT
public:
    enum AgeStyle{compact,expanded,normal};
    enum Speciality{InternalMedicine=0,
                    Paediatrics=1,
                    Orthopaedics=2,
                    Surgery=3,
                    ObGyn=4,
                    FamilyMedicine=5,
                    PhysicalTherapy=6};

    explicit dataHelper(QObject *parent = nullptr);
    static QString cleanHTML(QString string);
    static QString julianToAge(int totalDays=0, AgeStyle style=AgeStyle::normal);
    static QString daysToAge(int totalDays = 0);
    static int ageToYear(int totalDays = 0);
    static int julianToYear(int totalDays);
//    static QString numericToVisitType(int x);
    static bool str2bool(QString string);
    static QString bool2String(bool b);
    static int appversiontoint(QByteArray ba);
    static QString switchToEasternArabic(QString str);
    static void delay(const int &delay_msec);
    static bool doubleEqual(double a,double b);
    static QString getVisitType(int visitType,mSettings &settings);
    ~dataHelper();

signals:

public slots:
};

#endif // DATAHELPER_H
