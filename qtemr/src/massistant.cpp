// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "massistant.h"

#include "ui_massistant.h"

mAssistant::mAssistant(mLabelMsg &_labelMsg, QWidget *parent, bool &eMode)
    : mDialog(parent),
      labelMsg(_labelMsg),
      editingMode(eMode),
      sqlbase(new sqlBase(this, "qt_sql_base_mAssist", false)),
      sqlextra(new sqlExtra(this, "qt_sql_extra_mAssist", false)),
      calcModel(new QStandardItemModel),
      agendaModel(new QStandardItemModel),
      myRegisterModel(new QStandardItemModel),
      eddModel(new QStandardItemModel),
      ui(new Ui::mAssistant),
      fromCalWidget(new mCalendarWidget(this)),
      toCalWidget(new mCalendarWidget(this)) {
  ui->setupUi(this);
  // qRegisterMetaType<Qt::Orientation>("Qt::Orientation");
  setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
  ui->fromDate->setCalendarWidget(fromCalWidget);
  ui->toDate->setCalendarWidget(toCalWidget);

  QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",
                QSettings::NativeFormat);
  if (reg.value("viewSinceLastCheckout").toBool())
    ui->cbSinceLastCheckout->setChecked(true);
  else
    setTimePeriod();

  ui->agendaTableView->horizontalHeader()->setVisible(true);
  ui->agendaTableView->verticalHeader()->setVisible(true);
  ui->cashTableView->horizontalHeader()->setVisible(true);
  ui->cashTableView->verticalHeader()->setVisible(true);

  setcheckoutTooltip();

  if (settings.userSpeciality() == dataHelper::Speciality::ObGyn) {
    ui->mAssistantTabWidget->addTab(&expectedDeliveries,
                                    QString("Expected Deliveries"));
    QShortcut *F3 = new QShortcut(QKeySequence("F3"), this);
    connect(F3, &QShortcut::activated, this,
            &mAssistant::goExpectedDeliveriesTab);
    connect(&expectedDeliveries, &ExpectedDeliveries::reload, this,
            &mAssistant::loadDeliveries);
    connect(&eddModelFutureWatcher,
            &QFutureWatcher<QStandardItemModel *>::finished, this,
            &mAssistant::onEddModelLoaded);
    connect(expectedDeliveries.getTableView(), &QTableView::activated, this,
            &mAssistant::LoadPatient);
  }
  connect(ui->agendaTableView, &QTableView::activated, this,
          &mAssistant::LoadPatient);
  connect(ui->cashTableView, &QTableView::activated, this,
          &mAssistant::LoadPatient);
  connect(&agendaModelFutureWatcher,
          &QFutureWatcher<QStandardItemModel *>::finished, this,
          &mAssistant::onAgendaModelLoaded);
  connect(&cashModelFutureWatcher,
          &QFutureWatcher<QStandardItemModel *>::finished, this,
          &mAssistant::onCashModelLoaded);
  // connect(&registerServiceLoaderFutureWatcher,&QFutureWatcher<void>::finished,this,&mAssistant::doCalcs);
  connect(ui->cashTableView, &mCashTableView::doCalculations, this,
          &mAssistant::doCalcs);
  ui->agendaTableView->setToolTip(
      "<html>"
      "<table>"
      "<tr><b>Tips:</b></tr>"
      "<tr><b>Use F8 to F12 to change current Date.</b></tr>"
      "<tr><b style=\"color:Green; \"> &#9632;</b> : New Visit.</tr>"
      "<tr><b style=\"color:Yellow;\"> &#9632;</b> : Attended First follow "
      "up.</tr>"
      "<tr><b style=\"color:Red;   \"> &#9632;</b> : Missed First Follow "
      "up.</tr>"
      "<tr><b style=\"color:Grey;  \"> &#9632;</b> : Subsequent Follow "
      "ups.</tr>"
      "<tr><b style=\"color:Black; \"> &#9633;</b> : Free Visit.</tr>"
      "</table>"
      "</html>");
  ui->cashTableView->setToolTip(
      "<html>"
      "<table>"
      "<tr><b>Tips:</b></tr>"
      "<tr><b>Use F8 to F12 to change current Date.</b></tr>"
      "<tr><b style=\"color:Green; \"> &#9632;</b> : New Visit.</tr>"
      "<tr><b style=\"color:Yellow;\"> &#9632;</b> : Attended First follow "
      "up.</tr>"
      "<tr><b style=\"color:Grey;  \"> &#9632;</b> : Subsequent Follow "
      "ups.</tr>"
      "<tr><b style=\"color:Black; \"> &#9633;</b> : Free Visit.</tr>"
      "</table>"
      "</html>");
  QDesktopWidget mDW;
  this->resize(QSize(mDW.width() * 0.80, this->height()));
}

