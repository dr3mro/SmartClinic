// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "listeditor.h"

#include "ui_listeditor.h"

listEditor::listEditor(QWidget *parent)
    : mDialog(parent), ui(new Ui::listEditor) {
  ui->setupUi(this);
  ui->buttonDelete->setEnabled(false);
  sqlextra = new sqlExtra(this, "qt_sql_extra_listEdit", false);
  QStringList lists;
  lists << "allergies"
        << "complaints"
        << "diagnoses"
        << "dictionary"
        << "doses"
        << "drugs"
        << "surgeries"
        << "investigations"
        << "jobs"
        << "places"
        << "placeOfBirth";
  QString initialItem = lists.at(0);
  ui->lineEdit->setTableDeli(initialItem);
  emit loadCompleters();
  ui->lineEdit->setFocus(Qt::OtherFocusReason);
  QStringList items = sqlextra->getAutoCompleteList(initialItem);
  model = new QStringListModel(this);
  model->setStringList(items);
  proxy_model = new QSortFilterProxyModel(this);
  proxy_model->setFilterKeyColumn(0);
  proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
  proxy_model->setSourceModel(model);
  ui->tableView->setModel(proxy_model);
  ui->tableView->sortByColumn(0, Qt::AscendingOrder);
  ui->tableView->horizontalHeader()->setStretchLastSection(true);
  connect(ui->lineEdit, SIGNAL(completerLoaded()), this,
          SLOT(completerInitialized()));
  emit setReadWrite(true);
  ui->comboList->addItems(lists);
  this->setStyleSheet(settings.themeMaker());
  setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

listEditor::~listEditor() {
  delete model;
  delete proxy_model;
  sqlextra->optimize();
  delete sqlextra;
  QSqlDatabase::removeDatabase("qt_sql_extra_listEdit");
  delete ui;
}

void listEditor::on_comboList_currentIndexChanged(const QString &arg1) {
  QStringList contentsList = sqlextra->getAutoCompleteList(arg1);
  refreshCompleters();
  model->setStringList(contentsList);
  ui->buttonDelete->setDisabled(true);
}

void listEditor::refreshCompleters() {
  if (completerModelInitialized) {
    ui->lineEdit->setTableDeli(ui->comboList->currentText());
    ui->lineEdit->mUpdateCompleter();
  }
}

void listEditor::on_buttonDelete_clicked() {
  QModelIndex cell = ui->tableView->selectionModel()->currentIndex();
  int row = cell.row();
  int parentRow = proxy_model->mapToSource(proxy_model->index(row, 0)).row();
  QString item = cell.data(Qt::DisplayRole).toString();
  QString table = ui->comboList->currentText();
  bool b = sqlextra->removeFromAutoComplete(table, item);
  if (b) model->removeRow(parentRow);
  ui->buttonDelete->setDisabled((model->rowCount() < 1));
  refreshCompleters();
}

void listEditor::on_buttonAdd_clicked() {
  ui->buttonDelete->setEnabled(false);
  QFileDialog *fileDialog = new QFileDialog(this);
  QString listFile = fileDialog->getOpenFileName(this);
  QStringList list = dataIOhelper::getTextFileContentsAsList(listFile);
  for (int i = 0; i < list.count(); i++) {
    sqlextra->addToAutoComplete(ui->comboList->currentText(), list.at(i), true);
  }
  fileDialog->deleteLater();
  updateList();
}
void listEditor::updateList() {
  QString table = ui->comboList->currentText();
  model->setStringList(sqlextra->getAutoCompleteList(table));
  refreshCompleters();
}

void listEditor::on_lineEdit_returnPressed() {
  QString item = ui->lineEdit->text();

  bool b = sqlextra->addToAutoComplete(ui->comboList->currentText(), item);
  if (b) updateList();
}

void listEditor::closeEvent(QCloseEvent *event) {
  emit reloadCompleter();
  mDialog::closeEvent(event);
}

void listEditor::on_closeButton_clicked() { this->close(); }

void listEditor::completerInitialized() { completerModelInitialized = true; }

void listEditor::on_lineEdit_textChanged(const QString &arg1) {
  proxy_model->setFilterWildcard(arg1);
}

void listEditor::on_tableView_clicked(const QModelIndex &index) {
  Q_UNUSED(index)
  ui->buttonDelete->setEnabled(true);
}
