// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef DRUGEXAPNDER_H
#define DRUGEXAPNDER_H

#include <QDialog>

#include "mdialog.h"
#include "msettings.h"
#include "sqlextra.h"

namespace Ui {
class drugExapnder;
}

class drugExapnder : public mDialog {
  Q_OBJECT

 public:
  explicit drugExapnder(QWidget *parent = nullptr);
  ~drugExapnder();

 private slots:
  void on_closeButton_clicked();
  void on_buttonDel_clicked();
  void load(const QModelIndex &index);
  void addThisName();
  void save();
  void setFilter(QString arg);
  void currentRowChanged(const QModelIndex &i, const QModelIndex &);

 private:
  Ui::drugExapnder *ui;
  mSettings &settings = mSettings::instance();
  sqlExtra *sqlextra;
  QStringListModel *model;
  QSortFilterProxyModel *proxy_model;
  QItemSelectionModel *selectionModel;
  void reLoadAll();
 signals:
  void reloadCompleter();
  void newMessage(QString title, QString msg);
  void loadCompleters();
  void reloadDrugsCompleter();
  void setReadWrite(bool);
};

#endif  // DRUGEXAPNDER_H
