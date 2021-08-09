// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef DIETEDITOR_H
#define DIETEDITOR_H

#include <QDialog>
#include "msettings.h"
#include "sqlextra.h"
#include "dataiohelper.h"
#include "mdialog.h"

namespace Ui {
class DietEditor;
}

class DietEditor : public mDialog
{
    Q_OBJECT

public:
    explicit DietEditor(QWidget *parent = nullptr);
    ~DietEditor();

private slots:
    void on_dietList_clicked(const QModelIndex &index);
    void on_buttonAdd_clicked();
    void on_lineEdit_editingFinished();
    void on_buttonEdit_toggled(bool checked);
    void on_ButtonSave_clicked();
    void on_buttonDelete_clicked();
    void on_lineEdit_returnPressed();

    void on_closeButton_clicked();

private:
    void setEditable(bool state);
    mSettings& settings=mSettings::instance();
    QSqlTableModel *dietModel;
    sqlExtra *sqlextra;
    Ui::DietEditor *ui;

signals:
    void loadCompleters();
};

#endif // DIETEDITOR_H
