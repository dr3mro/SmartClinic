// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef WM_COMPLETERLOADER_H
#define WM_COMPLETERLOADER_H

#include <QObject>
#include <QRandomGenerator>

#include "sqlbase.h"
#include "sqlextra.h"

class wm_CompleterLoader : public QObject {
  Q_OBJECT
 public:
  explicit wm_CompleterLoader(QObject *parent = 0);
  void setTable(QString table);

 public slots:
  QStringList Work();

 signals:

 private:
  int r;
  QString tableName;
  sqlExtra *sqlextra = nullptr;
  QString connectionName;
};

#endif  // WM_COMPLETERLOADER_H
