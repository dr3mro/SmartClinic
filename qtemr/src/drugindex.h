// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef DRUGINDEX_H
#define DRUGINDEX_H

#include <QDialog>
#include "sqlcore.h"
#include "dataiohelper.h"
#include "msortfilterproxymodel.h"
#include "mdialog.h"
#include <QStyledItemDelegate>

class DrugsIndexPriceItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    DrugsIndexPriceItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) { }
    QString displayText(const QVariant &value, const QLocale &locale) const {
        if (value.type() == QVariant::Double) return locale.toString(value.toDouble(), 'f', 2);
        return QStyledItemDelegate::displayText(value, locale);
    }
};


namespace Ui {
class drugIndex;
}

class drugIndex : public mDialog
{
    Q_OBJECT
public:
    explicit drugIndex(QWidget *parent = nullptr);
    ~drugIndex();

private slots:
    void on_closeButton_clicked();
    void on_search_textChanged(const QString &arg1);
    void on_tradeName_clicked(bool status);
    void on_genericName_clicked(bool status);
    void on_indication_clicked(bool status);
    void setCategory(QString category);
    void setManufacturer(QString manufacturer);
    void setForm(QString form);
    void setResultsCount(QModelIndex, int, int);
    void on_resetButton_clicked();
    void toggleResetButton();

private:
    Ui::drugIndex *ui;
    QStandardItemModel *model;
    int filterColumn;
    mSortFilterProxyModel *proxy_model;
    sqlCore *sqlcore;

private slots:
    void setFilters();
    void load();
signals:


};



#endif // DRUGINDEX_H