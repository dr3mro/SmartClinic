#ifndef DRUGINDEX_H
#define DRUGINDEX_H

#include <QDialog>
#include "sqlcore.h"
#include "msortfilterproxymodel.h"
#include "mdialog.h"
#include <QStyledItemDelegate>
#include "staticstrings.h"
#include "mlabelmsg.h"


class DrugsIndexPriceItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    DrugsIndexPriceItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) { }
    QString displayText(const QVariant &value, const QLocale &locale) const {
#if QT_VERSION >= 0x060000
        if ( value.metaType().id() == QMetaType::Double) return locale.toString(value.toDouble(), 'f', 2);
#else
        if ( value.type() == QVariant::Double) return locale.toString(value.toDouble(), 'f', 2);
#endif
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
    mLabelMsg message;

private slots:
    void setFilters();
    void load();
    void on_updateButton_clicked();
    void on_resetDatabaseButton_clicked();
    void onDrugsDatabaseChange();

signals:


};



#endif // DRUGINDEX_H
