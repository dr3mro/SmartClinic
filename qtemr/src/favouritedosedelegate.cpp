// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "favouritedosedelegate.h"

favouriteDoseDelegate::favouriteDoseDelegate(QWidget *parent):
    QItemDelegate(parent),
    connectionName (QString("favoriteDelegate_%1").arg(QRandomGenerator::global()->bounded(0,9999999))),
    sqlextra( new sqlExtra(this,connectionName,false))
{
    
    
}

favouriteDoseDelegate::~favouriteDoseDelegate()
{
    sqlextra->optimize();
    delete sqlextra;
    QSqlDatabase::removeDatabase(connectionName);
}

QWidget *favouriteDoseDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int column = index.column();
    QString tableName;
    QLineEdit *linedit = new QLineEdit(parent);
    if (column == 0)
        tableName = "drugs";
    else if (column == 1)
        tableName = "doses";

    QStringList list= sqlextra->getAutoCompleteList(tableName);
    QCompleter *completer = new QCompleter(list,linedit);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    linedit->setCompleter(completer);
    linedit->setGeometry(option.rect);
    linedit->setClearButtonEnabled(true);
    return linedit;
}

void favouriteDoseDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value =index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *line = static_cast<QLineEdit*>(editor);
    line->setText(value);

}

void favouriteDoseDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *line = static_cast<QLineEdit*>(editor);
    QString value = line->text().simplified();
    model->setData(index, value, Qt::EditRole);
}

void favouriteDoseDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
