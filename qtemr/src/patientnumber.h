// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef PATIENTNUMBER_H
#define PATIENTNUMBER_H

#include <QLCDNumber>
#include <QObject>

class patientNumber : public QLCDNumber {
  Q_OBJECT
 public:
  explicit patientNumber(QWidget *parent = nullptr);
  void setMax(int max);

 public slots:
  void display(int value);
  void display(const QString &str);

 private:
  int maxValue;
  void toggleButtons(const int &value);

 signals:
  void enableGoLower(bool);
  void enableGoHigher(bool);
};

#endif  // PATIENTNUMBER_H
