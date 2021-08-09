// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef CONDITIONSEDIT_H
#define CONDITIONSEDIT_H

#include <QDialog>
#include "sqlbase.h"
#include "checkablesortfilterproxymodel.h"
#include "windowmanager.h"
namespace Ui {
class conditionsEdit;
}

class conditionsEdit : public QDialog
{
    Q_OBJECT

public:
    explicit conditionsEdit(QWidget *parent = nullptr);
    ~conditionsEdit();
public slots:
    void show();

private slots:
    void on_buttonAdd_clicked();
    void addCondition(QString name,int _id);
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_returnPressed();

private:
    Ui::conditionsEdit *ui;
    QSqlTableModel *model;
    CheckableSortFilterProxyModel *proxy_model;
    sqlBase *sqlbase;
    int getModelLength();
    WindowManager wm;
signals:
    void reload();
};

#endif // CONDITIONSEDIT_H
