// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef ZTABLEVIEW_H
#define ZTABLEVIEW_H

#include <QObject>
#include <QTableView>
#include <QKeyEvent>
#include <QStandardItemModel>
#include <QStandardItem>
#include "msettings.h"
class zTableView : public QTableView
{
    Q_OBJECT
public:
    explicit zTableView(QWidget *parent=nullptr);
    virtual ~zTableView();
    void setModel(QAbstractItemModel *_model);
    int getSelectedRows();
    int getRowsCount();
    void setReadOnly(bool b);
    QStandardItemModel *tableModel;
    bool isReadOnly;
    void setSortColumn(const int &col);

public slots:
    void makeReadWrite(bool rw);
    void setDefaultFont();
private:
    void moveRowDown();
    void moveRowUp();
    bool isValidRow(int row);
    mSettings& settings = mSettings::instance();
    int sortColumn=0;

protected:
    void keyPressEvent(QKeyEvent *e);
signals:
    void itemMoved();
    void drugsHasBeenAltered(bool);
};

#endif // ZTABLEVIEW_H
