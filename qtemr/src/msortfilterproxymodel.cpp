// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "msortfilterproxymodel.h"

mSortFilterProxyModel::mSortFilterProxyModel(QObject *) {}

void mSortFilterProxyModel::setCategory(QString category) {
  Category = category;
}

void mSortFilterProxyModel::setManufacturer(QString manufacturer) {
  Manufacturer = manufacturer;
}

void mSortFilterProxyModel::setForm(QString form) { Form = form; }

bool mSortFilterProxyModel::filterAcceptsRow(
    int source_row, const QModelIndex &source_parent) const {
  QModelIndex cIndex = sourceModel()->index(source_row, 3, source_parent);
  QModelIndex fIndex = sourceModel()->index(source_row, 4, source_parent);
  QModelIndex mIndex = sourceModel()->index(source_row, 5, source_parent);

  QString tCategory = sourceModel()->data(cIndex).toString();
  QString tManufacturer = sourceModel()->data(mIndex).toString();
  QString tForm = sourceModel()->data(fIndex).toString();

  if (Category == "All Drugs" && Manufacturer == "All Companies" &&
      Form == "All Forms") {
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
  }
  if (tCategory == Category && tManufacturer == Manufacturer && tForm == Form) {
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
  }

  if (tCategory == Category && tManufacturer == Manufacturer &&
      Form == "All Forms") {
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
  }

  if (tCategory == Category && Manufacturer == "All Companies" &&
      tForm == Form) {
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
  }
  if (tCategory == Category && Manufacturer == "All Companies" &&
      Form == "All Forms") {
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
  }

  if (Category == "All Drugs" && tManufacturer == Manufacturer &&
      tForm == Form) {
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
  }

  if (Category == "All Drugs" && Manufacturer == "All Companies" &&
      tForm == Form) {
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
  }
  if (Category == "All Drugs" && Manufacturer == tManufacturer &&
      Form == "All Forms") {
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
  }
  return false;
}
