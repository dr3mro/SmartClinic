// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "searchwidget.h"

#include "ui_searchwidget.h"

searchWidget::searchWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::searchWidget) {
  ui->setupUi(this);
  validator.setRegularExpression(QRegularExpression("^\\S(.*\\S)?$"));
  ui->filterLineEdit->setValidator(&validator);

  QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",
                QSettings::NativeFormat);
  setFilter(reg.value("filterColumn").toInt());
  isFuzzySearchEnabled = reg.value("enableFuzzySearch").toBool();
  ui->fuzzyCheckBox->setChecked(isFuzzySearchEnabled);

  ui->PatientListTableView->setConnection();
  ui->filtersWidget->hide();
  ui->PatientListTableView->hideColumn(2);

  //    qRegisterMetaType<QList<QPersistentModelIndex>
  //    >("QList<QPersistentModelIndex>");
  //    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");

  connect(this, SIGNAL(loadPatient()), ui->PatientListTableView,
          SLOT(loadPatient()));
  connect(this, SIGNAL(updatePatients()), ui->PatientListTableView,
          SLOT(updatePatients()));
  connect(ui->filterLineEdit, SIGNAL(focusPatientTable()), this,
          SLOT(focusList()));
  connect(ui->PatientListTableView, SIGNAL(focusFilterBox()), this,
          SLOT(focusFilter()), Qt::QueuedConnection);
  connect(ui->PatientListTableView, SIGNAL(setFilter(int)), this,
          SLOT(setFilter(int)), Qt::QueuedConnection);
}

void searchWidget::selectRow(int row) {
  ui->PatientListTableView->mSelectRow(row);
}

void searchWidget::clearFilter() { ui->filterLineEdit->clear(); }

void searchWidget::focusFilter() {
  ui->filterLineEdit->setFocus(Qt::OtherFocusReason);
  int row = ui->PatientListTableView->getID() - 1;
  ui->PatientListTableView->mSelectRow((row >= 0) ? row : 0);
}

void searchWidget::focusList() {
  ui->PatientListTableView->setFocus(Qt::OtherFocusReason);
  int row = ui->PatientListTableView->getID() - 1;
  ui->PatientListTableView->mSelectRow((row >= 0) ? row : 0);
}

void searchWidget::setID(int ID) { ui->PatientListTableView->setID(ID); }

void searchWidget::setSearchString(const QString &str) {
  ui->filterLineEdit->setText(str);
}

void searchWidget::closeDatabase() {
  ui->PatientListTableView->closeDatabase();
}

void searchWidget::reConnectDatabase() {
  ui->PatientListTableView->reOpenDatabase();
  // ui->PatientListTableView->setConnection();
}

void searchWidget::toggleListHeader(bool visible) {
  ui->PatientListTableView->horizontalHeader()->setVisible(visible);
}

void searchWidget::updatePatientList() {
  ui->PatientListTableView->updatePatients();
}

searchWidget::~searchWidget() { delete ui; }

void searchWidget::setFilter(int fc_) {
  switch (fc_) {
    case 0:
      ui->filterByIDRadio->setChecked(true);
      break;
    case 1:
      ui->filterByNameRadio->setChecked(true);
      break;
    case 2:
      ui->filterByMobileRadio->setChecked(true);
      break;
    default:
      break;
  }
}

void searchWidget::showHideFilters(bool checked) {
  filtersVisibility = checked;
  ui->filtersWidget->setVisible(checked);
}

void searchWidget::on_filterLineEdit_textChanged(const QString &arg1) {
  // Create a copy of static string
  QString str = arg1;

  // replace ؟ with ? to fix arabic search
  str.replace(QString("؟"), QString("?"));

  if (!filtersVisibility) {
    QRegularExpression phone("^[0][0-9]{0,10}");
    QRegularExpression id("[1-9]+[0-9]*");

    if (phone.match(str).hasMatch()) {  // check if str is a phone number
      ui->PatientListTableView->setFiletrByMobile();
      ui->PatientListTableView->sortByColumn(0, Qt::AscendingOrder);
      // mDebug() << str << "filter by mobile";
    } else if (id.match(str).hasMatch()) {  // check if str is ID
      ui->PatientListTableView->setFilterByID();
      ui->PatientListTableView->sortByColumn(0, Qt::AscendingOrder);
      // mDebug() << str << "filter by id";
    } else {  // if not then it should be a name
      ui->PatientListTableView->setFilterByName();
      ui->PatientListTableView->sortByColumn(0, Qt::AscendingOrder);
      // mDebug() << str << "filter by name";
    }
  }

  if (isFuzzySearchEnabled) {
    str.replace(" ", "*");
    str.replace(
        QRegularExpression(
            "[ا|أ|إ|آ]",
            QRegularExpression::PatternOption::UseUnicodePropertiesOption),
        "[ا,أ,إ,آ]");
    str.replace(
        QRegularExpression(
            "[ه|ة]",
            QRegularExpression::PatternOption::UseUnicodePropertiesOption),
        "[ه,ة]");
    str.replace(
        QRegularExpression(
            "[ى|ي]",
            QRegularExpression::PatternOption::UseUnicodePropertiesOption),
        "[ى,ي]");
    str.replace(QString("بو"), "بو*");
    str.replace(QString("عبد"), "عبد*");
    str.replace(
        QRegularExpression(
            "(?<!ب)[ؤ|و]+[ء]*",
            QRegularExpression::PatternOption::UseUnicodePropertiesOption),
        "[ؤ,و]*");
  }

  // mDebug() << str;
  ui->PatientListTableView->FilterPatients(str);
  ui->PatientListTableView->mSelectRow(0);
}

void searchWidget::on_filterByNameRadio_toggled(bool checked) {
  if (checked) ui->PatientListTableView->setFilterByName();
  filterToggled();
}

void searchWidget::on_filterByIDRadio_toggled(bool checked) {
  if (checked) ui->PatientListTableView->setFilterByID();
  filterToggled();
}

void searchWidget::on_filterByMobileRadio_toggled(bool checked) {
  if (checked) ui->PatientListTableView->setFiletrByMobile();
  filterToggled();
}

void searchWidget::filterToggled() { focusFilter(); }

void searchWidget::on_filterLineEdit_returnPressed() {
  if (ui->filterLineEdit->text().length() > 0) {
    emit loadPatient();
    emit closePatientList();
  }
}

void searchWidget::on_PatientListTableView_activated(const QModelIndex &index) {
  int ID = ui->PatientListTableView->getSelectedPatientID(&index);
  emit loadPatient(ID);
  emit closePatientList();
}

void searchWidget::on_fuzzyCheckBox_clicked(bool checked) {
  QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",
                QSettings::NativeFormat);
  isFuzzySearchEnabled = checked;
  reg.setValue("enableFuzzySearch", isFuzzySearchEnabled);
  on_filterLineEdit_textChanged(ui->filterLineEdit->text());
}
