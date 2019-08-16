#ifndef BUILD_H
#define BUILD_H
#define BUILD QString([](){\
  QLocale enUS = QLocale(QLocale::English,QLocale::UnitedStates);\
  QDate build_date = QDate::fromString(QString(__DATE__).simplified(),"MMM dd yyyy");\
  QTime build_time = QTime::fromString(QString(__TIME__).simplified(),"hh:mm:ss");\
  QString build_nr;\
  build_nr.setNum(build_date.toString("yyMMdd").toInt()*10000 + build_time.toString("hhmm").toInt(),36);\
  return build_nr.toUpper();\
  }())
#endif // BUILD_H


