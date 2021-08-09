// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef XLINEEDIT_H
#define XLINEEDIT_H

#include <QObject>
#include <QLineEdit>


class xLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit xLineEdit(QWidget *parent=nullptr);
public slots:
    void makeReadWrite(bool rw);
};

#endif // XLINEEDIT_H
