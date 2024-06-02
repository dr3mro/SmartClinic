// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "emptyprofiles.h"

#include "ui_emptyprofiles.h"

EmptyProfiles::EmptyProfiles(QWidget *parent)
    : mDialog(parent), ui(new Ui::EmptyProfiles) {
  ui->setupUi(this);
  sqlbase = new sqlBase(this, "qt_sql_base_profileGenerator", false);
  this->setWindowTitle("Empty Records Generator");
  startPatientID = sqlbase->getPatientIndexLength();
  ui->spinBox->setMinimum(startPatientID);
  ui->progressBar->setAlignment(Qt::AlignCenter);
  connect(sqlbase, SIGNAL(emptyProfileProgressbar(int, int)), this,
          SLOT(progressBarWorker(int, int)));
  connect(this, SIGNAL(killLoop()), sqlbase, SLOT(killLoopFlag()));
  this->setStyleSheet(settings.themeMaker());
  setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

EmptyProfiles::~EmptyProfiles() {
  sqlbase->optimize();
  delete sqlbase;
  QSqlDatabase::removeDatabase("qt_sql_base_profileGenerator");
  if (isEmptyRecordsCreated) {
    emit loadPatient(startPatientID);
    emit toggleEditMode(false);
    emit updatePList();
  }
  delete ui;
}

void EmptyProfiles::on_buttonOk_clicked() {
  MinPatients = sqlbase->getPatientIndexLength();
  MaxPatients = ui->spinBox->value();
  killLoopFlag_ = false;
  isEmptyRecordsCreated = sqlbase->createEmptyPatientProfiles(MaxPatients);
  ui->spinBox->setMinimum(MaxPatients + 1);
  ui->buttonOk->setEnabled(true);
  ui->buttonClose->setText("Close");
}

void EmptyProfiles::on_checkBox_toggled(bool checked) {
  ui->buttonOk->setEnabled(checked);
}

void EmptyProfiles::on_buttonClose_clicked()

{
  close();
}

void EmptyProfiles::closeEvent(QCloseEvent *e) {
  emit killLoop();
  mDialog::closeEvent(e);
}

void EmptyProfiles::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape)
    close();
  else
    QWidget::keyPressEvent(e);
}

void EmptyProfiles::on_closeButton_clicked() { this->close(); }

void EmptyProfiles::progressBarWorker(int a, int b) {
  ui->progressBar->setValue(a * 100 / b);
}
