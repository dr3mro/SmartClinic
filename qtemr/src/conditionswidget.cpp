// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "conditionswidget.h"

conditionsWidget::conditionsWidget(QWidget *parent)
    : QWidget(parent), sqlbase(new sqlBase(this, "conditionsWidget", false)) {
  setLayout(&layout);
  layout.setVerticalSpacing(1);
  layout.setHorizontalSpacing(2);
  layout.setContentsMargins(1, 1, 1, 1);
  load();
}

void conditionsWidget::fillConditions(const int &_ID) {
  this->ID = _ID;
  QList<QPair<QString, int> > list = sqlbase->readPatientConditions(ID);
  QPair<QString, int> pair;
  foreach (pair, list) {
    mCheckBox *cb = findChild<mCheckBox *>(pair.first);
    if (cb) cb->setChecked(bool(pair.second));
  }
}

void conditionsWidget::clear() {
  foreach (mCheckBox *cb, cbList) {
    if (cb) cb->setChecked(false);
  }
}

QList<QPair<QString, int> > conditionsWidget::getConditionsState() {
  QList<QPair<QString, int> > list;
  QPair<QString, int> pair;

  foreach (mCheckBox *cb, cbList) {
    pair.first = QString("c%1").arg(cb->objectName().split("_").at(1));
    pair.second = int(cb->isChecked());
    list.append(pair);
  }
  return list;
}

bool conditionsWidget::isConditionsModified() {
  QList<QPair<QString, int> > saved = sqlbase->readPatientConditions(ID);
  QList<QPair<QString, int> > visible = getConditionsState();

  if (saved.count() == 0) return false;

  for (int i = 0; i < conditionsCount; i++) {
    if ((saved.at(i).second != visible.at(i).second)) return true;
  }
  return false;
}

void conditionsWidget::setID(int id) { ID = id; }

conditionsWidget::~conditionsWidget() {
  sqlbase->optimize();
  delete sqlbase;
  QSqlDatabase::removeDatabase("conditionsWidget");
}

void conditionsWidget::load() {
  setConditions();
  setConditionsCount();
  loadCheckboxes();
}

void conditionsWidget::reload() {
  foreach (mCheckBox *cb, cbList) delete cb;

  setConditions();
  setConditionsCount();
  loadCheckboxes();
  fillConditions(ID);

  foreach (mCheckBox *cb, cbList) cb->setEnabled(editMode);
}

void conditionsWidget::setConditionsCount() {
  conditionsCount = conditions.length();
}

void conditionsWidget::setConditions() {
  conditions = sqlbase->getConditions();
}

void conditionsWidget::loadCheckboxes() {
  int row = 1;
  int col = 1;
  cbList = getCheckboxList();
  foreach (mCheckBox *cb, cbList) {
    if (col > 5) {
      col = 1;
      row++;
    }
    layout.addWidget(cb, row, col);
    col++;
  }
}

QList<mCheckBox *> conditionsWidget::getCheckboxList() {
  QList<mCheckBox *> list;
  for (int i = 0; i < conditionsCount; i++) {
    mCheckBox *cb = new mCheckBox(this);
    cb->setText(conditions.at(i).second);
    cb->setObjectName(QString("cb_%1").arg(conditions.at(i).first));
    list.append(cb);
  }
  return list;
}
