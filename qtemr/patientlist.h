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
