// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "wm_texteditcompleterloader.h"

wm_texteditCompleterLoader::wm_texteditCompleterLoader(QObject *parent)
    : QObject(parent),
      connectionName(
          QString("qt_sql_extra_%1_%2_%3")
              .arg(QString("dictionary"),
                   QString::number(
                       QRandomGenerator::global()->bounded(0, 9999999)),
                   QString::number(
                       QTime::currentTime().msecsSinceStartOfDay()))),
      sqlextra(new sqlExtra(this, connectionName, false)) {}

wm_texteditCompleterLoader::~wm_texteditCompleterLoader() {
  sqlextra->optimize();
  delete sqlextra;
  QSqlDatabase::removeDatabase(connectionName);
}

QStringList wm_texteditCompleterLoader::work() {
  return sqlextra->getAutoCompleteList(QString("dictionary"));
}
