// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef PATIENTTABLE_H
#define PATIENTTABLE_H

#include <QFutureWatcher>
#include <QHeaderView>
#include <QKeyEvent>
#include <QObject>
#include <QSettings>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>
#include <QtConcurrent/QtConcurrentRun>

#include "qabstractitemmodel.h"
#include "sqlbase.h"

class patientTable : public QTableView {
  Q_OBJECT

 public:
  void setFilterByName();
  void setFilterByID();
  void setFiletrByMobile();
  int getSelectedPatientID(const QModelIndex *index);
  void FilterPatients(QString filter);
  explicit patientTable(QWidget *parent = nullptr);
  void setConnection(QString conname = "qt_sql_base_patientList");
  void closeDatabase();
  void reOpenDatabase();
  void mSelectRow(int row);
  ~patientTable();

 public slots:
  void updatePatients();
  void setMyModel();
  void tweaksAfterModelLoadingIsFinished();
  void loadPatient();
  void setPatientIcon(bool b, int row);
  void setID(int id);
  int getID();

 private:
  sqlBase *sqlbase;
  QStandardItemModel *model = nullptr;
  QSortFilterProxyModel *proxy_model = nullptr;
  bool eventFilter(QObject *o, QEvent *e);
  bool loadingIsFinished;
  int filterColumn;
  QString connectionName;
  QFuture<QStandardItemModel *> modelFuture;
  QFutureWatcher<QStandardItemModel *> watcher;
  QFuture<QStandardItemModel *> initModelFuture;
  QFutureWatcher<QStandardItemModel *> initWatcher;
  int ID = 1;
  inline void commonTweaksForPatientTable();

 signals:
  void modelLoadingFinished();
  void loadSelectedPatient(const QModelIndex);
  void focusFilterBox();
  void setFilter(int x);

 protected:
  void keyPressEvent(QKeyEvent *ke);
 private slots:
  void updatePatientsCompleted();
};

#endif  // PATIENTTABLE_H
