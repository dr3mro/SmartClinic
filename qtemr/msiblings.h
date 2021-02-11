// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MSIBLINGS_H
#define MSIBLINGS_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QList>

#include <sqlbase.h>

class mSiblings : public QTableView
{
     Q_OBJECT
public:
    explicit mSiblings(QWidget *);
    void clear();
    void removeRow(int row);
    bool save(int ID);
    bool populateSiblings(int ID);
    void tweakCoulmnSize();
    QString calculateFPAL();
    QString calculateGPA();
    int getRowCount();
    int getSelectedRow();
    sqlBase::Sibling getSelectedRowContent();
    QStandardItemModel *getModel();
    ~mSiblings();

public slots:
    void appendRow(const sqlBase::Sibling &sibling);
    void editRow(int row,sqlBase::Sibling sibling);
private:
    QStandardItemModel *model;
    sqlBase *sqlbase;

};

#endif // MSIBLINGS_H
