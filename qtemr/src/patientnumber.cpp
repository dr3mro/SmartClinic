// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "patientnumber.h"

patientNumber::patientNumber(QWidget *parent) : QLCDNumber(parent) {
  setDigitCount(5);
}

void patientNumber::setMax(int max) { maxValue = max; }

void patientNumber::display(int value) {
  QString lcdID = QString("%1").arg(value, 5, 10, QLatin1Char('0'));
  toggleButtons(value);
  QLCDNumber::display(lcdID);
}

void patientNumber::display(const QString &str) {
  // int value = str.toInt();
  // toggleButtons(value);
  QLCDNumber::display(str);
}

void patientNumber::toggleButtons(const int &value) {
  if (value == 1) {
    emit enableGoLower(false);
    emit enableGoHigher(true);

  } else if (value >= maxValue) {
    emit enableGoLower(true);
    emit enableGoHigher(false);
  } else  // if ( value > 1 && value < maxValue)
  {
    emit enableGoLower(true);
    emit enableGoHigher(true);
  }
  if (maxValue <= 1) {
    enableGoHigher(false);
    enableGoLower(false);
  }
}