mAssistant::~mAssistant() {
  eddModelFuture.waitForFinished();
  agendaModelFuture.waitForFinished();
  agendaModelAttendedFuture.waitForFinished();
  cashModelFuture.waitForFinished();
  // registerServiceLoaderFuture.waitForFinished();
  calcModelFuture.waitForFinished();

  QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",
                QSettings::NativeFormat);
  reg.setValue("viewSinceLastCheckout", ui->cbSinceLastCheckout->isChecked());

  sqlbase->optimize();
  sqlextra->optimize();
  delete sqlbase;
  delete sqlextra;
  QSqlDatabase::removeDatabase("qt_sql_base_mAssist");
  QSqlDatabase::removeDatabase("qt_sql_extra_mAssist");
  delete calcModel;
  delete agendaModel;
  delete myRegisterModel;
  delete fromCalWidget;
  delete toCalWidget;
  delete eddModel;
  // delete labelMsg;
  delete ui;
}

void mAssistant::loadCurrentSelectedAgenda() {
  if (agendaModelAttendedFuture.isRunning() || agendaModelFuture.isRunning())
    return;

  if (ui->mAssistantTabWidget->currentIndex() == 0) {
    labelMsg.setMessage("<b> Please wait... </b>");
    labelMsg.show();
  }

  ui->agendaTableView->setModel(nullptr);
  int currentDate =
      static_cast<int>(ui->agendaCalendar->selectedDate().toJulianDay());
#if QT_VERSION >= 0x060000
  agendaModelFuture = QtConcurrent::run(&sqlBase::getAgendaModel, sqlbase,
                                        currentDate, agendaModel);
#else
  agendaModelFuture = QtConcurrent::run(sqlbase, &sqlBase::getAgendaModel,
                                        currentDate, agendaModel);
#endif

  agendaModelFutureWatcher.setFuture(agendaModelFuture);
  agendaModelFuture.waitForFinished();
}

void mAssistant::tweakRegisterTable() {
  int servicesCount = sqlextra->getPaidServicesList().count();
  for (int i = 0; i <= servicesCount; ++i) {
    ui->cashTableView->horizontalHeader()->setSectionResizeMode(
        i + 5, QHeaderView::ResizeToContents);
  }

  ui->cashTableView->horizontalHeader()->setCascadingSectionResizes(true);
  ui->cashTableView->sortByColumn(2, Qt::SortOrder::AscendingOrder);
  ui->cashTableView->hideColumn(2);
  ui->cashTableView->hideColumn(3);
  ui->cashTableView->hideColumn(5);
  ui->cashTableView->setSelectionBehavior(
      QTableView::SelectionBehavior::SelectRows);
  ui->cashTableView->setWordWrap(false);
  ui->cashTableView->horizontalHeader()->setSectionResizeMode(
      4, QHeaderView::ResizeToContents);
  ui->cashTableView->horizontalHeader()->setSectionResizeMode(
      1, QHeaderView::Stretch);
  ui->cashTableView->horizontalHeader()->setSectionResizeMode(
      0, QHeaderView::ResizeToContents);
}

