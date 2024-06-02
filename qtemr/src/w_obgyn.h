// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef W_OBGYN_H
#define W_OBGYN_H

#include <QStandardItemModel>
#include <QWidget>

#include "addsiblings.h"
#include "sqlbase.h"

namespace Ui {
class w_obGyn;
}

class w_obGyn : public QWidget {
  Q_OBJECT

 public:
  explicit w_obGyn(QWidget *parent = nullptr);
  void clear();
  QStandardItemModel *getSiblingsModel();
  QString getFPAL();
  void toggleEditMode(bool pEditMODE);
  void toggleHeaders(bool state);
  sqlBase::obGyn getObgyne(int id);
  void load(int ID);
  bool isObGynModified();
  void setID(int id);
  QString getHusbandHtml();
  ~w_obGyn();
 public slots:
  void syncLMPDateWithVisit(QDate date);

 private:
  Ui::w_obGyn *ui;
  bool pEditingMode;
  sqlBase *sqlbase;
  int ID;
 private slots:
  void toggleLMPdateBox(bool checked);
  void on_addSiblings_clicked();
  void on_removeSiblings_clicked();
  void on_fpalCalButton_clicked();
  void on_siblings_clicked(const QModelIndex &index);
  void on_editSiblingButton_clicked();
};

#endif  // W_OBGYN_H
