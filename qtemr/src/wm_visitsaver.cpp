// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "wm_visitsaver.h"

wm_visitSaver::wm_visitSaver(QObject *parent)
    : QObject(parent),
      connectionName(QString("qt_sql_base_visitSaver_%1_%2")
                         .arg(QRandomGenerator::global()->bounded(0, 9999999),
                              QTime::currentTime().msecsSinceStartOfDay())),
      sqlbase(new sqlBase(this, connectionName, false)) {}

wm_visitSaver::~wm_visitSaver() {
  sqlbase->optimize();
  delete sqlbase;
  QSqlDatabase::removeDatabase(connectionName);
}

void wm_visitSaver::setVisitData(const sqlBase::visitData &_data) {
  visitData = _data;
}

void wm_visitSaver::Work() {
  bool b = sqlbase->saveVisitData(visitData);
  emit finished();
  emit finishedSavingState(b);
}