void mAssistant::loadRegister() {
  if (cashModelFuture.isRunning() ||
      calcModelFuture
          .isRunning() /*|| registerServiceLoaderFuture.isRunning()*/)
    return;

  ui->goButton->setEnabled(false);
  if (ui->mAssistantTabWidget->currentIndex() == 1) {
    labelMsg.setMessage("<b> Please wait... </b>");
    labelMsg.show();
  }

  ui->cashTableView->setModel(nullptr);

  sqlBase::RegisterRange timeFrame;
  timeFrame.startDate = static_cast<int>(ui->fromDate->date().toJulianDay());
  timeFrame.startTime =
      static_cast<int>(ui->fromTime->time().msecsSinceStartOfDay() / 1000);
  timeFrame.endDate = static_cast<int>(ui->toDate->date().toJulianDay());
  timeFrame.endTime =
      static_cast<int>(ui->toTime->time().msecsSinceStartOfDay() / 1000);
  ui->cashTableView->setModel(nullptr);
#if QT_VERSION >= 0x060000
  cashModelFuture = QtConcurrent::run(&sqlBase::getMyRegisterModel, sqlbase,
                                      timeFrame, myRegisterModel, sqlextra);
#else
  cashModelFuture = QtConcurrent::run(sqlbase, &sqlBase::getMyRegisterModel,
                                      timeFrame, myRegisterModel, sqlextra);
#endif

  cashModelFutureWatcher.setFuture(cashModelFuture);
  cashModelFuture.waitForFinished();
}
void mAssistant::loadAgenda() {
  int currentDate;
  if (QTime::currentTime() <= QTime::fromString("23:59", "HH:mm") &&
      QTime::currentTime() >= QTime::fromString("08:00", "HH:mm")) {
    currentDate = static_cast<int>(QDate::currentDate().toJulianDay());
  } else {
    currentDate =
        static_cast<int>(QDate::currentDate().addDays(-1).toJulianDay());
  }
  ui->agendaCalendar->setSelectedDate(QDate::fromJulianDay(currentDate));
  loadCurrentSelectedAgenda();
}

void mAssistant::doCalcs() {
  double TOTAL = 0;
  QModelIndexList selection =
      ui->cashTableView->selectionModel()->selectedRows();
  ui->calcTableView->setModel(nullptr);
  calcModel->clear();

#if QT_VERSION >= 0x060000
  calcModelFuture = QtConcurrent::run(&sqlBase::getMyRegisterCalcModel, sqlbase,
                                      myRegisterModel, calcModel, sqlextra,
                                      std::ref(selection), std::ref(TOTAL));
#else
  calcModelFuture = QtConcurrent::run(sqlbase, &sqlBase::getMyRegisterCalcModel,
                                      myRegisterModel, calcModel, sqlextra,
                                      std::ref(selection), std::ref(TOTAL));
#endif

  calcModelFuture.waitForFinished();
  ui->calcTableView->setModel(calcModel);
  ui->calcTableView->setColumnWidth(0, 80);
  ui->calcTableView->setColumnWidth(1, 50);
  ui->calcTableView->setColumnWidth(2, 50);
  ui->calcTableView->horizontalHeader()->setStretchLastSection(true);
  ui->SUMlineEdit->setText(QString::number(TOTAL, 'f', 2));
  labelMsg.hide();
  ui->goButton->setEnabled(true);
}

void mAssistant::setTimePeriod() {
  mSettings::checkout checkout = settings.getCheckout();
  QDate checkDate = QDate::fromJulianDay(checkout.date);
  QTime checkTime = QTime::fromMSecsSinceStartOfDay(checkout.time * 1000);
  bool isCheckout = ui->cbSinceLastCheckout->isChecked();

  QDate selectedDate = ui->cashCalendar->selectedDate();
  QDate yesterDate = selectedDate.addDays(-1);
  QDate tomorroDate = selectedDate.addDays(1);
  QDate currentDate = QDate::currentDate();

  if (QTime::currentTime() >= QTime::fromString("08:00", "HH:mm") &&
      QTime::currentTime() <= QTime::fromString("23:59", "HH:mm")) {
    ui->fromDate->setDate(isCheckout ? checkDate : selectedDate);
    ui->toDate->setDate(tomorroDate);
  } else {
    if (selectedDate == currentDate) {
      ui->fromDate->setDate(isCheckout ? checkDate : yesterDate);
      ui->toDate->setDate(currentDate);
    } else {
      ui->fromDate->setDate(isCheckout ? checkDate : selectedDate);
      ui->toDate->setDate(tomorroDate);
    }
  }
  ui->fromTime->setTime(isCheckout ? checkTime
                                   : QTime::fromString("08:00", "HH:mm"));
  ui->toTime->setTime(QTime::fromString("07:59", "HH:mm"));
}

