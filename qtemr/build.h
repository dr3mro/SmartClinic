// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BUILD_H
#define BUILD_H
#define BUILD QString([](){\
  QLocale enUS = QLocale(QLocale::English,QLocale::UnitedStates);\
  QDate build_date = enUS.toDate(QString(__DATE__).simplified(),"MMM d yyyy");\
  QTime build_time = enUS.toTime(QString(__TIME__).simplified(),"hh:mm:ss");\
  QString build_nr;\
  build_nr.setNum(build_date.toString("yyMMdd").toInt()*10000 + build_time.toString("hhmm").toInt(),36);\
  return build_nr.toUpper();\
  }())
#endif // BUILD_H


