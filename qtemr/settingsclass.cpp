// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "settingsclass.h"
#include "ui_settingsclass.h"

settingsClass::settingsClass(QWidget *parent) :
    mDialog(parent),
    ui(new Ui::settingsClass),
    movie (new QMovie(":/Graphics/loadanimation"))
{
    ui->setupUi(this);

    exConName = QString("qt_sql_extra_settings_connection_%1").arg(qrand());
    bsConName = QString("qt_sql_base_settings_connection_%1").arg(qrand());
    sqlextra = new sqlExtra(this,exConName,false);
    sqlbase = new sqlBase(this,bsConName,false);

    ui->passwordLine->setFocus(Qt::OtherFocusReason);
    serviceModel = sqlextra->readServicesModel();

    spinboxdelegate = new spinBoxDelegate(ui->servicesTable);

    ui->servicesTable->setModel(serviceModel);
    ui->servicesTable->setColumnWidth(0,200);
    ui->servicesTable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->servicesTable->setItemDelegate(spinboxdelegate);

    initiateWatcher();

    connect(ui->createStartMenuShortcut,SIGNAL(clicked(bool)),this,SLOT(createStartMenuShortcut(bool)));
    connect(ui->createDesktopShortcut,SIGNAL(clicked(bool)),this,SLOT(createDesktopShortcut(bool)));
    connect(ui->encryptionSwitch,SIGNAL(clicked(bool)),this,SLOT(toggleEncryption(bool)));
    connect(ui->stylerWidget,SIGNAL(applyTheme()),this,SIGNAL(reloadTheme()));
    connect(ui->stylerWidget,SIGNAL(saveSelectedTheme(QString)),&msettings,SLOT(setSelectedTheme(QString)));

    movie->setScaledSize(ui->EncryptionProgress->size());
    ui->EncryptionProgress->setMovie(movie);

    setWindowFlags(windowFlags() | Qt::Window | Qt::FramelessWindowHint);
    QDesktopWidget* m = QApplication::desktop();
    QRect desktop = m->screenGeometry(m->screenNumber(QCursor::pos()));

    if (desktop.size() == QSize(800,600))
    {
        resize(width(),560);
    }
    else
    {
        resize(width(),600);
        wm.centerOnScreen(this);
    }
}

settingsClass::~settingsClass()
{
    serviceModel->clear();

    delete spinboxdelegate;
    delete serviceModel;

    sqlextra->optimize();
    sqlbase->optimize();

    delete sqlextra;
    delete sqlbase;

    QSqlDatabase::removeDatabase(bsConName);
    QSqlDatabase::removeDatabase(exConName);

    delete movie;
    delete ui;

}

