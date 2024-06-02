// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "wm_patientnamescompleterloader.h"

wm_patientnamesCompleterLoader::wm_patientnamesCompleterLoader(QObject *parent)
    : QObject(parent),
      connectionName(
          QString("qt_sql_base_%1_%2_%3")
              .arg(QString("patientNames"),
                   QString::number(
                       QRandomGenerator::global()->bounded(0, 9999999)),
                   QString::number(
                       QTime::currentTime().msecsSinceStartOfDay()))),
      sqlbase(new sqlBase(nullptr, connectionName, false)) {}

wm_patientnamesCompleterLoader::~wm_patientnamesCompleterLoader() {
  sqlbase->optimize();
  delete sqlbase;
  QSqlDatabase::removeDatabase(connectionName);
}

QStringList wm_patientnamesCompleterLoader::Work() {
  return sqlbase->getPatientNameList();
}
