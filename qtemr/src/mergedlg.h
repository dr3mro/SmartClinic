// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MERGEDLG_H
#define MERGEDLG_H

#include <QPair>
#include <QListWidgetItem>

#include "mdialog.h"
#include "sqlbase.h"
#include "mdebug.h"
#include "windowmanager.h"
#include "mymessagebox.h"
#include "msettings.h"

namespace Ui {
class MergeDlg;
}

class MergeDlg : public mDialog
{
    Q_OBJECT

public:
    explicit MergeDlg(QWidget *parent = nullptr);
    ~MergeDlg();

private slots:
    void on_closeButton_clicked();
    void on_btnApply_clicked();
    void on_cb_all_toggled(bool checked);
    void on_fromID_valueChanged(int);

private:
    Ui::MergeDlg *ui;
    mSettings& settings=mSettings::instance();
    sqlBase *sqlbase;
    bool valid=false;
    QStringList getSelectedVisits();
    void loadVisits();
    myMessageBox msgbox;
signals:
    void loadThisPatient(int);
    void reloadPatientsList();
    void toggleEditMode(bool);
};

#endif // MERGEDLG_H
