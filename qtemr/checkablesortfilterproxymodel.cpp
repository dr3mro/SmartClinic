#include "checkablesortfilterproxymodel.h"

CheckableSortFilterProxyModel::CheckableSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent){}

QVariant CheckableSortFilterProxyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if ( index.column() == 1 && (role == Qt::CheckStateRole || role == Qt::DisplayRole) )
    {
        if (role == Qt::CheckStateRole)
            return index.data(Qt::EditRole).toBool() ? QVariant(Qt::Checked) : QVariant(Qt::Unchecked);
        else if (role == Qt::DisplayRole)
            return QVariant();
    }

    return QSortFilterProxyModel::data(index,role);
}

bool CheckableSortFilterProxyModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid())
        return false;

    if( index.column() == 1 && role == Qt::CheckStateRole)
    {
        QVariant data = (value.toInt() == Qt::Checked) ? QVariant(1) : QVariant (0);
        return QSortFilterProxyModel::setData(index, data, Qt::EditRole);
    }
    else
        return QSortFilterProxyModel::setData(index,value,role);

}

Qt::ItemFlags CheckableSortFilterProxyModel::flags ( const QModelIndex & index ) const {
    if(!index.isValid())
        return Qt::ItemIsEnabled;

    if ( index.column() == 1 )
        return Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    else if ( index.column() == 0 )
        return Qt::ItemIsSelectable;
    else
        return QSortFilterProxyModel::flags(index);

}
