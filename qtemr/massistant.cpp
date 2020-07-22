#include "massistant.h"
#include "ui_massistant.h"

mAssistant::mAssistant(mLabelMsg& labelMsg, QWidget *parent,bool& eMode) :
    mDialog(parent),
    labelMsg(labelMsg),
    editingMode(eMode),
    sqlbase(new sqlBase(this,"qt_sql_base_mAssist",false)),
    sqlextra(new sqlExtra(this,"qt_sql_extra_mAssist",false)),
    calcModel(new QStandardItemModel(this)),
    agendaModel(new QStandardItemModel(this)),
    myRegisterModel ( new QStandardItemModel(this)),
    eddModel ( new QStandardItemModel(this)),
    ui(new Ui::mAssistant),
    fromCalWidget(new mCalendarWidget(this)),
    toCalWidget(new mCalendarWidget(this))
{
    ui->setupUi(this);
    //qRegisterMetaType<Qt::Orientation>("Qt::Orientation");
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    ui->fromDate->setCalendarWidget(fromCalWidget);
    ui->toDate->setCalendarWidget(toCalWidget);

    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    if (reg.value("viewSinceLastCheckout").toBool())
        ui->cbSinceLastCheckout->setChecked(true);
    else
        setTimePeriod();

    ui->agendaTableView->horizontalHeader()->setVisible(true);
    ui->agendaTableView->verticalHeader()->setVisible(true);
    ui->cashTableView->horizontalHeader()->setVisible(true);
    ui->cashTableView->verticalHeader()->setVisible(true);

    setcheckoutTooltip();

    if(settings.userSpeciality() == dataHelper::Speciality::ObGyn)
    {
        ui->mAssistantTabWidget->addTab(&expectedDeliveries,QString("Expected Deliveries"));
        QShortcut *F3 = new QShortcut(QKeySequence("F3"), this);
        connect(F3,&QShortcut::activated,this,&mAssistant::goExpectedDeliveriesTab);
        connect(&expectedDeliveries,&ExpectedDeliveries::reload,this,&mAssistant::loadDeliveries);
        connect(&eddModelFutureWatcher,&QFutureWatcher<QStandardItemModel*>::finished,
                this,&mAssistant::onEddModelLoaded);
        connect(expectedDeliveries.getTableView(),&QTableView::activated,this,&mAssistant::LoadPatient);
    }
    connect(ui->agendaTableView,&QTableView::activated,this,&mAssistant::LoadPatient);
    connect(ui->cashTableView,&QTableView::activated,this,&mAssistant::LoadPatient);
    connect(&agendaModelFutureWatcher,&QFutureWatcher<QStandardItemModel*>::finished,
            this,&mAssistant::onAgendaModelLoaded);
    connect(&cashModelFutureWatcher,&QFutureWatcher<QStandardItemModel*>::finished,
            this,&mAssistant::onCashModelLoaded);
    connect(&registerServiceLoaderFutureWatcher,&QFutureWatcher<void>::finished,this,&mAssistant::doCalcs);
    connect(ui->cashTableView,&mCashTableView::doCalculations,this,&mAssistant::doCalcs);
    ui->agendaTableView->setToolTip("<html>"
                                    "<table>"
                                    "<tr><b>Tips:</b></tr>"
                                    "<tr><b>Use F9 to F12 to change current Date.</b></tr>"
                                    "<tr><b style=\"color:Green; \"> &#9632;</b> : New Visit.</tr>"
                                    "<tr><b style=\"color:Yellow;\"> &#9632;</b> : Attended First follow up.</tr>"
                                    "<tr><b style=\"color:Red;   \"> &#9632;</b> : Missed First Follow up.</tr>"
                                    "<tr><b style=\"color:Grey;  \"> &#9632;</b> : Subsequent Follow ups.</tr>"
                                    "<tr><b style=\"color:Black; \"> &#9633;</b> : Free Visit.</tr>"
                                    "</table>"
                                    "</html>");
    ui->cashTableView->setToolTip("<html>"
                                  "<table>"
                                  "<tr><b>Tips:</b></tr>"
                                  "<tr><b>Use F9 to F12 to change current Date.</b></tr>"
                                  "<tr><b style=\"color:Green; \"> &#9632;</b> : New Visit.</tr>"
                                  "<tr><b style=\"color:Yellow;\"> &#9632;</b> : Attended First follow up.</tr>"
                                  "<tr><b style=\"color:Grey;  \"> &#9632;</b> : Subsequent Follow ups.</tr>"
                                  "<tr><b style=\"color:Black; \"> &#9633;</b> : Free Visit.</tr>"
                                  "</table>"
                                  "</html>");
}