mSettings::pSettings settingsClass::getValuesFromUI()
{
    mSettings::pSettings _settings;
    _settings.autoCompleteByWord =  ui->checkBoxAutoCompleteByWord->isChecked();
    _settings.speciality = ui->comboBoxSpeciality->currentIndex();
    _settings.showChronicConditions = ui->checkBoxChronic->isChecked();
    _settings.showNavArrows = ui->checkBoxNavArrow->isChecked();
    _settings.smallScreenMode = ui->checkBoxSmallScreen->isChecked();
    _settings.simpleExamination = ui->checkBoxSimpleExamination->isChecked();
    _settings.alwaysSave = ui->checkBoxAlwaysSave->isChecked();
    _settings.inLinePatientList = ui->inLinePatientList->isChecked();
    _settings.newVisitPrice = ui->newVisitDoubleSpinBox->value();
    _settings.followVisitprice1 = ui->doubleSpinBoxFollow1->value();
    _settings.followVisitprice2 = ui->doubleSpinBoxFollow2->value();
    _settings.followVisitprice3 = ui->doubleSpinBoxFollow3->value();
    _settings.followVisitprice4 = ui->doubleSpinBoxFollow4->value();
    _settings.autosaveinterval = ui->autosaveInt->value();
    if ( _settings.autosaveinterval <= 30 )
    {
        _settings.autosaveinterval = 30;
        ui->autosaveInt->setValue(30);
    }
    _settings.autoSave = ui->autoSave->isChecked();
    _settings.minimizeToTray = ui->minimizeToTray->isChecked();
    _settings.selectedTheme = ui->stylerWidget->getSelectedTheme();
    _settings.defaultFont = ui->defaultFont->currentText();
    _settings.defaultFontSize = ui->defaultFontSize->currentText().toDouble();
    _settings.defaultFontBold = ui->defaultFontBold->isChecked();
    _settings.textboxFont = ui->textboxFont->currentText();
    _settings.textboxFontSize = ui->textboxFontSize->currentText().toDouble();
    _settings.textboxFontBold = ui->textboxFontBold->isChecked();
    _settings.drugsDatabase = (mSettings::Database) ui->DrugsDatabase->currentIndex();
    _settings.maxFollowUps = ui->maxFollowUps->value();
    _settings.autoClosePrintDlg = ui->checkBoxAutoClosePrintDlg->isChecked();
    _settings.autoSetnewAfterMaxPerProblemIsReached = ui->checkBoxAutoNewVisit->isChecked();
    _settings.maxFollowUpsPerProblem = ui->maxFollowUpsPerProblem->value();
    _settings.enableVisualEffects = ui->enableVisualEffects->isChecked();
    _settings.updateNotify = ui->updateNotify->isChecked();
    _settings.useToast = ui->useToast->isChecked();
    _settings.usePhotoViewer = ui->usePhotoViewer->isChecked();
    _settings.remmberLastFollowupDate = ui->remmberLastFollowupDate->isChecked();
    return _settings;
}

void settingsClass::setValuesToUI(const mSettings::pSettings &_settings)
{
    ui->checkBoxAutoCompleteByWord->setChecked(_settings.autoCompleteByWord);
    ui->comboBoxSpeciality->setCurrentIndex(_settings.speciality);
    ui->checkBoxChronic->setChecked(_settings.showChronicConditions);
    ui->checkBoxNavArrow->setChecked(_settings.showNavArrows);
    ui->checkBoxSmallScreen->setChecked(_settings.smallScreenMode);
    ui->checkBoxSimpleExamination->setChecked(_settings.simpleExamination);
    ui->checkBoxAlwaysSave->setChecked(_settings.alwaysSave);
    ui->inLinePatientList->setChecked(_settings.inLinePatientList);
    ui->newVisitDoubleSpinBox->setValue(_settings.newVisitPrice);
    ui->doubleSpinBoxFollow1->setValue(_settings.followVisitprice1);
    ui->doubleSpinBoxFollow2->setValue(_settings.followVisitprice2);
    ui->doubleSpinBoxFollow3->setValue(_settings.followVisitprice3);
    ui->doubleSpinBoxFollow4->setValue(_settings.followVisitprice4);
    ui->autosaveInt->setValue(_settings.autosaveinterval);
    ui->autoSave->setChecked(_settings.autoSave);
    ui->autosaveInt->setEnabled(_settings.autoSave);
    ui->minimizeToTray->setChecked(_settings.minimizeToTray);
    ui->defaultFont->setCurrentText(_settings.defaultFont);
    ui->defaultFontSize->setCurrentText(QString::number(_settings.defaultFontSize));
    ui->defaultFontBold->setChecked(_settings.defaultFontBold);
    ui->textboxFont->setCurrentText(_settings.textboxFont);
    ui->textboxFontSize->setCurrentText(QString::number(_settings.textboxFontSize));
    ui->textboxFontBold->setChecked(_settings.textboxFontBold);
    ui->DrugsDatabase->setCurrentIndex(_settings.drugsDatabase);
    ui->maxFollowUps->setValue(_settings.maxFollowUps);
    ui->checkBoxAutoClosePrintDlg->setChecked(_settings.autoClosePrintDlg);
    ui->maxFollowUpsPerProblem->setValue(_settings.maxFollowUpsPerProblem);
    ui->checkBoxAutoNewVisit->setChecked(_settings.autoSetnewAfterMaxPerProblemIsReached);
    ui->enableVisualEffects->setChecked(_settings.enableVisualEffects);
    ui->updateNotify->setChecked(_settings.updateNotify);
    ui->useToast->setChecked(_settings.useToast);
    ui->usePhotoViewer->setChecked(_settings.usePhotoViewer);
    ui->remmberLastFollowupDate->setChecked(_settings.remmberLastFollowupDate);
    ui->stylerWidget->setSelectedTheme(_settings.selectedTheme);
    ui->appDir->setText(dataIOhelper::getCurrentFolder());
    ui->encryptionSwitch->setChecked(sqlbase->isEncryptionEnabled());
}