void mAssistant::setcheckoutTooltip() {
  mSettings::checkout checkout;
  checkout = settings.getCheckout();
  QString date = QDate::fromJulianDay(checkout.date).toString("dd/MM/yyyy");
  QString time = QTime::fromMSecsSinceStartOfDay(checkout.time * 1000)
                     .toString("hh:mm AP");
  ui->btnCheckout->setToolTip(QString("Last check out:\n"
                                      "%1 %2")
                                  .arg(date)
                                  .arg(time));
}

void mAssistant::LoadPatient(const QModelIndex &modelIndex) {
  if (editingMode) {
    QMessageBox msgbox;
    int reply = msgbox.question(
        nullptr, "Message",
        "You are in <EDIT MODE> , loading another record will lead to loss of "
        "any unsaved data are you sure that you want to cont.?",
        QMessageBox::Yes, QMessageBox::No);

    if (reply == QMessageBox::No) return;
  }

  int ID = modelIndex.sibling(modelIndex.row(), 0).data().toInt();
  emit toggleEditMode(false);
  emit loadThisPatient(ID);
  this->close();
}

void mAssistant::loadDeliveries() {
  if (settings.userSpeciality() == dataHelper::Speciality::ObGyn) {
    if (eddModelFuture.isRunning()) return;
    QDate startDate = QDate::fromString(QString("1/%1/%2")
                                            .arg(expectedDeliveries.getMonth())
                                            .arg(expectedDeliveries.getYear()),
                                        "d/M/yyyy");
    qint64 startJulian = startDate.toJulianDay();
    qint64 endJulian = startDate.addMonths(1).toJulianDay();
#if QT_VERSION >= 0x060000
    eddModelFuture = QtConcurrent::run(&sqlBase::getEddModel, sqlbase,
                                       startJulian, endJulian, eddModel);
#else
    eddModelFuture = QtConcurrent::run(sqlbase, &sqlBase::getEddModel,
                                       startJulian, endJulian, eddModel);
#endif

    eddModelFutureWatcher.setFuture(eddModelFuture);
    eddModelFuture.waitForFinished();
  }
}

void mAssistant::onEddModelLoaded() {
  eddModel = eddModelFuture.result();
  expectedDeliveries.setModel(eddModel);
}

void mAssistant::onAgendaModelLoaded() {
  double percent = 0;
  agendaModel = agendaModelFuture.result();
  ui->agendaTableView->setModel(agendaModel);
  ui->agendaTableView->horizontalHeader()->setCascadingSectionResizes(true);
  ui->agendaTableView->horizontalHeader()->setSectionResizeMode(
      2, QHeaderView::ResizeToContents);
  ui->agendaTableView->horizontalHeader()->setSectionResizeMode(
      1, QHeaderView::Stretch);
  ui->agendaTableView->horizontalHeader()->setSectionResizeMode(
      0, QHeaderView::ResizeToContents);
  ui->agendaTableView->clearSelection();

  int currentDate =
      static_cast<int>(ui->agendaCalendar->selectedDate().toJulianDay());
#if QT_VERSION >= 0x060000
  agendaModelAttendedFuture =
      QtConcurrent::run(&sqlBase::agendaAttendedLoader, sqlbase, currentDate,
                        agendaModel, std::ref(percent));
#else
  agendaModelAttendedFuture =
      QtConcurrent::run(sqlbase, &sqlBase::agendaAttendedLoader, currentDate,
                        agendaModel, std::ref(percent));
#endif
  agendaModelAttendedFuture.waitForFinished();

  ui->percentage->setText(QString("%1%").arg(percent, 2, 'f', 2));
  labelMsg.hide();
}

void mAssistant::onCashModelLoaded() {
  myRegisterModel = cashModelFuture.result();
  ui->cashTableView->setModel(myRegisterModel);
  tweakRegisterTable();
  doCalcs();
  //    registerServiceLoaderFuture =
  //    QtConcurrent::run(sqlbase,&sqlBase::registerServiceLoader,myRegisterModel,sqlextra);
  //    registerServiceLoaderFutureWatcher.setFuture(registerServiceLoaderFuture);
  //    registerServiceLoaderFuture.waitForFinished();
}

void mAssistant::goExpectedDeliveriesTab() {
  ui->mAssistantTabWidget->setCurrentIndex(2);
}

