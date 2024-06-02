// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef SQUEEZE_H
#define SQUEEZE_H

#include <QObject>

#include "dataiohelper.h"
class squeeze : public QObject {
  Q_OBJECT
 public:
  explicit squeeze(QObject *parent = nullptr);
  static void compact(QString filename, QString zipfilename);
  static void expand(QString zipfilename, QString filename);

 signals:

 public slots:
};

#endif  // SQUEEZE_H
