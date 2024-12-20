﻿#include "visitsbox.h"

#include "ui_visitsbox.h"
#include "visithelper.h"

visitsBox::visitsBox (QWidget *parent)
    : mDialog (parent), ui (new Ui::visitsBox),
      msgbox (new myMessageBox (this)),
      sqlbase (new sqlBase (this, "qt_sql_base_visitbox_connection", false)),
      sqlextra (
          new sqlExtra (this, "qt_sql_extra_visitbox_connection", false)),
      autoSaveTimer (new QTimer), add2CompleterWorker (new wm_add2Completer),
      visitSaverWorker (new wm_visitSaver), print (new printDrugs (this)),
      shift_pageUp (
          new QShortcut (QKeySequence (Qt::SHIFT | Qt::Key_PageUp), this)),
      shift_pageDown (
          new QShortcut (QKeySequence (Qt::SHIFT | Qt::Key_PageDown), this)),
      printShortcut (
          new QShortcut (QKeySequence (Qt::CTRL | Qt::Key_P), this)),
      easyPrintShortcut (
          new QShortcut (QKeySequence (Qt::CTRL | Qt::Key_O), this)),
      printPreviewShortcut (
          new QShortcut (QKeySequence (Qt::CTRL | Qt::Key_R), this)),
      toggleFollowupDate (new QShortcut (Qt::Key_F12, this)),
      vTypeUp (new QShortcut (Qt::Key_F10, this)),
      vTypeDown (new QShortcut (Qt::Key_F11, this)),
      visitAsRequest (
          new QShortcut (QKeySequence (Qt::SHIFT | Qt::Key_F3), this)),
      lastSelectedFollowupDate (
          QDate::fromJulianDay (settings.getLastSelectedFollowUpDate ()))

{
  ui->setupUi(this);
  tweakui();
  connectSignals(parent);
}

void visitsBox::tweakui() {
  this->setLocale(QLocale("en_US"));
  ui->dateFollowUp->setCalendarPopup(true);
  shift_pageUp->setContext(Qt::WindowShortcut);
  shift_pageDown->setContext(Qt::WindowShortcut);
  ui->presentationAnalysis->setMaximumHeight(this->height() / 6);
  setWindowFlags(this->windowFlags() | Qt::Window | Qt::FramelessWindowHint);
  autosaveint = settings.getAutoSaveInterval();
  autoSave = settings.isAutoSave();
  alwaysSave = settings.isAlwaysSave();
  maxFollows = settings.getMaxFollowUpsPerProblem();
  maxFollowUps = settings.getMaxFollowUps();
  speciality = settings.userSpeciality();
  screenMode = settings.getScreenMode();
  simpleExamination = settings.isSimpleExamination();
  autoCompleteByWord = settings.isAutoCompleteByWord();
  autoSetNewAfterMaxFollow = settings.autoSetNewAfterMaxFollowUpsPerProblem();

  ui->presentation->setFocus();
  ui->buttonRemoveDrug->setEnabled(false);

  ui->visitLists->setMaxFollows(maxFollows);

  ui->pPulse->setVitalType(0, speciality);
  ui->pBP->setVitalType(1, speciality);
  ui->pRR->setVitalType(2, speciality);
  ui->pTemp->setVitalType(3, speciality);
  ui->weight->setVitalType(4, speciality);
  ui->lineEditWeight->setVitalType(4, speciality);
  ui->height->setVitalType(5, speciality);
  ui->lineEditLength->setVitalType(5, speciality);
  ui->sPo2->setVitalType(6, speciality);
  ui->RBS->setVitalType(7, speciality);
  ui->lineEditHead->setVitalType(8, speciality);

  bool isTreatingMinors =
      (speciality == dataHelper::Speciality::Paediatrics ||
       speciality == dataHelper::Speciality::FamilyMedicine);

  ui->widgetBaby->setVisible(isTreatingMinors);
  ui->weight->setHidden(isTreatingMinors);
  ui->height->setHidden(isTreatingMinors);
  ui->sPo2->setHidden(isTreatingMinors);
  ui->RBS->setHidden(isTreatingMinors);
  ui->label_w->setHidden(isTreatingMinors);
  ui->label_h->setHidden(isTreatingMinors);
  ui->label_spo2->setHidden(isTreatingMinors);
  ui->label_rbs->setHidden(isTreatingMinors);

  if (speciality == dataHelper::Speciality::ObGyn) {
    ui->ObstWidget->show();
    ui->labelObstUS->show();
    ui->patientObstUS->show();
    ui->fpalLabel->show();
    ui->fpal->show();
    ui->labelPelvic->show();
    ui->patientPelvicExam->show();
    ui->notesLabel->hide();
    ui->plaintextNotes->hide();

  } else {
    ui->ObstWidget->hide();
    ui->labelObstUS->hide();
    ui->patientObstUS->hide();
    ui->fpalLabel->hide();
    ui->fpal->hide();
    ui->labelPelvic->hide();
    ui->patientPelvicExam->hide();
  }

  if (screenMode) {
    QRect dw = qApp->primaryScreen()->geometry();

    if (dw.size() == QSize(800, 600)) {
      setFixedSize(QSize(800, 560));
      move(QPoint(0, 0));
    } else {
      wm.centerOnScreen(this);
    }
    ui->plaintextNotes->hide();
    ui->notesLabel->hide();
  } else {
    if (speciality != dataHelper::Speciality::ObGyn) {
      ui->plaintextNotes->show();
      ui->notesLabel->show();
    }
    setFixedSize(800, 700);
    wm.centerOnScreen(this);
  }

  if (simpleExamination) {
    ui->patientHeartLungEx->hide();
    ui->patientAbdomentBack->hide();
    ui->patientLL->hide();
    ui->labelGeneral->setText("<b>EXAMINATION</b>");
    ui->labelHeartnLungs->hide();
    ui->labelAbdomenBack->hide();
    ui->LabelLL->hide();
  } else {
    ui->patientHeartLungEx->show();
    ui->patientAbdomentBack->show();
    ui->patientLL->show();
    ui->labelGeneral->setText("<b>General Examination</b>");
    ui->labelHeartnLungs->show();
    ui->labelAbdomenBack->show();
    ui->LabelLL->show();
  }
  ui->dateFollowUp->setMinimumDate(QDate::currentDate());
  ui->dateFollowUp->calendarWidget()->setFirstDayOfWeek(Qt::Saturday);
  ui->comboVisitType->fillContent(maxFollows);
  emit updateTextFont();
  toggleVisualEffects(settings.isVisualEffectsEnabled());
}

void visitsBox::on_ButtonNew_clicked() {
  if (newVisitCreationInProgress || aboutToClose) return;

  newVisitCreationInProgress = true;
  ui->ButtonNew->setEnabled(false);

  QLocale locale = QLocale(QLocale::English, QLocale::UnitedStates);

  QDateTime datetime = QDateTime::currentDateTime();
  QString englishDate = locale.toString(datetime, "dd/MM/yyyy");

  for (int i = 0; i < ui->visitLists->count(); i++) {
    QString visitItemText = ui->visitLists->itemText(i).left(10);
    QDate dt = locale.toDate(visitItemText, "dd/MM/yyyy");
    QString visitDate = dt.toString("dd/MM/yyyy");
    if (englishDate == visitDate) {
      msgbox->information(this, "Warning",
                          "You Can't Add more than one visit for the same "
                          "patient within a 24 hours period, Sorry!");
      ui->ButtonNew->setEnabled(true);
      newVisitCreationInProgress = false;
      return;
    }
  }
  int reply;

  QString msgText = "This will clear the current fields, Are you Sure?";
  reply = msgbox->question(this, "Warning", msgText, QMessageBox::Yes,
                           QMessageBox::No);
  if (reply == QMessageBox::No) {
    ui->ButtonNew->setEnabled(true);
    newVisitCreationInProgress = false;
    return;
  }

  ui->dateFollowUp->setMinimumDate(QDate::currentDate());
  ui->lmpDate->setDate(QDate::currentDate());

  sqlBase::Visit visit = grabVisit();

  QDate followUpDate = VisitHelper::makeFollowDate(
      lastFollowupDate, lastSelectedFollowupDate,
      settings.isRemmberlastFollowupDate(), VisitTypes::n_visitsType::NewVisit,
      (VisitHelper::WorkDays)settings.getWorkingDays(), maxFollowUps, sqlbase,
      patientBasicDetails.ID);

  ui->dateFollowUp->setDate(followUpDate);
  visitindex = 0;

  double visitPrice = visitTypes.getVisitTypesByUiIndex(visitindex).price;
  sqlbase->createNewVisit(
      patientBasicDetails.ID, visit.visitDateTime, datetime, followUpDate,
      visitindex, visitPrice, ui->vDrugsTable->getDrugsModel(),
      ui->InvestigationsTable->getInvestigationsModel(), sqlextra);
  ui->visitLists->populateWithVisitList(patientBasicDetails.ID);

  updateVisitAge();
  vEditMode = true;
  enableEditMode(vEditMode);
  emit newMessage("Information", "A New visit was Created");
  newVisitCreationInProgress = false;
  ui->ButtonNew->setEnabled(true);
}

