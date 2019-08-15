#ifndef BUILD_H
#define BUILD_H
#define BUILD QLocale(QLocale::English,QLocale::UnitedStates).toString(QDate::fromString(QString(__DATE__).simplified(),"MMM dd yyyy"),"yyyyMMdd")
#endif // BUILD_H


