// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef PSSPINBOX_H
#define PSSPINBOX_H

#include <QObject>
#include <QSpinBox>
#include <QWidget>

class psSpinBox : public QSpinBox {
  Q_OBJECT
 public:
  explicit psSpinBox(QWidget* parent = nullptr);
 private slots:
  void onValueChanged();
 signals:
  void refreshView();
};

#endif  // PSSPINBOX_H