void visitsBox::on_ButtonSave_clicked() {
  if (aboutToClose) return;

  save(grabVisit());
  initializeAutoSave();
}

sqlBase::Visit visitsBox::grabVisit() {
  sqlBase::Visit visit;
  visit.ID = patientBasicDetails.ID;
  visit.presentation = ui->presentation->text().simplified();
  visit.presentationAnalysis = ui->presentationAnalysis->toHtml();
  visit.diagnosis = ui->Diagnosis->text().simplified();
  visit.vitals.pulse =
      ui->pPulse->text().toInt() <= 0 ? -1 : ui->pPulse->text().toInt();
  visit.vitals.RR = ui->pRR->text().toInt() <= 0 ? -1 : ui->pRR->text().toInt();
  visit.vitals.T =
      ui->pTemp->text().toDouble() <= 0 ? -1 : ui->pTemp->text().toDouble();
  visit.vitals.BP = ui->pBP->text() == "" ? "-1" : ui->pBP->text();
  visit.vitals.weight =
      ui->weight->text().toDouble() <= 0 ? -1 : ui->weight->text().toDouble();
  visit.vitals.height =
      ui->height->text().toDouble() <= 0 ? -1 : ui->height->text().toDouble();
  visit.vitals.RBS = ui->RBS->text() == "" ? "-1" : ui->RBS->text();
  visit.vitals.sPo2 =
      ui->sPo2->text().toInt() <= 0 ? -1 : ui->sPo2->text().toInt();
  visit.headCir = ui->lineEditHead->text();
  visit.exGeneral = ui->patientGeneralEx->toHtml();
  visit.exChestHeart = ui->patientHeartLungEx->toHtml();
  visit.exAbdback = ui->patientAbdomentBack->toHtml();
  visit.exLL = ui->patientLL->toHtml();
  visit.visitDateTime = comboSelectedDataTime;
  visit.followDate = QString::number(ui->dateFollowUp->date().toJulianDay());
  visit.visitType = static_cast<int>(
      visitTypes.getVisitTypesByUiIndex(ui->comboVisitType->currentIndex()).id);
  visit.invResults = ui->investigationsResults->toHtml();
  visit.visitNotes = ui->plaintextNotes->toHtml();
  visit.checkButtonCaseClose =
      dataHelper::bool2String(ui->CheckButtonCaseClose->isChecked());
  visit.LMPDATE = static_cast<int>(ui->lmpDate->date().toJulianDay());
  visit.ObstUS = ui->patientObstUS->toHtml();
  visit.Antenatal = dataHelper::bool2String(ui->checkBoxAntenatal->isChecked());
  visit.pelvicExam = ui->patientPelvicExam->toHtml();
  return visit;
}

void visitsBox::fillVisit(const sqlBase::Visit &visit) {
  ui->presentation->setText(visit.presentation);
  ui->presentationAnalysis->setHtml(visit.presentationAnalysis);
  ui->Diagnosis->setText(visit.diagnosis);
  ui->pPulse->setText(visit.vitals.pulse <= 0
                          ? QString()
                          : QString::number(visit.vitals.pulse));
  ui->pRR->setText(visit.vitals.RR <= 0 ? QString()
                                        : QString::number(visit.vitals.RR));
  ui->pTemp->setText(visit.vitals.T <= 0 ? QString()
                                         : QString::number(visit.vitals.T));
  ui->pBP->setText(visit.vitals.BP == "-1" ? QString() : visit.vitals.BP);
  ui->weight->setText(visit.vitals.weight <= 0
                          ? QString()
                          : QString::number(visit.vitals.weight));
  ui->height->setText(visit.vitals.height <= 0
                          ? QString()
                          : QString::number(visit.vitals.height));
  ui->RBS->setText(visit.vitals.RBS == "-1" ? QString() : visit.vitals.RBS);
  ui->sPo2->setText(
      visit.vitals.sPo2 <= 0 ? QString() : QString::number(visit.vitals.sPo2));
  ui->lineEditHead->setText(visit.headCir);
  ui->patientGeneralEx->setHtml(visit.exGeneral);
  ui->patientHeartLungEx->setHtml(visit.exChestHeart);
  ui->patientAbdomentBack->setHtml(visit.exAbdback);
  ui->patientLL->setHtml(visit.exLL);

  ui->comboVisitType->setCurrentIndex(visitTypes.getVisitIndexFromId(
      static_cast<VisitTypes::n_visitsType>(visit.visitType)));
  ui->investigationsResults->setHtml(visit.invResults);
  ui->plaintextNotes->setHtml(visit.visitNotes);

  ui->lmpDate->setDate(QDate::fromJulianDay(visit.LMPDATE));
  ui->patientObstUS->setHtml(visit.ObstUS);
  ui->patientPelvicExam->setHtml(visit.pelvicExam);
  ui->CheckButtonCaseClose->setChecked(
      dataHelper::str2bool(visit.checkButtonCaseClose));
  ui->checkBoxAntenatal->setChecked(dataHelper::str2bool(visit.Antenatal));

  toggleAntenatal(dataHelper::str2bool(visit.Antenatal));

  QString visitDateTime = ui->visitLists->currentText().simplified();
  QLocale locale = QLocale(QLocale::English, QLocale::UnitedStates);
  int currentJulianDate = static_cast<int>(QDate::currentDate().toJulianDay());

  lastVisitDate =
      locale.toDateTime(visitDateTime, "dd/MM/yyyy hh:mm AP ddd").date();

  int visitJulianDate = static_cast<int>(lastVisitDate.toJulianDay());

  if (currentJulianDate == visitJulianDate) {
    vEditMode = true;
    enableEditMode(vEditMode);
  } else {
    vEditMode = false;
    enableEditMode(vEditMode);
  }
  updateVisitAge();

  qint64 t_visitJulianDate;
  qint64 t_visitTime;
  visitDateTimeSetter(t_visitJulianDate, t_visitTime);

  ui->vDrugsTable->loadPatientDrugsModel(patientBasicDetails.ID,
                                         t_visitJulianDate, t_visitTime);
  ui->InvestigationsTable->populateInvests(patientBasicDetails.ID,
                                           t_visitJulianDate, t_visitTime);

  ui->dateFollowUp->setMinimumDate(
      locale.toDateTime(visitDateTime, "dd/MM/yyyy hh:mm AP ddd").date());

  lastFollowupDate = QDate::fromJulianDay(visit.followDate.toInt());

  ui->dateFollowUp->setDate(lastFollowupDate);
  int selectedDateFollowUps = sqlbase->getFollowUpsCountForThisDate(
                                  lastFollowupDate, patientBasicDetails.ID) +
                              1;
  setFollowDateTooltip(selectedDateFollowUps, lastFollowupDate);
  setVitalsPlaceHolderText();
}

void visitsBox::clearVisit() {
  ui->presentation->clear();
  ui->presentationAnalysis->clear();
  ui->Diagnosis->clear();
  ui->pPulse->clear();
  ui->pRR->clear();
  ui->pTemp->clear();
  ui->pBP->clear();
  ui->RBS->clear();
  ui->sPo2->clear();
  ui->height->clear();
  ui->weight->clear();
  ui->lineEditLength->clear();
  ui->lineEditWeight->clear();
  ui->patientGeneralEx->clear();
  ui->patientHeartLungEx->clear();
  ui->patientAbdomentBack->clear();
  ui->patientLL->clear();
  ui->comboVisitType->setCurrentIndex(0);
  ui->lineEditWeight->clear();
  ui->lineEditLength->clear();
  ui->lineEditHead->clear();
  ui->investigationsResults->clear();
  ui->plaintextNotes->clear();
  ui->CheckButtonCaseClose->setChecked(false);
  ui->checkBoxAntenatal->setChecked(false);
  ui->lmpDate->setDate(QDate::currentDate());
  ui->patientObstUS->clear();
  ui->patientPelvicExam->clear();
  ui->InvestigationsTable->clearInvestigations();
  ui->vDrugsTable->clear();
  ui->dateFollowUp->setEnabled(true);
}

