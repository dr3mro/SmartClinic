// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "servicemodel.h"

serviceModel::serviceModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db) {}

Qt::ItemFlags serviceModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags result = QSqlTableModel::flags(index);
  int col = index.column();
  if (col == 0)
    return (result &= ~Qt::ItemIsEditable);
  else
    return result;
}
