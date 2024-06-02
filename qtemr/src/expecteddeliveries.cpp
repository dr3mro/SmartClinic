// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "expecteddeliveries.h"

#include "ui_expecteddeliveries.h"

ExpectedDeliveries::ExpectedDeliveries(QWidget *parent)
    : QWidget(parent), ui(new Ui::ExpectedDeliveries) {
  ui->setupUi(this);

  QStringList months = QStringList() << "JANUARY"
                                     << "FEBRUARY"
                                     << "MARCH"
                                     << "APRIL"
                                     << "MAY"
                                     << "JUNE"
                                     << "JULY"
                                     << "AUGUST"
                                     << "SEPTEMBER"
                                     << "OCTOBER"
                                     << "NOVEMBER"
                                     << "DECEMBER";
  ui->Month->addItems(months);
  for (int x = 2019; x < 2100; x++) ui->Year->addItem(QString::number(x));
  ui->Month->setCurrentIndex(QDate::currentDate().month() - 1);
  ui->Year->setCurrentText(QString::number(QDate::currentDate().year()));
  connect(ui->Month, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &ExpectedDeliveries::reload);
  connect(ui->Year, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &ExpectedDeliveries::reload);
}

void ExpectedDeliveries::setModel(QStandardItemModel *model) {
  ui->tableView->setModel(model);
  ui->tableView->clearSelection();
  ui->tableView->setWordWrap(false);
  ui->tableView->setColumnWidth(0, 40);
  ui->tableView->setColumnWidth(1, 260);
}

int ExpectedDeliveries::getMonth() { return ui->Month->currentIndex() + 1; }

int ExpectedDeliveries::getYear() { return ui->Year->currentText().toInt(); }

QTableView *ExpectedDeliveries::getTableView() { return ui->tableView; }

ExpectedDeliveries::~ExpectedDeliveries() { delete ui; }
