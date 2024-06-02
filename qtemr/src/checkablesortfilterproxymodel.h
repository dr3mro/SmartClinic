// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef CHECKABLESORTFILTERPROXYMODEL_H
#define CHECKABLESORTFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QtSql/QSqlQueryModel>

class CheckableSortFilterProxyModel : public QSortFilterProxyModel {
  Q_OBJECT
 public:
  explicit CheckableSortFilterProxyModel(QObject *parent = nullptr);
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);
  Qt::ItemFlags flags(const QModelIndex &index) const;

 protected:
 signals:

 public slots:
};
#endif
