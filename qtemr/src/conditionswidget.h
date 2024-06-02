// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef CONDITIONSWIDGET_H
#define CONDITIONSWIDGET_H

#include <QGridLayout>
#include <QList>
#include <QObject>
#include <QWidget>

#include "mcheckbox.h"
#include "sqlbase.h"

class conditionsWidget : public QWidget {
  Q_OBJECT
 public:
  explicit conditionsWidget(QWidget *parent = nullptr);
  void fillConditions(const int &_ID);
  void clear();
  QList<QPair<QString, int> > getConditionsState();
  bool isConditionsModified();
  void setID(int id);
  bool editMode = true;
  ~conditionsWidget();
 signals:

 public slots:
  void load();
  void reload();

 private:
  void loadCheckboxes();
  void setConditionsCount();
  void setConditions();

  int ID;
  int conditionsCount = 0;
  int columns = 5;
  int rows;

  QList<QPair<int, QString> > conditions;
  QList<mCheckBox *> cbList;
  QList<mCheckBox *> getCheckboxList();
  sqlBase *sqlbase;
  QGridLayout layout;
};

#endif  // CONDITIONSWIDGET_H
