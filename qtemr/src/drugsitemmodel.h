// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef DRUGSITEMMODEL_H
#define DRUGSITEMMODEL_H

#include <QObject>
#include <QStandardItemModel>

#include "mdebug.h"

class DrugsItemModel : public QStandardItemModel {
  Q_OBJECT
 public:
  explicit DrugsItemModel(QObject *parent = nullptr);
  ~DrugsItemModel();
  bool isThereActiveDrugs();
  bool isThereInactiveDrugs();
  int getPrintableDrugsCount();
};

#endif  // DRUGSITEMMODEL_H
