#ifndef WM_TEXTEDITCOMPLETERLOADER_H
#define WM_TEXTEDITCOMPLETERLOADER_H

#include <QObject>
#include "sqlextra.h"
#include <QRandomGenerator>
class wm_texteditCompleterLoader : public QObject
{
    Q_OBJECT
public:
    explicit wm_texteditCompleterLoader(QObject *parent = nullptr);
    ~wm_texteditCompleterLoader();

signals:

public slots:
    QStringList work();
private:
    sqlExtra *sqlextra;
    QString connectionName;
    QRandomGenerator generator;
};

#endif // WM_TEXTEDITCOMPLETERLOADER_H
