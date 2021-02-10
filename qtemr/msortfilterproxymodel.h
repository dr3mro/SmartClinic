// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MSORTFILTERPROXYMODEL_H
#define MSORTFILTERPROXYMODEL_H

#include <QObject>
#include <QModelIndex>
#include <QSortFilterProxyModel>

class mSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit mSortFilterProxyModel(QObject *parent=nullptr);
public slots:
    void setCategory(QString category);
    void setManufacturer(QString manufacturer);
    void setForm(QString form);
private:
    QString Category;
    QString Manufacturer;
    QString Form;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const;
};

#endif // MSORTFILTERPROXYMODEL_H
