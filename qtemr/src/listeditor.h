// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef LISTEDITOR_H
#define LISTEDITOR_H

#include <QCloseEvent>
#include <QDialog>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QStringListModel>
#include <QTableView>

#include "dataiohelper.h"
#include "mdialog.h"
#include "msettings.h"
#include "sqlextra.h"

namespace Ui {
class listEditor;
}

class listEditor : public mDialog {
  Q_OBJECT
 public:
  explicit listEditor(QWidget *parent = nullptr);
  ~listEditor();

 private slots:
  void on_comboList_currentIndexChanged(const QString &arg1);
  void on_buttonDelete_clicked();
  void on_buttonAdd_clicked();
  void on_lineEdit_returnPressed();
  void refreshCompleters();
  void on_closeButton_clicked();
  void completerInitialized();
  void on_lineEdit_textChanged(const QString &arg1);
  void on_tableView_clicked(const QModelIndex &index);

 signals:
  void reloadCompleter();
  void setReadWrite(bool);
  void loadCompleters();

 private:
  void updateList();
  bool completerModelInitialized = false;
  sqlExtra *sqlextra;
  Ui::listEditor *ui;
  QStringListModel *model;
  QSortFilterProxyModel *proxy_model;
  mSettings &settings = mSettings::instance();

 protected:
  void closeEvent(QCloseEvent *event) override;
};

#endif  // LISTEDITOR_H
