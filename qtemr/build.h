#ifndef BUILD_H
#define BUILD_H
#define BUILD QString::fromStdString([](){\
  QLocale enUS = QLocale(QLocale::English,QLocale::UnitedStates);\
  QDate build_date = QDate::fromString(QString(__DATE__).simplified(),"MMM dd yyyy");\
  QTime build_time = QTime::fromString(QString(__TIME__).simplified(),"hh:mm:ss");\
  std::stringstream stream;\
  stream << std::hex << (build_date.toString("yyMMdd").toInt()*10000 + build_time.toString("hhmm").toInt());\
  std::string result( stream.str() );\
  return result;\
  }())
#endif // BUILD_H


