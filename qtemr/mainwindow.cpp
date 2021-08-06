// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow),
    add2CompleterWorker (new wm_add2Completer),
    sqlbase (new sqlBase(this,QString("qt_sql_base_MainWin_connection"),true)),
    sqlextra(new sqlExtra(this,QString("qt_sql_extra_MainWin_connection"),true)),
    sqlcore (new sqlCore(this,QString("qt_sql_core_MainWin_connection"))),
    gSettings(new settingsClass(this)),
    calWidget(new mCalendarWidget),
    drugindex(new drugIndex(this)),
    assistant(new mAssistant(std::ref(labelMsg),this,std::ref(pEditingMode))),
    mship(new mShip(this)),
    msgbox(new myMessageBox(this)),
    trayIcon(new appTrayIcon(this)),
    QuitShortcut(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()))),
    settingsShortcut(new QShortcut(QKeySequence(Qt::Key_F9), this, SLOT(show_settings_win()))),
    menuShortcut(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_M),this)),
    remoteAssistShortcut(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F1), this, SLOT(showRemoteAssistWin()))),
    blureffect(new QGraphicsBlurEffect(this)),
    rAssistant(new remoteAssist(this)),
    WA_widget(new QWidget(this)),
    WA_vLayout(new QVBoxLayout(WA_widget)),
    WA_title(new QLabel("Send a Whatsapp Message to."))
{
    ui->setupUi(this);
}

void MainWindow::boot()
{
    clickTimer.setInterval(500);
    selected_date = QDate::currentDate();
    BirthDateWindow.setLayout(&layoutCal);
    layoutCal.addWidget(calWidget);
    BirthDateWindow.setWindowFlags(Qt::Popup);
    BirthDateWindow.setWindowOpacity(0.99);
    calWidget->setMinimumDate(QDate(1900,01,01));

    phoneValidator.setRegExp(
     QRegExp("([1-9][0-9]*\\W+|"
             "\\D*\\W+|"
             "\\W*\\-*\\W*|"
             "\\W*[0][1][0-9]{9}\\W*|"
             "\\W*[0][2-9][0-9]{8}\\W*)*"));
    ui->patientMobile->setValidator(&phoneValidator);

    // WhatsApp widget & action creation

    WA_widget->setWindowFlags(Qt::Popup);
    WA_widget->setWindowOpacity(0.99);
    WA_widget->setLayout(WA_vLayout);
    WA_widget->setObjectName("WA_widget");
    WA_title->setStyleSheet("font-weight: bold; font-size : 12pt;");
    WA_vLayout->addWidget(WA_title);

    QAction *WAaction = ui->patientMobile->addAction(QIcon(":/ionicons/ionicons/whatsapp.png"), QLineEdit::ActionPosition::TrailingPosition);
    WAaction->setVisible(false);

    connect(WAaction,&QAction::triggered,this,&MainWindow::WAaction_clicked);

    connect(ui->patientMobile,&xLineEdit::textChanged,[=](){
        QString phones = ui->patientMobile->text();
        WAaction->setVisible(phones.contains(QRegExp("[0][1][0-9]{9}")));
    });

    // end of WA init code




    blureffect->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
    blureffect->setBlurRadius(3);

    // initializing variables - end

    checkDatabaseCompatibility();

    if ( settings.isDeviceBlocked() && !regMyApp.check_eval_copy() )
        showHelloPirate();

    QLocale curLocale(QLocale("en_US"));
    QLocale::setDefault(curLocale);
    setLocale(QLocale("en_US"));


    //
    setDefaultAppFont();
    //2b removed - start
    ui->allergyList->setListVariables("allergies");
    ui->opAdmissionsList->setListVariables("surgeries");
    //2b removed - end

    connect(mship,SIGNAL(showHelloPirate()),this,SLOT(showHelloPirate()));

    indexLength = sqlbase->getPatientIndexLength();
    pEditingMode = true;
    //patient = new Patient(this);
    ID = indexLength;


    ui->DateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->DateTimeEdit->setLocale(curLocale);
    ui->DateTimeEdit->setDisplayFormat("dd/MM/yyyy hh:mm AP");
    ui->DateTimeEdit->calendarWidget()->setFirstDayOfWeek(Qt::Saturday);
    ui->patientnumber->setMax(indexLength-1);
    ui->patientnumber->display(ID);

    ui->searchWidgetx->setID(ID);
    ui->conditionswidget->setID(ID);
    ui->dev->setID(ID);
    ui->perinatal->setID(ID);
    ui->ObstWidget->setID(ID);

    ui->crashTool->setVisible(false);

    trayIcon->show();
    tweakui();
    setCompleters();
    toggleEditMODE(pEditingMode);
    registeration();


    QuitShortcut->setContext(Qt::ApplicationShortcut);
    settingsShortcut->setContext(Qt::ApplicationShortcut);
    menuShortcut->setContext(Qt::ApplicationShortcut);
    connect (menuShortcut,SIGNAL(activated()),trayIcon,SLOT(showMenu()));
    connect (this,SIGNAL(clearDrugLineSignal()),ui->drugLine,SLOT(clear()),Qt::QueuedConnection);
    connect (ui->buttonAddDrug,SIGNAL(clicked()),this,SLOT(addDrug()),Qt::QueuedConnection);
    connect (ui->drugLine,SIGNAL(returnPressed()),this,SLOT(addDrug()),Qt::QueuedConnection);
    connect (ui->buttonAddAllergy,SIGNAL(clicked()),this,SLOT(addAllergy()),Qt::QueuedConnection);
    connect (ui->allergyLine,SIGNAL(returnPressed()),this,SLOT(addAllergy()),Qt::QueuedConnection);
    connect (ui->buttonAddOP,SIGNAL(clicked()),this,SLOT(AddOperation()),Qt::QueuedConnection);
    connect (ui->opAdLine,SIGNAL(returnPressed()),this,SLOT(AddOperation()),Qt::QueuedConnection);
    connect (ui->allergyList,SIGNAL(enableItemRemoveButton(bool)),ui->buttonRemoveAllergy,SLOT(setEnabled(bool)));
    connect (ui->opAdmissionsList,SIGNAL(enableItemRemoveButton(bool)),ui->buttonRemoveOP,SLOT(setEnabled(bool)));
    connect (this,SIGNAL(clearPatientName()),ui->patientName,SLOT(clear()),Qt::QueuedConnection);
    connect (ui->pDrugsTable,SIGNAL(clicked(QModelIndex)),this,SLOT(enableRemoveDrugButton()));
    connect (ui->pDrugsTable,SIGNAL(popUpMessage(QString,QString)),this,SLOT(popUpMessage(QString,QString)));
    connect (sqlbase,SIGNAL(showMessage(QString,QString)),this,SLOT(popUpMessage(QString,QString)));
    connect (sqlbase,SIGNAL(reloadPatientList()),ui->searchWidgetx,SIGNAL(updatePatients()));
    connect (ui->searchWidgetx,SIGNAL(loadPatient(int)),this,SLOT(on_PatientSelected(int)));
    connect (this,SIGNAL(toggleTrayMenuActions(bool)),trayIcon,SLOT(toggleActions(bool)));
    connect (ui->patientnumber,SIGNAL(enableGoHigher(bool)),ui->goHigherID,SLOT(setEnabled(bool)));
    connect (ui->patientnumber,SIGNAL(enableGoLower(bool)),ui->goLowerID,SLOT(setEnabled(bool)));
    connect (ui->pDrugsTable,SIGNAL(reloadDrugsLineAutoComplete()),ui->drugLine,SLOT(mUpdateCompleter()));
    connect (calWidget,SIGNAL(clicked(const QDate&)), this, SLOT(on_birthDateClicked(const QDate&)));
    connect (gSettings,SIGNAL(reloadMainWindow()),this,SLOT(reloadMainWindow()));
    connect (ui->pDrugsTable,SIGNAL(saveDrugs()),this,SLOT(saveDrugs()));
    connect (ui->pDrugsTable,SIGNAL(drugsHasBeenAltered(bool)),this,SLOT(toggleDrugsAlteredStatus(bool)));
    connect (gSettings,SIGNAL(reloadTheme()),this,SLOT(reloadTheme()));
    connect (&themeFutureWatcher,SIGNAL(finished()),this,SLOT(loadThemeWatcher()));
    connect (add2CompleterWorker,SIGNAL(finished()),this,SIGNAL(reloadCompleter()));
    connect (assistant,SIGNAL(loadThisPatient(int)),this,SLOT(loadThisPatient(int)));
    connect (assistant,SIGNAL(toggleEditMode(bool)),this,SLOT(toggleEditMODE(bool)));
    connect (&clickTimer,&QTimer::timeout,&clickTimer,&QTimer::stop);
    connect (&netserver,&NetServer::loadVisitors,rAssistant,&remoteAssist::loadVisitors);
    connect (rAssistant,&remoteAssist::search,ui->searchWidgetx,&searchWidget::setSearchString);
    connect (rAssistant,&remoteAssist::createVisitor,this,&MainWindow::newPatientWithData);
    if ( ! settings.isDeviceActivated())
        mship->run();

    QTimer::singleShot(0,this,&MainWindow::createVisitBox);

    connect ( gSettings ,SIGNAL ( newMessage(QString,QString) ),this,SLOT(popUpMessage(QString,QString)) );
    connect ( gSettings ,SIGNAL ( refreshCompleter() ),this,SIGNAL(reloadCompleter()));

    if (settings.isUpdateNotify())
    {
        microupdater = new microUpdater(this);
        connect( microupdater,SIGNAL(launchMiniUpdater()),this,SLOT(show_update_win()));
        connect( microupdater,SIGNAL(deleteMe()),microupdater,SLOT(deleteLater()));
    }

    connect ( &t_bugTicker,SIGNAL(timeout()),this,SLOT(bugTicker()));
    t_bugTicker.start(500);
    passwordPopup();
}

