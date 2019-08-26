#include "visitsbox.h"
#include "ui_visitsbox.h"

visitsBox::visitsBox(QWidget *parent) : mDialog(parent),
  ui(new Ui::visitsBox),
  msgbox(new myMessageBox(this)),
  sqlbase(new sqlBase(this,"qt_sql_base_visitbox_connection",false)),
  sqlextra(new sqlExtra(this,"qt_sql_extra_visitbox_connection",false)),
  autoSaveTimer(new QTimer),
  add2CompleterWorker(new wm_add2Completer),
  visitSaverWorker(new wm_visitSaver),
  print(new printDrugs(this)),
  //calWidget(new mCalendarWidget(this)),
  shift_pageUp(new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_PageUp), this)),
  shift_pageDown(new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_PageDown), this)),
  printShortcut(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P),this)),
  easyPrintShortcut(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O),this)),
  printPreviewShortcut(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I),this)),
  toggleFollowupDate(new QShortcut(Qt::Key_F12,this)),
  vTypeUp(new QShortcut(Qt::Key_F10,this)),
  vTypeDown(new QShortcut(Qt::Key_F11,this))

{
  ui->setupUi(this);
  tweakui();
  connectSignals(parent);
}

void visitsBox::tweakui()
{
  this->setLocale(QLocale("en_US"));
  ui->dateFollowUp->setCalendarPopup(true);
  shift_pageUp->setContext(Qt::WindowShortcut);
  shift_pageDown->setContext(Qt::WindowShortcut);
  ui->presentationAnalysis->setMaximumHeight(this->height()/6);
  setWindowFlags(this->windowFlags() | Qt::Window | Qt::FramelessWindowHint);
  autosaveint =  settings.getAutoSaveInterval();
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

  ui->pPulse ->setVitalType(0,speciality);
  ui->pBP->setVitalType(1,speciality);
  ui->pRR->setVitalType(2,speciality);
  ui->pTemp->setVitalType(3,speciality);

  bool isTreatingMinors =
      ( speciality == dataHelper::Speciality::Paediatrics || speciality == dataHelper::Speciality::FamilyMedicine );

  ui->widgetBaby->setVisible(isTreatingMinors);

  if ( speciality == dataHelper::Speciality::ObGyn )
    {
      ui->ObstWidget->show();
      ui->labelObstUS->show();
      ui->patientObstUS->show();
      ui->fpalLabel->show();
      ui->fpal->show();
      ui->labelPelvic->show();
      ui->patientPelvicExam->show();
      ui->notesLabel->hide();
      ui->plaintextNotes->hide();

    }
  else
    {
      ui->ObstWidget->hide();
      ui->labelObstUS->hide();
      ui->patientObstUS->hide();
      ui->fpalLabel->hide();
      ui->fpal->hide();
      ui->labelPelvic->hide();
      ui->patientPelvicExam->hide();
    }


  if ( screenMode )
    {   //setWindowState(this->windowState() | Qt::WindowMaximized);
      QDesktopWidget* m = QApplication::desktop();
      QRect dw = m->screenGeometry(m->screenNumber(QCursor::pos()));

      if ( dw.size() == QSize(800,600) )
        {
          setFixedSize(QSize(800,560));
          move(QPoint(0,0));
        }
      else
        {
          wm.centerOnScreen(this);
        }
      ui->plaintextNotes->hide();
      ui->notesLabel->hide();

    }
  else
    {
      if ( speciality != dataHelper::Speciality::ObGyn  )
        {
          ui->plaintextNotes->show();
          ui->notesLabel->show();
        }
      setFixedSize(800,700);
      wm.centerOnScreen(this);
    }

  if (simpleExamination)
    {
      ui->patientHeartLungEx->hide();
      ui->patientAbdomentBack->hide();
      ui->patientLL->hide();
      ui->labelGeneral->setText("<b>EXAMINATION</b>");
      ui->labelHeartnLungs->hide();
      ui->labelAbdomenBack->hide();
      ui->LabelLL->hide();
    }
  else
    {
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

void visitsBox::on_ButtonNew_clicked()
{
  if(newVisitCreationInProgress || aboutToClose)
    return;

  newVisitCreationInProgress=true;
  ui->ButtonNew->setEnabled(false);

  QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );

  QDateTime datetime = QDateTime::currentDateTime();
  QString englishDate = locale.toString(datetime, "dd/MM/yyyy");

  for ( int i = 0 ; i < ui->visitLists->count() ; i++ )
    {
      QString visitItemText = ui->visitLists->itemText(i).left(10);
      QDate dt = locale.toDate( visitItemText,"dd/MM/yyyy");
      QString visitDate = dt.toString("dd/MM/yyyy");
      if ( englishDate == visitDate )
        {
          msgbox->information(this,"Message","You Can't Add more than one visit for the same patient within a 24 hours period, Sorry!");
          ui->ButtonNew->setEnabled(true);
          newVisitCreationInProgress=false;
          return;
        }
    }
  int reply;

  QString msgText = "This will clear the current fields, Are you Sure?";
  reply = msgbox->question(this, "Message",msgText,
                           QMessageBox::Yes,QMessageBox::No);
  if (reply == QMessageBox::No)
    {
      ui->ButtonNew->setEnabled(true);
      newVisitCreationInProgress=false;
      return;

    }

//  ui->dateFollowUp->setDate(settings.isRemmberlastFollowupDate()? lastSelectedFollowupDate:QDate::currentDate());
  ui->dateFollowUp->setMinimumDate(QDate::currentDate());
  ui->lmpDate->setDate(QDate::currentDate());

  sqlBase::Visit visit = grabVisit();

//  if (vEditMode)
//    save(visit,false);

  visitindex = 0;
  double visitPrice = settings.getVisitPrice(visitindex);
  sqlbase->createNewVisit(ID,
                          visit.visitDateTime,
                          datetime,
                          visitindex,
                          visitPrice,
                          lastSelectedFollowupDate,
                          ui->vDrugsTable->getDrugsModel(),
                          ui->InvestigationsTable->getInvestigationsModel(),
                          sqlextra);
  ui->visitLists->populateWithVisitList(ID);
  updateVisitAge();
  vEditMode = true;
  enableEditMode(vEditMode);
  emit newMessage("Information","A New visit was Created");
  newVisitCreationInProgress=false;
  ui->ButtonNew->setEnabled(true);
}

void visitsBox::on_ButtonSave_clicked()
{
  if(aboutToClose)
    return;

  save(grabVisit());
  initializeAutoSave();
}

sqlBase::Visit visitsBox::grabVisit()
{
  sqlBase::Visit visit;
  visit.ID = ID;
  visit.presentation  = ui->presentation->text().simplified();
  visit.presentationAnalysis = ui->presentationAnalysis->toHtml();
  visit.diagnosis = ui->Diagnosis->text().simplified();
  visit.pulse = ui->pPulse->text();
  visit.rr = ui->pRR->text();
  visit.temp = ui->pTemp->text();
  visit.bp = ui->pBP->text();
  visit.weight = ui->lineEditWeight->text();
  visit.length = ui->lineEditLength->text();
  visit.headCir = ui->lineEditHead->text();
  visit.exGeneral = ui->patientGeneralEx->toHtml();
  visit.exChestHeart = ui->patientHeartLungEx->toHtml();
  visit.exAbdback = ui->patientAbdomentBack->toHtml();
  visit.exLL = ui->patientLL->toHtml();
  visit.visitDateTime = comboSelectedDataTime;
  visit.followDate = QString::number(ui->dateFollowUp->date().toJulianDay());
  visit.visitType = QString::number( ui->comboVisitType->currentIndex());
  visit.invResults = ui->investigationsResults->toHtml();
  visit.visitNotes = ui->plaintextNotes->toHtml();
  visit.checkButtonCaseClose = dataHelper::bool2String( ui->CheckButtonCaseClose->isChecked() );
  visit.LMPDATE = static_cast<int>(ui->lmpDate->date().toJulianDay());
  visit.ObstUS = ui->patientObstUS->toHtml();
  visit.Antenatal = dataHelper::bool2String(ui->checkBoxAntenatal->isChecked());
  visit.pelvicExam = ui->patientPelvicExam->toHtml();
  return visit;
}

void visitsBox::fillVisit(const sqlBase::Visit &visit)
{
  ui->presentation->setText(visit.presentation);
  ui->presentationAnalysis->setHtml(visit.presentationAnalysis);
  ui->Diagnosis->setText(visit.diagnosis);
  ui->pPulse->setText(visit.pulse);
  ui->pRR->setText(visit.rr);
  ui->pTemp->setText(visit.temp);
  ui->pBP->setText(visit.bp);
  ui->lineEditWeight->setText(visit.weight);
  ui->lineEditLength->setText(visit.length);
  ui->lineEditHead->setText(visit.headCir);
  ui->patientGeneralEx->setHtml(visit.exGeneral);
  ui->patientHeartLungEx->setHtml(visit.exChestHeart);
  ui->patientAbdomentBack->setHtml(visit.exAbdback);
  ui->patientLL->setHtml(visit.exLL);
  ui->comboVisitType->setCurrentIndex(visit.visitType.split(" ").at(0).toInt() );
  ui->investigationsResults->setHtml(visit.invResults);
  ui->plaintextNotes->setHtml(visit.visitNotes);

  ui->lmpDate->setDate(QDate::fromJulianDay(visit.LMPDATE));
  ui->patientObstUS->setHtml(visit.ObstUS);
  ui->patientPelvicExam->setHtml(visit.pelvicExam);
  ui->CheckButtonCaseClose->setChecked(dataHelper::str2bool(visit.checkButtonCaseClose));
  ui->checkBoxAntenatal->setChecked(dataHelper::str2bool(visit.Antenatal));

  toggleAntenatal(dataHelper::str2bool(visit.Antenatal));

  QString visitDateTime = ui->visitLists->currentText().simplified();
  QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
  int currentJulianDate = static_cast<int>(QDate::currentDate().toJulianDay());
  int visitJulianDate = static_cast<int>(locale.toDateTime(visitDateTime,"dd/MM/yyyy hh:mm AP ddd").date().toJulianDay());

  if (currentJulianDate == visitJulianDate)
    {

      vEditMode = true;
      enableEditMode(vEditMode);
    }
  else
    {
      vEditMode = false;
      enableEditMode(vEditMode);
    }
  updateVisitAge();
  ui->vDrugsTable->loadPatientDrugsModel(ID,visitDateTime2JulianDate());
  ui->InvestigationsTable->populateInvests(ID,visitDateTime2JulianDate());
  ui->dateFollowUp->setMinimumDate(locale.toDateTime(visitDateTime,"dd/MM/yyyy hh:mm AP ddd").date());

  QDate fd = QDate::fromJulianDay(visit.followDate.toInt());
  ui->dateFollowUp->setDate(fd);
  int selectedDateFollowUps = sqlbase->getFollowUpsCountForThisDate(fd,ID)+1;
  setFollowDateTooltip(selectedDateFollowUps,fd);
}

void visitsBox::clearVisit()
{
  ui->presentation->clear();
  ui->presentationAnalysis->clear();
  ui->Diagnosis->clear();
  ui->pPulse->clear();
  ui->pRR->clear();
  ui->pTemp->clear();
  ui->pBP->clear();
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

}

void visitsBox::on_visitLists_currentIndexChanged(const QString &arg1)
{
  if(arg1.isEmpty())
    return;
  clearVisit();
  comboSelectedDataTime = arg1;
  updateVisitAge();
  if (sqlbase->isVisitExists(ID,comboSelectedDataTime) )
    {
      loadedVisit = sqlbase->getPatientVisitData(ID,comboSelectedDataTime);
      fillVisit(loadedVisit);
    }
  else
    {
      ui->presentation->setFocus();
      QString visitDateString = comboSelectedDataTime.left(10);
      ui->dateFollowUp->setDate(settings.isRemmberlastFollowupDate()? lastSelectedFollowupDate:QDate::fromString(visitDateString,"dd/MM/yyyy")); //.addDays(7));
      ui->dateFollowUp->setMinimumDate(QDate::fromString(visitDateString,"dd/MM/yyyy"));
      ui->vDrugsTable->loadPatientDrugsModel(ID,visitDateTime2JulianDate());
      ui->InvestigationsTable->populateInvests(ID,visitDateTime2JulianDate());
      vEditMode = true;
      enableEditMode(vEditMode);
    }
  toggleContollers();
}

void visitsBox::on_ButtonDel_clicked()
{
  if(newVisitCreationInProgress||aboutToClose)
    return;
  newVisitCreationInProgress=true;

  if ( ui->visitLists->count() < 2 )
    {
      msgbox->information(this,"Error","Can't have less than One visit in your Visit List , Sorry");
      newVisitCreationInProgress=false;
      return;
    }
  ui->ButtonDel->setEnabled(false);
  QString ComboCurrentVisit = QString ( ui->visitLists->currentText());
  int reply;
  QString msgText = "This will delete the (  " + ComboCurrentVisit  + "  ) Visit, Are you Sure? , This Can't be undone";
  reply = msgbox->question(this, "Message",msgText,
                           QMessageBox::Yes,QMessageBox::No,true);
  if (reply == QMessageBox::No)
    {
      ui->ButtonDel->setEnabled(true);
      newVisitCreationInProgress=false;
      return;
    }

  QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
  int julianDate = static_cast<int>(locale.toDateTime(ComboCurrentVisit,"dd/MM/yyyy hh:mm AP ddd").date().toJulianDay());

  if(sqlbase->deletePatientVisit(ID,julianDate))
    {
      ui->visitLists->populateWithVisitList(ID);
      emit newMessage("Information","Visit deletion success.");
    }
  else
    {
      emit newMessage("Information","Visit deletion failed.");
    }

  newVisitCreationInProgress=false;
}

void visitsBox::closeEvent(QCloseEvent *event)
{
  if (!visitLoaded)
    event->ignore();

  emit onVisitBoxClose();//this will clear popups and lineedits

  if ( vEditMode && isVisitModified()  )
    {
      if(!alwaysSave)
        {
          int reply = msgbox->question(this, "Message",
                                       "Do you want to save changes?",
                                       QMessageBox::Yes,QMessageBox::No);

          if (reply == QMessageBox::No) {

              autoSaveTimer->stop();
              aboutToClose=true;
              mDialog::closeEvent(event);
            }
        }

      save(grabVisit(),false);
    }
  autoSaveTimer->stop();
  aboutToClose=true;
  mDialog::closeEvent(event);
}

void visitsBox::updateVisitAge()
{

  currentVisitDateTime = ui->visitLists->currentText();
  QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
  QDateTime englishDateTime = locale.toDateTime(currentVisitDateTime, "dd/MM/yyyy hh:mm AP ddd");
  int jdstr = static_cast<int>(englishDateTime.date().toJulianDay());
  int jpAge = pAge.toInt();
  int jvisitAge = jdstr - jpAge;

  if (jvisitAge < 0 )
    jvisitAge = 0;

  visitAge = QString::number(jvisitAge) ;

  printableAge = sqlbase->getAge(visitAge.toInt(),true);

  ui->patientAge->setText(printableAge);
}

void visitsBox::on_buttonAddDrug_clicked()
{
  QString newDrugName = ui->drugLine->text().simplified();
  addNewDrug(newDrugName);

}

void visitsBox::on_buttonRemoveDrug_clicked()
{
  ui->vDrugsTable->removeCurrentSelectedDrugFromList();
  ui->drugLine->clear();
  if ( ui->vDrugsTable->getRowsCount() == 0 )
    {
      ui->buttonRemoveDrug->setEnabled(false);
    }
  emit ui->vDrugsTable->drugTableItemChanged();
}

void visitsBox::on_drugLine_returnPressed()
{
  QString newDrugName = ui->drugLine->text().simplified();
  addNewDrug(newDrugName);
}

void visitsBox::on_buttonAddInvestigations_clicked()
{
  QString newInvestigation = ui->investigationsLine->text().simplified();//.replace(QRegExp("[^A-Za-z\\d\\s]"),"_")  ;
  addNewInvestigation(newInvestigation);
  emit clearInvLine();

}

void visitsBox::on_buttonRemoveInvestigations_clicked()
{
  bool isValid= ui->InvestigationsTable->selectionModel()->currentIndex().isValid();
  bool invTableHasFocus=ui->InvestigationsTable->hasFocus();
  if(!isValid || !invTableHasFocus)
    return;

  int row = ui->InvestigationsTable->selectionModel()->currentIndex().row();
  QString invName = ui->InvestigationsTable->invModel->item(row,1)->text();
  int visitDate = ui->InvestigationsTable->invModel->item(row,2)->text().toInt();
  QString path = ui->InvestigationsTable->invModel->item(row,3)->text();

  sqlbase->deleteInvestigation(ID,visitDate,path,invName);
  ui->InvestigationsTable->populateInvests(ID,visitDate);
  lastInvestigationRow = (row==0)? 0:row-1;
  emit clearInvLine();
}

void visitsBox::on_investigationsLine_returnPressed()
{
  QString newInvestigation = ui->investigationsLine->text().simplified();//.replace(QRegExp("[^A-Za-z\\d\\s]"),"_")  ;
  addNewInvestigation(newInvestigation);
  emit clearInvLine();
}


void visitsBox::save(sqlBase::Visit visit,bool threading)
{
  if ( saving )
    return;
  else
    saving = true;


  visit.visitDateTime = QString ( ui->visitLists->currentText() );

  updateVisitAge();

  if ( visit.visitDateTime == "")
    {
      QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
      QDateTime date = QDateTime::currentDateTime();
      visit.visitDateTime = locale.toString(date, "dd/MM/yyyy hh:mm AP ddd");
      ui->visitLists->addItem(visit.visitDateTime);
      ui->visitLists->setCurrentText(visit.visitDateTime);
    }

  mSave(visit,threading);
}

void visitsBox::on_ButtonVisit_clicked()
{
  if(newVisitCreationInProgress||aboutToClose)
    return;

  newVisitCreationInProgress=true;

  visitindex = ui->comboVisitType->currentIndex();

  QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
  QDateTime datetime = QDateTime::currentDateTime();

  int dtJulian = static_cast<int>(datetime.date().toJulianDay());

  for ( int i = 0 ; i < ui->visitLists->count() ; i++ )
    {
      int visitJ = static_cast<int>(locale.toDateTime(ui->visitLists->itemText(i),"dd/MM/yyyy hh:mm AP ddd").date().toJulianDay());
      if ( visitJ == dtJulian )
        {
          msgbox->information(this,"Message","You Can't Add more than one visit for the same patient within a 24 hours period, Sorry!");
          newVisitCreationInProgress=false;
          return;
        }
    }
  ui->ButtonVisit->setEnabled(false);

//  ui->dateFollowUp->setDate(settings.isRemmberlastFollowupDate()? lastSelectedFollowupDate:QDate::currentDate());
  ui->dateFollowUp->setMinimumDate(QDate::currentDate());

  sqlBase::Visit visit = grabVisit();

  if ( dtJulian != visit.followDate.toInt())
    {
      int reply = msgbox->question(this,"Warning","<center>You are creating a new follow up visit in a date that differs from the squeduled date in last visit, do you want to set today as the follow up date for the last visit? ( <b>yes</b> or <b>No</b>) \n <b> Note: THIS CANNOT BE UNDONE!</b></center>",QMessageBox::Yes,QMessageBox::No,QMessageBox::Cancel);
      if ( reply == QMessageBox::Yes)
        {
          sqlbase->setFollowDate(visit.ID,visit.visitDateTime,dtJulian);
        }
      else if (reply == QMessageBox::Cancel)
        {
          ui->ButtonVisit->setEnabled(true);
          newVisitCreationInProgress=false;
          return;
        }
    }

  if (vEditMode)
    save(visit,false);

  if ( visitindex < maxFollows )
    visitindex +=1;
  else if ( visitindex == maxFollows && autoSetNewAfterMaxFollow)
    visitindex = 0;


  double visitPrice = settings.getVisitPrice(visitindex);
  ui->comboVisitType->setCurrentIndex(visitindex);

  sqlbase->createNewVisit(ID,
                          visit.visitDateTime,
                          datetime,
                          visitindex,
                          visitPrice,
                          lastSelectedFollowupDate,
                          ui->vDrugsTable->getDrugsModel(),
                          ui->InvestigationsTable->getInvestigationsModel(),
                          sqlextra);
  ui->visitLists->clear();
  ui->visitLists->populateWithVisitList(ID);
  updateVisitAge();
  emit newMessage("Information","A New follow up visit was Created");
  newVisitCreationInProgress=false;

}


void visitsBox::on_CheckButtonCaseClose_toggled(bool checked)
{
  ui->dateFollowUp->setDisabled(checked);
  ui->ButtonVisit->setDisabled((ui->visitLists->currentIndex() == 0)? checked:false);
}

void visitsBox::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_Escape && visitLoaded)
    {
      close();
    }
  else if ( e->key() == Qt::Key_F6)
    {
      setWindowOpacity(double(0));
      emit toggleBlur(true);
    }
  else if ( !visitLoaded )
    {
      e->ignore();
    }
  mDialog::keyPressEvent(e);
}

