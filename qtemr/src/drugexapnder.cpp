// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "drugexapnder.h"

#include "ui_drugexapnder.h"

drugExapnder::drugExapnder(QWidget *parent)
    : mDialog(parent), ui(new Ui::drugExapnder) {
  ui->setupUi(this);
  this->setStyleSheet(settings.themeMaker());
  this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
  sqlextra = new sqlExtra(this, "qt_sql_extra_connection", false);

  QStringList list = sqlextra->getExpandList();
  model = new QStringListModel(this);
  model->setStringList(list);
  proxy_model = new QSortFilterProxyModel(this);
  proxy_model->setFilterKeyColumn(0);
  proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
  proxy_model->setSourceModel(model);

  ui->tableView->setModel(proxy_model);
  ui->tableView->horizontalHeader()->setSectionResizeMode(0,
                                                          QHeaderView::Stretch);
  connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this,
          SLOT(load(QModelIndex)));
  connect(ui->shortcut, SIGNAL(returnPressed()), this, SLOT(addThisName()));
  connect(ui->buttonAdd, SIGNAL(clicked(bool)), this, SLOT(addThisName()));
  connect(ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(save()));
  connect(ui->shortcut, SIGNAL(textChanged(QString)), this,
          SLOT(setFilter(QString)));

  emit loadCompleters();
  emit setReadWrite(true);

  selectionModel = ui->tableView->selectionModel();
  connect(selectionModel, SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
          this, SLOT(currentRowChanged(QModelIndex, QModelIndex)));
}

drugExapnder::~drugExapnder() {
  // emit reloadCompleter();
  emit reloadDrugsCompleter();
  delete model;
  delete proxy_model;
  delete sqlextra;
  delete ui;
}

void drugExapnder::on_closeButton_clicked() { this->close(); }

void drugExapnder::save() {
  QString expand = ui->expandText->toHtml();
  QModelIndex cell = ui->tableView->selectionModel()->currentIndex();
  QString name = cell.data(Qt::DisplayRole).toString();
  sqlextra->saveExpand(name, expand);
}

void drugExapnder::setFilter(QString arg) {
  proxy_model->setFilterWildcard(arg);
}

void drugExapnder::currentRowChanged(const QModelIndex &i,
                                     const QModelIndex &) {
  load(i);
}

void drugExapnder::on_buttonDel_clicked() {
  QModelIndex cell = ui->tableView->selectionModel()->currentIndex();
  QString name = cell.data(Qt::DisplayRole).toString();
  bool b = sqlextra->deleteExapnd(name);
  if (b) {
    reLoadAll();
    ui->buttonDel->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->expandText->setEnabled(false);
    ui->expandText->clear();
    ui->shortcut->clear();
  }
}

void drugExapnder::load(const QModelIndex &index) {
  QString name = index.data(Qt::DisplayRole).toString();
  ui->buttonDel->setEnabled(true);
  ui->saveButton->setEnabled(true);
  ui->expandText->setEnabled(true);
  ui->expandText->setHtml(sqlextra->getExpand(name));
}

void drugExapnder::reLoadAll() {
  model->setStringList(sqlextra->getExpandList());
  ui->buttonDel->setEnabled(false);
  ui->saveButton->setEnabled(false);
  ui->expandText->setEnabled(false);
  ui->expandText->clear();
  emit reloadCompleter();
  // emit reloadDrugsCompleter();
}

void drugExapnder::addThisName() {
  QString name = ui->shortcut->text().simplified();
  bool b = sqlextra->addNewExpand(name);
  reLoadAll();
  if (!b)
    emit newMessage(
        "WARNING",
        "FAILED TO ADD THIS SHORTCUT,MAY BE IT'S ALREADY THERE OR A DUPLICATE");
  ui->shortcut->clear();
  ui->shortcut->setFocus();
}