void MainWindow::setCompleters()
{
    emit loadCompleters();
}

void MainWindow::tweakui()
{
    loadTheme();
    // This part tweak the user Interface for Internal Medicine
    user_speciality = settings.userSpeciality();
    ui->comboBoxMaritalStatus->setComboName("MaritalStatus");
    ui->patientGender->setComboName("Gender");
    ui->patientGender->setUserSpeciality(user_speciality);
    ui->comboBoxMaritalStatus->setUserSpeciality(user_speciality);

    if ( user_speciality == dataHelper::Speciality::InternalMedicine)
    {

    }

    if ( user_speciality == dataHelper::Speciality::Paediatrics )
    {
        ui->spinBoxAge->hide();
        ui->patientAge->show();
        ui->labelYears->hide();
        ui->widgetSmokeAlcohol->hide();
        ui->comboBoxMaritalStatus->setCurrentIndex(0);
        ui->comboBoxMaritalStatus->setEnabled(false);
        //ui->comboBoxMaritalStatus->hide();
        ui->groupBoxDev->show();
    }
    else
    {
        ui->patientAge->hide();
        ui->spinBoxAge->show();
        ui->labelYears->show();
        ui->widgetSmokeAlcohol->show();
        ui->comboBoxMaritalStatus->setEnabled(pEditingMode);
        //ui->comboBoxMaritalStatus->show();
        ui->groupBoxDev->hide();
    }
    // This part tweak the user Interface for Ortho
    if (user_speciality == dataHelper::Speciality::Orthopaedics)
    {}
    // This part tweak the user Interface for Surgery
    if (user_speciality == dataHelper::Speciality::Surgery)
    {}
    // This part tweak the user Interface for Ob/Gyn
    if ( user_speciality == dataHelper::Speciality::ObGyn)
    {
        ui->ObstWidget->show();
        ui->patientGender->setCurrentIndex(1);
        ui->patientGender->setEnabled(false);
        ui->labelDrugs->setText("Drugs & Contraceptives");
    }
    else
    {
        ui->ObstWidget->hide();
        ui->patientGender->setEnabled(pEditingMode);
        ui->labelDrugs->setText("Drugs");
    }
    // This part tweak the user Interface for Family Medicine
    if ( user_speciality == dataHelper::Speciality::FamilyMedicine )
    {
        ui->spinBoxAge->hide();
        ui->labelYears->hide();
        ui->groupBoxDev->show();
        ui->patientAge->show();
    }
    // tweaks
    if ( settings.showChronicBox() )
    {
        //ui->GBox->show();
        ui->condGroupBox->show();
    }
    else
    {
        ui->condGroupBox->hide();
    }
    if ( settings.showNavigation() )
    {
        ui->goLowerID->show();
        ui->goHigherID->show();
    }
    else
    {
        ui->goLowerID->hide();
        ui->goHigherID->hide();
    }

    if ( indexLength == 0 )
        ui->ButtonSaveEdit->setEnabled(false);
    else
        ui->ButtonSaveEdit->setEnabled(true);

    if (settings.isInLinePatientList())
    {
        ui->settingButton->show();
        ui->buttonPatientList->hide();
        ui->searchWidgetx->show();
    }
    else
    {
        ui->searchWidgetx->hide();
        ui->settingButton->hide();
        ui->buttonPatientList->show();
    }
    ui->patientName->setFocus(Qt::OtherFocusReason);
    ui->buttonSuricalNotes->setVisible((user_speciality > dataHelper::Speciality::Paediatrics &&
                                        user_speciality < dataHelper::Speciality::FamilyMedicine));
    ui->buttonNewCancel->setEnabled( (sqlbase->getPatientIndexLength() > 1) );
    setAgeCalButtonToolTip();
}

void MainWindow::fillPatient(const sqlBase::Patient &_patient)
{
    ID = _patient.ID;
    ui->patientnumber->display(ID);
    ui->patientName->setText(_patient.name);
    ui->DateTimeEdit->setDateTime(datetime.fromString(_patient.dateTime,"yyyy-MM-dd hh:mm:ss"));
    ui->patientAge->setText(dataHelper::daysToAge( _patient.age.toInt()));
    if (settings.userSpeciality() != dataHelper::Speciality::Paediatrics)
    {
        ui->spinBoxAge->setValue(dataHelper::ageToYear(_patient.age.toInt()));
        ui->spinBoxAge->setToolTip(dataHelper::daysToAge(_patient.age.toInt()));
    }

    selected_date = QDate::fromJulianDay(_patient.age.split(" ").at(0).toInt());
    calWidget->setSelectedDate(selected_date);
    setAgeCalButtonToolTip();
    ui->patientGender->setCurrentText(_patient.gender);
    ui->patientResidence->setText(_patient.residence);
    ui->comboBoxMaritalStatus->setCurrentText(_patient.maritalStatus);
    ui->patientPlaceBirth->setText(_patient.birthPlace);
    ui->patientOccupation->setText(_patient.occupation);
    ui->checkBoxSmoker->setChecked(dataHelper::str2bool(_patient.smoker));
    ui->spinBoxCigarettesPerDay->setValue(_patient.cigarretsPerDay.toInt());
    //--------------------------------------------------------------------------------------------//
    int y =0;
    if(_patient.smokingYears.toInt() !=0)
        y = QDate::currentDate().year()-_patient.smokingYears.toInt();
    ui->spinBoxSmokingYears->setValue(y);
    //--------------------------------------------------------------------------------------------//
    ui->patientMobile->setText(_patient.mobile);
    ui->checkBoxAlcohol->setChecked(dataHelper::str2bool(_patient.alcohol));
    ui->ABO->setCurrentIndex(_patient.ABO);

    ui->PastHx->setHtml(_patient.pastHistory);
    ui->familyHx->setHtml(_patient.familyHistory);
    ui->Notes->setHtml(_patient.notes);

    ui->allergyList->clear();
    ui->opAdmissionsList->clear();
    allergiesAltered=false;
    opAdAltered=false;
    ui->pDrugsTable->loadPatientDrugsModel(ID,0);

    ui->allergyList->addItems(_patient.allergy.split("|"));
    ui->opAdmissionsList->addItems(_patient.operations.split("|"));

    for ( int x = 0 ; x < ui->allergyList->count() ; x++)
    {
        if ( ui->allergyList->item(x)->text().isEmpty() )
        {
            delete ui->allergyList->item(x);
        }
    }

    for ( int z = 0 ; z < ui->opAdmissionsList->count() ; z++)
    {
        if ( ui->opAdmissionsList->item(z)->text().isEmpty() )
        {
            delete ui->opAdmissionsList->item(z);
        }
    }

    ui->buttonNewCancel->setEnabled(true);
    if (pEditingMode || _patient.name.contains(QString("#%1").arg(ID) ) || _patient.name.length() < 6 )
    {
        ui->ButtonDelete->setEnabled(false);
        ui->ButtonVisit->setEnabled(false);
        ui->buttonSuricalNotes->setEnabled(false);
    }
    else
    {
        ui->ButtonDelete->setEnabled(true);
        ui->ButtonVisit->setEnabled(true);
        ui->buttonSuricalNotes->setEnabled(true);
    }

    if (settings.isInLinePatientList())
        ui->searchWidgetx->selectRow(_patient.ID-1);

    ui->conditionswidget->fillConditions(ID);
    ui->dev->load(ID);
    ui->perinatal->load(ID);
    ui->ObstWidget->load(ID);
    ui->searchWidgetx->setID(ID);
}

void MainWindow::updateSettings()
{
    setDefaultAppFont();
    tweakui();
    showWorkingWindow("Please wait while applying your settings ...");
    visitsbox->tweakui();
    emit updateTextFont();
    hideWorkingWindow();
}

void MainWindow::fixDatabase()
{
    //sqlbase->fixDatabase();
    dbOptimizer dbopt;
    dbopt.exec();

}