mAssistant::~mAssistant()
{
    eddModelFuture.waitForFinished();
    agendaModelFuture.waitForFinished();
    agendaModelAttendedFuture.waitForFinished();
    cashModelFuture.waitForFinished();
    registerServiceLoaderFuture.waitForFinished();
    calcModelFuture.waitForFinished();

    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    reg.setValue("viewSinceLastCheckout",ui->cbSinceLastCheckout->isChecked());

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
    //delete labelMsg;
    delete ui;
}

void mAssistant::loadCurrentSelectedAgenda()
{
    if(agendaModelAttendedFuture.isRunning() || agendaModelFuture.isRunning())
        return;

    if(ui->mAssistantTabWidget->currentIndex() == 0 ){
        labelMsg.setMessage("<b> Please wait... </b>");
        labelMsg.show();
    }

    ui->agendaTableView->setModel(nullptr);
    int currentDate = static_cast<int>(ui->agendaCalendar->selectedDate().toJulianDay());
    agendaModelFuture = QtConcurrent::run(sqlbase,&sqlBase::getAgendaModel,currentDate,agendaModel);
    agendaModelFutureWatcher.setFuture(agendaModelFuture);

    agendaModelFuture.waitForFinished();
}

void mAssistant::tweakRegisterTable()
{
    int servCOUNT = sqlextra->getPaidServicesList().count();
    servCOUNT = (servCOUNT>4)? 4:servCOUNT;
    int servPixelWidth = 50*servCOUNT;
    ui->cashTableView->horizontalHeader()->setDefaultSectionSize(50);
    ui->cashTableView->horizontalHeader()->setStretchLastSection(true);
    ui->cashTableView->setColumnWidth(0,40);
    ui->cashTableView->setColumnWidth(1,350-servPixelWidth);
    ui->cashTableView->setColumnWidth(4,80);

    ui->cashTableView->sortByColumn(2,Qt::SortOrder::AscendingOrder);
    ui->cashTableView->hideColumn(2);
    ui->cashTableView->hideColumn(3);
    ui->cashTableView->hideColumn(5);
    ui->cashTableView->setSelectionBehavior(QTableView::SelectionBehavior::SelectRows);
    ui->cashTableView->setWordWrap(false);
}

void mAssistant::loadRegister()
{
    if(cashModelFuture.isRunning() || calcModelFuture.isRunning() )
        return;

    if(ui->mAssistantTabWidget->currentIndex() == 1){
        labelMsg.setMessage("<b> Please wait... </b>");
        labelMsg.show();
    }

    ui->cashTableView->setModel(nullptr);

    sqlBase::RegisterRange timeFrame;
    timeFrame.startDate = static_cast<int>(ui->fromDate->date().toJulianDay());
    timeFrame.startTime = static_cast<int>(ui->fromTime->time().msecsSinceStartOfDay()/1000);
    timeFrame.endDate = static_cast<int>(ui->toDate->date().toJulianDay());
    timeFrame.endTime = static_cast<int>(ui->toTime->time().msecsSinceStartOfDay()/1000);
    cashModelFuture = QtConcurrent::run(sqlbase,&sqlBase::getMyRegisterModel,timeFrame,myRegisterModel,sqlextra);
    cashModelFutureWatcher.setFuture(cashModelFuture);
    cashModelFuture.waitForFinished();
}
void mAssistant::loadAgenda()
{
    int currentDate;
    if (QTime::currentTime() <= QTime::fromString("23:59","HH:mm") &&
            QTime::currentTime() >= QTime::fromString("08:00","HH:mm")    ){
        currentDate = static_cast<int>(QDate::currentDate().toJulianDay());
    }else{
        currentDate = static_cast<int>(QDate::currentDate().addDays(-1).toJulianDay());
    }
    ui->agendaCalendar->setSelectedDate(QDate::fromJulianDay(currentDate));
    loadCurrentSelectedAgenda();
}

void mAssistant::doCalcs()
{
    double TOTAL=0;
    QModelIndexList selection = ui->cashTableView->selectionModel()->selectedRows();

    calcModelFuture = QtConcurrent::run(sqlbase,&sqlBase::getMyRegisterCalcModel,
                                        myRegisterModel,
                                        calcModel,
                                        sqlextra,
                                        std::ref(selection),
                                        std::ref(TOTAL));

    calcModelFuture.waitForFinished();
    ui->calcTableView->setModel(calcModel);
    ui->calcTableView->setColumnWidth(0,80);
    ui->calcTableView->setColumnWidth(1,50);
    ui->calcTableView->setColumnWidth(2,50);
    ui->calcTableView->horizontalHeader()->setStretchLastSection(true);
    ui->SUMlineEdit->setText(QString::number(TOTAL,'f',2));
    labelMsg.hide();

}

