// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef VISITSLIST_H
#define VISITSLIST_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QWheelEvent>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include "wm_visitlistloader.h"
#include "visittypes.h"

class visitsList : public QComboBox
{
    Q_OBJECT

public:
    explicit visitsList(QWidget *parent = nullptr);
    void populateWithVisitList(const int &ID);
    void setMaxFollows(int mxf);
    QDate getParentVisitDate(int index);
    void setVisitIcon(int type, QIcon icon);
    ~visitsList();

public slots:
    void insertVisits();
    void makeReadWrite(bool b);
    void stopLoading();

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
    QVector<sqlBase::visitItem> list;
    bool _stopLoadingNow=false;
    QListView *_view;
    VisitTypes & visitTypes = VisitTypes::instance();
private slots:
    void addDetails();


protected:
    void wheelEvent(QWheelEvent *e);

};

#endif // VISITSLIST_H
