// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "inviconhelper.h"

invIconHelper::invIconHelper(QObject *parent) : QObject(parent) {}

QString invIconHelper::getInvestigationTooltip(const QString &path,
                                               const QString &name,
                                               const int &scale) {
  if (path.endsWith(".jpg", Qt::CaseInsensitive) ||
      path.endsWith(".jpeg", Qt::CaseInsensitive) ||
      path.endsWith(".png", Qt::CaseInsensitive)) {
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    QImageReader imageReader;
    imageReader.setFileName(path);
    imageReader.setAutoTransform(true);
    QImage image = imageReader.read();
    image.scaled(scale, scale, Qt::KeepAspectRatio, Qt::FastTransformation)
        .save(&buffer, "PNG");
    QString iconBase64 = QString::fromLatin1(byteArray.toBase64().data());
    buffer.close();
    return QString(
               "<center>"
               "<b>%1</b><br/>"
               "<img src='data:image/png;base64, %2'><br/>"
               "<i>Double click to open file.</i>"
               "</center>")
        .arg(name)
        .arg(QString(iconBase64));
  }
  return name;
}

int invIconHelper::getScale() {
  // QRect rec = qApp->topLevelWindows().at(0)->screen()->geometry();
  QRect rec = qApp->primaryScreen()->geometry();
  int height = rec.height();
  return height / 3;
}