void mAssistant::setTimePeriod()
{
    mSettings::checkout checkout = settings.getCheckout();
    QDate checkDate = QDate::fromJulianDay(checkout.date);
    QTime checkTime = QTime::fromMSecsSinceStartOfDay(checkout.time*1000);
    bool isCheckout = ui->cbSinceLastCheckout->isChecked();

    QDate selectedDate = ui->cashCalendar->selectedDate();
    QDate yesterDate = selectedDate.addDays(-1);
    QDate tomorroDate = selectedDate.addDays(1);
    QDate currentDate = QDate::currentDate();

    if (QTime::currentTime() >= QTime::fromString("08:00","HH:mm") &&
            QTime::currentTime() <= QTime::fromString("23:59","HH:mm"))
    {
        ui->fromDate->setDate(isCheckout? checkDate:selectedDate);
        ui->toDate->setDate(tomorroDate);
    }
    else
    {
        if ( selectedDate == currentDate)
        {
            ui->fromDate->setDate(isCheckout? checkDate:yesterDate);
            ui->toDate->setDate(currentDate);
        }
        else
        {
            ui->fromDate->setDate(isCheckout? checkDate:selectedDate);
            ui->toDate->setDate(tomorroDate);
        }
    }
    ui->fromTime->setTime(isCheckout? checkTime:QTime::fromString("08:00","HH:mm"));
    ui->toTime->setTime(QTime::fromString("07:59","HH:mm"));
}

void mAssistant::setcheckoutTooltip()
{
    mSettings::checkout checkout;
    checkout = settings.getCheckout();
    QString date = QDate::fromJulianDay(checkout.date).toString("dd/MM/yyyy");
    QString time = QTime::fromMSecsSinceStartOfDay(checkout.time*1000).toString("hh:mm AP");
    ui->btnCheckout->setToolTip(QString("Last check out:\n"
                                        "%1 %2").arg(date)
                                .arg(time));

}

void mAssistant::LoadPatient(const QModelIndex &modelIndex)
{
    if ( editingMode )
    {
        QMessageBox msgbox;
        int reply = msgbox.question(nullptr,"Message",
                                    "You are in <EDIT MODE> , loading another record will lead to loss of any unsaved data are you sure that you want to cont.?",
                                    QMessageBox::Yes,QMessageBox::No);

        if (reply == QMessageBox::No)
            return;
    }

    int ID = modelIndex.sibling(modelIndex.row(),0).data().toInt();
    emit toggleEditMode(false);
    emit loadThisPatient(ID);
    this->close();
}

void mAssistant::loadDeliveries()
{
    if(settings.userSpeciality() == dataHelper::Speciality::ObGyn)
    {
        if(eddModelFuture.isRunning())
            return;
        QDate startDate = QDate::fromString(QString("1/%1/%2")
                                            .arg(expectedDeliveries.getMonth())
                                            .arg(expectedDeliveries.getYear()),"d/M/yyyy");
        qint64 startJulian = startDate.toJulianDay();
        qint64 endJulian = startDate.addMonths(1).toJulianDay();
        eddModelFuture = QtConcurrent::run(sqlbase,&sqlBase::getEddModel,startJulian,endJulian,eddModel);
        eddModelFutureWatcher.setFuture(eddModelFuture);
        eddModelFuture.waitForFinished();
    }
}

void mAssistant::onEddModelLoaded()
{
    eddModel = eddModelFuture.result();
    expectedDeliveries.setModel(eddModel);
}

void mAssistant::onAgendaModelLoaded()
{
    double percent = 0;
    agendaModel = agendaModelFuture.result();
    ui->agendaTableView->setModel(agendaModel);
    ui->agendaTableView->resizeColumnToContents(2);
    ui->agendaTableView->setColumnWidth(0,40);
    ui->agendaTableView->setColumnWidth(1,340);
    ui->agendaTableView->horizontalHeader()->setStretchLastSection(true);
    ui->agendaTableView->clearSelection();


    int currentDate = static_cast<int>(ui->agendaCalendar->selectedDate().toJulianDay());

    agendaModelAttendedFuture = QtConcurrent::run(sqlbase,&sqlBase::agendaAttendedLoader,currentDate,agendaModel,std::ref(percent));
    agendaModelAttendedFuture.waitForFinished();

    ui->percentage->setText(QString("%1%").arg(percent,2,'f',2));
    labelMsg.hide();
}

