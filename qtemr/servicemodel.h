#ifndef SERVICEMODEL_H
#define SERVICEMODEL_H

#include <QObject>
#include <QSqlTableModel>


class serviceModel : public QSqlTableModel
{
public:
    explicit serviceModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase());
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
};

#endif // SERVICEMODEL_H
