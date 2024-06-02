// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef WM_INVESTTOOLTIPLOADER_H
#define WM_INVESTTOOLTIPLOADER_H

#include <QCoreApplication>
#include <QObject>

#include "investmodel.h"
#include "inviconhelper.h"

class wm_investTooltipLoader : public QObject {
  Q_OBJECT
 public:
  explicit wm_investTooltipLoader(QObject *parent = nullptr);
  void setInvestigationsModel(InvestModel *investModel);
  void setScale(const int &s);

 signals:

 public slots:
  InvestModel *Work();
  void killloop();

 private:
  InvestModel *model;
  int scale;
  bool killloopFlag = false;
};

#endif  // WM_INVESTTOOLTIPLOADER_H