void settingsClass::closeEvent(QCloseEvent *event)
{
    if(working)
    {
        event->ignore();
        return;
    }

    mSettings::pSettings storedSettings = msettings.readSettings();
    mSettings::pSettings uiSettings = getValuesFromUI();

    bool isThemeSelectionChanged = (storedSettings.selectedTheme != uiSettings.selectedTheme);
    bool isThemeModified = (ui->stylerWidget->save() || isThemeSelectionChanged);
    isSettingsModified = !(uiSettings == storedSettings);

    if(isThemeModified)
        emit reloadTheme();

    if (isSettingsModified)
        msettings.saveSettings(uiSettings);

    if(encryptionToggled)
        emit reloadMainWindow();

    mDialog::closeEvent(event);
}

void settingsClass::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
}

int settingsClass::exec()
{
    isSettingsModified=false;
    settings = msettings.readSettings();
    setValuesToUI(settings);
    encryptionToggled=false;
    return mDialog::exec();
}

void settingsClass::on_setPasswdButton_clicked()
{
    set_clear_pass();
}

void settingsClass::on_passwordLine_textChanged(const QString &arg1)
{
    if (arg1.length() == 0)
        ui->setPasswdButton->setText(tr("Clear"));
    else
        ui->setPasswdButton->setText(tr("Set"));
}

void settingsClass::on_passwordLine_returnPressed()
{
    set_clear_pass();
}

void settingsClass::set_clear_pass()
{
    QString message;

    if ( ui->passwordLine->text().simplified().length() == 0)
    {
        sqlbase->clearPW();
        message = tr("Password had been cleared successfuly.");
    }
    else
    {
        sqlbase->setPassWD(ui->passwordLine->text());
        message = tr("New Password had been set successfuly.");
    }

    emit newMessage(tr("Information"),message);
}

void settingsClass::initiateWatcher()
{
    appPath = QString(QCoreApplication::applicationFilePath().replace('/','\\'));
    lnkDesktopPath = QString("%1\\%2.lnk")
            .arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).replace('/','\\'))
            .arg(APPNAME);
    lnkStartMenuPath = QString("%1\\%2.lnk")
            .arg(QString(QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation).at(0)).replace('/','\\'))
            .arg(APPNAME);

    linkWatcher.addPath(lnkDesktopPath);
    linkWatcher.addPath(lnkStartMenuPath);

    shortcutChecker();
    portabilityChecker();

    portabilityWatcher.addPath(dataIOhelper::PortabilityLockFile());

    connect(&portabilityWatcher,SIGNAL(fileChanged(QString)),this,SLOT(portabilityChecker()));
    connect(&linkWatcher,SIGNAL(fileChanged(QString)),this,SLOT(shortcutChecker()));
}


void settingsClass::mklnk(const QString &path, const bool &create)
{
    if(create)
    {
        QFile::link(appPath,path);
        linkWatcher.addPath(path);
    }
    else
    {
        QFile lnk(path);
        lnk.remove();
    }
}

void settingsClass::portabilityChecker()
{
    bool portability = dataIOhelper::isPortable();
    ui->portability_status->setText(portability? "Portabel mode is enabled":"Portabel mode is disabled");
    ui->appDir->setDisabled(portability);
    ui->selectDirButton->setDisabled(portability);
    ui->cb_portability->setChecked(portability);
}

void settingsClass::on_autoSave_toggled(bool checked)
{
    ui->autosaveInt->setEnabled(checked);
}

void settingsClass::on_closeButton_clicked()
{
    close();
}

