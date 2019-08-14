#ifndef MSURGICALNOTES_H
#define MSURGICALNOTES_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include "sqlbase.h"

class mSurgicalNotes : public QTableView
{
    Q_OBJECT

public:
    explicit mSurgicalNotes(QWidget *);
    void fillTable(int ID);
    ~mSurgicalNotes();
    QStandardItemModel *model;
    sqlBase *sqlbase;

signals:
    void disableDeleteEditButton();
};

#endif // MSURGICALNOTES_H
