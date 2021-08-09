// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef XLISTWIDGET_H
#define XLISTWIDGET_H

#include <QObject>
#include <QListWidget>
#include "mlineedit.h"
#include "msettings.h"

class xListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit xListWidget(QWidget *parent=nullptr);
    void setListVariables(QString ln);
    void addItem(const QString &label);
public slots:
    void makeReadWrite(bool rw);
    void selectedRowChanged();
    void setDefaultFont();
private slots:

private:
    bool pEditingMode;
    QString listName;
    mSettings& settings=mSettings::instance();

signals:
    void popUpMessage(QString,QString);
    void afterAddItemxListWidget(QString tn, QString newItemText);
    void enableItemRemoveButton(bool b);

};

#endif // XLISTWIDGET_H
