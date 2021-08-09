// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef INVESLIST_H
#define INVESLIST_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QObject>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include "dataiohelper.h"
#include "wm_invmodelloader.h"
#include "sqlbase.h"
#include "getinvestigationname.h"
#include "mdialog.h"
#include "inviconhelper.h"
#include "wm_investtooltiploader.h"
#include "mrequestviewer.h"
#include "msettings.h"

namespace Ui {
class invesList;
}

class invesList : public mDialog
{
    Q_OBJECT
public:
    explicit invesList(QWidget *parent, int _id);
    ~invesList();
public slots:
    void mHide();
    void mShow();
private slots:
    void on_tableView_activated(const QModelIndex &index);
    void uptodate();
    void on_closeButton_clicked();
    void loadInvestigations();
    void putToolTip();
    void on_ButtonNew_clicked();
    void addInvestigation(QString Name,QString Path);
    void on_ButtonDel_clicked();
    void on_tableView_clicked(const QModelIndex &index);


signals:
    //void reInvBtn();
    void popUpMessge(QString title,QString message);

private:
    wm_invModelLoader *worker;
    wm_investTooltipLoader *invTooltipWorker;
    QFuture<InvestModel*> future;
    QFutureWatcher<InvestModel*> watcher;
    QFuture<InvestModel*> tooltipFuture;
    QFutureWatcher<InvestModel*> tooltipWatcher;
    InvestModel *model=nullptr;
    QTimer *timer;
    sqlBase *sqlbase;
    getInvestigationName *getNameDlg;
    int ID;
    Ui::invesList *ui;
    void load();
    void createTooltips(InvestModel *m);
    int scale;
    mRequestViewer requestViewer;
    mSettings& settings=mSettings::instance();

protected:
    void showEvent(QShowEvent *e);

};

#endif // INVESLIST_H