void mAssistant::onCashModelLoaded()
{
    myRegisterModel = cashModelFuture.result();
    ui->cashTableView->setModel(myRegisterModel);
    tweakRegisterTable();
    registerServiceLoaderFuture = QtConcurrent::run(sqlbase,&sqlBase::registerServiceLoader,myRegisterModel,sqlextra);
    registerServiceLoaderFutureWatcher.setFuture(registerServiceLoaderFuture);
    registerServiceLoaderFuture.waitForFinished();
}

void mAssistant::goExpectedDeliveriesTab()
{
    ui->mAssistantTabWidget->setCurrentIndex(2);
}

void mAssistant::keyPressEvent(QKeyEvent *event)
{
    if ( event->key() == Qt::Key_F1){
        ui->mAssistantTabWidget->setCurrentIndex(0);
    }else if ( event->key() == Qt::Key_F2){
        ui->mAssistantTabWidget->setCurrentIndex(1);
    }else if (ui->mAssistantTabWidget->currentIndex() == 0){
        if (event->key() == Qt::Key_F9){
            ui->agendaCalendar->setSelectedDate(ui->agendaCalendar->selectedDate().addDays(-1));
            emit ui->agendaCalendar->clicked(ui->agendaCalendar->selectedDate());
        }else if (event->key() == Qt::Key_F10 ){
            ui->agendaCalendar->setSelectedDate(ui->agendaCalendar->selectedDate().addDays(7));
            emit ui->agendaCalendar->clicked(ui->agendaCalendar->selectedDate());
        }else if (event->key() == Qt::Key_F11 ){
            ui->agendaCalendar->setSelectedDate(ui->agendaCalendar->selectedDate().addDays(-7));
            emit ui->agendaCalendar->clicked(ui->agendaCalendar->selectedDate());
        }else if (event->key() == Qt::Key_F12 ){
            ui->agendaCalendar->setSelectedDate(ui->agendaCalendar->selectedDate().addDays(1));
            emit ui->agendaCalendar->clicked(ui->agendaCalendar->selectedDate());
        }
    }else if (ui->mAssistantTabWidget->currentIndex() == 1){
        if (event->key() == Qt::Key_F9){
            ui->cashCalendar->setSelectedDate(ui->cashCalendar->selectedDate().addDays(-1));
            emit ui->cashCalendar->clicked(ui->cashCalendar->selectedDate());
        }else if (event->key() == Qt::Key_F10 ){
            ui->cashCalendar->setSelectedDate(ui->cashCalendar->selectedDate().addDays(7));
            emit ui->cashCalendar->clicked(ui->cashCalendar->selectedDate());
        }else if (event->key() == Qt::Key_F11 ){
            ui->cashCalendar->setSelectedDate(ui->cashCalendar->selectedDate().addDays(-7));
            emit ui->cashCalendar->clicked(ui->cashCalendar->selectedDate());
        }else if (event->key() == Qt::Key_F12 ){
            ui->cashCalendar->setSelectedDate(ui->cashCalendar->selectedDate().addDays(1));
            emit ui->cashCalendar->clicked(ui->cashCalendar->selectedDate());
        }
    }
    mDialog::keyPressEvent(event);
}

void mAssistant::keyReleaseEvent(QKeyEvent *event)
{
    if ( event->key() == Qt::Key_Shift || event->key() == Qt::Key_Control )
        if ( ui->cashTableView->selectionModel()->currentIndex().row() >= 0)
            doCalcs();
    mDialog::keyReleaseEvent(event);
}

void mAssistant::showEvent(QShowEvent *e)
{
    int width = this->width();
    int height = static_cast<int>(wm.getDesktop().height() *0.9);
    resize(width,height);
    mDialog::showEvent(e);
}

void mAssistant::closeEvent(QCloseEvent *e)
{   labelMsg.show();
    myRegisterModel->clear();
    calcModel->clear();
    eddModel->clear();
    agendaModel->clear();
    labelMsg.hide();
    mDialog::closeEvent(e);
}

void mAssistant::on_closeButton_clicked()
{
    this->close();
}

void mAssistant::on_goButton_clicked()
{
    labelMsg.setMessage("<b> Please wait... </b>");
    labelMsg.show();
    loadRegister();
}

void mAssistant::on_fromDate_dateChanged(const QDate &fromDate)
{
    QTime toTime = ui->toTime->time();
    QTime fromTime = ui->fromTime->time();
    QDate toDate = ui->toDate->date();
    ui->goButton->setEnabled(((fromTime <= toTime && fromDate == toDate)||(toDate>fromDate))? true:false);
    //mDebug() << toCalWidget->selectedDate().toJulianDay();
    toCalWidget->setMinimumDate(fromCalWidget->selectedDate());
    //ui->toDate->setMinimumDate(fromCalWidget->selectedDate());
}

