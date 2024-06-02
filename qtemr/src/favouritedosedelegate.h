// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef FAVOURITEDOSEDELEGATE_H
#define FAVOURITEDOSEDELEGATE_H

#include <QCompleter>
#include <QItemDelegate>
#include <QLineEdit>
#include <QObject>
#include <QRandomGenerator>

#include "sqlextra.h"
class favouriteDoseDelegate : public QItemDelegate {
 public:
  explicit favouriteDoseDelegate(QWidget *parent = nullptr);
  ~favouriteDoseDelegate();
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const;

 private:
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;
  QString connectionName;
  sqlExtra *sqlextra;
};

#endif  // FAVOURITEDOSEDELEGATE_H
