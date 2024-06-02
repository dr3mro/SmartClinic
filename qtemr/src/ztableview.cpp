// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ztableview.h"

#include "investmodel.h"

zTableView::zTableView(QWidget *parent)
    : QTableView(parent)  //-V730
{
  connect(parent->window(), SIGNAL(updateTextFont()), this,
          SLOT(setDefaultFont()));
}

zTableView::~zTableView() { tableModel = nullptr; }

void zTableView::setModel(QAbstractItemModel *_model) {
  tableModel = static_cast<QStandardItemModel *>(_model);
  QTableView::setModel(tableModel);
}

void zTableView::moveRowDown() {
  int row = getSelectedRows();
  if ((row >= getRowsCount() - 1) || isValidRow(row + 1) || isReadOnly) return;
  QList<QStandardItem *> aItems = tableModel->takeRow(row);
  QList<QStandardItem *> bItems = tableModel->takeRow(row);  //-V656
  tableModel->insertRow(row, bItems);
  tableModel->insertRow(row + 1, aItems);
  selectRow(row + 1);
  emit itemMoved();
  emit drugsHasBeenAltered(true);
}

void zTableView::moveRowUp() {
  int row = getSelectedRows();
  if (row < 1 || isValidRow(row) || isReadOnly) return;
  QList<QStandardItem *> aItems = tableModel->takeRow(row);
  QList<QStandardItem *> bItems = tableModel->takeRow(row - 1);
  tableModel->insertRow(row - 1, aItems);
  tableModel->insertRow(row, bItems);
  selectRow(row - 1);
  emit itemMoved();
  emit drugsHasBeenAltered(true);
}

bool zTableView::isValidRow(int row) {
  if (sortColumn == 5)  // Drugs table
    return (tableModel->item(row, sortColumn)->text().toInt() == 0);
  else if (sortColumn == 6)  // InvestTable
  {
    // normal=0,hasMedia=1,isPaid=2,wasPaid=3,nonPrintable=4,PrintableWithMedia=5};

    InvestModel::InvestigationsStates mPreviousRowState =
        static_cast<InvestModel::InvestigationsStates>(
            tableModel->item(row - 1, sortColumn)->text().toInt());
    InvestModel::InvestigationsStates mSelectedRowState =
        static_cast<InvestModel::InvestigationsStates>(
            tableModel->item(row, sortColumn)->text().toInt());

    return (mPreviousRowState != mSelectedRowState);

    //        if(mPreviousRowState == InvestModel::InvestigationsStates::isPaid
    //        || mPreviousRowState ==
    //        InvestModel::InvestigationsStates::wasPaid){
    //            return (mSelectedRowState !=
    //            InvestModel::InvestigationsStates::isPaid && mSelectedRowState
    //            != InvestModel::InvestigationsStates::wasPaid);
    //        }

    //        if(mPreviousRowState ==
    //        InvestModel::InvestigationsStates::PrintableWithMedia){
    //            return (mSelectedRowState !=
    //            InvestModel::InvestigationsStates::PrintableWithMedia);
    //        }

    //        if( tableModel->item(row-1,sortColumn)->text().toInt() == 2 ||
    //            tableModel->item(row-1,sortColumn)->text().toInt() == 3 ||
    //            tableModel->item(row-1,sortColumn)->text().toInt() == 5)
    //        {
    //            return  ( tableModel->item(row,sortColumn)->text().toInt() < 2
    //            ||
    //                      tableModel->item(row,sortColumn)->text().toInt() > 3
    //                      );
    //        }
    //        else
    //        {
    //            return  ( tableModel->item(row,sortColumn)->text().toInt() ==
    //            4 );
    //        }
  }
  return false;
}

int zTableView::getSelectedRows() {
  return selectionModel()->currentIndex().row();
}

int zTableView::getRowsCount() { return tableModel->rowCount(); }
void zTableView::setReadOnly(bool b) { isReadOnly = b; }

void zTableView::setSortColumn(const int &col) { sortColumn = col; }

void zTableView::makeReadWrite(bool rw) {
  setReadOnly(!rw);
  clearSelection();
}

void zTableView::setDefaultFont() {
  mSettings::defaultFont defaultfont = settings.getDefaultFont();
  QFont defaultFont = QFont(defaultfont.fontName);
  int defaultPointSize = static_cast<int>(defaultfont.fontSize);
  bool defaultBold = defaultfont.fontBold;
  defaultFont.setBold(defaultBold);
  defaultFont.setPointSize(defaultPointSize);
  setFont(defaultFont);
}

void zTableView::keyPressEvent(QKeyEvent *e) {
  if (e->modifiers() == Qt::SHIFT) {
    if (e->key() == Qt::Key_Up) {
      moveRowUp();
      return;
    }
    if (e->key() == Qt::Key_Down) {
      moveRowDown();
      return;
    }
  }
  QTableView::keyPressEvent(e);
}
