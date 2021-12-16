// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MLINEEDIT_H
#define MLINEEDIT_H

#include <QObject>
#include <QLineEdit>
#include <QStringListModel>
#include <QKeyEvent>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include "mcompleter.h"
#include "msettings.h"

class mLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit mLineEdit(QWidget *parent=nullptr);
    QStringList autoCompleteStringList;
    virtual ~mLineEdit();

public slots:
    void makeEditable(bool b);
    void addUniqueItem2Model(QString item, QString objName);

private:
    bool isCompleterPopupVisible();
    void toggleonTextChangedSignal(bool c);
    QWidget *parent;
    QStringListModel *model;
    mSettings& settings=mSettings::instance();

private slots:
    void onTextChanged();
    void setDefaultFont();

protected slots:
    void completerLoader();

signals:
    void completerLoaded();
    void reportCompleterPopUpVisibility(bool);
    void removeFromCompleter(int);
    void removeItemFromCompleter(QString,QString);
    void updateDrugsCompleter();
    bool isAutoCompleteByWord();

protected:
    QString windowName;
    void keyPressEvent(QKeyEvent *e);
    char delimeter;
    mCompleter *mcompleter=nullptr;
    QString tableName;
    mSettings::defaultFont font;
    QFuture<QStringList> future;
    QFutureWatcher<QStringList> watcher;
};

#endif // MLINEEDIT_H