void mAssistant::keyPressEvent(QKeyEvent *event) {
  if (ignoreKeyEvents) {
    mDialog::keyPressEvent(event);
    return;
  }

  if (event->key() == Qt::Key_F1)
    ui->mAssistantTabWidget->setCurrentIndex(0);
  else if (event->key() == Qt::Key_F2)
    ui->mAssistantTabWidget->setCurrentIndex(1);

  if (ui->mAssistantTabWidget->currentIndex() == 0)
    calendar = ui->agendaCalendar;
  else if (ui->mAssistantTabWidget->currentIndex() == 1)
    calendar = ui->cashCalendar;

  if (event->key() == Qt::Key_F8) {
    calendar->setSelectedDate(QDate::currentDate());
    emit calendar->clicked(calendar->selectedDate());
  } else if (event->key() == Qt::Key_F9) {
    calendar->setSelectedDate(calendar->selectedDate().addDays(-1));
    emit calendar->clicked(calendar->selectedDate());
  } else if (event->key() == Qt::Key_F10) {
    calendar->setSelectedDate(calendar->selectedDate().addDays(7));
    emit calendar->clicked(calendar->selectedDate());
  } else if (event->key() == Qt::Key_F11) {
    calendar->setSelectedDate(calendar->selectedDate().addDays(-7));
    emit calendar->clicked(calendar->selectedDate());
  } else if (event->key() == Qt::Key_F12) {
    calendar->setSelectedDate(calendar->selectedDate().addDays(1));
    emit calendar->clicked(calendar->selectedDate());
  }

  mDialog::keyPressEvent(event);
}

void mAssistant::keyReleaseEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Shift || event->key() == Qt::Key_Control)
    if (ui->cashTableView->selectionModel()->currentIndex().row() >= 0)
      doCalcs();
  mDialog::keyReleaseEvent(event);
}

void mAssistant::showEvent(QShowEvent *e) {
  int width = this->width();
  int height = static_cast<int>(wm.getDesktop().height() * 0.9);
  resize(width, height);
  mDialog::showEvent(e);
  ignoreKeyEvents = false;
}

void mAssistant::closeEvent(QCloseEvent *e) {
  ignoreKeyEvents = true;
#if QT_VERSION >= 0x060000
  auto f1 = QtConcurrent::run(&QStandardItemModel::clear, myRegisterModel);
  auto f2 = QtConcurrent::run(&QStandardItemModel::clear, calcModel);
  auto f3 = QtConcurrent::run(&QStandardItemModel::clear, eddModel);
  auto f4 = QtConcurrent::run(&QStandardItemModel::clear, agendaModel);
#else
  auto f1 = QtConcurrent::run(myRegisterModel, &QStandardItemModel::clear);
  auto f2 = QtConcurrent::run(calcModel, &QStandardItemModel::clear);
  auto f3 = QtConcurrent::run(eddModel, &QStandardItemModel::clear);
  auto f4 = QtConcurrent::run(agendaModel, &QStandardItemModel::clear);
#endif
  mDialog::closeEvent(e);
  f4.waitForFinished();
  f3.waitForFinished();
  f2.waitForFinished();
  f1.waitForFinished();
}

void mAssistant::on_closeButton_clicked() { this->close(); }

void mAssistant::on_goButton_clicked() {
  labelMsg.setMessage("<b> Please wait... </b>");
  labelMsg.show();
  loadRegister();
}

void mAssistant::on_fromDate_dateChanged(const QDate &fromDate) {
  QTime toTime = ui->toTime->time();
  QTime fromTime = ui->fromTime->time();
  QDate toDate = ui->toDate->date();
  ui->goButton->setEnabled(
      ((fromTime <= toTime && fromDate == toDate) || (toDate > fromDate))
          ? true
          : false);
  // mDebug() << toCalWidget->selectedDate().toJulianDay();
  toCalWidget->setMinimumDate(fromCalWidget->selectedDate());
  // ui->toDate->setMinimumDate(fromCalWidget->selectedDate());
}

