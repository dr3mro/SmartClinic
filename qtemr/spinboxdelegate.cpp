// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "spinboxdelegate.h"

spinBoxDelegate::spinBoxDelegate(QWidget *parent):QItemDelegate(parent)
{

}

QWidget *spinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    QDoubleSpinBox *spinbox = new QDoubleSpinBox(parent);
    spinbox->setGeometry(option.rect);
    spinbox->setMaximum(99999.00);
    spinbox->setMinimum(0.00);
    return spinbox;
}

void spinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*> (editor);
    double value = index.data(Qt::DisplayRole).toDouble();
    spinbox->setValue(value);
}

void spinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*> (editor);
    double value = spinbox->value();
    model->setData(index,value,Qt::EditRole);
}

void spinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*> (editor);
    spinbox->setGeometry(option.rect);
}

