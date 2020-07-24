#ifndef FAVOURITEDOSEDELEGATE_H
#define FAVOURITEDOSEDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QLineEdit>
#include <QCompleter>

#include "sqlextra.h"
class favouriteDoseDelegate : public QItemDelegate
{
public:
    explicit favouriteDoseDelegate(QWidget *parent=nullptr);
    ~favouriteDoseDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    sqlExtra *sqlextra;
    QString connectionName;
    
};

#endif // FAVOURITEDOSEDELEGATE_H
