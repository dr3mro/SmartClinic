// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef GETINVESTIGATIONNAME_H
#define GETINVESTIGATIONNAME_H

#include <QDialog>
#include <QFileDialog>
#include <QStandardPaths>

#include "dataiohelper.h"
#include "mdialog.h"
// #include <QObject>
#include <QAction>

namespace Ui {
class getInvestigationName;
}

class getInvestigationName : public mDialog {
  Q_OBJECT

 public:
  explicit getInvestigationName(QWidget *parent = nullptr);
  int exec();
  ~getInvestigationName();

 public slots:
  void show();

 private slots:
  void on_closeButton_clicked();
  void setPath();
  void close();
  void on_OK_clicked();
  void on_Close_clicked();
  void on_Name_textChanged(const QString &arg1);
  void on_Path_textChanged(const QString &arg1);

 private:
  Ui::getInvestigationName *ui;

 signals:
  void investigationAccepted(QString Name, QString Path);
  void popUpMessage(QString title, QString msg);
  void hideParentWindow();
  void showParentWindow();
};

#endif  // GETINVESTIGATIONNAME_H
