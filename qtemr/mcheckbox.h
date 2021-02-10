// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MCHECKBOX_H
#define MCHECKBOX_H

#include <QObject>
#include <QCheckBox>


class mCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit mCheckBox(QWidget *parent=nullptr);
public slots:
    void makeEditable(bool b);
private slots:
    void sendCheckBoxName(bool);
signals:
    void sendCheckBoxName(QString);
};

#endif // MCHECKBOX_H
