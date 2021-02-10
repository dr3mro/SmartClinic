// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef XDATETIMEEDIT_H
#define XDATETIMEEDIT_H

#include <QObject>
#include <QDateTimeEdit>

class xDateTimeEdit : public QDateTimeEdit
{
    Q_OBJECT
public:
    explicit xDateTimeEdit(QWidget *parent=nullptr);
public slots:
    void makeReadWrite(bool rw);
};

#endif // XDATETIMEEDIT_H