void visitsBox::keyReleaseEvent(QKeyEvent *e)
{
  if ( (e->key() == Qt::Key_F6) && !e->isAutoRepeat())
    {
      setWindowOpacity(double(1));
      emit toggleBlur(false);
    }
  else
    {
      QWidget::keyPressEvent(e);
    }
}

visitsBox::~visitsBox()
{
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

void visitsBox::grabSave()
{
  if(isVisitModified() && vEditMode)
    save(grabVisit(),true);
}

void visitsBox::onDrugLoadCompleted()
{
  if(!visitLoaded)
    emit loadCompleters();
  initializeAutoSave();
  toggleSyncPrintButtons();
  drugLoadCompleted = true;
  visitLoaded = true;
}

void visitsBox::add2RoshettaAutoComplete(QString w)
{
  sqlextra->addToAutoComplete("dictionary",w);
}

void visitsBox::popUpMessage(QString title, QString message)
{
  emit newMessage(title,message);
}

void visitsBox::isCompleterPopupVisible(bool v)
{
  mLineEditPopUpVisible = v;
}

void visitsBox::removeItemFromCompleter(QString item, QString table)
{
  sqlextra->removeFromAutoComplete(table,item);
}

void visitsBox::removeItemFromDictionary(QString item, int row)
{
  sqlextra->removeFromAutoComplete("dictionary",item);
  emit removeFromCompleter(row);
}

void visitsBox::finishedSavingVisit(bool state)
{
  QString msg = state? "Visit Data was Saved Successfuly":"Sorry, Visit Data was NOT Saved";
  emit newMessage("Information",msg);
  saving=false;
  autoSaveTimer->start();
}

void visitsBox::navButtonsLeftClicked()
{
  if(ui->InvestigationsTable->isWorking() || ui->vDrugsTable->isWorking())
    return;

  QString mCaller = sender()->objectName();
  if ( mCaller == "nexVisit")
    goNextVisit();
  else if ( mCaller == "preVisit")
    goPreviousVisit();
}

void visitsBox::navButtonsRightClicked()
{
  if(ui->InvestigationsTable->isWorking() || ui->vDrugsTable->isWorking())
    return;
  QString mCaller = sender()->objectName();
  if (mCaller == "nexVisit")
    goLastVisit();
  else if (mCaller == "preVisit")
    goFirstVisit();
}

mSettings::defaultFont visitsBox::getDefaultFont()
{
  return settings.getDefaultFont();
}

bool visitsBox::isCompleteByWord()
{
  return settings.isAutoCompleteByWord();
}

void visitsBox::on_toolButtonRefresh_clicked()
{
  if(aboutToClose)
    return;

  int reply = msgbox->question(this,"Confirm patient visit reloading",
                               "Are you sure that you want to reload visit data from disk? "
                               "This can not be undone",QMessageBox::Yes,QMessageBox::No,true);
  if(reply==QMessageBox::No)
    return;

  fillVisit(sqlbase->getPatientVisitData(ID,comboSelectedDataTime));
  emit newMessage("Information","Visit data was reloaded");
}

void visitsBox::toggleEditMode()
{

  if ( vEditMode &&  alwaysSave )
    {
      vEditMode = mSave(grabVisit(),false)? !vEditMode:vEditMode;
      enableEditMode(vEditMode);
      return;

    }
  else if ( vEditMode )
    {
      int reply;
      reply = msgbox->question(this, "Message",
                               "Do you want to save changes?",
                               QMessageBox::Yes,QMessageBox::No);
      if (reply == QMessageBox::No) {
          vEditMode = !vEditMode;
          enableEditMode(vEditMode);
          return;

        }
      else
        {
          vEditMode = mSave(grabVisit(),false)? !vEditMode:vEditMode;
          enableEditMode(vEditMode);
          return;
        }
    }
  vEditMode = !vEditMode;
  enableEditMode(vEditMode);
  return;
}

void visitsBox::enableEditMode(bool vEditMode)
{
  ui->buttonAddInvestigations->setEnabled(ui->investigationsLine->text().isEmpty()? false:vEditMode);
  ui->buttonAddDrug->setEnabled(ui->drugLine->text().isEmpty()? false:vEditMode);
  ui->buttonRemoveInvestigations->setEnabled((ui->InvestigationsTable->getSelectedRows() > 0)? vEditMode:false);
  ui->buttonRemoveDrug->setEnabled(( ui->vDrugsTable->getSelectedRows() > 0)? vEditMode:false);
  ui->lmpDate->setReadOnly(!vEditMode);
  ui->comboVisitType->setEnabled(vEditMode);
  ui->toolButtonRefresh->setEnabled(vEditMode);
  ui->dateFollowUp->setEnabled(( ! dataHelper::str2bool(loadedVisit.checkButtonCaseClose) )? vEditMode:false);
  ui->lockUnlockButton->setIcon(QIcon(vEditMode? ":/Graphics/unlock":":/Graphics/lock"));
  emit setReadWrite(vEditMode);
}

bool sortDrugsStar(const QString &s1,const QString &s2)
{
  return s1.endsWith("*") < s2.endsWith("*");
}


void visitsBox::on_buttonInvest_clicked()
{
  invesList *invList = new invesList(this,ID);
  invList->toggleVisualEffects(settings.isVisualEffectsEnabled());
  invList->exec();
  delete invList;
}

void visitsBox::autosave()
{
  if ( ! saving && vEditMode && isVisitModified())
    {
      mSave(grabVisit(),false);
      if ( !mLineEditPopUpVisible )
        emit newMessage("autosave","Visit Data was Saved to disk");
    }
}

void visitsBox::on_investigationsLine_textChanged(const QString &arg1)
{
  if ( arg1.length() == 0 )
    ui->buttonAddInvestigations->setEnabled(false);
  else
    ui->buttonAddInvestigations->setEnabled(vEditMode);
}


void visitsBox::on_drugLine_textChanged(const QString &arg1)
{
  if ( arg1.length() == 0 )
    ui->buttonAddDrug->setEnabled(false);
  else
    ui->buttonAddDrug->setEnabled(vEditMode);
}

void visitsBox::SyncToPatient(bool sync)
{ 
  int reply = msgbox->question(this,"Confirm Drugs %1",QString(
                                 "Are you sure that you want to %1 %2")
                               .arg(sync? "Sync this visit prescripton to Patient drugs list? ":
                                          "Replace patients drugs with this visit drugs.")
                               .arg(sync? "Sync will update only and will not replace drugs. ":
                                          "<b>This can not be undone</b>"),
                               QMessageBox::Yes,
                               QMessageBox::No);
  if(reply==QMessageBox::No)
    return;


  int row = ui->vDrugsTable->getRowsCount();
  if ( row == 0)
    {
      emit newMessage("Warning",QString("No available Drugs to %1").arg(sync? "Sync.":"Replace."));
      return;
    }

  QList<QStringList> array;
  QStringList list;
  for ( int r =0 ; r < row ; r++)
    {
      for ( int c = 0 ; c < 8 ; c++)
        {
          list << ui->vDrugsTable->getDrugsModel()->item(r,c)->text().simplified();
        }
      array.append(list);
      list.clear();

    }
  emit syncDrugs(array,sync);
}

void visitsBox::SyncToVisit()
{
  int reply = msgbox->question(this,"Confirm Drugs sync",
                               "Are you sure that you want to copy patient current drugs to this visit?",
                               QMessageBox::Yes,QMessageBox::No);
  if(reply==QMessageBox::No)
    return;

  int vRow = ui->vDrugsTable->getRowsCount();


  if ( vRow != 0 )
    {
      emit newMessage("Warning","Visit drugs list should be empty prior filling from current patient drugs.");
      return;
    }

  //int pRow = getDrugsCountForVists(ID,0);//sqlbase->readDrugs(ID,0,ui->vDrugsTable->getDrugsModel())->rowCount();

  if ( !doeshaveDrugsInPatient())
    {
      emit newMessage("Warning","No drugs to copy from patients record to this visit.");
      return;
    }

  ui->vDrugsTable->loadPatientDrugsModel(ID,0,true);
}

void visitsBox::SyncLastVisit()
{

  int reply = msgbox->question(this,"Confirm Drugs sync",
                               "Are you sure that you want to copy last visit drugs to this visit? ",
                               QMessageBox::Yes,QMessageBox::No);
  if(reply==QMessageBox::No)
    return;

  int vCount = ui->visitLists->count();
  int row = ui->vDrugsTable->getRowsCount();
  int idx = ui->visitLists->currentIndex();

  QString visitDateTime =   ui->visitLists->itemText(idx+1).simplified();
  QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
  QDateTime dt = locale.toDateTime(visitDateTime,"dd/MM/yyyy hh:mm AP ddd");
  int date = static_cast<int>(dt.date().toJulianDay());

  if (!doesHaveDrugsInLastVisit())
    {
      emit newMessage("Warning","No Drugs Found in last visit.");
      return;
    }


  if ( ( row != 0 ) || !( idx < vCount ) )
    {
      emit newMessage("Warning","Visit drugs list should be empty prior filling from last visit drugs.");
      return;
    }
  ui->vDrugsTable->loadPatientDrugsModel(ID,date,true);

}

void visitsBox::on_comboVisitType_currentIndexChanged(int index)
{
  int currentSelectedVisit = ui->visitLists->currentIndex();
  if ( index == 0 )
    ui->visitLists->setItemIcon(currentSelectedVisit,QIcon(":/Graphics/newvisit"));
  else if (index <= maxFollows)
    ui->visitLists->setItemIcon(currentSelectedVisit,QIcon(":/Graphics/fvisit"));
  else if (index > maxFollows)
    ui->visitLists->setItemIcon(currentSelectedVisit,QIcon(":/Graphics/free"));
}

void visitsBox::on_closeButton_clicked()
{
  close();
}

void visitsBox::addNewInvestigation(QString newInvName)
{
  int state = 0;
  double price = 0;
  QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
  int julianDate = static_cast<int>(locale.toDateTime(ui->visitLists->currentText(),"dd/MM/yyyy hh:mm AP ddd").date().toJulianDay());
  QStringList paidServices = sqlextra->getPaidServicesList();
  if ( paidServices.contains(newInvName))
    {
      state = 2;
      price = sqlextra->getPaidServicePrice(newInvName);
    }

  ui->InvestigationsTable->addNewInvest(ID,julianDate,newInvName,state,price);
  emit insertUniqueItem(newInvName,"investigationsLine");
  ui->InvestigationsTable->saveInvestigation(ID,julianDate);
}

void visitsBox::addNewDrug(QString newDrugName)
{
  if(ui->vDrugsTable->addDrug2DrugList(newDrugName))
    {
      newDrugName.remove("*");
      emit insertUniqueItem(newDrugName,"drugLine");
      emit insertDrug2Patient(newDrugName,"drugLine");
      emit clearDrugLine();
    }
}

void visitsBox::mousePressEvent(QMouseEvent *event)
{
  m_nMouseClick_X_Coordinate = event->x();
  m_nMouseClick_Y_Coordinate = event->y();
}
void visitsBox::mouseMoveEvent(QMouseEvent *event)
{
  if ( event->modifiers() == Qt::ControlModifier )
    {
      move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
    }

}

//void visitsBox::wheelEvent(QWheelEvent *event)
//{
//    double delta = event->delta()/120;
//    transparency = transparency + (delta/100);
//    if (transparency > 1.00)
//    {
//        transparency = 1.00;
//    }
//    if ( transparency < 0.40 )
//    {
//        transparency = 0.40;
//    }
//    if ( event->modifiers() == Qt::ControlModifier)
//    {
//        this->setWindowOpacity(transparency);
//        emit toggleBlur((dataHelper::doubleEqual(transparency,0)? true:false));
//    }
//}

int visitsBox::visitDateTime2JulianDate()
{
  QString visitDateTime =  ui->visitLists->currentText().simplified();
  QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
  QDateTime dt = locale.toDateTime(visitDateTime,"dd/MM/yyyy hh:mm AP ddd");
  int julianDate = static_cast<int>(dt.date().toJulianDay());
  return julianDate;
}

QString visitsBox::genRoshettaHTML(mSettings::prescriptionPrintSettings mPrintsettings,QString selectedDiet,int drugsMode )
{
  QString t_unit,drug_b,body,unit,drug,dose,HTML,t_oneColumn,t_twoColumn,
      t_nCompact,expandName,banner,drugsSeparator,expandedname,dose_b;
  QString align = (mPrintsettings.centerRequests)? "style=\"text-align: center;\"":"style=\"text-align: left;\"";


  //int drugsNumber=0;
  QList<DrugsItemModel*> drugsModelList;

  switch (drugsMode) {
    case 0:
      drugsModelList << ui->vDrugsTable->getDrugsModel();
      //drugsNumber = ui->vDrugsTable->getDrugsModel()->rowCount();
      break;
    case 1:
      drugsModelList << getDrugsModel();
      //drugsNumber = getDrugsModel()->rowCount();
      break;
    case 2:
      drugsModelList << ui->vDrugsTable->getDrugsModel();
      drugsModelList << getDrugsModel();
      //drugsNumber = ui->vDrugsTable->getDrugsModel()->rowCount() + getDrugsModel()->rowCount();
      break;
    default:
      return QString();
      //break;
    }

  double pageWidth = (mPrintsettings.pageOrientation == 0)?
        mPrintsettings.pageWidth * static_cast<double>(logicalDpiX()):mPrintsettings.pageHeight * static_cast<double>(logicalDpiX());
  double widthCorrection = mPrintsettings.leftMargin + mPrintsettings.rightMargin;

  pageWidth -= widthCorrection*static_cast<double>(logicalDpiX());

  double invPad = mPrintsettings.invPad * static_cast<double>(logicalDpiX());
  int drugsWidth = static_cast<int>(pageWidth *  static_cast<double>(mPrintsettings.drugsColPerc/ 100));
  int bannerWidth = static_cast<int>(pageWidth *   static_cast<double>((mPrintsettings.bannerWidth/100)));
  int dietWidth = static_cast<int>(mPrintsettings.dietWidth * static_cast<double>(logicalDpiX()));
  int invWidth= static_cast<int>((static_cast<double>(mPrintsettings.investigationsWidth) - 0.2 )* logicalDpiX());

  HTML = QString("<!DOCTYPE HTML style=\"width:%1;\"><html><head><meta name=\"qrichtext\" content=\"1\" /></head>").arg(pageWidth);
  body = QString("<body style=\"font-family:\"%1\"; font-size:%2pt; font-weight:%3;width:%4px;background-color:#FF0000;\">")
      .arg(mPrintsettings.font)
      .arg(mPrintsettings.point)
      .arg(mPrintsettings.bold? "bold":"normal")
      .arg(pageWidth);

  if (mPrintsettings.showBanner)
    {

      QLocale locale(QLocale::English, QLocale::UnitedStates);

      //QString visitDate = locale.toDateTime(comboSelectedDataTime,"dd/MM/yyyy hh:mm AP ddd").date().toString("dd/MM/yyyy");
      QString visitDate = locale.toString(locale.toDateTime(comboSelectedDataTime,"dd/MM/yyyy hh:mm AP ddd").date(),"dd/MM/yyyy");
      QString followDate = (visitDate==ui->dateFollowUp->text())? QString():ui->dateFollowUp->text();

      banner = QString(
            "<table width=\"%1\">"
            "<tr><td colspan=\"3\"><hr/></td></tr>"
            "<tr>"
            "<td width=\"50%\"><b>Name :</b> %2 </td>"
            "<td><b> Age :</b> %3 </td>"
            "<td><b> Code :</b> %4 </td>"
            "</tr>"
            "<tr>"
            "<td width=\"50%\"><b>Diagnosis :</b> %5 </td>"
            "<td><b> Date :</b> %6 </td>"
            "<td><b> Next :</b> %7 </td>"
            "</tr>"
            "<tr><td colspan=\"3\"><hr/></td></tr>"
            "</table>"
            )
          .arg(bannerWidth)
          .arg(pName)
          .arg(printableAge)
          .arg(ID)
          .arg(ui->Diagnosis->text().simplified())
          .arg(visitDate)
          .arg(followDate);

      HTML.append(banner);

    }

  bool isActiveHeaderPrinted=false;
  bool isPrescriptionHeaderPrinted=false;
  bool DrugsFound = false;

  HTML.append(body);
  if (mPrintsettings.showDrugs )
    {
      drug_b = "<b>%1</b>";
      dose_b = "<b>%1</b>";
      t_nCompact = mPrintsettings.compactMode ? "":"<br/>";
      drugsSeparator = mPrintsettings.showDrugsSeparator ? "<hr/>":"";

      t_oneColumn = "<tr valign=\"top\"><td><div align=\"%4\">%1</div><div dir=RTL "
                    "valign =\"%3\" align=\"%5\" >%2</div></td></tr>";
      t_twoColumn = "<tr valign=\"top\"><td><div align=\"%4\" >%1&#160;"+t_nCompact+drugsSeparator+"</div></td><td>"
                                                                                                   "<div dir=RTL valign =\"%3\" align=\"%5\" >&#160;%2</div></td></tr>";

      HTML.append(QString("<table border=\"0\" width=\"%1\" "
                          "style=\"display:inline-block;float:left;table-layout:fixed;\">").arg(drugsWidth));

      t_unit = mPrintsettings.doseinNewLine ? t_oneColumn:t_twoColumn;


      QString doseAlign,drugAlign;
      if ( mPrintsettings.doseinNewLine)
        {
          if( mPrintsettings.centerDrugs)
            doseAlign = drugAlign = "center";
          else
            {
              doseAlign = "left";
              drugAlign = "left";
            }

        }
      else
        {
          if( mPrintsettings.centerDrugs)
            {
              doseAlign = "left";
              drugAlign = "right";
            }
          else
            {
              doseAlign = "right";
              drugAlign = "left";
            }
        }

      QString drugsHeader = "<tr><th style=\"padding:8px;\"%1>"
                            "<div style=\"background-color:LightSteelBlue;\">"
                            "<b>%2</b></div></th></tr>";

      int model_index = 0;
      foreach (DrugsItemModel *drugsModel, drugsModelList)
        {
          for ( int d = 0 ; d < drugsModel->rowCount() ; d++ )
            {
              if ( drugsModel->item(d,5)->text().toInt() == 1)
                {
                  if(!isPrescriptionHeaderPrinted && (drugsMode == 0 || drugsMode == 2 ) && model_index == 0 )
                    {
                      if(mPrintsettings.showDrugsTitle)
                        HTML.append(QString(drugsHeader)
                                    .arg(mPrintsettings.doseinNewLine? "":"colspan=\"2\"")
                                    .arg("PRESCRIPTION"));
                      isPrescriptionHeaderPrinted=true;
                    }
                  else if(!isActiveHeaderPrinted && ( ( drugsMode == 1 && model_index == 0 ) || ( drugsMode == 2 && model_index == 1 ) ) )
                    {
                      if(mPrintsettings.showDrugsTitle)
                        HTML.append(QString(drugsHeader)
                                    .arg(mPrintsettings.doseinNewLine? "":"colspan=\"2\"")
                                    .arg("CURRENT ACTIVE DRUGS"));
                      isActiveHeaderPrinted=true;
                    }

                  expandName = drugsModel->item(d,0)->text();
                  if (sqlextra->isExpandExists(expandName))
                    {
                      dose = mPrintsettings.setEastArabicNumbers ? dataHelper::switchToEasternArabic(drugsModel->item(d,2)->text()):drugsModel->item(d,2)->text();
                      dose.append(t_nCompact+drugsSeparator);
                      expandedname = sqlextra->getExpand(expandName);

                      expandedname.remove(QRegExp("color:#[A-Fa-f0-9]{6};"));
                      expandedname.remove(QRegExp("font-size:[0-9]{0,2}pt;"));
                      expandedname.remove(QRegExp("font-weight:\\d+;"));
                      expandedname.remove(QRegExp("font-family:'\\w+';"));
                      expandedname.remove(QRegExp("font-style:'\\w+';"));

                      unit = QString(t_unit)
                          .arg((mPrintsettings.tradeNameinBold || mPrintsettings.bold )?
                                 QString(drug_b).arg(expandedname):expandedname)
                          .arg(mPrintsettings.bold? QString(dose_b).arg(dose):dose)
                          .arg("bottom")
                          .arg(drugAlign)
                          .arg(doseAlign);
                      HTML.append(unit);
                      DrugsFound = true;
                      continue;
                    }
                  drug = drugsModel->item(d,0)->text();
                  if ( mPrintsettings.noQty )
                    {
                      drug.remove("(IMP)");
                      drug.remove("e/n");
                      drug.remove("e/e");
                      drug.remove(QRegExp("\\d+[(A|ST.|T|C|BX|S|V|CT|NV|P|D|F|L]+\\W+"));
                    }
                  dose = mPrintsettings.setEastArabicNumbers ? dataHelper::switchToEasternArabic(drugsModel->item(d,2)->text()):drugsModel->item(d,2)->text();
                  dose.append(t_nCompact+drugsSeparator);

                  unit = QString(t_unit)
                      .arg((mPrintsettings.tradeNameinBold || mPrintsettings.bold )? QString(drug_b).arg(drug):drug)
                      .arg(mPrintsettings.bold? QString(dose_b).arg(dose):dose)
                      .arg("top")
                      .arg(drugAlign)
                      .arg(doseAlign);

                  DrugsFound = true;
                  HTML.append(unit);
                }
            }
          model_index+=1;
        }
      HTML.append("</table>");

    }
  QStringList investigations = ui->InvestigationsTable->getInvestigationsList();

  int investigations_count = investigations.count();

  if ( !DrugsFound || !mPrintsettings.showDrugs  )
    invPad += drugsWidth;

  if ( mPrintsettings.showInvestigations && investigations_count >0 )
    {

      HTML.append(QString("<table bgcolor=\"Aliceblue\" style=\"display:inline-block;float:left;margin-left:%1px;\">")
                  .arg(invPad));
      HTML.append("<tr><th style=\"padding:3px;\" ><div style=\"background-color:LightSteelBlue;\"><b>REQUESTS</b></div></th></tr>");
      foreach (QString inv, investigations)
        {
          HTML.append(QString("<tr><td  width=\"%4\" ><div %3 %1>&#9679; %2</div></td></tr>")
                      .arg(align)
                      .arg(inv)
                      .arg(mPrintsettings.bold? "style=\"font-weight:bold;\"":"")
                      .arg(invWidth));
        }

      HTML.append("</table>");
    }

  if(selectedDiet!="-")
    {
      HTML.append(QString("<table style=\"display:inline-block;float:left;margin-top:%1px;margin-left:%2px;\">")
                  .arg(mPrintsettings.dietTopPadding*logicalDpiX())
                  .arg(mPrintsettings.dietLeftPadding*logicalDpiX()));
      HTML.append(QString("<tr><td width=\"%1\">").arg(dietWidth));
      HTML.append(QString("<div dir=RTL  align=\"justify\" >%1</div>").arg(sqlextra->getDiet(selectedDiet)));
      HTML.append("</tr></td>");
      HTML.append("</table>");

      HTML.append("</body>");
      HTML.append("</html>");
    }

  return HTML;
}

void visitsBox::followUpDateChanged(const QDate &date)
{
  int selectedDateFollowUps = followNotify(date);
  setFollowDateTooltip(selectedDateFollowUps,date);
  lastSelectedFollowupDate = date;
}

void visitsBox::onShift_pageUp()
{
  goLastVisit();
}

void visitsBox::onShift_pageDown()
{
  goFirstVisit();
}

void visitsBox::selectLastInvRow()
{
  ui->InvestigationsTable->selectRow(lastInvestigationRow);
  bool _s = ui->InvestigationsTable->selectionModel()->currentIndex().isValid();
  ui->buttonRemoveInvestigations->setEnabled(_s);
}

void visitsBox::showCosts(double est,bool percision)
{
  if (percision)
    ui->rxCost->setText(QString("est. Cost = %1 LE.").arg(est));
  else
    ui->rxCost->setText(QString("est. Cost > %1 LE. !").arg(est));
}

void visitsBox::toggleDrugsAlteredStatus(bool b)
{
  drugsAltered = b;
}

int visitsBox::getDrugsCountForVists(int _id,int julianDate)
{
  return sqlbase->getDrugsCout(_id,julianDate);
}

int visitsBox::getPatientsDrugsCount(int _id)
{
  return sqlbase->getDrugsCout(_id,0);
}

bool visitsBox::doesHaveDrugsInLastVisit()
{
  int visit_count = ui->visitLists->count();

  if ( visit_count < 2)
    return false;

  int index = ui->visitLists->currentIndex();
  int last_visit_index = index+1;

  if ( last_visit_index == visit_count )
    return false;

  QString visitDateTime =   ui->visitLists->itemText(last_visit_index).simplified();
  QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
  QDateTime dt = locale.toDateTime(visitDateTime,"dd/MM/yyyy hh:mm AP ddd");
  int date = static_cast<int>(dt.date().toJulianDay());
  return (getDrugsCountForVists(ID,date) > 0);
}

bool visitsBox::doeshaveDrugsInPatient()
{
  return (getPatientsDrugsCount(ID) > 0);
}

void visitsBox::toggleDateFollowup()
{
  if(ui->dateFollowUp->date() == QDate::currentDate())
    ui->dateFollowUp->setDate(lastSelectedFollowupDate);
  else if (ui->dateFollowUp->date() == lastSelectedFollowupDate)
    ui->dateFollowUp->setDate(QDate::currentDate());
  QDate cd = ui->dateFollowUp->date();//currentdate
  int selectedDateFollowUps = followNotify(cd);
  setFollowDateTooltip(selectedDateFollowUps,cd);
}

void visitsBox::connectSignals(QWidget *parent)
{
  connect ( this,SIGNAL(clearInvLine()),ui->investigationsLine,SLOT(clear()),Qt::QueuedConnection);
  connect ( this,SIGNAL(clearDrugLine()),ui->drugLine,SLOT(clear()),Qt::QueuedConnection);
  connect ( ui->vDrugsTable,SIGNAL(clicked(QModelIndex)),this,SLOT(enableRemoveDrugButton()));
  connect ( ui->vDrugsTable,SIGNAL(popUpMessage(QString,QString)),parent,SLOT(popUpMessage(QString,QString)));
  connect ( ui->vDrugsTable,SIGNAL(loadCompleted()),this,SLOT(onDrugLoadCompleted()));
  connect ( ui->vDrugsTable,SIGNAL(drugTableItemChanged()),this,SLOT(toggleSyncPrintButtons()));
  connect ( ui->InvestigationsTable,SIGNAL(togglePrintButton()),this,SLOT(toggleSyncPrintButtons()));
  connect ( ui->InvestigationsTable,SIGNAL(popUpMessage(QString,QString)),parent,SLOT(popUpMessage(QString,QString)));
  connect ( ui->visitLists,SIGNAL(loadCompleted()),this,SLOT(toggleContollers()));
  connect ( ui->visitLists,SIGNAL(saveVisit()),this,SLOT(grabSave()));
  connect ( ui->dateFollowUp->calendarWidget(),SIGNAL(clicked(QDate)),this,SLOT(followUpDateChanged(QDate)));
  connect ( ui->vDrugsTable,SIGNAL(reloadDrugsLineAutoComplete()),ui->drugLine,SLOT(mUpdateCompleter()));
  connect ( this,SIGNAL(updateDrugsCompleter()),ui->drugLine,SIGNAL(updateDrugsCompleter()));
  connect ( autoSaveTimer,SIGNAL(timeout()),this,SLOT(autosave()));
  connect ( shift_pageUp,SIGNAL(activated()),this,SLOT(onShift_pageUp()));
  connect ( shift_pageDown,SIGNAL(activated()),this,SLOT(onShift_pageDown()));
  connect ( printShortcut,SIGNAL(activated()),this,SLOT(on_fastPrint_leftButtonClicked()));
  connect ( printPreviewShortcut,SIGNAL(activated()),print,SLOT(showPrintPreviewDialog()));
  connect ( this,SIGNAL(showPreview()),print,SLOT(showPrintPreviewDialog()));// this is for rt
  connect ( easyPrintShortcut,SIGNAL(activated()),this,SLOT(on_fastPrint_middleButtonClicked()));
  connect ( ui->vDrugsTable,SIGNAL(syncDrugs(QList<QStringList>,bool)),this,SIGNAL(syncDrugs(QList<QStringList>,bool)));
  connect ( ui->InvestigationsTable,SIGNAL(selectLastInvRow()),this,SLOT(selectLastInvRow()) );
  connect ( ui->vDrugsTable,SIGNAL(showRxCost(double,bool)),this,SLOT(showCosts(double,bool)));
  connect ( print,SIGNAL(add2AutoComplete(QString)),this,SLOT(add2RoshettaAutoComplete(QString)));
  connect ( print,SIGNAL(refreshRoshetta(mSettings::prescriptionPrintSettings,QString,int)),this,SLOT(genRoshettaHTML(mSettings::prescriptionPrintSettings,QString,int)));
  connect ( print,SIGNAL(message(QString,QString)),this,SIGNAL(newMessage(QString,QString)));
  connect ( ui->lockUnlockButton,SIGNAL(clicked()),this,SLOT(toggleEditMode()));
  connect ( ui->InvestigationsTable,SIGNAL(toggleRemoveInvButton(bool)),ui->buttonRemoveInvestigations,SLOT(setEnabled(bool)));
  connect ( ui->vDrugsTable,SIGNAL(drugsHasBeenAltered(bool)),this,SLOT(toggleDrugsAlteredStatus(bool)));
  connect ( add2CompleterWorker,SIGNAL(finished()),this,SIGNAL(reloadCompleter()));
  connect ( add2CompleterWorker,SIGNAL(finished()),this,SIGNAL(reloadMWCompleter()));
  connect ( visitSaverWorker,SIGNAL(finishedSavingState(bool)),this,SLOT(finishedSavingVisit(bool)));

  connect ( ui->vDrugsTable,SIGNAL(SyncToVisit()),this,SLOT(SyncToVisit()));
  connect ( ui->vDrugsTable,SIGNAL(SyncToPatient(bool)),this,SLOT(SyncToPatient(bool)));
  connect ( ui->vDrugsTable,SIGNAL(SyncLastVisit()),this,SLOT(SyncLastVisit()));

  connect ( ui->vDrugsTable,SIGNAL(doeshaveDrugsInPatient()),this,SLOT(doeshaveDrugsInPatient()));
  connect ( ui->vDrugsTable,SIGNAL(doesHaveDrugsInLastVisit()),this,SLOT(doesHaveDrugsInLastVisit()));
  connect ( toggleFollowupDate,&QShortcut::activated,this,&visitsBox::toggleDateFollowup);
  connect ( vTypeUp,&QShortcut::activated,ui->comboVisitType,&vTypeComboBox::goUp);
  connect ( vTypeDown,&QShortcut::activated,ui->comboVisitType,&vTypeComboBox::goDown);
}

//void visitsBox::initializeVariables()
//{
//    calWidget = new mCalendarWidget(ui->dateFollowUp);
//    ui->dateFollowUp->setCalendarWidget(calWidget);
//    shift_pageUp  = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_PageUp), this);
//    shift_pageUp->setContext(Qt::WindowShortcut);
//    shift_pageDown = new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_PageDown), this);
//    shift_pageDown->setContext(Qt::WindowShortcut);
//    printShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P),this);
//    easyPrintShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O),this);
//    printPreviewShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I),this);
//}

void visitsBox::addThisToCompleter(sqlBase::Visit visit)
{
  add2CompleterWorker->setVisitData(visit);
  add2CompleterWorker->setMode(autoCompleteByWord);
  QtConcurrent::run(add2CompleterWorker,&wm_add2Completer::vWork);
}

void visitsBox::toggleAntenatal(bool checked)
{
  ui->labelEDD->setVisible(checked);
  ui->eddDate->setVisible(checked);
  ui->checkBoxAntenatal->setText(checked ? "":"Antenatal");
}

void visitsBox::initializeAutoSave()
{
  if (autoSave)
    {
      autoSaveTimer->setInterval(1000*autosaveint);
      if (autoSaveTimer->isActive())
        autoSaveTimer->stop();

      autoSaveTimer->start();
    }
}

bool visitsBox::isVisitModified()
{
  sqlBase::Visit currentVisit = grabVisit();
  return((currentVisit!=loadedVisit)||drugsAltered);
}

void visitsBox::setFollowDateTooltip(const int & selectedDateFollowUps, const QDate &date)
{
  QLocale en_US = QLocale(QLocale::English,QLocale::UnitedStates);
  QString day = en_US.toString(date,"dddd dd/MM/yyyy");
  ui->dateFollowUp->setToolTip(QString("%1 has currently %2/%3 patients.").arg(day).arg(selectedDateFollowUps).arg(maxFollowUps));
}

void visitsBox::goSaveVisit(int index)
{
  if ( vEditMode && isVisitModified())
    {
      save(grabVisit(),false);
      emit newMessage("Information","Visit Data was Saved");
    }
  ui->visitLists->setCurrentIndex(index);
}

void visitsBox::goFirstVisit()
{
  int visits_count =  ui->visitLists->count();
  int currentIndex = visits_count-1;
  goSaveVisit(currentIndex);
}

void visitsBox::goLastVisit()
{
  goSaveVisit(0);
}

void visitsBox::goPreviousVisit()
{
  int currentIndex = ui->visitLists->currentIndex();
  int visits_count =  ui->visitLists->count();
  if ( (currentIndex < visits_count) && (visits_count!=1))
    currentIndex++;
  goSaveVisit(currentIndex);
}

void visitsBox::goNextVisit()
{
  int currentIndex = ui->visitLists->currentIndex();
  int visits_count =  ui->visitLists->count();
  if ( (currentIndex > 0) && (visits_count!=1))
    currentIndex--;
  goSaveVisit(currentIndex);
}

int visitsBox::followNotify(const QDate &date)
{
  QLocale en_US = QLocale(QLocale::English,QLocale::UnitedStates);

  int selectedDateFollowUps = sqlbase->getFollowUpsCountForThisDate(date,ID)+1;
  if ( selectedDateFollowUps > maxFollowUps && maxFollowUps > 0)
    {
      newMessage("Message",
                 QString("Warning, Follow up limit exceeded for (%1) , current : %2, limit : %3")
                 .arg(en_US.toString(date,"dd/MM/yyyy"))
                 .arg(selectedDateFollowUps)
                 .arg(maxFollowUps));
    }
  else if ( maxFollowUps > 0)
    {
      newMessage("Message",
                 QString("The date (%1) currently has %2/%3 follow ups")
                 .arg(en_US.toString(date,"dd/MM/yyyy"))
                 .arg(selectedDateFollowUps)
                 .arg(maxFollowUps));
    }
  return  selectedDateFollowUps;
}

bool visitsBox::mSave(sqlBase::Visit visit,bool threading)
{
  saving = true;

  if(isVisitModified())
    addThisToCompleter(visit);

  if ( ui->visitLists->currentIndex() == 0 )
    emit syncLMPDateWithPatients(ui->lmpDate->date());

  sqlBase::visitData visitData;
  visitData.ID =  ID;
  visitData.visit = visit;
  visitData.visitDateTime = visit.visitDateTime;
  visitData.visitDate = visitDateTime2JulianDate();
  visitData.drugsModel = ui->vDrugsTable->getDrugsModel();
  visitData.invModel = ui->InvestigationsTable->getInvestigationsModel();
  visitData.visitPrice = settings.getVisitPrice(visit.visitType.toInt());
  if (threading)
    {
      visitSaverWorker->setVisitData(visitData);
      QtConcurrent::run(visitSaverWorker,&wm_visitSaver::Work);
      return true;
    }
  else
    {
      bool b = sqlbase->saveVisitData(visitData);
      saving = false;
      return b;
    }

}
void visitsBox::toggleSyncPrintButtons()
{
  //    bool isThereActiveDrug = (ui->vDrugsTable->isThereActiveDrugs() || getDrugsModel()->isThereActiveDrugs()  );
  //    bool isTherePrintableInvestigations = ui->InvestigationsTable->printableInvestigationsExists();
  //    ui->fastPrint->setEnabled((isThereActiveDrug || isTherePrintableInvestigations));
  //    //mDebug() << isThereActiveDrug << isTherePrintableInvestigations;
  ui->buttonRemoveInvestigations->setEnabled( vEditMode && ui->InvestigationsTable->getSelectedRows() != -1 );
  ui->buttonRemoveDrug->setEnabled(vEditMode && ui->vDrugsTable->selectionModel()->hasSelection());
}

void visitsBox::setPatient(int id, QString Age, QString Name, QString fpal)
{
  aboutToClose = false;
  vEditMode = true;
  visitLoaded = false;
  ui->visitLists->clear();
  clearVisit();
  emit styleVitals(settings);
  pAge = Age;
  pName = Name;
  FPAL = fpal;
  ID = id;
  ui->patientName->setText(pName);
  ui->fpal->setText(FPAL);

  ui->InvestigationsTable->setPatientID(ID);
  ui->visitLists->populateWithVisitList(ID);
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


void visitsBox::on_fastPrint_leftButtonClicked()
{
  if (!drugLoadCompleted)
    return;
  print->loadDiets(sqlextra->getDietList());
  print->show();
}

void visitsBox::on_fastPrint_rightButtonClicked()
{
  if (!drugLoadCompleted)
    return;
  print->showPrintPreviewDialog();
}

void visitsBox::on_fastPrint_middleButtonClicked()
{
  if (!drugLoadCompleted)
    return;
  print->mPrint();
}

void visitsBox::enableRemoveDrugButton()
{
  ui->buttonRemoveDrug->setEnabled(vEditMode);
}


void visitsBox::on_InvestigationsTable_clicked(const QModelIndex )
{
  ui->buttonRemoveInvestigations->setEnabled(vEditMode && (ui->InvestigationsTable->getSelectedRows() != -1 ));
}

void visitsBox::on_lmpDate_userDateChanged(const QDate &date)
{
  ui->eddDate->setDate(QDate::fromJulianDay(date.toJulianDay()+280));
}

void visitsBox::on_lineEditWeight_textChanged(const QString &arg1)
{
  ui->obstWeight->setText(arg1);
}

void visitsBox::on_obstWeight_textChanged(const QString &arg1)
{
  ui->lineEditWeight->setText(arg1);
}

void visitsBox::on_checkBoxAntenatal_clicked(bool checked)
{
  toggleAntenatal(checked);
}

void visitsBox::toggleContollers()
{
  int visits_count =  ui->visitLists->count();
  int currentIndex = ui->visitLists->currentIndex();
  bool enableSave = (visits_count>0);
  bool enableDelete = ((visits_count>1) && (currentIndex < visits_count-1));
  bool enableFollows = currentIndex == 0 && !ui->CheckButtonCaseClose->isChecked() ;
  bool previusVisitFound = ((currentIndex < visits_count-1) && (visits_count!=1));
  bool nextVisitFound = ((currentIndex > 0) && (visits_count!=1));
  ui->ButtonVisit->setEnabled(enableFollows);
  ui->ButtonSave->setEnabled(enableSave);
  ui->ButtonDel->setEnabled(enableDelete);
  ui->nexVisit->setEnabled(nextVisitFound);
  ui->preVisit->setEnabled(previusVisitFound);
}
