#ifndef INVICONHELPER_H
#define INVICONHELPER_H

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QBuffer>
#include <QImageReader>
#include <QDesktopWidget>
#include <QRect>
#include <QApplication>
#include "mdebug.h"

class invIconHelper : public QObject
{
    Q_OBJECT
public:
    explicit invIconHelper(QObject *parent = nullptr);
    static QString getInvestigationTooltip(QString &path, QString &name, int &scale);
    static int getScale();
signals:

private:

public slots:
};

#endif // INVICONHELPER_H