void visitsBox::on_visitLists_currentIndexChanged(int index) {
  if (index < 0 || index > ui->visitLists->count() - 1) return;

  clearVisit();
  comboSelectedDataTime = ui->visitLists->itemText(index);
  updateVisitAge();
  if (sqlbase->isVisitExists(patientBasicDetails.ID, comboSelectedDataTime)) {
    loadedVisit = sqlbase->getPatientVisitData(patientBasicDetails.ID,
                                               comboSelectedDataTime);
    fillVisit(loadedVisit);
  } else {
    loadedVisit.clear();  // clean any previous loaded visits.
    // fillVisit(loadedVisit); // useless as it is already cleared.
    ui->presentation->setFocus();
    QString visitDateString = comboSelectedDataTime.left(10);
    lastVisitDate = QDate::fromString(visitDateString, "dd/MM/yyyy");
    QDate followUpDate = VisitHelper::makeFollowDate(
        lastVisitDate, lastSelectedFollowupDate,
        settings.isRemmberlastFollowupDate(),
        VisitTypes::n_visitsType::NewVisit,
        (VisitHelper::WorkDays)settings.getWorkingDays(), maxFollowUps, sqlbase,
        patientBasicDetails.ID);

    ui->dateFollowUp->setDate(followUpDate);
    ui->dateFollowUp->setMinimumDate(lastVisitDate);
    int selectedDateFollowUps = sqlbase->getFollowUpsCountForThisDate(
                                    followUpDate, patientBasicDetails.ID) +
                                1;
    setFollowDateTooltip(selectedDateFollowUps, followUpDate);

    qint64 t_visitJulianDate;
    qint64 t_visitTime;
    visitDateTimeSetter(t_visitJulianDate, t_visitTime);

    ui->vDrugsTable->loadPatientDrugsModel(patientBasicDetails.ID,
                                           t_visitJulianDate, t_visitTime);
    ui->InvestigationsTable->populateInvests(patientBasicDetails.ID,
                                             t_visitJulianDate, t_visitTime);
    if (suggestedVisitType != 0) {
      ui->comboVisitType->setCurrentIndex(suggestedVisitType);
      suggestedVisitType = 0;
    }
    vEditMode = true;
    setVitalsPlaceHolderText();
    enableEditMode(vEditMode);
  }
  toggleContollers();
  drugsAltered = false;
}

void visitsBox::on_ButtonDel_clicked() {
  if (newVisitCreationInProgress || aboutToClose) return;
  newVisitCreationInProgress = true;

  if (ui->visitLists->count() < 2) {
    msgbox->information(
        this, "Error",
        "Can't have less than One visit in your Visit List , Sorry");
    newVisitCreationInProgress = false;
    return;
  }
  ui->ButtonDel->setEnabled(false);
  QString ComboCurrentVisit = QString(ui->visitLists->currentText());
  int reply;
  QString msgText = "This will delete the (  " + ComboCurrentVisit +
                    "  ) Visit, Are you Sure? , This Can't be undone";
  reply = msgbox->question(this, "Message", msgText, QMessageBox::Yes,
                           QMessageBox::No, true);
  if (reply == QMessageBox::No) {
    ui->ButtonDel->setEnabled(true);
    newVisitCreationInProgress = false;
    return;
  }

  QLocale locale = QLocale(QLocale::English, QLocale::UnitedStates);
  int julianDate = static_cast<int>(
      locale.toDateTime(ComboCurrentVisit, "dd/MM/yyyy hh:mm AP ddd")
          .date()
          .toJulianDay());
  int mVisitTime =
      static_cast<int>(
          locale.toDateTime(ComboCurrentVisit, "dd/MM/yyyy hh:mm AP ddd")
              .time()
              .msecsSinceStartOfDay()) /
      1000;
  if (sqlbase->deletePatientVisit(patientBasicDetails.ID, julianDate,
                                  mVisitTime)) {
    ui->visitLists->populateWithVisitList(patientBasicDetails.ID);
    emit newMessage("Information", "Visit deletion success.");
  } else {
    emit newMessage("Information", "Visit deletion failed.");
  }

  newVisitCreationInProgress = false;
}

void visitsBox::closeEvent(QCloseEvent *event) {
  // mDebug() << drugsAltered;
  if (!visitLoaded) event->ignore();

  emit onVisitBoxClose();  // this will clear popups and lineedits

  ui->visitLists->stopLoading();
  if (vEditMode && isVisitModified()) {
    if (!alwaysSave) {
      int reply =
          msgbox->question(this, "Message", "Do you want to save changes?",
                           QMessageBox::Yes, QMessageBox::No);

      if (reply == QMessageBox::No) {
        autoSaveTimer->stop();
        aboutToClose = true;
        mDialog::closeEvent(event);
      }
    }

    save(grabVisit(), false);
  }
  settings.saveLastSelectedFollowUpDate(lastSelectedFollowupDate);
  autoSaveTimer->stop();
  aboutToClose = true;
  mDialog::closeEvent(event);
}

// void visitsBox::showEvent(QShowEvent *event)
//{
//     mDialog::showEvent(event);
//     lastFollowupDate2 = QDate::currentDate();
//     mDebug() << lastFollowupDate2;
// }

void visitsBox::updateVisitAge() {
  currentVisitDateTime = ui->visitLists->currentText();
  QLocale locale = QLocale(QLocale::English, QLocale::UnitedStates);
  QDateTime englishDateTime =
      locale.toDateTime(currentVisitDateTime, "dd/MM/yyyy hh:mm AP ddd");
  int jdstr = static_cast<int>(englishDateTime.date().toJulianDay());
  int jvisitAge = jdstr - patientBasicDetails.age;

  if (jvisitAge < 0) jvisitAge = 0;

  visitAge = QString::number(jvisitAge);

  printableAge = sqlbase->getAge(visitAge.toInt(), true);

  ui->patientAge->setText(printableAge);
}

void visitsBox::on_buttonAddDrug_clicked() {
  QString newDrugName = ui->drugLine->text().simplified();
  addNewDrug(newDrugName);
}

void visitsBox::on_buttonRemoveDrug_clicked() {
  ui->vDrugsTable->removeCurrentSelectedDrugFromList();
  ui->drugLine->clear();
  if (ui->vDrugsTable->getRowsCount() == 0) {
    ui->buttonRemoveDrug->setEnabled(false);
  }
  emit ui->vDrugsTable->drugTableItemChanged();
}

void visitsBox::on_drugLine_returnPressed() { on_buttonAddDrug_clicked(); }

void visitsBox::on_buttonAddInvestigations_clicked() {
  QString newInvestigation =
      ui->investigationsLine->text()
          .simplified();  //.replace(QRegExp("[^A-Za-z\\d\\s]"),"_")  ;
  addNewInvestigation(newInvestigation);
  emit clearInvLine();
}

void visitsBox::on_buttonRemoveInvestigations_clicked() {
  bool isValid =
      ui->InvestigationsTable->selectionModel()->currentIndex().isValid();
  bool invTableHasFocus = ui->InvestigationsTable->hasFocus();
  if (!isValid || !invTableHasFocus) return;

  int row = ui->InvestigationsTable->selectionModel()->currentIndex().row();
  QString invName = ui->InvestigationsTable->invModel->item(row, 1)->text();
  // int visitDate =
  // ui->InvestigationsTable->invModel->item(row,2)->text().toInt();
  qint64 visitJulianDate = ui->InvestigationsTable->getVisitJulianDate();
  qint64 visitTime = ui->InvestigationsTable->getVisitTime();
  QString path = ui->InvestigationsTable->invModel->item(row, 3)->text();

  sqlbase->deleteInvestigation(patientBasicDetails.ID, visitJulianDate,
                               visitTime, path, invName);
  ui->InvestigationsTable->populateInvests(patientBasicDetails.ID,
                                           visitJulianDate, visitTime);
  lastInvestigationRow = (row == 0) ? 0 : row - 1;
  emit clearInvLine();
}

void visitsBox::on_investigationsLine_returnPressed() {
  on_buttonAddInvestigations_clicked();
}

void visitsBox::save(sqlBase::Visit visit, bool threading) {
  if (saving)
    return;
  else
    saving = true;

  visit.visitDateTime = QString(ui->visitLists->currentText());
  updateVisitAge();
  if (visit.visitDateTime.isEmpty()) {
    QLocale locale = QLocale(QLocale::English, QLocale::UnitedStates);
    QDateTime date = QDateTime::currentDateTime();
    visit.visitDateTime = locale.toString(date, "dd/MM/yyyy hh:mm AP ddd");
    ui->visitLists->addItem(visit.visitDateTime);
    ui->visitLists->setCurrentText(visit.visitDateTime);
  }

  mSave(visit, threading);
}