void mAssistant::on_toDate_dateChanged(const QDate &toDate)
{
    QTime toTime = ui->toTime->time();
    QDate fromDate = ui->fromDate->date();
    QTime fromTime = ui->fromTime->time();
    ui->goButton->setEnabled(((fromTime <= toTime && fromDate == toDate)||(toDate>fromDate))? true:false);
    //mDebug() << fromCalWidget->selectedDate().toJulianDay();
    fromCalWidget->setMaximumDate(toCalWidget->selectedDate());
    //ui->fromDate->setMaximumDate(toCalWidget->selectedDate());
}

void mAssistant::on_fromTime_timeChanged(const QTime &fromTime)
{
    QTime toTime = ui->toTime->time();
    QDate fromDate = ui->fromDate->date();
    QDate toDate = ui->toDate->date();
    ui->goButton->setEnabled(((fromTime <= toTime && fromDate == toDate)||(toDate>fromDate))? true:false);
}


void mAssistant::on_toTime_timeChanged(const QTime &toTime)
{
    QTime fromTime = ui->fromTime->time();
    QDate fromDate = ui->fromDate->date();
    QDate toDate = ui->toDate->date();
    ui->goButton->setEnabled(((fromTime <= toTime && fromDate == toDate)||(toDate>fromDate))? true:false);
}

void mAssistant::on_btnCheckout_clicked()
{

    QItemSelectionModel *selectionModel = ui->cashTableView->selectionModel();
    int row = selectionModel->currentIndex().row();

    QString msg;

    if ( row < 0)
        msg = "Are you Sure you want to set current time last check out point?";
    else
        msg = "Are you Sure you want to set current selected patient last check out point?";

    int reply = QMessageBox::question(nullptr,"Confirmation",
                                      msg,
                                      QMessageBox::Yes,QMessageBox::No);

    if ( reply == QMessageBox::No)
        return;

    qint64 checkoutDate;
    qint64 checkoutTime;
    QString checkout;

    if ( row < 0 )
    {
        checkoutDate = QDate::currentDate().toJulianDay();
        checkoutTime = QTime::currentTime().msecsSinceStartOfDay()/1000;
    }
    else
    {
        checkout = selectionModel->model()->index(row,2).data(Qt::DisplayRole).toString();
        checkoutDate = checkout.left(7).toInt();
        checkoutTime = checkout.remove(0,7).toInt()+1;
    }

    settings.setCheckout(checkoutDate,checkoutTime);
    setcheckoutTooltip();

    if (ui->cbSinceLastCheckout->isChecked())
    {
        loadCheckout();
        loadRegister();
    }
    else
        ui->cbSinceLastCheckout->setChecked(true);

}

void mAssistant::loadCheckout()
{
    mSettings::checkout checkout = settings.getCheckout();
    ui->cashCalendar->setSelectedDate(QDate::fromJulianDay(checkout.date));
    ui->fromDate->setDate(QDate::fromJulianDay(checkout.date));
    ui->fromTime->setTime(QTime::fromMSecsSinceStartOfDay(checkout.time*1000));
    ui->toDate->setDate(QDate::currentDate());
    ui->toTime->setTime(QTime::currentTime());
}

void mAssistant::on_cbSinceLastCheckout_toggled(bool checked)
{
    if (checked)
    {
        loadCheckout();
    }
    else
    {
        ui->cashCalendar->setSelectedDate(QDate::currentDate());
        setTimePeriod();
    }

    ui->fromDate->setReadOnly(checked);
    ui->fromTime->setReadOnly(checked);
    ui->toDate->setReadOnly(checked);
    ui->toTime->setReadOnly(checked);

    loadRegister();

}

void mAssistant::on_cashCalendar_clicked(const QDate &date)
{
    Q_UNUSED(date)
    ui->cbSinceLastCheckout->setChecked(false);
    setTimePeriod();
    loadRegister();
}

void mAssistant::load()
{
    ui->cashCalendar->setSelectedDate(QDate::currentDate());
    setTimePeriod();
    QTimer::singleShot(0,this,&mAssistant::loadAgenda);
    QTimer::singleShot(250,this,&mAssistant::loadRegister);
    QTimer::singleShot(500,this,&mAssistant::loadDeliveries);
}

void mAssistant::on_agendaCalendar_clicked(const QDate &date)
{
    Q_UNUSED(date)
    loadCurrentSelectedAgenda();
}
