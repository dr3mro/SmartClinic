#ifndef WM_COMPLETERLOADER_H
#define WM_COMPLETERLOADER_H

#include <QObject>
#include "sqlbase.h"
#include "sqlextra.h"
#include <QRandomGenerator>
class wm_CompleterLoader : public QObject
{
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
    sqlExtra *sqlextra=nullptr;
    QString connectionName;
    QRandomGenerator generator;
};

#endif // WM_COMPLETERLOADER_H
