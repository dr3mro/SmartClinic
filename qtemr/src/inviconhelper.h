// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef INVICONHELPER_H
#define INVICONHELPER_H

#include <QApplication>
#include <QBuffer>
#include <QImage>
#include <QImageReader>
#include <QObject>
#include <QPixmap>
#include <QRect>
#include <QScreen>

#include "mdebug.h"

class invIconHelper : public QObject {
  Q_OBJECT
 public:
  explicit invIconHelper(QObject *parent = nullptr);
  static QString getInvestigationTooltip(const QString &path,
                                         const QString &name, const int &scale);
  static int getScale();
 signals:

 private:
 public slots:
};

#endif  // INVICONHELPER_H