void settingsClass::on_resetDrugsButton_clicked()
{
    int reply = QMessageBox::question(nullptr,tr("Are you sure?"),tr("Are you sure that you want to reset autocompleter for drugs to default ? "
                                                         "This can not be undone."),QMessageBox::Yes,QMessageBox::No);
    if ( reply == QMessageBox::Yes)
    {
        if (  sqlextra->resetDrugsTable() )
        {
            emit refreshCompleter();
            newMessage(tr("System Message"),tr("Drugs autocompleter was reset successfuly."));
        }
        else
        {
            newMessage(tr("System Message"),tr("Drugs autocompleter reset operation was failed."));
        }
    }
    QSqlDatabase::removeDatabase("qt_sql_core_resetDrugs");

}

void settingsClass::on_buttonAddService_clicked()
{
    addNewService();
}

void settingsClass::on_buttonDeleteService_clicked()
{
    int row = ui->servicesTable->currentIndex().row();
    QString selectedService = ui->servicesTable->currentIndex().sibling(row,0).data().toString();
    sqlextra->deleteSrvice(selectedService);
    sqlextra->updateServiceModel();
    ui->buttonDeleteService->setDisabled(true);
}

void settingsClass::on_serviceLine_returnPressed()
{
    addNewService();
}

void settingsClass::addNewService()
{

    QStringList items;
    QString newItem = ui->serviceLine->text().simplified();
    if (newItem.length() == 0 )
        return;
    int rows = ui->servicesTable->model()->rowCount();
    for ( int row=0; row<rows; row++)
    {
        items << ui->servicesTable->model()->data(ui->servicesTable->model()->index(row,0)).toString();
    }
    if ( !items.contains(newItem,Qt::CaseInsensitive))
    {
        sqlextra->addService(newItem);
        sqlextra->updateServiceModel();
        ui->serviceLine->clear();
    }
    else
    {
        emit newMessage("Warning","The Item you are trying to add already Exists");
    }
}


void settingsClass::on_serviceLine_textChanged(const QString &arg1)
{
    ui->buttonAddService->setEnabled(arg1.length() > 0);
}

void settingsClass::on_servicesTable_clicked(const QModelIndex&)
{
    ui->buttonDeleteService->setEnabled(true);
}

void settingsClass::on_comboBoxSpeciality_currentIndexChanged(int index)
{
    bool b = (index==4); //this will disable common conditions if obgyn is used
    ui->checkBoxChronic->setEnabled(!b);
    ui->checkBoxChronic->setChecked(!b);
}

void settingsClass::shortcutChecker()
{
    ui->createDesktopShortcut->setChecked(QFile(lnkDesktopPath).exists());
    ui->createStartMenuShortcut->setChecked(QFile(lnkStartMenuPath).exists());
}

void settingsClass::createDesktopShortcut(bool b)
{
    mklnk(lnkDesktopPath,b);
}

void settingsClass::createStartMenuShortcut(bool b)
{
    mklnk(lnkStartMenuPath,b);
}


void settingsClass::on_selectDirButton_clicked()
{
    int reply  = QMessageBox::question(nullptr,"Message",
                             QString("%1 will exit after you change data path . Are you sure? please make sure you have no unsaved data.")
                                       .arg(APPNAME)
                                       ,QMessageBox::Yes,
                                       QMessageBox::No);

    if(reply==QMessageBox::Yes)
        ui->appDir->setText(dataIOhelper::setCurrentFolder(true));
}

void settingsClass::toggleEncryption(bool b)
{
    working = true;
    ui->EncryptionProgress->show();
    ui->encryptionSwitch->setEnabled(false);
    movie->start();
    ui->closeButton->setEnabled(false);
    sqlbase->toggleEncryption(b);
    movie->stop();
    ui->EncryptionProgress->hide();
    ui->closeButton->setEnabled(true);
    working = false;
    encryptionToggled=true;
    ui->encryptionSwitch->setEnabled(true);
}

void settingsClass::on_cb_portability_clicked(bool checked)
{
    bool operation_status = dataIOhelper::makePortable(checked);

    if(operation_status)
        ui->portability_msg->setText("- restart is needed");

    if(checked)
        portabilityWatcher.addPath(dataIOhelper::PortabilityLockFile());

    portabilityChecker();
}