void MainWindow::grabPatient()
{
    if (ui->patientAge->text()=="")
        ui->patientAge->setText("0 Years 0 Months 0 Days");

    patient.ID = static_cast<int>(ui->patientnumber->value());
    patient.name = ui->patientName->text().simplified();

    QLocale locale(QLocale::English , QLocale::UnitedStates );
    patient.dateTime =  locale.toString(ui->DateTimeEdit->dateTime(),"yyyy-MM-dd hh:mm:ss");
    patient.age = QString::number(selected_date.toJulianDay());
    patient.gender = ui->patientGender->currentText();
    patient.residence = ui->patientResidence->text().simplified();
    patient.maritalStatus = ui->comboBoxMaritalStatus->currentText();
    patient.birthPlace = ui->patientPlaceBirth->text().simplified();
    patient.occupation = ui->patientOccupation->text().simplified();
    patient.smoker = dataHelper::bool2String(ui->checkBoxSmoker->isChecked());
    patient.cigarretsPerDay = (ui->spinBoxCigarettesPerDay->isVisible())? ui->spinBoxCigarettesPerDay->text():"0";
    //--------------------- fix smoking year s bug ----------------------//
    int y=0;
    if(ui->spinBoxSmokingYears->value() != 0)
        y=QDate::currentDate().year() - ui->spinBoxSmokingYears->value();
    patient.smokingYears = QString::number(y);
    //--------------------------------------------------------------------//
    patient.mobile = ui->patientMobile->text();
    patient.alcohol =  dataHelper::bool2String( ui->checkBoxAlcohol->isChecked());
    patient.ABO = ui->ABO->currentIndex();
    patient.pastHistory = ui->PastHx->toHtml(); // toPlainText();
    patient.familyHistory = ui->familyHx->toHtml(); // toPlainText();

    patient.allergy.clear();
    patient.operations.clear();

    for ( int x =0 ; x < ui->allergyList->count(); x ++ )
    {
        patient.allergy += "|" + ui->allergyList->item(x)->text();
    }

    for ( int z =0 ; z < ui->opAdmissionsList->count(); z ++ )
    {
        patient.operations += "|" + ui->opAdmissionsList->item(z)->text();
    }

    patient.notes = ui->Notes->toHtml();
}

void MainWindow::on_ButtonSaveEdit_clicked()
{
    if (clickTimer.isActive())
        return;

    clickTimer.start();

    ui->ButtonVisit->setEnabled(false);
    ui->ButtonDelete->setEnabled(false);

    if ( pEditingMode)
    {
        //ui->ButtonSaveEdit->setText("Saving!");
        //ui->ButtonSaveEdit->setIcon(QIcon(":/ionicons/clock"));

        bool personalHistoryEdited = personalHistoryEditChecker();
        bool historyExtraEdited = isHistoryEditExtraChecker();
        bool reloadInlinePatientList = (settings.isInLinePatientList() && personalHistoryEdited );
        pEditingMode = !save();

        if (!pEditingMode)
        {
            if(personalHistoryEdited || historyExtraEdited )
                addToMyCompleters();
            if ( reloadInlinePatientList )
                ui->searchWidgetx->updatePatientList();
            drugsAltered=false;
            popUpMessage("Information","Patient data was saved successfully.");

        }
        else
        {
            popUpMessage("Error","Saving failed for unknown reason.");
        }
    }
    else
    {
        pEditingMode = true;
        editing = true;
        if ( sqlbase->isPatientExists(patient.ID))
            selected_date = QDate::fromJulianDay( sqlbase->genericQuery(patient.ID,"Age","patients").toInt() );
    }
    toggleEditMODE(pEditingMode);
}

