// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef WM_TEXTEDITCOMPLETERLOADER_H
#define WM_TEXTEDITCOMPLETERLOADER_H

#include <QObject>
#include "sqlextra.h"

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
    
};

#endif // WM_TEXTEDITCOMPLETERLOADER_H
