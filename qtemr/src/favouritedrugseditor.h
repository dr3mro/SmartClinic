// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef FAVOURITEDRUGSEDITOR_H
#define FAVOURITEDRUGSEDITOR_H

#include <QDialog>
#include <QSortFilterProxyModel>

#include "dataiohelper.h"
#include "favouritedosedelegate.h"
#include "mdialog.h"
#include "settingsclass.h"
#include "sqlextra.h"

namespace Ui {
class favouriteDrugsEditor;
}

class favouriteDrugsEditor : public mDialog {
  Q_OBJECT

 public:
  explicit favouriteDrugsEditor(QWidget *parent = nullptr);
  ~favouriteDrugsEditor();

 private slots:
  void on_ButtonDel_clicked();
  void on_tableView_clicked(const QModelIndex &index);
  void addButtonToggler(QString arg1);
  void on_ButtonNew_clicked();
  void dataChanged(QModelIndex topLeft, QModelIndex bottomRight,
                   QVector<int> vect);
  void setFilter(QString arg1);

 private:
  sqlExtra *sqlextra;
  QSqlTableModel *model;
  QSortFilterProxyModel *proxy_model;
  favouriteDoseDelegate *doseDelegate;
  Ui::favouriteDrugsEditor *ui;
 signals:
  void reloadCompleter();
  void loadCompleters();
};

#endif  // FAVOURITEDRUGSEDITOR_H