void visitsBox::on_ButtonVisit_clicked() {
  if (newVisitCreationInProgress || aboutToClose) return;
  newVisitCreationInProgress = true;
  bool visitIsRequest =
      QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier);
  lastFollowupDate2 = ui->dateFollowUp->date();  // backup
  visitindex = ui->comboVisitType->currentIndex();
  QLocale locale = QLocale(QLocale::English, QLocale::UnitedStates);
  QDateTime datetime = QDateTime::currentDateTime();
  int dtJulian = static_cast<int>(datetime.date().toJulianDay());
  for (int i = 0; i < ui->visitLists->count(); i++) {
    int visitJ = static_cast<int>(
        locale
            .toDateTime(ui->visitLists->itemText(i), "dd/MM/yyyy hh:mm AP ddd")
            .date()
            .toJulianDay());
    if (visitJ == dtJulian) {
      msgbox->information(this, "Warning",
                          "You Can't Add more than one visit for the same "
                          "patient within a 24 hours period, Sorry!");
      newVisitCreationInProgress = false;
      return;
    }
  }
  ui->ButtonVisit->setEnabled(false);

  //  ui->dateFollowUp->setDate(settings.isRemmberlastFollowupDate()?
  //  lastSelectedFollowupDate:QDate::currentDate());
  sqlBase::Visit visit = grabVisit();
  if (dtJulian != visit.followDate.toInt() && !visitIsRequest) {
    int reply = msgbox->question(
        this, "Warning",
        "<center>You are creating a new follow up visit in a date that differs "
        "from the squeduled date in last visit, do you want to set today as "
        "the follow up date for the last visit? ( <b>yes</b> or <b>No</b>) \n "
        "<b> Note: THIS CANNOT BE UNDONE!</b></center>",
        QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
    if (reply == QMessageBox::Yes) {
      sqlbase->setFollowDate(visit.ID, visit.visitDateTime, dtJulian);
    } else if (reply == QMessageBox::Cancel) {
      ui->ButtonVisit->setEnabled(true);
      newVisitCreationInProgress = false;
      return;
    }
  }

  if (vEditMode) save(visit, false);

  if (visitIsRequest) {
    visitindex = VisitTypes::n_visitsType::Requests;
    sqlbase->setFollowDate(visit.ID, visit.visitDateTime, dtJulian);
    ui->investigationsResults->setFocus(Qt::OtherFocusReason);
  } else {
    visitindex = (suggestedVisitType == 0)
                     ? visitTypes.advance(
                           visitTypes.getVisitTypesByUiIndex(visitindex).id)
                     : suggestedVisitType;
  }
  double visitPrice = visitTypes.getVisitTypesByAlgoIndex(visitindex).price;
  ui->comboVisitType->setCurrentIndex(visitindex);

  QDate followUpDate = VisitHelper::makeFollowDate(
      lastFollowupDate, lastSelectedFollowupDate,
      settings.isRemmberlastFollowupDate(),
      (VisitTypes::n_visitsType)visitindex,
      (VisitHelper::WorkDays)settings.getWorkingDays(), maxFollowUps, sqlbase,
      patientBasicDetails.ID);

  sqlbase->createNewVisit(
      patientBasicDetails.ID, visit.visitDateTime, datetime, followUpDate,
      visitindex, visitPrice, ui->vDrugsTable->getDrugsModel(),
      ui->InvestigationsTable->getInvestigationsModel(), sqlextra);
  ui->visitLists->clear();
  ui->visitLists->populateWithVisitList(patientBasicDetails.ID);
  updateVisitAge();
  emit newMessage("Information", "A New follow up visit was Created");
  newVisitCreationInProgress = false;
  ui->dateFollowUp->setMinimumDate(QDate::currentDate());
}

void visitsBox::on_CheckButtonCaseClose_toggled(bool checked) {
  ui->dateFollowUp->setDisabled(checked);
  ui->ButtonVisit->setDisabled((ui->visitLists->currentIndex() == 0) ? checked
                                                                     : false);
}

void visitsBox::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape && visitLoaded) {
    close();
  } else if (e->key() == Qt::Key_F6) {
    setWindowOpacity(double(0));

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    grabKeyboard();
#endif

    emit toggleBlur(true);
  } else if (!visitLoaded) {
    e->ignore();
  } else if (e->modifiers() == Qt::ControlModifier) {
    switch (e->key()) {
      case Qt::Key_1:
        ui->presentation->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_2:
        ui->investigationsLine->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_3:
        ui->Diagnosis->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_4:
        ui->drugLine->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_5:
        ui->pPulse->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_6:
        ui->pRR->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_7:
        ui->pBP->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_8:
        ui->pTemp->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_D:
        ui->vDrugsTable->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_I:
        ui->InvestigationsTable->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_F:
        ui->dateFollowUp->setFocus(Qt::OtherFocusReason);
        break;
    }
  } else if (e->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier)) {
    switch (e->key()) {
      case Qt::Key_Percent:
        ui->weight->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_AsciiCircum:
        ui->height->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_Ampersand:
        ui->sPo2->setFocus(Qt::OtherFocusReason);
        break;
      case Qt::Key_Asterisk:
        ui->RBS->setFocus(Qt::OtherFocusReason);
        break;
    }
  }

  //    mDebug() << e->key();
  mDialog::keyPressEvent(e);
}

void visitsBox::keyReleaseEvent(QKeyEvent *e) {
  if ((e->key() == Qt::Key_F6) && !e->isAutoRepeat()) {
    setWindowOpacity(double(1));

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    releaseKeyboard();
#endif

    emit toggleBlur(false);
  } else {
    QWidget::keyPressEvent(e);
  }
}

visitsBox::~visitsBox() {
  delete add2CompleterWorker;
  delete visitSaverWorker;
  delete print;
  delete printShortcut;
  delete printPreviewShortcut;
  delete easyPrintShortcut;
  delete toggleFollowupDate;
  delete vTypeUp;
  delete vTypeDown;
  //  delete calWidget;
  sqlbase->optimize();
  sqlextra->optimize();
  delete sqlbase;
  delete sqlextra;
  QSqlDatabase::removeDatabase("qt_sql_base_visitbox_connection");
  QSqlDatabase::removeDatabase("qt_sql_extra_visitbox_connection");

  delete msgbox;
  delete autoSaveTimer;
  delete shift_pageUp;
  delete shift_pageDown;
  delete ui;
}

void visitsBox::grabSave() {
  if (isVisitModified() && vEditMode) save(grabVisit(), true);
}

void visitsBox::onDrugLoadCompleted() {
  if (!visitLoaded) emit loadCompleters();
  initializeAutoSave();
  toggleSyncPrintButtons();
  drugLoadCompleted = true;
  visitLoaded = true;
}

void visitsBox::add2RoshettaAutoComplete(QString w) {
  sqlextra->addToAutoComplete("dictionary", w);
}

void visitsBox::popUpMessage(QString title, QString message) {
  emit newMessage(title, message);
}

void visitsBox::isCompleterPopupVisible(bool v) { mLineEditPopUpVisible = v; }

void visitsBox::removeItemFromCompleter(QString item, QString table) {
  sqlextra->removeFromAutoComplete(table, item);
}

void visitsBox::removeItemFromDictionary(QString item, int row) {
  sqlextra->removeFromAutoComplete("dictionary", item);
  emit removeFromCompleter(row);
}

void visitsBox::finishedSavingVisit(bool state) {
  QString msg = state ? "Visit Data was Saved Successfuly"
                      : "Sorry, Visit Data was NOT Saved";
  emit newMessage("Information", msg);
  drugsAltered = !state;
  saving = false;
  autoSaveTimer->start();
}

void visitsBox::navButtonsLeftClicked() {
  if (ui->InvestigationsTable->isWorking() || ui->vDrugsTable->isWorking())
    return;

  QString mCaller = sender()->objectName();
  if (mCaller == "nexVisit")
    goNextVisit();
  else if (mCaller == "preVisit")
    goPreviousVisit();
}

void visitsBox::navButtonsRightClicked() {
  if (ui->InvestigationsTable->isWorking() || ui->vDrugsTable->isWorking())
    return;
  QString mCaller = sender()->objectName();
  if (mCaller == "nexVisit")
    goLastVisit();
  else if (mCaller == "preVisit")
    goFirstVisit();
}

mSettings::defaultFont visitsBox::getDefaultFont() {
  return settings.getDefaultFont();
}

bool visitsBox::isCompleteByWord() { return settings.isAutoCompleteByWord(); }

void visitsBox::setSuggestedVisitType(const int &_visitType) {
  suggestedVisitType = _visitType;
}

void visitsBox::on_toolButtonRefresh_clicked() {
  if (aboutToClose) return;

  int reply = msgbox->question(
      this, "Confirm patient visit reloading",
      "Are you sure that you want to reload visit data from disk? "
      "This can not be undone",
      QMessageBox::Yes, QMessageBox::No, true);
  if (reply == QMessageBox::No) return;

  fillVisit(sqlbase->getPatientVisitData(patientBasicDetails.ID,
                                         comboSelectedDataTime));
  emit newMessage("Information", "Visit data was reloaded");
}

