#ifndef VISITSLIST_H
#define VISITSLIST_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QWheelEvent>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include "wm_visitlistloader.h"


class visitsList : public QComboBox
{
    Q_OBJECT

public:
    explicit visitsList(QWidget *parent = nullptr);
    void populateWithVisitList(int ID);
    void setMaxFollows(int mxf);
    ~visitsList();
public slots:
    void insertVisits();
    void makeReadWrite(bool b);

signals:
    void loadCompleted();
    void saveVisit();
private:
    bool eventFilter(QObject *o, QEvent *e);
    int ID;
    wm_visitListLoader *worker;
    bool isReadOnly;
    int maxFollows;
    QFuture<QVector<sqlBase::visitItem> > future;
    QFutureWatcher<QVector<sqlBase::visitItem> > watcher;
    QIcon getVisitIcon(int visitType) const;

protected:
    void wheelEvent(QWheelEvent *e);

};

#endif // VISITSLIST_H
