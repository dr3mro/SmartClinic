// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef WM_INVMODELLOADER_H
#define WM_INVMODELLOADER_H

#include <QObject>
#include <QRandomGenerator>

#include "investmodel.h"
#include "sqlbase.h"

class wm_invModelLoader : public QObject {
  Q_OBJECT
 public:
  explicit wm_invModelLoader(QObject *parent = nullptr);
  void setIdJulianDateTime(int id, qint64 jdate, qint64 time);
  void setInvestigationsModel(InvestModel *investModel);
  ~wm_invModelLoader();

 signals:

 public slots:
  InvestModel *Work();

 private:
  int ID;
  qint64 visitJulianDate;
  qint64 visitTime;
  sqlBase *sqlbase;
  InvestModel *model;
  int r;
  QString connectionName;
};

#endif  // WM_INVMODELLOADER_H
