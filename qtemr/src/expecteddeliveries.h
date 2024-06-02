// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef EXPECTEDDELIVERIES_H
#define EXPECTEDDELIVERIES_H

#include <QComboBox>
#include <QDate>
#include <QObject>
#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>

namespace Ui {
class ExpectedDeliveries;
}

class ExpectedDeliveries : public QWidget {
  Q_OBJECT

 public:
  explicit ExpectedDeliveries(QWidget *parent = nullptr);
  void setModel(QStandardItemModel *model);
  int getMonth();
  int getYear();
  QTableView *getTableView();
  ~ExpectedDeliveries();

 private slots:

 private:
  Ui::ExpectedDeliveries *ui;

 signals:
  void reload();
};

#endif  // EXPECTEDDELIVERIES_H
