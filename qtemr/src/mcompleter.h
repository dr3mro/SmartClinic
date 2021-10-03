// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MCOMPLETER_H
#define MCOMPLETER_H


#include <QCompleter>
#include <QLineEdit>
#include <QStringListModel>
#include <QStringList>
#include <QString>
#include <QAbstractItemView>
//#include "msettings.h"

class QString;
//class QStringList;


class mCompleter : public QCompleter
{
    Q_OBJECT
public:
    mCompleter(QLineEdit *parent, char _delimiter/*,mSettings::defaultFont defaultfont*/);
    mCompleter(QLineEdit *parent, char _delimiter/*,mSettings::defaultFont defaultfont*/, QStringListModel *model);
    mCompleter(QLineEdit *parent, char _delimiter/*,mSettings::defaultFont defaultfont*/, const QStringList &list);
    QString pathFromIndex(const QModelIndex &index) const;
    QStringList splitPath(const QString &path) const;
    void putModel(QStringListModel *model);

public slots:
//    void setDefaultFont();

private:
    char delimiter;
    mutable int cursor_pos = -1;
    int originalPos=-1;
    void connectSignals();
    QLineEdit *line_edit;
    //mSettings::defaultFont defaultfont;
signals:

private slots:
    void onActivated(const QString&);
    void onCursorPositionChanged(int old_pos, int new_pos);
    void removeItemFromModel(int row);

};

#endif // MCOMPLETER_H