bool MainWindow::save()
{
    grabPatient();
    ID = patient.ID;

    if ( appLocked() &&  ID >  regMyApp.eval_max())
        return false;

    bool alwaysSave = settings.isAlwaysSave();
    QString msg = "";

    if ( pEditingMode && alwaysSave )
        msg = "<b><p1>Unable to Save that patient because patient's name is too short to be valid.</p1><p2>Save manually or leave EDIT MODE <AUTOSAVE ENABLED></p2></b>" ;
    else
        msg = "<b>This name is too short to be considered a valid name.</b>";

    ui->spinBoxAge->setToolTip(dataHelper::daysToAge(patient.age.toInt()));


    if ( patient.name.length() < 6 )
    {
        applyBlurEffect();
        msgbox->information(this,"Message",msg);
        removeBlurEffect();
        return false;
    }
    if ( sqlbase->haveSameNameWithDifferentID(patient.ID,patient.name))
    {
        if ( pEditingMode && alwaysSave )
            msg = "<b><p>Unable to save that patient because another patient with the same exact name already Exist.<p>change name manually or leave EDIT MODE <AUTOSAVE ENABLED></p></b>";
        else
            msg = "<b>Another record with the same Name already Exist, Can't save this patients Name!";

        applyBlurEffect();
        msgbox->information(this,"Message",msg);
        removeBlurEffect();
        return false;
    }
    if ( patient.name.contains(QString("#%1").arg(ID)))
    {
        applyBlurEffect();
        msgbox->information(this,"Message","Sorry, you are not allowed to add patient <b>number</b> to patient's <b>Name</b>");
        removeBlurEffect();
        return false;
    }


    if ( ( patient.name != "" ) && ( patient.name.length()>=6  ) )
    {
        bool s_ = sqlbase->savePatientData(patient,
                                           ui->pDrugsTable->getDrugsModel(),
                                           ui->ObstWidget->getSiblingsModel(),
                                           ui->conditionswidget->getConditionsState(),
                                           ui->dev->getDevelopment(patient.ID),
                                           ui->perinatal->getPerinatal(patient.ID),
                                           ui->ObstWidget->getObgyne(patient.ID));
        if ( s_)
        {
            indexLength = sqlbase->getPatientIndexLength();
            ui->patientnumber->setMax(indexLength-1);
            ui->buttonNewCancel->setEnabled( (indexLength > 1) );
            ui->ButtonVisit->setEnabled(true);
            ui->ButtonDelete->setEnabled(true);
            ui->buttonNewCancel->setEnabled(true);
            ui->ButtonRefresh->setEnabled(true);
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void MainWindow::on_buttonNewCancel_clicked()
{
    if (clickTimer.isActive())
        return;

    clickTimer.start();

    int maxID = indexLength -1;
    int reply;
    QString warningMessage;
    if ( appLocked() )
    {
        toggleEditMODE(false);
        loadThisPatient(maxID);
        return;
    }
    if ( pEditingMode )
    {
        bool historyEdited = (editing && (personalHistoryEditChecker() ||
                                          isHistoryEditExtraChecker()));
        bool personalEmpty = (!editing && personalHistoryEmptyChecker());
        bool showWarning = (historyEdited || personalEmpty);

        if (historyEdited)
            warningMessage = "This Will <b>Cancel</b> any changes you made to the current patient record, Are you Sure?"
                             "<center> <i>This Can't be undone!</i></center>";
        else if (personalEmpty )
            warningMessage = "This Patient is not saved yet <b>Are you sure that you want to cancel without saving</b>\n"
                             "<center> <i>This Can't be undone!</i></center>";
        if (showWarning)
        {
            applyBlurEffect();
            reply = msgbox->question(this,"Message",warningMessage,QMessageBox::Yes,QMessageBox::No,true);
            removeBlurEffect();
            if (reply == QMessageBox::No)
                return;
        }
        editing = false;
        ID =  (!sqlbase->isPatientExists(ID)) ? maxID:ID;
        toggleEditMODE(false);
        loadThisPatient(ID);
        visitsbox->setSuggestedVisitType(0);
    }
    else
    {
        toggleEditMODE(true);
        clear();
        patient.clear();
        selected_date = QDate::currentDate();
        ui->ButtonVisit->setEnabled(false);
        ui->ButtonDelete->setEnabled(false);
        ui->ButtonRefresh->setEnabled(false);
        ui->patientnumber->display(maxID + 1);
        ID = maxID+1;

        ui->searchWidgetx->clearFilter();
        ui->searchWidgetx->setID(ID);
        ui->perinatal->setID(ID);
        ui->dev->setID(ID);
        ui->ObstWidget->setID(ID);
        ui->conditionswidget->setID(ID);
    }
    if ( indexLength == 1)
        ui->patientnumber->display(1);
}
void MainWindow::clear()
{
    ui->patientName->clear();
    ui->DateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->patientAge->clear();
    ui->spinBoxAge->setValue(0);
    ui->spinBoxAge->setToolTip("");
    ui->patientGender->setCurrentIndex((user_speciality == dataHelper::Speciality::ObGyn )? 1:0);
    ui->patientResidence->clear();
    ui->comboBoxMaritalStatus->setCurrentIndex(0);
    ui->patientPlaceBirth->clear();
    ui->patientOccupation->clear();
    ui->checkBoxSmoker->setChecked(false);
    ui->spinBoxCigarettesPerDay->setValue(0);
    ui->spinBoxSmokingYears->setValue(0);
    ui->patientMobile->clear();
    ui->checkBoxAlcohol->setChecked(false);
    ui->ABO->setCurrentIndex(0);

    ui->PastHx->clear();
    ui->familyHx->clear();
    ui->allergyList->clear();
    ui->pDrugsTable->drugsModel->clear();
    ui->opAdmissionsList->clear();
    ui->Notes->clear();

    ui->conditionswidget->clear();
    ui->dev->clear();
    ui->perinatal->clear();
    ui->ObstWidget->clear();

    //    ui->patientMobile->setStyleSheet("QLineEdit{background-color: white; color:black;}");
    //    ui->patientMobile->setToolTip("");

    setAgeCalButtonToolTip();
}

void MainWindow::on_ButtonDelete_clicked()
{
    if ( clickTimer.isActive() || appLocked() )
        return;

    clickTimer.start();

    applyBlurEffect();

    int reply = msgbox->question(this,"Message",
                                 "This Will <b>Delete</b> the currently Active Patient Are you Sure?"
                                 "<center> <i>This Can't be undone!</i></center>",
                                 QMessageBox::Yes,QMessageBox::No,true);

    removeBlurEffect();
    if (reply == QMessageBox::No)
        return;

    ui->ButtonVisit->setEnabled(false);
    sqlbase->deletePatientRecord(patient.ID);

    if ( settings.isInLinePatientList() )
        ui->searchWidgetx->updatePatientList();

    loadThisPatient(patient.ID);
}

void MainWindow::on_ButtonVisit_clicked()
{
    if (clickTimer.isActive())
        return;

    clickTimer.start();
    ID = patient.ID;
    visitsbox->toggleVisualEffects(settings.isVisualEffectsEnabled());

    patientBasicDetails.ID = patient.ID;
    patientBasicDetails.Name = patient.name;
    patientBasicDetails.age = patient.age.toInt();
    patientBasicDetails.fPal = ui->ObstWidget->getFPAL();
    patientBasicDetails.sex = patient.gender == "Male" ? mSettings::mSex::male : mSettings::mSex::female;


    visitsbox->setPatient(patientBasicDetails);
    applyBlurEffect();
    visitsbox->exec();
    removeBlurEffect();
}

void MainWindow::show_about_win()
{
    AboutWindow *about = new AboutWindow(this);
    about->toggleVisualEffects(settings.isVisualEffectsEnabled());
    connect ( about ,SIGNAL ( registerApp() ),this,SLOT(registeration()) );
    applyBlurEffect();
    about->exec();
    removeBlurEffect();
    about->deleteLater();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int reply;

    if ( !appLocked() &&
         pEditingMode &&
         ((  editing && ( personalHistoryEditChecker() || isHistoryEditExtraChecker() ) )||
         ( !editing && ( personalHistoryEmptyChecker() && ui->patientName->text().length()>=6))))
    {
        applyBlurEffect();
        reply = msgbox->question(this,"Message","Do you want to save any unsaved data?",
                                 QMessageBox::Yes,QMessageBox::No,QMessageBox::Cancel);
        removeBlurEffect();
        if (reply == QMessageBox::Cancel)
        {
            event->ignore();
            return;
        }

        if (reply == QMessageBox::Yes)
        {
            if(save())
            {
                event->accept();
                qApp->quit();
                return;
            }
        }
        if (reply == QMessageBox::No)
        {
            event->accept();
            qApp->quit();
            return;
        }
    }
    else
    {
        applyBlurEffect();
        reply = msgbox->question(this,"Message",
                                 QString("Are you sure you want to <b>QUIT %1 %2</b> now?")
                                 .arg(APPNAME).arg(APPVERSION),
                                 QMessageBox::Yes,QMessageBox::No);
        removeBlurEffect();
        if (reply == QMessageBox::Yes)
        {
            event->accept();
            qApp->quit();
            return;

        }
        event->ignore();
        return;
    }
}

void MainWindow::on_ButtonAgeCal_clicked()
{
    QToolButton* buttonAgeCal=static_cast<QToolButton*> (QObject::sender());
    calWidget->setMaximumDate(QDate::currentDate());
    calWidget->setSelectedDate(selected_date);
    BirthDateWindow.move(buttonAgeCal->geometry().bottomRight());
    BirthDateWindow.show();
}

void MainWindow::on_birthDateClicked(const QDate &birthDate)
{
    int birthDateInDays = static_cast<int>(birthDate.toJulianDay());
    ui->patientAge->setText(dataHelper::daysToAge(birthDateInDays));
    ui->spinBoxAge->setValue(dataHelper::ageToYear(birthDateInDays));
    BirthDateWindow.close();
    selected_date = birthDate;
    setAgeCalButtonToolTip();
    ui->spinBoxAge->setToolTip(dataHelper::daysToAge(static_cast<int>(birthDate.toJulianDay())));
}

void MainWindow::on_patientName_returnPressed()
{
    QString name = ui->patientName->text().simplified();
    ID = sqlbase->getPatientIDfromName(name);

    if ( name == "")
    {
        ui->patientName->clear();
        return;
    }

    if ( name.length()<6 )
    {   applyBlurEffect();
        msgbox->information(this,"Message","<b>Patient's Name is too short, Please Enter a Valid Name for your Patinet</b>");
        ui->patientName->setFocus(Qt::OtherFocusReason);
        removeBlurEffect();
        return;
    }

    if(sqlbase->isPatientNameUsed(name))
    {
        int reply;
        applyBlurEffect();
        reply = msgbox->question(this,"Message",
                                 "The Patient Name you have Entered Already Exists,do you want to Load This Patient?",
                                 QMessageBox::Yes,QMessageBox::No);
        removeBlurEffect();
        if (reply == QMessageBox::Yes) {

            patient = sqlbase->getPatientData(ID);
            ID = patient.ID;
            fillPatient(patient);
            ui->ButtonVisit->setEnabled(true);
            ui->ButtonDelete->setEnabled(true);
            ui->ButtonRefresh->setEnabled(true);
            toggleEditMODE(false);
        }
        else
        {
            emit clearPatientName();
        }
    }
}

void MainWindow::show_settings_win()
{
    applyBlurEffect();
    gSettings->toggleVisualEffects(settings.isVisualEffectsEnabled());
    gSettings->exec();

    if(gSettings->isSettingsModified)
        updateSettings();

    removeBlurEffect();
}

void MainWindow::show_gen_win()
{
    if ( appLocked() )
        return;
    if ( regMyApp.check_eval_copy() )
    {
        QMessageBox::information(nullptr,"Warning","This feature is not available in the trial version.");
        return;
    }

    EmptyProfiles generator;
    generator.toggleVisualEffects(settings.isVisualEffectsEnabled());
    connect(&generator ,SIGNAL(updatePList()),ui->searchWidgetx,SLOT(updatePatientList()));
    connect(&generator ,SIGNAL(loadPatient(int)),this,SLOT(loadThisPatient(int)));
    connect(&generator ,SIGNAL(toggleEditMode(bool)),this,SLOT(toggleEditMODE(bool)) );
    applyBlurEffect();
    generator.exec();
    removeBlurEffect();
    indexLength = sqlbase->getPatientIndexLength();
    ui->patientnumber->setMax(indexLength-1);
    ui->buttonNewCancel->setEnabled( (indexLength > 1) );
}

void MainWindow::on_buttonRemoveDrug_clicked()
{
    ui->pDrugsTable->removeCurrentSelectedDrugFromList();
    ui->drugLine->clear();
    if ( ui->pDrugsTable->getRowsCount() == 0 )
    {
        ui->buttonRemoveDrug->setEnabled(false);
    }
    emit ui->pDrugsTable->drugTableItemChanged();
}

void MainWindow::addDrug()
{
    QString newDrug = ui->drugLine->text().simplified();
    if(ui->pDrugsTable->addDrug2DrugList(newDrug))
    {
        newDrug.remove("*");
        emit clearDrugLineSignal();
        emit insertUniqueItem(newDrug,"drugLine");
        emit insertDrug2Visit(newDrug,"drugLine");
    }
}

void MainWindow::addAllergy()
{
    QString newAllergy = ui->allergyLine->text().simplified();
    ui->allergyList->addItem(newAllergy);
    emit insertUniqueItem(newAllergy,"allergyLine");
    allergiesAltered=true;
}

void MainWindow::AddOperation()
{
    QString newEvent = ui->opAdLine->text().simplified();
    ui->opAdmissionsList->addItem(newEvent);
    emit insertUniqueItem(newEvent,"opAdLine");
    opAdAltered=true;
}

void MainWindow::on_buttonRemoveAllergy_clicked()
{
    delete ui->allergyList->currentItem();
    ui->allergyLine->clear();
    if ( ui->allergyList->count() == 0)
        ui->buttonRemoveAllergy->setEnabled(false);
    allergiesAltered=true;
}

void MainWindow::on_buttonAgenda_clicked()
{
    assistant->toggleVisualEffects(settings.isVisualEffectsEnabled());
    applyBlurEffect();
    QTimer::singleShot(375,assistant,&mAssistant::load);
    assistant->exec();
    removeBlurEffect();
}

void MainWindow::showRemoteAssistWin()
{
    rAssistant->exec();
}


void MainWindow::on_buttonRemoveOP_clicked()
{
    delete ui->opAdmissionsList->currentItem();
    ui->opAdLine->clear();
    if ( ui->opAdmissionsList->count() == 0 )
        ui->buttonRemoveOP->setEnabled(false);
    opAdAltered=true;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if ( ID == indexLength )
        ID = indexLength -1;

    if (e->key() == Qt::Key_Escape && ! pEditingMode )
        close();
    else if ( e->key() == Qt::Key_Escape && pEditingMode )
        on_buttonNewCancel_clicked();
    else if ( e->key() == Qt::Key_F1 )
        ui->patientName->setFocus(Qt::OtherFocusReason);
    else if ( e->key() == Qt::Key_F2 )
        ui->searchWidgetx->focusFilter();

    else if ( e->key() == Qt::Key_PageUp && e->modifiers() == Qt::SHIFT && !pEditingMode)
    {
        if ( ID != indexLength-1)
        {
            ID = indexLength-1;
            loadThisPatient(ID);
        }
    }
    else if ( e->key() == Qt::Key_PageDown && e->modifiers() == Qt::SHIFT && !pEditingMode)
    {
        if ( ID != 1)
        {
            ID = 1;
            loadThisPatient(ID);
        }
    }
    else if ( e->key() == Qt::Key_F12 && e->modifiers() == Qt::SHIFT )
        errViewer.showMaximized();
    else if ( e->key() == Qt::Key_F12 )
        ui->searchWidgetx->clearFilter();

    else if ( e->key() == Qt::Key_F11)
        showNotifywidget();

    QMainWindow::keyPressEvent(e);
}

void MainWindow::on_buttonPatientList_clicked()
{
    if ( settings.isInLinePatientList() )
    {
        ui->searchWidgetx->focusFilter();
    }
    else if ( ! settings.isInLinePatientList() )
    {
        PatientList *patientlist = new PatientList(this);
        patientlist->toggleVisualEffects(settings.isVisualEffectsEnabled());
        //connect ( patientlist,SIGNAL ( toggleEditMode(bool) ),this,SLOT(toggleEditMODE(bool)) );
        applyBlurEffect();
        patientlist->exec();
        removeBlurEffect();
        delete patientlist;
    }
}

void MainWindow::loadThisPatient(int _ID)
{
    //mDebug() << QSqlDatabase::connectionNames().count();
    int _xID_ = patient.ID;
    patient = sqlbase->getPatientData(_ID);
    clear();
    fillPatient(patient);
    if ( _xID_ != _ID )
        popUpMessage("Message",QString("Patient ID (%1) is Loaded Successfully.").arg(QString::number(_ID).rightJustified(5, '0')));
}

void MainWindow::popUpMessage(QString title, QString Message )
{
    if (! settings.isUseToast())
    {
        enum MessageIcon { NoIcon, Information, Warning, Critical };
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(Information);
        trayIcon->showMessage(title,Message,icon,10000);
    }
    else
    {
        notificationsList.insert(0,QString("[%1] { %2 : %3 }").arg(QTime::currentTime().toString("hh:mm AP")).arg(title).arg(Message));
        notifyWidget.fillList(notificationsList);
        tNotify.setCenterPos(getCenterPos());
        tNotify.setMessage(title,Message);
        tNotify.show();
    }
}

void MainWindow::afterAddItemxListWidget(QString tn,QString newItemText)
{
    sqlextra->addToAutoComplete(tn,newItemText);
    if (tn == "allergies")
    {
        ui->allergyLine->setFocus();
        ui->allergyLine->clear();
        ui->allergyLine->mUpdateCompleter();
    }
    else if (tn == "surgeries")
    {
        ui->opAdLine->setFocus();
        ui->opAdLine->clear();
        ui->opAdLine->mUpdateCompleter();
    }
}

void MainWindow::navButtonsLeftClicked()
{
    if (pEditingMode)
        return;
    QString emitter = sender()->objectName();
    if ( emitter == "goHigherID")
        ID +=1;
    else if ( emitter == "goLowerID")
    {
        if (ID == 1)
            return;
        else
            ID -=1;
    }
    loadThisPatient(ID);
}

void MainWindow::navButtonsRightClicked()
{
    if (pEditingMode)
        return;
    QString emitter = sender()->objectName();
    if ( emitter == "goHigherID")
    {
        ID = indexLength-1;
        loadThisPatient(ID);
    }
    else if ( emitter == "goLowerID")
    {
        ID = 1;
        loadThisPatient(ID);
    }
}

void MainWindow::removeItemFromCompleter(QString item, QString table)
{
    sqlextra->removeFromAutoComplete(table,item);
}

void MainWindow::removeItemFromDictionary(QString item, int row)
{
    sqlextra->removeFromAutoComplete("dictionary",item);
    emit removeFromCompleter(row);
}

void MainWindow::reloadMainWindow()
{
    if(!pEditingMode)
        loadThisPatient(patient.ID);
    ui->searchWidgetx->updatePatientList();
}

void MainWindow::on_ButtonRefresh_clicked()
{
    int reply = msgbox->question(this,"Confirm patient record reloading",
                                 "Are you sure that you want to reload patient data from disk? "
                                 "This can not be undone",QMessageBox::Yes,QMessageBox::No,true);
    if(reply==QMessageBox::No)
        return;

    loadThisPatient(ID);
    popUpMessage("Information","patient data was reloaded");

    toggleEditMODE(true);
}

void MainWindow::quitApp(){
    deleteLockFile();
    exit(0);
}

void MainWindow::registeration()
{
    reg_status = regMyApp.compare_reg_data();
    eval_copy = regMyApp.check_eval_copy();
    if ( reg_status )
    {
        ui->ButtonSaveEdit->setEnabled(reg_status);

    }
    else
    {
        if ( eval_copy )
        {
            ui->ButtonSaveEdit->setEnabled(eval_copy);
            popUpMessage("Message",QString("This Application is in Evaluation Period! The App will limit you to %1 patient files only!").arg(regMyApp.eval_max()));

        }
        else
        {
            popUpMessage("Message","This Application is NOT registered , please contact Dr.Amr Nasr Osman <dr3mro@gmail.com>, Thank you!");
            ui->ButtonSaveEdit->setEnabled(eval_copy);
        }
    }
}

bool MainWindow::appLocked()
{
    if ( !eval_copy && !reg_status )
    {
        popUpMessage("Message","This Application is NOT registered, Thank you!");
        return true;
    }
    if ( eval_copy && indexLength > regMyApp.eval_max() )
    {
        popUpMessage("Message",QString("Trial has Expired!"));
        return true;
    }
    return false;
}
//CREATE A SIGNAL AND MAKE THIS SMALLER
void MainWindow::toggleEditMODE(bool pEditMODE)
{
    bool inlinePatientList = settings.isInLinePatientList();
    int pNumber=static_cast<int>(ui->patientnumber->value());
    emit setReadWrite(pEditMODE);
    ui->ButtonRefresh->setEnabled((sqlbase->isPatientExists(ID))? pEditMODE:false);
    ui->ButtonAgeCal->setEnabled(pEditMODE);

    ui->buttonSuricalNotes->setEnabled(!pEditMODE && !(patient.name.contains(QString("#%1").arg(ID) ) || patient.name.length() < 6));

    ui->goHigherID->setDisabled((pNumber >= indexLength-1)? true:pEditMODE);
    ui->goLowerID->setDisabled((pNumber != 1)? pEditMODE:true);
    ui->buttonInvestigations->setEnabled(sqlbase->isPatientExists(ID));
    ui->buttonAddAllergy->setEnabled(( ui->allergyLine->text().length() > 0 )? pEditMODE:false);
    ui->buttonRemoveAllergy->setEnabled(( ui->allergyList->selectedItems().count() == 0 )? false:pEditMODE);
    ui->buttonAddDrug->setEnabled(( ui->drugLine->text().length() == 0 )? false:pEditMODE);
    ui->buttonRemoveDrug->setEnabled(( ui->pDrugsTable->selectionModel()->selection().indexes().count() == 0 )? false:pEditMODE);
    ui->buttonAddOP->setEnabled(( ui->opAdLine->text().length() == 0 )? false:pEditMODE);
    ui->buttonRemoveOP->setEnabled(( ui->opAdmissionsList->selectedItems().count() == 0 )? false:pEditMODE);
    //ui->buttonPatientList->setEnabled(( sqlbase->isPatientExists(ui->patientnumber->value()))?!pEditMODE:pEditMODE);
    ui->drugLine->clear();
    ui->allergyLine->clear();
    ui->opAdLine->clear();

    if ( !pEditMODE && inlinePatientList)
    {
        ui->searchWidgetx->focusFilter();
        ui->searchWidgetx->clearFilter();
    }
    else if ( pEditMODE )
        ui->patientName->setFocus(Qt::OtherFocusReason);

    ui->conditionswidget->editMode = pEditMODE;
    ui->ObstWidget->toggleEditMode(pEditMODE);
    pEditingMode = pEditMODE;
}

void MainWindow::setAgeCalButtonToolTip()
{
    ui->ButtonAgeCal->setToolTip(selected_date.toString("dd/MM/yyyy"));
}

void MainWindow::deleteLockFile()
{
    QFile lockFile(".lock");
    lockFile.remove();
}

bool MainWindow::isErrorLogEmpty()
{
    QFile f("error.log");
    return ( f.size() == 0 );
}

int MainWindow::getCenterPos()
{
    QDesktopWidget* m = QApplication::desktop();
    QRect desktop = m->screenGeometry(m->screenNumber(QCursor::pos()));
    return desktop.width()/2;
}

void MainWindow::on_PatientSelected(int _id )
{
    if ( pEditingMode )
    {
        int reply;
        applyBlurEffect();
        reply = msgbox->question( this,"Message",
                                  "You are in <EDIT MODE> , loading another record will lead to loss of any unsaved data are you sure that you want to cont.?",
                                  QMessageBox::Yes,QMessageBox::No);
        removeBlurEffect();

        if (reply == QMessageBox::Yes)
        {
            ID = _id;
            ui->searchWidgetx->clearFilter();
            pEditingMode = false;
            toggleEditMODE(pEditingMode);
            emit loadThisPatient( ID );
        }
        if (reply == QMessageBox::No)
        {
            return;
        }
    }
    else
    {
        ID = _id;
        int _xID_ = patient.ID;
        if (ID == _xID_)
        {
            popUpMessage("Message",QString("Patient ID (%1) is already loaded.").arg(QString::number(ID).rightJustified(5, '0')));
            return;
        }
        else
        {
            ui->searchWidgetx->clearFilter();
            emit loadThisPatient( ID );
        }
    }

}

void MainWindow::closeDataBase()
{
    sqlbase->optimize();
    sqlextra->optimize();
    sqlcore->optimize();
    sqlbase->closeDataBase();
    sqlextra->closeDataBase();
    sqlcore->closeDataBase();
    delete sqlbase;
    delete sqlextra;
    delete sqlcore;
    QSqlDatabase::removeDatabase("qt_sql_base_MainWin_connection");
    QSqlDatabase::removeDatabase("qt_sql_extra_MainWin_connection");
    QSqlDatabase::removeDatabase("qt_sql_core_MainWin_connection");
    ui->searchWidgetx->closeDatabase();
    delete visitsbox;
}

void MainWindow::reOpenDataBase()
{
    sqlbase = new sqlBase(this,"qt_sql_base_MainWin_connection",false);
    sqlextra = new sqlExtra(this,"qt_sql_extra_MainWin_connection",false);
    sqlcore = new sqlCore(this,"qt_sql_core_MainWin_connection");
    setCompleters();
    indexLength = sqlbase->getPatientIndexLength();
    ui->searchWidgetx->reConnectDatabase();
    visitsbox = new visitsBox(this);
    QTimer::singleShot(0,this,&MainWindow::createVisitBox);
}

void MainWindow::toggleWindow(QSystemTrayIcon::ActivationReason reason)
{
    if ( reason != QSystemTrayIcon::DoubleClick )
    {
        return;
    }

    if( this->isHidden())
    {
        this->show();
        this->setWindowState(Qt::WindowMaximized);
    }
    else
    {
        this->hide();
        popUpMessage("Message",QString("%1 %2 is now Minimized to tray!").arg(APPNAME).arg(APPVERSION));
    }
}

void MainWindow::showMainwindowIfMinimizedToTray()
{
    this->show();
    this->setWindowState(Qt::WindowMaximized);
}

void MainWindow::showHelloPirate()
{
    QMessageBox::critical(nullptr,"Hello Pirate!","This device has been blocked for Piracy!");
    exit(0);
}

void MainWindow::showWorkingWindow(QString message)
{
    labelMsg.setMessage(message);
    labelMsg.show();
    qApp->processEvents();
    applyBlurEffect();
}

void MainWindow::hideWorkingWindow()
{
    labelMsg.hide();
    removeBlurEffect();
}

void MainWindow::show_expand_win()
{
    drugExapnder dexpand;
    dexpand.toggleVisualEffects(settings.isVisualEffectsEnabled());
    connect(&dexpand,SIGNAL(reloadDrugsCompleter()),ui->drugLine,SIGNAL(updateDrugsCompleter()));
    connect(&dexpand,SIGNAL(reloadDrugsCompleter()),visitsbox,SIGNAL(updateDrugsCompleter()));
    connect(&dexpand,SIGNAL(newMessage(QString,QString)),this,SLOT(popUpMessage(QString,QString)));
    applyBlurEffect();
    dexpand.exec();
    showWorkingWindow("Please wait...");
    removeBlurEffect();
    hideWorkingWindow();
}

void MainWindow::showDieteditWin()
{
    applyBlurEffect();
    DietEditor dietedit;
    dietedit.toggleVisualEffects(settings.isVisualEffectsEnabled());
    dietedit.exec();
    removeBlurEffect();
}
//MOVE TO KERNEL
void MainWindow::exportPatientList()
{
    QFileDialog fileDialog;
    QString desktop = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString savePath = fileDialog.getSaveFileName(this,"Select Export File",desktop, "Microsoft Excel (*.xls);;XML files (*.xml)",nullptr);
    QFileInfo info(savePath);

    if (info.baseName().isEmpty())
        return;

    QFile file(savePath);
    if (file.exists())
        file.remove();

    if (!file.open(QFile::WriteOnly))
    {
        QMessageBox::information(nullptr,"Message","Export Failed,I don't have permission to create file in this location.");
        return;
    }

    else
    {
        file.close();
        file.remove();
    }

    QString suffix = info.suffix();
    bool w = false;
    if (suffix.toUpper() == "XML")
        w = sqlbase->exportPatientListToXML(savePath);
    else if (suffix.toUpper() == "XLS")
        w = sqlbase->exportPatientListToXLS(savePath);
    if (w)
        QMessageBox::information(nullptr,"Message","Export finished Successfully");
    else
        QMessageBox::information(nullptr,"Message","Export Failed!");
}

void MainWindow::addSurgicalNotes(int _ID,QString surgeryID ,int julianDate, QString opName, QString opReport)
{
    sqlbase->addSurgicalNote(_ID,surgeryID,julianDate,opName,opReport);
}

void MainWindow::show_listEdit_win()
{
    listEditor listeditor;
    listeditor.toggleVisualEffects(settings.isVisualEffectsEnabled());
    connect ( &listeditor ,SIGNAL ( reloadCompleter() ),this,SIGNAL(reloadCompleter()) );
    applyBlurEffect();
    listeditor.exec();
    removeBlurEffect();
}

void MainWindow::show_favouritesDrugs_win()
{
    favouriteDrugsEditor *favouritesEditor = new favouriteDrugsEditor(this);
    favouritesEditor->toggleVisualEffects(settings.isVisualEffectsEnabled());
    connect ( favouritesEditor ,SIGNAL ( reloadCompleter() ),this,SIGNAL(reloadCompleter()) );
    applyBlurEffect();
    favouritesEditor->exec();
    removeBlurEffect();
    favouritesEditor->deleteLater();
}
void MainWindow::on_buttonInvestigations_clicked()
{
    applyBlurEffect();
    invesList invList(this,ID);
    invList.toggleVisualEffects(settings.isVisualEffectsEnabled());
    invList.exec();
    removeBlurEffect();
}

void MainWindow::on_spinBoxAge_valueChanged(int arg1)
{
    selected_date = QDate::currentDate().addYears(arg1*-1);
    ui->spinBoxAge->setToolTip("");
    setAgeCalButtonToolTip();
    calWidget->setSelectedDate(selected_date);
}

void MainWindow::on_drugLine_textChanged(const QString &arg1)
{
    if ( arg1.length() == 0 )
        ui->buttonAddDrug->setEnabled(false);
    else
        ui->buttonAddDrug->setEnabled(pEditingMode);
}
//THIS WILL BE REMOVED AFTER SUBCLASSING THE ALLERGY/OPERATIONS LIST
void MainWindow::on_allergyLine_textChanged(const QString &arg1)
{
    if ( arg1.length() == 0 )
        ui->buttonAddAllergy->setEnabled(false);
    else
        ui->buttonAddAllergy->setEnabled(pEditingMode);
}
//THIS WILL BE REMOVED AFTER SUBCLASSING THE ALLERGY/OPERATIONS LIST
void MainWindow::on_opAdLine_textChanged(const QString &arg1)
{
    if ( arg1.length() == 0 )
        ui->buttonAddOP->setEnabled(false);
    else
        ui->buttonAddOP->setEnabled(pEditingMode);
}

void MainWindow::loadTheme()
{
    this->setStyleSheet(settings.themeMaker());
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

void MainWindow::on_ExitButton_clicked()
{
    this->close();
}

void MainWindow::on_minimizeButton_clicked()
{
    if (settings.isMinimizedToTray())
        this->hide();
    else
        this->showMinimized();
    QApplication::sendPostedEvents(nullptr,QEvent::DeferredDelete);
}


void MainWindow::passwordPopup()
{
    if ( sqlbase->isPasswordSet() )
    {
        userpass *upass = new userpass(this);
        connect ( upass ,SIGNAL ( quitme() ),this,SLOT(quitApp()) );
        connect ( upass ,SIGNAL ( newMessage(QString,QString) ),this,SLOT(popUpMessage(QString,QString)) );
        upass->exec();
        delete upass;
    }
}

void MainWindow::checkDatabaseCompatibility()
{
    double currentDbVersion = sqlbase->getDatabaseVersion();
    if ( currentDbVersion < static_cast<double>(minimumDatabaseVersion) )
    {
        QMessageBox::information
                (nullptr,"Message",
                 QString("<b>%1</b> Detected that your current database version [%2] is not supported.\n"
                         "Application will now exit")
                 .arg(APPNAMEVER)
                 .arg(QString::number(currentDbVersion)));
        exit(0);
    }
}

void MainWindow::applyBlurEffect()
{
    blureffect->setEnabled(true);
    setGraphicsEffect(blureffect);
    ui->searchWidgetx->toggleListHeader(false);
    ui->ObstWidget->toggleHeaders(false);
    emit toggleTrayMenuActions(false);
}

void MainWindow::removeBlurEffect()
{
    blureffect->setEnabled(false);
    ui->searchWidgetx->toggleListHeader(true);
    ui->ObstWidget->toggleHeaders(true);
    ui->searchWidgetx->selectRow(ID-1);
    emit toggleTrayMenuActions(true);
}

MainWindow::~MainWindow()
{
    delete add2CompleterWorker;
    delete QuitShortcut;
    delete calWidget;
    delete blureffect;
    delete msgbox;
    delete trayIcon;
    delete visitsbox;
    delete drugindex;
    delete assistant;
    delete gSettings;
    delete mship;
    delete rAssistant;
    delete WA_title;
    delete WA_vLayout;
    delete WA_widget;
    sqlextra->optimize();
    sqlbase->optimize();
    sqlcore->optimize();
    delete sqlextra;
    delete sqlbase;
    delete sqlcore;
    QSqlDatabase::removeDatabase("qt_sql_base_MainWin_connection");
    QSqlDatabase::removeDatabase("qt_sql_extra_MainWin_connection");
    QSqlDatabase::removeDatabase("qt_sql_core_MainWin_connection");

    deleteLockFile();

    delete ui;
}

void MainWindow::on_drugIndexButton_clicked()
{
    drugindex->toggleVisualEffects(settings.isVisualEffectsEnabled());
    applyBlurEffect();
    drugindex->exec();
    removeBlurEffect();
}

void MainWindow::toggleBlur(bool b)
{
    blureffect->setEnabled(!b);
}

void MainWindow::show_backup_win()
{
    applyBlurEffect();
    backup b;
    b.toggleVisualEffects(settings.isVisualEffectsEnabled());
    connect (&b,SIGNAL(loadFirstPatient()),this,SLOT(loadFirstPatient()));
    connect (&b,SIGNAL(closeDataBase()),this,SLOT(closeDataBase()));
    connect (&b,SIGNAL(reOpenDataBase()),this,SLOT(reOpenDataBase()));
    sqlbase->WAL_CheckPoint(QString("TRUNCATE"));
    sqlextra->WAL_CheckPoint(QString("TRUNCATE"));
    b.exec();
    removeBlurEffect();
}

void MainWindow::show_update_win()
{
    miniupdater = new miniUpdater(this);
    emit toggleTrayMenuActions(false);
    miniupdater->exec();
    emit toggleTrayMenuActions(true);
    delete miniupdater;
}

void MainWindow::show_commonConditionsEdit()
{
    conditionsEdit conEdit;
    connect(&conEdit,SIGNAL(reload()),ui->conditionswidget,SLOT(reload()));
    conEdit.exec();
}

void MainWindow::showMergedlg()
{
    applyBlurEffect();
    emit toggleTrayMenuActions(false);
    MergeDlg mDlg;
    connect (&mDlg,SIGNAL(reloadPatientsList()),ui->searchWidgetx,SLOT(updatePatientList()));
    connect (&mDlg,SIGNAL(loadThisPatient(int)),this,SLOT(loadThisPatient(int)));
    connect (&mDlg,SIGNAL(toggleEditMode(bool)),this,SLOT(toggleEditMODE(bool)) );
    mDlg.toggleVisualEffects(settings.isVisualEffectsEnabled());
    mDlg.exec();
    removeBlurEffect();
    emit toggleTrayMenuActions(true);
}

void MainWindow::loadFirstPatient()
{
    indexLength = sqlbase->getPatientIndexLength();
    ID = 1;
    loadThisPatient(ID);
    toggleEditMODE(false);
}
//WHY THIS IS NOT A SIGNAL
void MainWindow::enableRemoveDrugButton()
{
    ui->buttonRemoveDrug->setEnabled(pEditingMode);
}

//WHY SAVE DRUGS IS NOT A SIMPLE SIGNAL
bool MainWindow::saveDrugs()
{
    return sqlbase->saveDrugs(patient.ID,0,ui->pDrugsTable->getDrugsModel());
}

void MainWindow::on_settingButton_clicked()
{
    show_settings_win();
}

void MainWindow::addToMyCompleters() //in Thread
{  
    add2CompleterWorker->setPatientData(patient);
    add2CompleterWorker->setHusband(ui->ObstWidget->getHusbandHtml());
    QtConcurrent::run(add2CompleterWorker,&wm_add2Completer::pWork);
}

void MainWindow::appendCheckBoxTextToPastHx(QString text)
{
    mCheckBox *checkBox = dynamic_cast<mCheckBox*>(sender());
    if ( checkBox->isChecked() )
        ui->PastHx->append(QString("<font color=red> <b>%1:</b></font> </br>").arg(text));
    else
        ui->PastHx->findRemoveText(text);
}

void MainWindow::on_buttonSuricalNotes_clicked()
{
    surgicalNotes surgNotes(ID,this);
    connect(&surgNotes,SIGNAL(addsNoteSignal(QString,int,QString,QString)),this,SLOT(addsNoteSlot(QString,int,QString,QString)));
    connect(&surgNotes,SIGNAL(savesNoteSignal(QString,int,QString,QString)),this,SLOT(savesNoteSlot(QString,int,QString,QString)));
    connect(&surgNotes,SIGNAL(deleteNote(QString)),this,SLOT(deleteNoteSlot(QString)));
    connect(this,SIGNAL(reloadSurgeryNotes(int)),&surgNotes,SLOT(reloadNotes(int)));
    applyBlurEffect();
    surgNotes.exec();
    removeBlurEffect();
}

void MainWindow::addsNoteSlot(QString surgeryID, int julianDate, QString opName , QString opReport)
{
    if (! sqlbase->addSurgicalNote(ID ,surgeryID ,julianDate,opName,opReport))
    {
        popUpMessage("Error", "Failed to Add Report");
    }
    else
    {
        popUpMessage("Done", "New Report was added");
        emit reloadSurgeryNotes(ID);
    }

}

void MainWindow::savesNoteSlot(QString surgeryID, int julianDate, QString opName, QString opReport)
{
    if (! sqlbase->updateSurgicalNote(ID ,surgeryID ,julianDate,opName,opReport))
    {
        popUpMessage("Error", "Failed to save Report");
    }
    else
    {
        popUpMessage("Done", "Report was saved");
        emit reloadSurgeryNotes(ID);
    }
}

void MainWindow::deleteNoteSlot(QString surgeryID)
{
    if (!sqlbase->deleteSugicalNote(ID,surgeryID))
    {
        popUpMessage("Error","Failed to Delete Report");
    }
    else
    {
        popUpMessage("Done","Report Deleted");
        emit reloadSurgeryNotes(ID);
    }
}

void MainWindow::createVisitBox()
{
    visitsbox = new visitsBox(this);
    connect ( visitsbox ,SIGNAL ( newMessage(QString,QString) ),this,SLOT(popUpMessage(QString,QString)) );
    connect ( visitsbox ,SIGNAL ( reloadMWCompleter() ),this,SIGNAL(reloadCompleter()));
    connect ( visitsbox ,SIGNAL ( syncDrugs(QList<QStringList>,bool) ),ui->pDrugsTable,SLOT(DrugSyncWithVisit(QList<QStringList>,bool)));
    connect ( visitsbox ,SIGNAL ( toggleBlur(bool)),this,SLOT(toggleBlur(bool)));
    connect ( visitsbox ,SIGNAL ( syncLMPDateWithPatients(QDate)),ui->ObstWidget,SLOT(syncLMPDateWithVisit(QDate)));
    connect ( visitsbox ,SIGNAL ( insertDrug2Patient(QString,QString)),this,SIGNAL(insertUniqueItem(QString,QString)));
    connect ( this ,SIGNAL ( insertDrug2Visit(QString,QString)),visitsbox,SIGNAL(insertUniqueItem(QString,QString)));
    connect ( visitsbox , SIGNAL(getDrugsModel()),ui->pDrugsTable,SLOT(getDrugsModel()));
}

void MainWindow::setDefaultAppFont()
{
    mSettings::defaultFont defaultfont = settings.getDefaultFont();
    QFont defaultFont = QFont(defaultfont.fontName);
    double defaultPointSize = defaultfont.fontSize;
    bool defaultBold = defaultfont.fontBold;
    defaultFont.setBold(defaultBold);
    defaultFont.setPointSize(static_cast<int>(defaultPointSize));
    qApp->setFont(defaultFont);
    setFont(defaultFont);
}

void MainWindow::bugTicker()
{
    bool state = ui->crashTool->isVisible();
    if (!isErrorLogEmpty())
        if (ui->crashTool->underMouse())
            state = true;
        else
            state = !state;
    else
        state=false;
    ui->crashTool->setVisible(state);
}

void MainWindow::on_crashTool_clicked()
{
    errViewer.showMaximized();
}

void MainWindow::showNotifywidget()
{
    if (settings.isUseToast())
        notifyWidget.showMaximized();
}

bool MainWindow::personalHistoryEditChecker()
{
    QString name,residence,occupation,mobile,gender,marital;
    name       = ui->patientName->text();
    residence  = ui->patientResidence->text();
    occupation = ui->patientOccupation->text();
    mobile     = ui->patientMobile->text();
    gender     = ui->patientGender->currentText();
    marital    = ui->comboBoxMaritalStatus->currentText();


    //    mDebug() <<    "age" << (patient.age != QString::number(selected_date.toJulianDay()) ) << patient.age << QString::number(selected_date.toJulianDay()) <<
    //                   "name"<< (patient.name!=name) << patient.name << name <<
    //                   "res" << (patient.residence!=residence) << patient.residence << residence <<
    //                   "ocu" << (patient.occupation!=occupation) << patient.occupation << occupation <<
    //                   "mob" << (patient.mobile!=mobile) << patient.occupation << occupation <<
    //                   "gend"<< (patient.gender!=gender) << patient.gender << gender <<
    //                   "ms"  << (patient.maritalStatus!=marital) << patient.maritalStatus << marital;

    return ((patient.age != QString::number(selected_date.toJulianDay()) ) ||
            (patient.name!=name) ||
            (patient.residence!=residence) ||
            (patient.occupation!=occupation) ||
            (patient.mobile!=mobile) ||
            ((user_speciality==dataHelper::Speciality::ObGyn)? false:(patient.gender!=gender)) ||
            (patient.maritalStatus!=marital) );
}

bool MainWindow::personalHistoryEmptyChecker()
{
    QStringList personalHistory;
    personalHistory << ui->patientName->text().simplified()
                    << ui->patientResidence->text().simplified()
                    << ui->patientOccupation->text().simplified()
                    << ui->patientMobile->text().simplified()
                    << ui->patientPlaceBirth->text().simplified();

    foreach (QString item, personalHistory)
    {
        if(item.length() > 0)
            return true;
    }
    return false;
}

bool MainWindow::isHistoryEditExtraChecker()
{
    QString placeofbirth = ui->patientPlaceBirth->text().simplified();
    QString smoker = dataHelper::bool2String(ui->checkBoxSmoker->isChecked());
    QString alcohol = dataHelper::bool2String(ui->checkBoxAlcohol->isChecked());
    QString cigaretts = QString::number(ui->spinBoxCigarettesPerDay->value());
    int speciality = settings.userSpeciality();

    int abo = ui->ABO->currentIndex();

    bool pastHxModified = ui->PastHx->document()->isModified();
    bool familyHxModified = ui->familyHx->document()->isModified();
    bool notesModified = ui->Notes->document()->isModified();
    bool conditionsModified = ui->conditionswidget->isConditionsModified();

    bool ogModified = (speciality==dataHelper::Speciality::ObGyn)? ui->ObstWidget->isObGynModified():false;
    bool pnatalModified = (speciality==dataHelper::Speciality::Paediatrics)? ui->perinatal->isPnatalModified():false;
    bool devModified = (speciality==dataHelper::Speciality::Paediatrics)? ui->dev->isDevelopmentModified():false;

    QString smokingyears =
            (ui->spinBoxSmokingYears->value() != 0) ?
                QString::number(QDate::currentDate().year() - ui->spinBoxSmokingYears->value()):
                QString::number(0);


    //    mDebug() << "placeofbirth" << (placeofbirth != patient.birthPlace) <<
    //                "smoker" << (smoker != patient.smoker) <<
    //                "alcohol" << (alcohol != patient.alcohol) <<
    //                "cigaretts" << (cigaretts != patient.cigarretsPerDay) <<
    //                "smokingyears" << (smokingyears != patient.smokingYears) <<
    //                "abo" << (abo != patient.ABO)<<
    //                "pastHxModified" << pastHxModified <<
    //                "familyHxModified" << familyHxModified <<
    //                "notesModified" << notesModified <<
    //                "drugsAltered" << drugsAltered <<
    //                "allergiesAltered" << allergiesAltered <<
    //                "opAdAltered" << opAdAltered <<
    //                "conditionsModified" << conditionsModified <<
    //                "ogModified" << ogModified <<
    //                "pnatalModified" << pnatalModified <<
    //                "devModified" << devModified;


    return((placeofbirth != patient.birthPlace) ||
           (smoker != patient.smoker) ||
           (alcohol != patient.alcohol) ||
           (cigaretts != patient.cigarretsPerDay) ||
           (smokingyears != patient.smokingYears) ||
           (abo != patient.ABO)||
           pastHxModified||
           familyHxModified||
           notesModified||
           drugsAltered||
           allergiesAltered||
           opAdAltered ||
           conditionsModified ||
           ogModified ||
           pnatalModified ||
           devModified
           );
}

void MainWindow::on_patientMobile_textChanged(const QString &arg1)
{
    int pos = 0;
    QString string = arg1;

    mSettings::lineStyle style = settings.getLineStylesheet();

    if(ui->patientMobile->validator()->validate(string,pos) == QValidator::Acceptable)
    {
        ui->patientMobile->setStyleSheet(style.normalStylesheet);
        ui->patientMobile->setToolTip("");
    }
    else if (ui->patientMobile->validator()->validate(string,pos) == QValidator::Intermediate)
    {
        ui->patientMobile->setStyleSheet(style.warningStylesheet);
        ui->patientMobile->setToolTip("One or more of phone numbers are slightly invalid.");
    }
    else if (ui->patientMobile->validator()->validate(string,pos) == QValidator::Invalid)
    {
        ui->patientMobile->setStyleSheet(style.errorStylesheet);
        ui->patientMobile->setToolTip("One or more of phone numbers are invalid.");
    }

}

void MainWindow::toggleDrugsAlteredStatus(bool b)
{
    drugsAltered=b;
}

void MainWindow::reloadTheme()
{
    themeFuture = QtConcurrent::run(&settings,&mSettings::themeMaker);
    themeFutureWatcher.setFuture(themeFuture);
}

void MainWindow::loadThemeWatcher()
{
    this->setStyleSheet(themeFuture.result());
    on_patientMobile_textChanged(ui->patientMobile->text());// this to fix bug that not update color
}

void MainWindow::newPatientWithData(const remoteAssist::Visitor &visitor)
{
    ID = indexLength;
    toggleEditMODE(true);
    clear();
    patient.clear();
    selected_date = QDate::currentDate();
    ui->ButtonVisit->setEnabled(false);
    ui->ButtonDelete->setEnabled(false);
    ui->ButtonRefresh->setEnabled(false);
    ui->patientnumber->display(ID);


    ui->searchWidgetx->clearFilter();
    ui->searchWidgetx->setID(ID);
    ui->perinatal->setID(ID);
    ui->dev->setID(ID);
    ui->ObstWidget->setID(ID);
    ui->conditionswidget->setID(ID);

    ui->patientName->setText(visitor.name);
    ui->spinBoxAge->setValue(visitor.age);
    ui->patientGender->setCurrentIndex(visitor.sex);
    ui->comboBoxMaritalStatus->setCurrentIndex(visitor.marital);
    ui->patientResidence->setText(visitor.residence);
    ui->patientPlaceBirth->setText(visitor.placeofbirth);
    ui->patientOccupation->setText(visitor.job);
    ui->patientMobile->setText(visitor.tel);
    visitsbox->setSuggestedVisitType(visitor.visitType);
}

void MainWindow::WAaction_clicked()
{
    for (auto b:WA_widget->findChildren<m_ClickableLabel*>())
        delete b;

    QStringList numbers = ui->patientMobile->text().split(" ");

    if ( numbers.count() <= 0 )
        return;

    for(auto number:numbers){
        if(number.contains(QRegExp("[0][1][0-9]{9}"))){
            m_ClickableLabel *l = new m_ClickableLabel(QString("📞 %1").arg(number));
            l->setPhoneNumber(number);
            l->setStyleSheet("font-weight: normal; font-size : 12pt;");
            WA_vLayout->addWidget(l);

            connect(l,&m_ClickableLabel::leftMouseButtonClicked,[=](){
               QDesktopServices::openUrl(QUrl(QString("https://api.whatsapp.com/send/?phone=2%1&text&app_absent=0&lang=en").arg(l->getPhoneNumber())));
            });

            connect(l,&m_ClickableLabel::setFontBold,[l](bool isBold){
                if(isBold)
                    l->setStyleSheet("font-weight: bold; font-size : 12pt;");
                else
                    l->setStyleSheet("font-weight: normal; font-size : 12pt;");
            });
        }
    }
    WA_widget->move(QCursor::pos());
    WA_widget->adjustSize();
    WA_widget->show();
}