void mAssistant::on_toDate_dateChanged(const QDate &toDate) {
  QTime toTime = ui->toTime->time();
  QDate fromDate = ui->fromDate->date();
  QTime fromTime = ui->fromTime->time();
  ui->goButton->setEnabled(
      ((fromTime <= toTime && fromDate == toDate) || (toDate > fromDate))
          ? true
          : false);
  // mDebug() << fromCalWidget->selectedDate().toJulianDay();
  fromCalWidget->setMaximumDate(toCalWidget->selectedDate());
  // ui->fromDate->setMaximumDate(toCalWidget->selectedDate());
}

void mAssistant::on_fromTime_timeChanged(const QTime &fromTime) {
  QTime toTime = ui->toTime->time();
  QDate fromDate = ui->fromDate->date();
  QDate toDate = ui->toDate->date();
  ui->goButton->setEnabled(
      ((fromTime <= toTime && fromDate == toDate) || (toDate > fromDate))
          ? true
          : false);
}

void mAssistant::on_toTime_timeChanged(const QTime &toTime) {
  QTime fromTime = ui->fromTime->time();
  QDate fromDate = ui->fromDate->date();
  QDate toDate = ui->toDate->date();
  ui->goButton->setEnabled(
      ((fromTime <= toTime && fromDate == toDate) || (toDate > fromDate))
          ? true
          : false);
}

void mAssistant::on_btnCheckout_clicked() {
  QItemSelectionModel *selectionModel = ui->cashTableView->selectionModel();
  int row = selectionModel->currentIndex().row();

  QString msg;

  if (row < 0)
    msg = "Are you Sure you want to set current time last check out point?";
  else
    msg =
        "Are you Sure you want to set current selected patient last check out "
        "point?";

  int reply = QMessageBox::question(nullptr, "Confirmation", msg,
                                    QMessageBox::Yes, QMessageBox::No);

  if (reply == QMessageBox::No) return;

  qint64 checkoutDate;
  qint64 checkoutTime;
  QString checkout;

  if (row < 0) {
    checkoutDate = QDate::currentDate().toJulianDay();
    checkoutTime = QTime::currentTime().msecsSinceStartOfDay() / 1000;
  } else {
    checkout =
        selectionModel->model()->index(row, 2).data(Qt::DisplayRole).toString();
    checkoutDate = checkout.left(7).toInt();
    checkoutTime = checkout.remove(0, 7).toInt() + 1;
  }

  settings.setCheckout(checkoutDate, checkoutTime);
  setcheckoutTooltip();

  if (ui->cbSinceLastCheckout->isChecked()) {
    loadCheckout();
    loadRegister();
  } else
    ui->cbSinceLastCheckout->setChecked(true);
}

void mAssistant::loadCheckout() {
  mSettings::checkout checkout = settings.getCheckout();
  ui->cashCalendar->setSelectedDate(QDate::fromJulianDay(checkout.date));
  ui->fromDate->setDate(QDate::fromJulianDay(checkout.date));
  ui->fromTime->setTime(QTime::fromMSecsSinceStartOfDay(checkout.time * 1000));
  ui->toDate->setDate(QDate::currentDate());
  ui->toTime->setTime(QTime::currentTime());
}

void mAssistant::on_cbSinceLastCheckout_toggled(bool checked) {
  if (checked) {
    loadCheckout();
  } else {
    ui->cashCalendar->setSelectedDate(QDate::currentDate());
    setTimePeriod();
  }

  ui->fromDate->setReadOnly(checked);
  ui->fromTime->setReadOnly(checked);
  ui->toDate->setReadOnly(checked);
  ui->toTime->setReadOnly(checked);

  loadRegister();
}

void mAssistant::on_cashCalendar_clicked(const QDate &date) {
  Q_UNUSED(date)
  ui->cbSinceLastCheckout->setChecked(false);
  setTimePeriod();
  loadRegister();
}

void mAssistant::load() {
  ui->cashCalendar->setSelectedDate(QDate::currentDate());
  setTimePeriod();
  QTimer::singleShot(0, this, &mAssistant::loadAgenda);
  QTimer::singleShot(250, this, &mAssistant::loadRegister);
  QTimer::singleShot(500, this, &mAssistant::loadDeliveries);
}

void mAssistant::on_agendaCalendar_clicked(const QDate &date) {
  Q_UNUSED(date)
  loadCurrentSelectedAgenda();
}
