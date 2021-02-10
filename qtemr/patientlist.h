// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef PATIENTLIST_H
#define PATIENTLIST_H

#include <QWidget>
#include <QKeyEvent>
#include "mdialog.h"

namespace Ui {
class PatientList;
}

class PatientList : public mDialog
{
    Q_OBJECT
public:
    explicit PatientList(QWidget *parent = nullptr);
    ~PatientList();

private:
    Ui::PatientList *ui;

public slots:
private slots:
    void keyPressEvent(QKeyEvent *e);
    void on_closeButton_clicked();

signals:
protected:
};

#endif // PATIENTLIST_H
