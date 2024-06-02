// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef GENERICONLINESEARCH_H
#define GENERICONLINESEARCH_H

#include <QDesktopServices>
#include <QMouseEvent>
#include <QStringListModel>
#include <QUrl>

#include "mDialog.h"

namespace Ui {
class genericOnlineSearch;
}

class genericOnlineSearch : public mDialog {
  Q_OBJECT

 public:
  explicit genericOnlineSearch(QWidget *parent = nullptr);
  void setModel(QStringList drugs);
  void setTradeName(QString tname);
  ~genericOnlineSearch();

 private slots:
  void on_listView_activated(const QModelIndex &index);
  void on_buttonSearch_clicked();
  void on_listView_clicked(const QModelIndex &index);
  void tradeNameDoubleClicked();
  void searchGoogle();

 private:
  Ui::genericOnlineSearch *ui;
  QStringListModel *model;
  QString rawTradeName;
  int x_cord;
  int y_cord;
  QString searchEngine();
  void openUrl(QString generic, QString engine);
  void doOpen(const QModelIndex &index);

 protected:
  void keyPressEvent(QKeyEvent *e);
};

#endif  // GENERICONLINESEARCH_H