void visitsBox::toggleEditMode() {
  if (vEditMode && alwaysSave) {
    vEditMode = mSave(grabVisit(), false) ? !vEditMode : vEditMode;
    enableEditMode(vEditMode);
    return;

  } else if (vEditMode) {
    int reply;
    reply = msgbox->question(this, "Message", "Do you want to save changes?",
                             QMessageBox::Yes, QMessageBox::No);
    if (reply == QMessageBox::No) {
      vEditMode = !vEditMode;
      enableEditMode(vEditMode);
      return;

    } else {
      vEditMode = mSave(grabVisit(), false) ? !vEditMode : vEditMode;
      enableEditMode(vEditMode);
      return;
    }
  }
  vEditMode = !vEditMode;
  enableEditMode(vEditMode);
  return;
}

void visitsBox::enableEditMode(bool _vEditMode) {
  ui->buttonAddInvestigations->setEnabled(
      ui->investigationsLine->text().isEmpty() ? false : _vEditMode);
  ui->buttonAddDrug->setEnabled(ui->drugLine->text().isEmpty() ? false
                                                               : _vEditMode);
  ui->buttonRemoveInvestigations->setEnabled(
      (ui->InvestigationsTable->getSelectedRows() > 0) ? _vEditMode : false);
  ui->buttonRemoveDrug->setEnabled(
      (ui->vDrugsTable->getSelectedRows() > 0) ? _vEditMode : false);
  ui->lmpDate->setReadOnly(!_vEditMode);
  ui->comboVisitType->setEnabled(_vEditMode);
  ui->toolButtonRefresh->setEnabled(_vEditMode);
  ui->dateFollowUp->setEnabled(
      (!dataHelper::str2bool(loadedVisit.checkButtonCaseClose)) ? _vEditMode
                                                                : false);
  ui->lockUnlockButton->setIcon(
      QIcon(_vEditMode ? ":/Graphics/unlock" : ":/Graphics/lock"));
  emit setReadWrite(_vEditMode);
}
// obselete method
bool sortDrugsStar(const QString &s1, const QString &s2) {
  return s1.endsWith("*") < s2.endsWith("*");
}

void visitsBox::on_buttonInvest_clicked() {
  invesList invList(this, patientBasicDetails.ID);
  invList.toggleVisualEffects(settings.isVisualEffectsEnabled());
  invList.exec();
}

void visitsBox::autosave() {
  if (!saving && vEditMode && isVisitModified()) {
    mSave(grabVisit(), false);
    if (!mLineEditPopUpVisible)
      emit newMessage("autosave", "Visit Data was Saved to disk");
  }
}

void visitsBox::on_investigationsLine_textChanged(const QString &arg1) {
  if (arg1.length() == 0)
    ui->buttonAddInvestigations->setEnabled(false);
  else
    ui->buttonAddInvestigations->setEnabled(vEditMode);
}

void visitsBox::on_drugLine_textChanged(const QString &arg1) {
  if (arg1.length() == 0)
    ui->buttonAddDrug->setEnabled(false);
  else
    ui->buttonAddDrug->setEnabled(vEditMode);
}

void visitsBox::SyncToPatient(bool sync) {
  int reply = msgbox->question(
      this, "Confirm Drugs %1",
      QString("Are you sure that you want to %1 %2")
          .arg(sync ? "Sync this visit prescripton to Patient drugs list? "
                    : "Replace patients drugs with this visit drugs.")
          .arg(sync ? "Sync will update only and will not replace drugs. "
                    : "<b>This can not be undone</b>"),
      QMessageBox::Yes, QMessageBox::No);
  if (reply == QMessageBox::No) return;

  int row = ui->vDrugsTable->getRowsCount();
  if (row == 0) {
    emit newMessage(
        "Warning",
        QString("No available Drugs to %1").arg(sync ? "Sync." : "Replace."));
    return;
  }

  QList<QStringList> array;
  QStringList list;
  for (int r = 0; r < row; r++) {
    for (int c = 0; c < 8; c++) {
      list << ui->vDrugsTable->getDrugsModel()->item(r, c)->text().simplified();
    }
    array.append(list);
    list.clear();
  }
  emit syncDrugs(array, sync);
}

void visitsBox::SyncToVisit() {
  int reply = msgbox->question(
      this, "Confirm Drugs sync",
      "Are you sure that you want to copy patient current drugs to this visit?",
      QMessageBox::Yes, QMessageBox::No);
  if (reply == QMessageBox::No) return;

  int vRow = ui->vDrugsTable->getRowsCount();

  if (vRow != 0) {
    emit newMessage("Warning",
                    "Visit drugs list should be empty prior filling from "
                    "current patient drugs.");
    return;
  }

  // int pRow =
  // getDrugsCountForVists(ID,0);//sqlbase->readDrugs(ID,0,ui->vDrugsTable->getDrugsModel())->rowCount();

  if (!doeshaveDrugsInPatient()) {
    emit newMessage("Warning",
                    "No drugs to copy from patients record to this visit.");
    return;
  }

  ui->vDrugsTable->loadPatientDrugsModel(patientBasicDetails.ID, 0, 0, true);
}

void visitsBox::SyncLastVisit() {
  int reply = msgbox->question(
      this, "Confirm Drugs sync",
      "Are you sure that you want to copy last visit drugs to this visit? ",
      QMessageBox::Yes, QMessageBox::No);
  if (reply == QMessageBox::No) return;

  int vCount = ui->visitLists->count();
  int row = ui->vDrugsTable->getRowsCount();
  int idx = ui->visitLists->currentIndex();

  QString visitDateTime = ui->visitLists->itemText(idx + 1).simplified();
  QLocale locale = QLocale(QLocale::English, QLocale::UnitedStates);
  QDateTime dt = locale.toDateTime(visitDateTime, "dd/MM/yyyy hh:mm AP ddd");
  qint64 date = dt.date().toJulianDay();
  qint64 time = dt.time().msecsSinceStartOfDay() / 1000;

  if (!doesHaveDrugsInLastVisit()) {
    emit newMessage("Warning", "No Drugs Found in last visit.");
    return;
  }

  if ((row != 0) || !(idx < vCount)) {
    emit newMessage("Warning",
                    "Visit drugs list should be empty prior filling from last "
                    "visit drugs.");
    return;
  }
  ui->vDrugsTable->loadPatientDrugsModel(patientBasicDetails.ID, date, time,
                                         true);
}

void visitsBox::on_comboVisitType_currentIndexChanged(int index) {
  if (index < VisitTypes::n_visitsType::NewVisit ||
      index > VisitTypes::n_visitsType::Undefined)
    return;

  ui->visitLists->setVisitIcon(visitTypes.getVisitTypesByUiIndex(index).id,
                               visitTypes.getVisitTypesByUiIndex(index).icon);
}

void visitsBox::on_closeButton_clicked() { close(); }

void visitsBox::addNewInvestigation(QString newInvName) {
  int state = 0;
  double price = 0;
  qint64 julianDate;
  qint64 visitTime;
  visitDateTimeSetter(julianDate, visitTime);

  QStringList paidServices = sqlextra->getPaidServicesList();
  if (paidServices.contains(newInvName)) {
    state = 2;
    price = sqlextra->getPaidServicePrice(newInvName);
  }

  ui->InvestigationsTable->addNewInvest(patientBasicDetails.ID, julianDate,
                                        newInvName, state, price);
  emit insertUniqueItem(newInvName, "investigationsLine");
  ui->InvestigationsTable->saveInvestigation(patientBasicDetails.ID, julianDate,
                                             visitTime);
}

void visitsBox::addNewDrug(QString newDrugName) {
  if (ui->vDrugsTable->addDrug2DrugList(newDrugName)) {
    newDrugName.remove("*");
    emit insertUniqueItem(newDrugName, "drugLine");
    emit insertDrug2Patient(newDrugName, "drugLine");
    emit clearDrugLine();
  }
}

void visitsBox::mousePressEvent(QMouseEvent *event) {
#if QT_VERSION >= 0x060000
  m_nMouseClick_X_Coordinate = event->globalPosition().x();
  m_nMouseClick_Y_Coordinate = event->globalPosition().y();
#else
  m_nMouseClick_X_Coordinate = event->x();
  m_nMouseClick_Y_Coordinate = event->y();
#endif
}
void visitsBox::mouseMoveEvent(QMouseEvent *event) {
  if (event->modifiers() == Qt::ControlModifier) {
#if QT_VERSION >= 0x060000
    move(event->globalPosition().x() - m_nMouseClick_X_Coordinate,
         event->globalPosition().y() - m_nMouseClick_Y_Coordinate);
#else
    move(event->globalX() - m_nMouseClick_X_Coordinate,
         event->globalY() - m_nMouseClick_Y_Coordinate);

#endif
  }
}

