#ifndef CHECKABLESORTFILTERPROXYMODEL_H
#define CHECKABLESORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include <QObject>

class CheckableSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit CheckableSortFilterProxyModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    Qt::ItemFlags flags ( const QModelIndex & index ) const;

protected:

signals:

public slots:

};
#endif
