// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef GENERICLINEEDIT_H
#define GENERICLINEEDIT_H

#include <QObject>
#include "mlineedit.h"
#include "wm_completerloader.h"

class genericLineEdit : public mLineEdit
{
    Q_OBJECT
public:
    explicit genericLineEdit(QWidget *parent=nullptr);
    virtual ~genericLineEdit();
    void mSetCompleter(QString table, char deli[]=const_cast<char*>(""));
    void setTableDeli(QString table, char deli[]=const_cast<char*>(""));
public slots:
    void mUpdateCompleter();
protected slots:
    void createCompleter();
    void loadCompleter();
protected:
    wm_CompleterLoader *worker;
};

#endif // GENERICLINEEDIT_H