// int visitsBox::visitDateTime2JulianDate()
//{
//     QString visitDateTime =  ui->visitLists->currentText().simplified();
//     QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
//     QDateTime dt = locale.toDateTime(visitDateTime,"dd/MM/yyyy hh:mm AP
//     ddd"); int julianDate = static_cast<int>(dt.date().toJulianDay()); return
//     julianDate;
// }

void visitsBox::visitDateTimeSetter(qint64 &t_visitJulianDate,
                                    qint64 &t_visitTime) {
  QString visitDateTime = ui->visitLists->currentText().simplified();
  QLocale locale = QLocale(QLocale::English, QLocale::UnitedStates);
  QDateTime dt = locale.toDateTime(visitDateTime, "dd/MM/yyyy hh:mm AP ddd");
  t_visitJulianDate = dt.date().toJulianDay();
  t_visitTime = dt.time().msecsSinceStartOfDay() / 1000;
}

void visitsBox::followUpDateChanged(const QDate &date) {
  int selectedDateFollowUps = followNotify(date);
  setFollowDateTooltip(selectedDateFollowUps, date);
  lastSelectedFollowupDate = date;
  settings.saveLastSelectedFollowUpDate(date);
}

void visitsBox::onShift_pageUp() { goLastVisit(); }

void visitsBox::onShift_pageDown() { goFirstVisit(); }

void visitsBox::selectLastInvRow() {
  ui->InvestigationsTable->selectRow(lastInvestigationRow);
  bool _s = ui->InvestigationsTable->selectionModel()->currentIndex().isValid();
  ui->buttonRemoveInvestigations->setEnabled(_s);
}

void visitsBox::showCosts(double est, bool percision) {
  if (percision)
    ui->rxCost->setText(QString("est. Cost = %1 LE.").arg(est));
  else
    ui->rxCost->setText(QString("est. Cost > %1 LE. !").arg(est));
}

void visitsBox::toggleDrugsAlteredStatus(bool b) { drugsAltered = b; }

int visitsBox::getDrugsCountForVists(int _id, int julianDate) {
  return sqlbase->getDrugsCout(_id, julianDate);
}

int visitsBox::getPatientsDrugsCount(int _id) {
  return sqlbase->getDrugsCout(_id, 0);
}

bool visitsBox::doesHaveDrugsInLastVisit() {
  int visit_count = ui->visitLists->count();

  if (visit_count < 2) return false;

  int index = ui->visitLists->currentIndex();
  int last_visit_index = index + 1;

  if (last_visit_index == visit_count) return false;

  QString visitDateTime =
      ui->visitLists->itemText(last_visit_index).simplified();
  QLocale locale = QLocale(QLocale::English, QLocale::UnitedStates);
  QDateTime dt = locale.toDateTime(visitDateTime, "dd/MM/yyyy hh:mm AP ddd");
  int date = static_cast<int>(dt.date().toJulianDay());
  return (getDrugsCountForVists(patientBasicDetails.ID, date) > 0);
}

bool visitsBox::doeshaveDrugsInPatient() {
  return (getPatientsDrugsCount(patientBasicDetails.ID) > 0);
}

void visitsBox::toggleDateFollowup() {
  if (!vEditMode) return;

  bool isRequest =
      visitTypes.getVisitTypesByUiIndex(ui->comboVisitType->currentIndex())
          .id == VisitTypes::n_visitsType::Requests;
  if (ui->dateFollowUp->date() == lastVisitDate) {
    if (!isRequest) {
      while (true) {
        if (((1 << lastSelectedFollowupDate.dayOfWeek()) &
             (VisitHelper::WorkDays)settings.getWorkingDays()) &&
            (sqlbase->getFollowUpsCountForThisDate(lastSelectedFollowupDate,
                                                   patientBasicDetails.ID) <
             settings.getMaxFollowUps())) {
          ui->dateFollowUp->setDate(lastSelectedFollowupDate);
          break;
        } else if (settings.getMaxFollowUps() > 0) {
          lastSelectedFollowupDate = lastSelectedFollowupDate.addDays(1);
        }
      }
    } else {
      ui->dateFollowUp->setDate((lastFollowupDate != lastFollowupDate2)
                                    ? lastFollowupDate2
                                    : lastFollowupDate);
      // mDebug() << lastFollowupDate << lastFollowupDate2;
    }

  } else {
    ui->dateFollowUp->setDate(lastVisitDate);
  }

  int selectedDateFollowUps = followNotify(lastSelectedFollowupDate, isRequest);
  setFollowDateTooltip(selectedDateFollowUps, lastSelectedFollowupDate);
}

void visitsBox::connectSignals(QWidget *parent) {
  connect(this, SIGNAL(clearInvLine()), ui->investigationsLine, SLOT(clear()),
          Qt::QueuedConnection);
  connect(this, SIGNAL(clearDrugLine()), ui->drugLine, SLOT(clear()),
          Qt::QueuedConnection);
  connect(ui->vDrugsTable, SIGNAL(clicked(QModelIndex)), this,
          SLOT(enableRemoveDrugButton()));
  connect(ui->vDrugsTable, SIGNAL(popUpMessage(QString, QString)), parent,
          SLOT(popUpMessage(QString, QString)));
  connect(ui->vDrugsTable, SIGNAL(loadCompleted()), this,
          SLOT(onDrugLoadCompleted()));
  connect(ui->vDrugsTable, SIGNAL(drugTableItemChanged()), this,
          SLOT(toggleSyncPrintButtons()));
  connect(ui->InvestigationsTable, SIGNAL(togglePrintButton()), this,
          SLOT(toggleSyncPrintButtons()));
  connect(ui->InvestigationsTable, SIGNAL(popUpMessage(QString, QString)),
          parent, SLOT(popUpMessage(QString, QString)));
  connect(ui->visitLists, SIGNAL(loadCompleted()), this,
          SLOT(toggleContollers()));
  connect(ui->visitLists, SIGNAL(saveVisit()), this, SLOT(grabSave()));
  connect(ui->dateFollowUp->calendarWidget(), SIGNAL(clicked(QDate)), this,
          SLOT(followUpDateChanged(QDate)));
  connect(ui->vDrugsTable, SIGNAL(reloadDrugsLineAutoComplete()), ui->drugLine,
          SLOT(mUpdateCompleter()));
  connect(this, SIGNAL(updateDrugsCompleter()), ui->drugLine,
          SIGNAL(updateDrugsCompleter()));
  connect(autoSaveTimer, SIGNAL(timeout()), this, SLOT(autosave()));
  connect(shift_pageUp, SIGNAL(activated()), this, SLOT(onShift_pageUp()));
  connect(shift_pageDown, SIGNAL(activated()), this, SLOT(onShift_pageDown()));
  connect(printShortcut, SIGNAL(activated()), this,
          SLOT(on_fastPrint_leftButtonClicked()));
  connect(printPreviewShortcut, SIGNAL(activated()), this,
          SLOT(on_fastPrint_rightButtonClicked()));
  // connect (
  // this,SIGNAL(showPreview()),print,SLOT(showPrintPreviewDialog()));// this is
  // for rt
  connect(easyPrintShortcut, SIGNAL(activated()), this,
          SLOT(on_fastPrint_middleButtonClicked()));
  connect(ui->vDrugsTable, SIGNAL(syncDrugs(QList<QStringList>, bool)), this,
          SIGNAL(syncDrugs(QList<QStringList>, bool)));
  connect(ui->InvestigationsTable, SIGNAL(selectLastInvRow()), this,
          SLOT(selectLastInvRow()));
  connect(ui->vDrugsTable, SIGNAL(showRxCost(double, bool)), this,
          SLOT(showCosts(double, bool)));
  // connect (
  // print,SIGNAL(add2AutoComplete(QString)),this,SLOT(add2RoshettaAutoComplete(QString)));
  // connect (
  // print,SIGNAL(refreshRoshetta(mSettings::prescriptionPrintSettings,QString,int)),this,SLOT(genRoshettaHTML(mSettings::prescriptionPrintSettings,QString,int)));
  connect(print, SIGNAL(message(QString, QString)), this,
          SIGNAL(newMessage(QString, QString)));
  connect(ui->lockUnlockButton, SIGNAL(clicked()), this,
          SLOT(toggleEditMode()));
  connect(ui->InvestigationsTable, SIGNAL(toggleRemoveInvButton(bool)),
          ui->buttonRemoveInvestigations, SLOT(setEnabled(bool)));
  connect(ui->vDrugsTable, SIGNAL(drugsHasBeenAltered(bool)), this,
          SLOT(toggleDrugsAlteredStatus(bool)), Qt::QueuedConnection);
  connect(add2CompleterWorker, SIGNAL(finished()), this,
          SIGNAL(reloadCompleter()));
  connect(add2CompleterWorker, SIGNAL(finished()), this,
          SIGNAL(reloadMWCompleter()));
  connect(visitSaverWorker, SIGNAL(finishedSavingState(bool)), this,
          SLOT(finishedSavingVisit(bool)));

  connect(ui->vDrugsTable, SIGNAL(SyncToVisit()), this, SLOT(SyncToVisit()));
  connect(ui->vDrugsTable, SIGNAL(SyncToPatient(bool)), this,
          SLOT(SyncToPatient(bool)));
  connect(ui->vDrugsTable, SIGNAL(SyncLastVisit()), this,
          SLOT(SyncLastVisit()));

  connect(ui->vDrugsTable, SIGNAL(doeshaveDrugsInPatient()), this,
          SLOT(doeshaveDrugsInPatient()));
  connect(ui->vDrugsTable, SIGNAL(doesHaveDrugsInLastVisit()), this,
          SLOT(doesHaveDrugsInLastVisit()));
  connect(toggleFollowupDate, &QShortcut::activated, this,
          &visitsBox::toggleDateFollowup);
  connect(vTypeUp, &QShortcut::activated, ui->comboVisitType,
          &vTypeComboBox::goUp);
  connect(vTypeDown, &QShortcut::activated, ui->comboVisitType,
          &vTypeComboBox::goDown);
  connect(visitAsRequest, &QShortcut::activated, this,
          &visitsBox::on_ButtonVisit_clicked);
}

