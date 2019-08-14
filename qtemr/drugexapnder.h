#ifndef DRUGEXAPNDER_H
#define DRUGEXAPNDER_H

#include <QDialog>
#include "sqlextra.h"
#include "mdialog.h"

namespace Ui {
class drugExapnder;
}

class drugExapnder : public mDialog
{
    Q_OBJECT

public:
    explicit drugExapnder(QWidget *parent = nullptr);
    ~drugExapnder();

private slots:
    void on_closeButton_clicked();
    void on_buttonDel_clicked();
    void load(const QModelIndex &index);
    void addThisName();
    void save();
    void setFilter(QString arg);
    void currentRowChanged(QModelIndex i,QModelIndex);

private:
    Ui::drugExapnder *ui;
    sqlExtra *sqlextra;
    QStringListModel *model;
    QSortFilterProxyModel *proxy_model;
    QItemSelectionModel *selectionModel;
    void reLoadAll();
signals:
    void reloadCompleter();
    void newMessage(QString title, QString msg);
    void loadCompleters();
    void reloadDrugsCompleter();
    void setReadWrite(bool);
};

#endif // DRUGEXAPNDER_H
