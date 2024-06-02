// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "investmodel.h"

InvestModel::InvestModel(QObject *parent) : QStandardItemModel(parent) {
  // mDebug() << "InvObject Created" << this;
}

QVector<QVector<QString> > InvestModel::getMediaVector() {
  int rows = rowCount();
  int state;
  QString mediaURL, title;
  QVector<QString> titles;
  QVector<QString> urls;
  QVector<QVector<QString> > vector;
  // QStringList mediaList;

  for (int row = 0; row < rows; row++) {
    state = item(row, 6)->text().toInt();
    mediaURL = item(row, 3)->text();
    title = item(row, 1)->text();
    if ((state == InvestModel::InvestigationsStates::hasMedia ||
         state == InvestModel::InvestigationsStates::PrintableWithMedia) ||
        mediaURL.length() > 8) {
      titles.append(title);
      urls.append(mediaURL);
    }
  }
  vector.append(titles);
  vector.append(urls);
  return vector;
}

void InvestModel::clear() {
  emit modelAboutToBeClear();
  QStandardItemModel::clear();
}

InvestModel::~InvestModel() {
  // mDebug() << "InvObject Deleted" << this;
}