void visitsBox::addThisToCompleter(const sqlBase::Visit &visit) {
  add2CompleterWorker->setVisitData(visit);
  add2CompleterWorker->setMode(autoCompleteByWord);
#if QT_VERSION >= 0x060000
  auto f = QtConcurrent::run(&wm_add2Completer::vWork, add2CompleterWorker);
#else
  auto f = QtConcurrent::run(add2CompleterWorker, &wm_add2Completer::vWork);
#endif
}

void visitsBox::toggleAntenatal(bool checked) {
  ui->labelEDD->setVisible(checked);
  ui->eddDate->setVisible(checked);
  ui->checkBoxAntenatal->setText(checked ? "" : "Antenatal");
}

void visitsBox::initializeAutoSave() {
  if (autoSave) {
    autoSaveTimer->setInterval(1000 * autosaveint);
    if (autoSaveTimer->isActive()) autoSaveTimer->stop();

    autoSaveTimer->start();
  }
}

bool visitsBox::isVisitModified() {
  sqlBase::Visit currentVisit = grabVisit();
  return ((currentVisit != loadedVisit) || drugsAltered);
}

void visitsBox::setFollowDateTooltip(const int &selectedDateFollowUps,
                                     const QDate &date) {
  QLocale en_US = QLocale(QLocale::English, QLocale::UnitedStates);
  QString day = en_US.toString(date, "dddd dd/MM/yyyy");
  ui->dateFollowUp->setToolTip(QString("%1 has currently %2/%3 patients.")
                                   .arg(day)
                                   .arg(selectedDateFollowUps)
                                   .arg(maxFollowUps));
}

void visitsBox::goSaveVisit(int index) {
  if (ui->investigationsLine->completer()->popup()->isVisible() ||
      ui->drugLine->completer()->popup()->isVisible())
    return;

  if (vEditMode && isVisitModified()) {
    save(grabVisit(), false);
    emit newMessage("Information", "Visit Data was Saved");
  }
  ui->visitLists->setCurrentIndex(index);
  //    ui->drugLine->completer()->popup()->hide();
  //    ui->drugLine->clear();
  //    ui->investigationsLine->completer()->popup()->hide();
  //    ui->investigationsLine->clear();
}

void visitsBox::goFirstVisit() {
  int visits_count = ui->visitLists->count();
  int currentIndex = visits_count - 1;
  goSaveVisit(currentIndex);
}

void visitsBox::goLastVisit() { goSaveVisit(0); }

void visitsBox::goPreviousVisit() {
  int currentIndex = ui->visitLists->currentIndex();
  int visits_count = ui->visitLists->count();
  if ((currentIndex < visits_count) && (visits_count != 1)) currentIndex++;
  goSaveVisit(currentIndex);
}

void visitsBox::goNextVisit() {
  int currentIndex = ui->visitLists->currentIndex();
  int visits_count = ui->visitLists->count();
  if ((currentIndex > 0) && (visits_count != 1)) currentIndex--;
  goSaveVisit(currentIndex);
}

int visitsBox::followNotify(const QDate &date, bool isRequest) {
  QLocale en_US = QLocale(QLocale::English, QLocale::UnitedStates);

  int selectedDateFollowUps =
      sqlbase->getFollowUpsCountForThisDate(date, patientBasicDetails.ID) + 1;

  if (!isRequest) {
    if (selectedDateFollowUps > maxFollowUps && maxFollowUps > 0) {
      newMessage("Warning", QString("Warning, Follow up limit exceeded for "
                                    "(%1) , current : %2, limit : %3")
                                .arg(en_US.toString(date, "dddd dd/MM/yyyy"))
                                .arg(selectedDateFollowUps)
                                .arg(maxFollowUps));
    } else if (maxFollowUps > 0) {
      newMessage("Message",
                 QString("The date (%1) currently has %2/%3 follow ups")
                     .arg(en_US.toString(date, "dddd dd/MM/yyyy"))
                     .arg(selectedDateFollowUps)
                     .arg(maxFollowUps));
    }
  } else {
    newMessage("Message", QString("The follow up was set to %1")
                              .arg(en_US.toString(date, "dddd dd/MM/yyyy")));
  }

  return selectedDateFollowUps;
}

mSettings::Roshetta visitsBox::getRoshetta() {
  mSettings::Roshetta roshetta;

  roshetta.ID =
      QStringLiteral("%1").arg(patientBasicDetails.ID, 5, 10, QLatin1Char('0'));
  roshetta.name = patientBasicDetails.Name;
  roshetta.age = patientBasicDetails.age;
  roshetta.sex = patientBasicDetails.sex;
  roshetta.Diagnosis = ui->Diagnosis->text().simplified();
  roshetta.visitDate =
      ui->visitLists->getParentVisitDate(ui->visitLists->currentIndex());
  roshetta.nextDate = ui->dateFollowUp->date();
  roshetta.printedinDate = QDateTime::currentDateTime();
  roshetta.caseClosed = ui->CheckButtonCaseClose->isChecked();
  roshetta.visitSymbole = visitTypes.getVisitSymbole(
      ui->comboVisitType->currentIndex(), ui->CheckButtonCaseClose->isChecked(),
      roshetta.printedinDate.date() == roshetta.nextDate);

  if (settings.userSpeciality() == dataHelper::Speciality::Paediatrics ||
      settings.userSpeciality() == dataHelper::Speciality::FamilyMedicine)
    roshetta.ageStyle = dataHelper::AgeStyle::compact;
  else
    roshetta.ageStyle = dataHelper::AgeStyle::printable;

  roshettaDrugsfiller(roshetta.baseDrugsList, getDrugsModel(), false);
  roshettaDrugsfiller(roshetta.currentDrugsList,
                      ui->vDrugsTable->getDrugsModel(), false);
  roshettaDrugsfiller(roshetta.baseAlteredDrugsList, getDrugsModel(), true);
  roshettaDrugsfiller(roshetta.currentAlteredDrugsList,
                      ui->vDrugsTable->getDrugsModel(), true);

  foreach (QString inv, ui->InvestigationsTable->getInvestigationsList())
    roshetta.requests << inv;

  roshettaVitalsFiller(roshetta.vitals);

  return roshetta;
}

void visitsBox::roshettaDrugsfiller(QList<mSettings::drug> &drugs,
                                    DrugsItemModel *drugsModel,
                                    bool alteredDrugsOnly) {
  for (int i = 0; i < drugsModel->rowCount(); i++) {
    if (!drugsModel->item(i, 5)->text().toInt()) continue;

    if (alteredDrugsOnly && drugsModel->item(i, 3)->text().toInt() !=
                                QDate::currentDate().toJulianDay())
      continue;

    mSettings::drug drug;
    drug.TradeName = drugsModel->item(i, 0)->text();
    QString genericName = drugsModel->item(i, 1)->text();

    if (sqlextra->isExpandExists(drug.TradeName)) {
      if (genericName.isEmpty())
        drug.TradeName = sqlextra->getExpand(drug.TradeName);
      else
        drug.TradeName = genericName;
      dataHelper::cleanExpanderHTML(drug.TradeName);
    } else {
      dataHelper::cleanDrugName(drug.TradeName);
    }
    drug.TradeName.insert(0, " ");                 // add space
    drug.TradeName.insert(0, PRESCRIPTIONSYMBOL);  //"℞"
    drug.Dose = drugsModel->item(i, 2)->text();
    drug.StartDate =
        QDate::fromJulianDay(drugsModel->item(i, 3)->text().toInt())
            .toString("dd/MM/yyyy");
    drugs << drug;
  }
}

