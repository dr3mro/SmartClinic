// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mcompleter.h"


mCompleter::mCompleter(QLineEdit *parent, char _delimiter/*,mSettings::defaultFont defaultfont*/)
        : QCompleter(parent), delimiter(_delimiter),line_edit(qobject_cast<QLineEdit*>(parent))//,defaultfont(defaultfont)
{
    setCaseSensitivity(Qt::CaseInsensitive);
    setParent(line_edit);
    line_edit->setCompleter(this);
    connectSignals();
    popup()->setAlternatingRowColors(true);

}


mCompleter::mCompleter(QLineEdit *parent, char _delimiter,/*mSettings::defaultFont defaultfont,*/QStringListModel *model)
        : QCompleter(model, parent), delimiter(_delimiter),line_edit(qobject_cast<QLineEdit*>(parent))//,defaultfont(defaultfont)
{
    setCaseSensitivity(Qt::CaseInsensitive);
    setParent(line_edit);
    line_edit->setCompleter(this);
    connectSignals();
    popup()->setAlternatingRowColors(true);
}


mCompleter::mCompleter(QLineEdit *parent, char _delimiter,/* mSettings::defaultFont defaultfont,*/ const QStringList &list)
        : QCompleter(list, parent), delimiter(_delimiter),line_edit(qobject_cast<QLineEdit*>(parent))//,defaultfont(defaultfont)
{
    setCaseSensitivity(Qt::CaseInsensitive);
    setParent(line_edit);
    line_edit->setCompleter(this);
    connectSignals();
    popup()->setAlternatingRowColors(true);
}


QString mCompleter::pathFromIndex(const QModelIndex &index) const {
    QString auto_string = index.data(Qt::EditRole).toString();

    QString str = line_edit->text();

    // If cursor position was saved, restore it, else save it
    if(cursor_pos != originalPos)
        line_edit->setCursorPosition(cursor_pos);
 //   else
 //       cursor_pos = originalPos;

    // Get current prosition
    int cur_index = line_edit->cursorPosition();

    /**
     * NOTE
     *
     * prev_delimiter_index should actually point at final white space AFTER the delimiter.
     */

    // Get index of last delimiter before current position
    int prev_delimiter_index = str.mid(0, cur_index).lastIndexOf(delimiter);
    while(str.at(prev_delimiter_index + 1).isSpace()) prev_delimiter_index++;

    // Get index of first delimiter after current position (or EOL if no delimiter after cursor)
    int next_delimiter_index = str.indexOf(delimiter, cur_index);
    if(next_delimiter_index == -1) {
        next_delimiter_index = str.size();
    }

    // Get part of string that occurs before cursor
    QString part1 = str.mid(0, prev_delimiter_index + 1);

    // Get string value from before auto finished string is selected
    //QString pre = str.mid(prev_delimiter_index + 1, cur_index - prev_delimiter_index - 1);

    // Get part of string that occurs AFTER cursor
    QString part2 = str.mid(next_delimiter_index);

    return part1 + auto_string + part2;
}

QStringList mCompleter::splitPath(const QString &path) const
{
    QStringList string_list;
    int index = path.mid(0,line_edit->cursorPosition()).lastIndexOf(delimiter) + 1;
    QString str = path.mid(index, line_edit->cursorPosition()-index).trimmed();
    string_list << str;
    return string_list;
}

void mCompleter::putModel(QStringListModel *model)
{
    setModel(model);
}

void mCompleter::connectSignals()
{

    connect(this, SIGNAL(activated(const QString &)),
            this, SLOT(onActivated(const QString &)));

    connect(line_edit, SIGNAL (cursorPositionChanged(int, int)),
            this    , SLOT   (onCursorPositionChanged(int, int)));

    connect(line_edit, SIGNAL (removeFromCompleter(int)),
            this    , SLOT   (removeItemFromModel(int)));

}

void mCompleter::onActivated(const QString&)
{
    cursor_pos = originalPos;
}

void mCompleter::onCursorPositionChanged(int old_pos, int new_pos)
{
    if(old_pos != cursor_pos)
        cursor_pos = new_pos;
}

void mCompleter::removeItemFromModel(int row)
{
    QStringListModel *model = static_cast<QStringListModel*> (this->model());
    model->removeRow(row);
}
