#ifndef MCASHTABLEVIEW_H
#define MCASHTABLEVIEW_H

#include <QObject>
#include <QTableView>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>

class mCashTableView : public QTableView
{
    Q_OBJECT
public:
    explicit mCashTableView(QWidget *parent=nullptr);

protected:
    bool eventFilter(QObject *o, QEvent *e);
signals:
    void doCalculations();
};

#endif // MCASHTABLEVIEW_H
