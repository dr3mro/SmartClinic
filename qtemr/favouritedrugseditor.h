#ifndef FAVOURITEDRUGSEDITOR_H
#define FAVOURITEDRUGSEDITOR_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include "settingsclass.h"
#include "dataiohelper.h"
#include "sqlextra.h"
#include "favouritedosedelegate.h"
#include "mdialog.h"

namespace Ui {
class favouriteDrugsEditor;
}

class favouriteDrugsEditor : public mDialog
{
    Q_OBJECT

public:
    explicit favouriteDrugsEditor(QWidget *parent = nullptr);
    ~favouriteDrugsEditor();

private slots:
    void on_ButtonDel_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void addButtonToggler(QString arg1);
    void on_ButtonNew_clicked();
    void dataChanged(QModelIndex topLeft, QModelIndex bottomRight, QVector<int> vect);
    void setFilter(QString arg1);

private:
    sqlExtra *sqlextra;
    QSqlTableModel *model;
    QSortFilterProxyModel *proxy_model;
    favouriteDoseDelegate *doseDelegate;
    Ui::favouriteDrugsEditor *ui;
signals:
    void reloadCompleter();
    void loadCompleters();
};

#endif // FAVOURITEDRUGSEDITOR_H