void visitsBox::roshettaVitalsFiller(mSettings::Vitals &vitals) {
  vitals.weight = ui->weight->text().toDouble();
  vitals.height = ui->height->text().toInt();
  vitals.sPo2 = ui->sPo2->text().toInt();
  vitals.RBS = ui->RBS->text();
  vitals.pulse = ui->pPulse->text().toInt();
  vitals.RR = ui->pRR->text().toInt();
  vitals.BP = ui->pBP->text();
  vitals.T = ui->pTemp->text().toDouble();
}

void visitsBox::setVitalsPlaceHolderText() {
  QLocale locale(QLocale::English, QLocale::UnitedStates);
  QDateTime mDate = locale.toDateTime(ui->visitLists->currentText(),
                                      "dd/MM/yyyy hh:mm AP ddd");
  int mVisitDate = mDate.date().toJulianDay();

  mSettings::Vitals placeHolderText =
      sqlbase->getPatientVisitVitalsforPlaceholderText(patientBasicDetails.ID,
                                                       mVisitDate);

  ui->pPulse->setPlaceholderText(placeHolderText.pulse <= 0
                                     ? QString()
                                     : QString::number(placeHolderText.pulse));
  ui->pRR->setPlaceholderText(placeHolderText.RR <= 0
                                  ? QString()
                                  : QString::number(placeHolderText.RR));
  ui->pTemp->setPlaceholderText(
      placeHolderText.T <= 0 ? QString() : QString::number(placeHolderText.T));
  ui->pBP->setPlaceholderText(placeHolderText.BP == "-1" ? QString()
                                                         : placeHolderText.BP);
  ui->weight->setPlaceholderText(placeHolderText.weight <= 0
                                     ? QString()
                                     : QString::number(placeHolderText.weight));
  ui->height->setPlaceholderText(placeHolderText.height <= 0
                                     ? QString()
                                     : QString::number(placeHolderText.height));
  ui->RBS->setPlaceholderText(
      placeHolderText.RBS == "-1" ? QString() : placeHolderText.RBS);
  ui->sPo2->setPlaceholderText(placeHolderText.sPo2 <= 0
                                   ? QString()
                                   : QString::number(placeHolderText.sPo2));
  ui->lineEditWeight->setPlaceholderText(
      placeHolderText.weight <= 0 ? QString()
                                  : QString::number(placeHolderText.weight));
  ui->lineEditLength->setPlaceholderText(
      placeHolderText.height <= 0 ? QString()
                                  : QString::number(placeHolderText.height));
}

bool visitsBox::mSave(const sqlBase::Visit &visit, const bool &threading) {
  saving = true;

  if (isVisitModified()) addThisToCompleter(visit);

  if (ui->visitLists->currentIndex() == 0)
    emit syncLMPDateWithPatients(ui->lmpDate->date());

  sqlBase::visitData visitData;
  visitData.ID = patientBasicDetails.ID;
  visitData.visit = visit;
  visitData.visitDateTime = visit.visitDateTime;
  visitDateTimeSetter(visitData.visitDate, visitData.visitTime);
  visitData.drugsModel = ui->vDrugsTable->getDrugsModel();
  visitData.invModel = ui->InvestigationsTable->getInvestigationsModel();
  visitData.visitPrice =
      visitTypes.getVisitTypesByAlgoIndex(visit.visitType).price;
  if (threading) {
    visitSaverWorker->setVisitData(visitData);
#if QT_VERSION >= 0x060000
    auto f = QtConcurrent::run(&wm_visitSaver::Work, visitSaverWorker);
#else
    auto f = QtConcurrent::run(visitSaverWorker, &wm_visitSaver::Work);
#endif
    drugsAltered =
        true;  // might be not needed as it will be changed in the post thread.
    return true;
  } else {
    bool b = sqlbase->saveVisitData(visitData);
    saving = false;
    drugsAltered = !b;
    return b;
  }
}
void visitsBox::toggleSyncPrintButtons() {
  //    bool isThereActiveDrug = (ui->vDrugsTable->isThereActiveDrugs() ||
  //    getDrugsModel()->isThereActiveDrugs()  ); bool
  //    isTherePrintableInvestigations =
  //    ui->InvestigationsTable->printableInvestigationsExists();
  //    ui->fastPrint->setEnabled((isThereActiveDrug ||
  //    isTherePrintableInvestigations));
  //    //mDebug() << isThereActiveDrug << isTherePrintableInvestigations;
  ui->buttonRemoveInvestigations->setEnabled(
      vEditMode && ui->InvestigationsTable->getSelectedRows() != -1);
  ui->buttonRemoveDrug->setEnabled(
      vEditMode && ui->vDrugsTable->selectionModel()->hasSelection());
}

void visitsBox::setPatient(
    const visitsBox::mPatientBasicDetails &_patientBasicDetails) {
  aboutToClose = false;
  vEditMode = true;
  visitLoaded = false;
  ui->visitLists->clear();
  clearVisit();
  emit styleVitals(settings);

  this->patientBasicDetails = _patientBasicDetails;

  ui->patientName->setText(patientBasicDetails.Name);
  ui->fpal->setText(patientBasicDetails.fPal);

  ui->InvestigationsTable->setPatientID(patientBasicDetails.ID);
  ui->visitLists->populateWithVisitList(patientBasicDetails.ID);
  ui->lmpDate->setDate(QDate::currentDate());
  ui->eddDate->setHidden(!ui->checkBoxAntenatal->isChecked());
  ui->labelEDD->setHidden(!ui->checkBoxAntenatal->isChecked());
  ui->presentation->setFocus(Qt::OtherFocusReason);
  //    auto _cons = cons;

  //    cons = QSqlDatabase::connectionNames();
  //    for(const auto &b:cons )
  //    {
  //        if(!_cons.contains(b))
  //            mDebug() << b;
  //    }
}

void visitsBox::on_fastPrint_leftButtonClicked() {
  if (!drugLoadCompleted) return;
  print->loadDiets(sqlextra->getDietList());
  print->setRoshettaData(getRoshetta());
  print->show();
}

void visitsBox::on_fastPrint_rightButtonClicked() {
  if (!drugLoadCompleted) return;
  print->setRoshettaData(getRoshetta());
  print->showPrintPreviewDialog();
}

void visitsBox::on_fastPrint_middleButtonClicked() {
  if (!drugLoadCompleted) return;
  print->setRoshettaData(getRoshetta());
  print->mPrint(true);
}

void visitsBox::enableRemoveDrugButton() {
  ui->buttonRemoveDrug->setEnabled(vEditMode);
}

void visitsBox::on_InvestigationsTable_clicked(const QModelIndex &index) {
  Q_UNUSED(index)
  ui->buttonRemoveInvestigations->setEnabled(
      vEditMode && (ui->InvestigationsTable->getSelectedRows() != -1));
}

void visitsBox::on_lmpDate_userDateChanged(const QDate &date) {
  ui->eddDate->setDate(QDate::fromJulianDay(date.toJulianDay() + 280));
}

void visitsBox::on_lineEditWeight_textChanged(const QString &arg1) {
  ui->weight->setText(arg1);
}

void visitsBox::on_weight_textChanged(const QString &arg1) {
  ui->lineEditWeight->setText(arg1);
}

void visitsBox::on_checkBoxAntenatal_clicked(bool checked) {
  toggleAntenatal(checked);
}

void visitsBox::toggleContollers() {
  int visits_count = ui->visitLists->count();
  int currentIndex = ui->visitLists->currentIndex();
  bool enableSave = (visits_count > 0);
  bool enableDelete = ((visits_count > 1) && (currentIndex < visits_count - 1));
  bool enableFollows =
      currentIndex == 0 && !ui->CheckButtonCaseClose->isChecked();
  bool previusVisitFound =
      ((currentIndex < visits_count - 1) && (visits_count != 1));
  bool nextVisitFound = ((currentIndex > 0) && (visits_count != 1));
  ui->ButtonVisit->setEnabled(enableFollows);
  ui->ButtonSave->setEnabled(enableSave);
  ui->ButtonDel->setEnabled(enableDelete);
  ui->nexVisit->setEnabled(nextVisitFound);
  ui->preVisit->setEnabled(previusVisitFound);
}

void visitsBox::on_lineEditLength_textChanged(const QString &arg1) {
  ui->height->setText(arg1);
}

void visitsBox::on_height_textChanged(const QString &arg1) {
  ui->lineEditLength->setText(arg1);
}
