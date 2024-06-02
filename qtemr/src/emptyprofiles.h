// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef EMPTYPROFILES_H
#define EMPTYPROFILES_H

#include <QCloseEvent>
#include <QDialog>
#include <QTimer>

#include "dataiohelper.h"
#include "mdialog.h"
#include "msettings.h"
#include "sqlbase.h"

namespace Ui {
class EmptyProfiles;
}

class EmptyProfiles : public mDialog {
  Q_OBJECT
  bool killLoopFlag_;
  int MaxPatients;
  int MinPatients;
  sqlBase *sqlbase;

 public:
  explicit EmptyProfiles(QWidget *parent = nullptr);
  ~EmptyProfiles();

 private slots:
  void on_buttonOk_clicked();
  void on_checkBox_toggled(bool checked);
  void on_buttonClose_clicked();
  void keyPressEvent(QKeyEvent *e);
  void on_closeButton_clicked();
  void progressBarWorker(int a, int b);

 signals:
  void updatePList();
  void killLoop();
  void loadPatient(int);
  void toggleEditMode(bool);

 private:
  Ui::EmptyProfiles *ui;
  bool isEmptyRecordsCreated = false;
  int startPatientID = 1;
  mSettings &settings = mSettings::instance();

 protected:
  void closeEvent(QCloseEvent *e) override;
};

#endif  // EMPTYPROFILES_H
