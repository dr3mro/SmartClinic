// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "msiblings.h"

mSiblings::mSiblings(QWidget *) {
  model = new QStandardItemModel(this);
  sqlbase = new sqlBase(this, "qt_sql_base_siblings_connection", false);
  QStringList labels = QStringList() << "DateOfBirth"
                                     << "TOD"
                                     << "Gender"
                                     << "PlaceOfBirth"
                                     << "Complications"
                                     << "Term";
  model->setHorizontalHeaderLabels(labels);

  this->setModel(model);
  tweakCoulmnSize();
}

void mSiblings::clear() { model->removeRows(0, model->rowCount()); }

void mSiblings::removeRow(int row) { model->removeRow(row); }

bool mSiblings::save(int ID) { return sqlbase->saveSiblings(ID, model); }

bool mSiblings::populateSiblings(int ID) {
  bool b = sqlbase->readSiblings(ID, model);
  tweakCoulmnSize();
  return b;
}

void mSiblings::tweakCoulmnSize() {
  setColumnWidth(0, 85);
  setColumnWidth(1, 55);
  setColumnWidth(2, 55);
  setColumnWidth(4, 160);
}

QString mSiblings::calculateFPAL() {
  int f = 0, p = 0, a = 0, l = 0;
  QStringList term = QStringList() << "FullTerm"
                                   << "PreTerm"
                                   << "Abortion";
  for (int r = 0; r < model->rowCount(); r++) {
    switch (term.indexOf(model->item(r, 5)->text())) {
      case 0:
        f += 1;
        break;

      case 1:
        p += 1;
        break;

      case 2:
        a += 1;
        break;
    }
  }
  l = f + p;
  return QString("%1-%2-%3-%4").arg(f).arg(p).arg(a).arg(l);
}

QString mSiblings::calculateGPA() {
  int g, p, a, l;
  g = p = a = 0;
  QStringList term = QStringList() << "FullTerm"
                                   << "PreTerm"
                                   << "Abortion";
  for (int r = 0; r < model->rowCount(); r++) {
    switch (term.indexOf(model->item(r, 5)->text())) {
      case 0:
        g += 1;
        p += 1;
        break;

      case 1:
        g += 1;
        p += 1;
        break;

      case 2:
        g += 1;
        a += 1;
        break;
    }
  }
  l = g - a;
  return QString("G%1-P%2+%4").arg(g).arg(p).arg(l);
}

int mSiblings::getRowCount() { return model->rowCount(); }

int mSiblings::getSelectedRow() {
  return selectionModel()->currentIndex().row();
}

sqlBase::Sibling mSiblings::getSelectedRowContent() {
  int row = getSelectedRow();
  sqlBase::Sibling sibling;
  sibling.DateOfBirth = model->data(model->index(row, 0)).toString();
  sibling.Gender = model->data(model->index(row, 1)).toString();
  sibling.TypeOfDelivery = model->data(model->index(row, 2)).toString();
  sibling.PlaceOfBirth = model->data(model->index(row, 3)).toString();
  sibling.Complications = model->data(model->index(row, 4)).toString();
  sibling.Term = model->data(model->index(row, 5)).toString();

  return sibling;
}

QStandardItemModel *mSiblings::getModel() { return model; }

void mSiblings::appendRow(const sqlBase::Sibling &sibling) {
  QStandardItem *dob_item = new QStandardItem;
  QStandardItem *tod_item = new QStandardItem;
  QStandardItem *gndr_item = new QStandardItem;
  QStandardItem *pob_item = new QStandardItem;
  QStandardItem *cmpl_item = new QStandardItem;
  QStandardItem *term_item = new QStandardItem;

  QList<QStandardItem *> newRow;
  newRow.clear();
  newRow.append(dob_item);
  newRow.append(tod_item);
  newRow.append(gndr_item);
  newRow.append(pob_item);
  newRow.append(cmpl_item);
  newRow.append(term_item);

  dob_item->setText(sibling.DateOfBirth);
  tod_item->setText(sibling.TypeOfDelivery);
  gndr_item->setText(sibling.Gender);
  pob_item->setText(sibling.PlaceOfBirth);
  cmpl_item->setText(sibling.Complications);
  term_item->setText(sibling.Term);

  pob_item->setToolTip(sibling.PlaceOfBirth);
  cmpl_item->setToolTip(sibling.Complications);

  model->appendRow(newRow);
  setModel(model);
  tweakCoulmnSize();
}

void mSiblings::editRow(int row, const sqlBase::Sibling &sibling) {
  model->item(row, 0)->setText(sibling.DateOfBirth);
  model->item(row, 1)->setText(sibling.TypeOfDelivery);
  model->item(row, 2)->setText(sibling.Gender);
  model->item(row, 3)->setText(sibling.PlaceOfBirth);
  model->item(row, 4)->setText(sibling.Complications);
  model->item(row, 5)->setText(sibling.Term);
}

mSiblings::~mSiblings() {
  delete model;
  sqlbase->optimize();
  delete sqlbase;
  QSqlDatabase::removeDatabase("qt_sql_base_siblings_connection");
}
