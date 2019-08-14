#ifndef SQUEEZE_H
#define SQUEEZE_H

#include <QObject>
#include "dataiohelper.h"
class squeeze : public QObject
{
    Q_OBJECT
public:
    explicit squeeze(QObject *parent = nullptr);
    static void compact (QString filename , QString zipfilename);
    static void expand (QString zipfilename , QString filename);

signals:

public slots:

};

#endif // SQUEEZE_H
