// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef REMOTEASSIST_H
#define REMOTEASSIST_H

#include <QComboBox>
#include <QDialog>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "mdebug.h"
#include "sqlbase.h"

namespace Ui {
class remoteAssist;
}

class remoteAssist : public QDialog {
  Q_OBJECT

 public:
  struct Visitor {
    QString name = "-1";
    QString ID = "-1";
    int sex = -1;
    int marital = -1;
    int age = -1;
    QString residence = "-1";
    QString placeofbirth = "-1";
    QString job = "-1";
    QString tel = "-1";
    int visitType = -1;
  };
  explicit remoteAssist(QWidget *parent = nullptr);
  ~remoteAssist();

 public slots:
  void loadVisitors();

 private slots:
  void on_visitorsTableView_clicked(const QModelIndex &index);
  void searchByID();
  void searchByName();
  void searchByTel();
  void on_visitorsTableView_doubleClicked(const QModelIndex &index);
  void on_loadID_clicked();
  void on_loadName_clicked();

 private:
  QJsonDocument getJsonDocument();
  QStandardItemModel *model;
  remoteAssist::Visitor getVisitor(const int &row);
  void showVisitor(const QModelIndex &current, const QModelIndex &previous);
  void tweakTable();
  sqlBase *sqlbase;
  Ui::remoteAssist *ui;

 signals:
  void search(const QString &str);
  void createVisitor(const Visitor &visitor);
};

#endif  // REMOTEASSIST_H
