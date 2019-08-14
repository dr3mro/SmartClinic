#ifndef PATIENTNAMELINEEDIT_H
#define PATIENTNAMELINEEDIT_H

#include <QObject>
#include <QKeyEvent>
#include "mlineedit.h"
#include "wm_patientnamescompleterloader.h"

class patientNameLineEdit : public mLineEdit
{
    Q_OBJECT
public:
    explicit patientNameLineEdit(QWidget *parent=nullptr);
    ~patientNameLineEdit();
private slots:
    void loadCompleter();
    void createCompleter();
protected:
    void keyPressEvent(QKeyEvent *e);

private:
    wm_patientnamesCompleterLoader *Worker;
};

#endif // PATIENTNAMELINEEDIT_H
