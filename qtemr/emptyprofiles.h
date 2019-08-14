#ifndef EMPTYPROFILES_H
#define EMPTYPROFILES_H

#include <QDialog>
#include <QCloseEvent>
#include <QTimer>
#include "dataiohelper.h"
#include "msettings.h"
#include "sqlbase.h"
#include "mdialog.h"

namespace Ui {
class EmptyProfiles;
}

class EmptyProfiles : public mDialog
{
    Q_OBJECT
    bool killLoopFlag_;
    int MaxPatients;
    int MinPatients;
    sqlBase *sqlbase;

public:
    explicit EmptyProfiles(QWidget *parent = nullptr);
    ~EmptyProfiles();

private slots:
    void on_buttonOk_clicked();
    void on_checkBox_toggled(bool checked);
    void on_buttonClose_clicked();
    void keyPressEvent(QKeyEvent *e);
    void on_closeButton_clicked();
    void progressBarWorker(int a, int b);

signals:
    void updatePList();
    void killLoop();
    void loadPatient(int);
    void toggleEditMode(bool);
private:
    Ui::EmptyProfiles *ui;
    bool isEmptyRecordsCreated=false;
    int startPatientID=1;

protected:
    void closeEvent(QCloseEvent *e);
};

#endif // EMPTYPROFILES_H
