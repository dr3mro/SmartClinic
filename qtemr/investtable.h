// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef INVESTTABLE_H
#define INVESTTABLE_H

#include <QObject>
#include <QHeaderView>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFileDialog>
#include <QTimer>
#include <QDesktopServices>
#include <QFuture>
#include <QtConcurrent>
#include <QEvent>
#include "investmodel.h"
#include "wm_invmodelloader.h"
#include "sqlbase.h"
#include "sqlextra.h"
#include "ztableview.h"
#include "mymessagebox.h"
#include "inviconhelper.h"
#include "wm_investtooltiploader.h"
#include "mrequestviewer.h"
#include "msettings.h"

class investTable : public zTableView
{
    Q_OBJECT

public:
    explicit investTable(QWidget *parent= nullptr);
    void populateInvests(int id, int julianDate);
    bool saveInvestigation(const int &ID, const int &julianDate);
    bool addNewInvest(int ID, int julianDate, QString newInvest, int state = 0, double price=0);
    bool addInvMedia(bool setState = true);
    void tweakTable();
    void setPatientID(int id);
    InvestModel *getInvestigationsModel();
    InvestModel *invModel ;
    void clearInvestigations();
    QStringList getInvestigationsList(); // not services;
    bool printableInvestigationsExists();
    bool isWorking();
    ~investTable();

public slots:
    void tweakInveMedia();
    void loadInvestigations();
    void createTooltips(InvestModel *m);
    void clearSelection();
    void save();
    void putToolTip();

private:
    QTimer *timer;
    QImage img;
    int ID;
    int julianDate;
    sqlBase *sqlbase;
    sqlExtra *sqlextra;
    wm_invModelLoader *worker;
    wm_investTooltipLoader *invTooltipWorker;
    bool isModelLoaded=false;
    bool working=false;

    QFont nonPrintableFont;
    QFont printableFont;
    QFont serviceFont;
    QFuture<InvestModel*> future;
    QFutureWatcher <InvestModel*> watcher;
    QFuture<InvestModel*> tooltipFuture;
    QFutureWatcher<InvestModel*> tooltipWatcher;
    void toggleInvestaigationState(const int &state,const QModelIndex &cell);
    void deleteInvMedia(QString &mediaURL, QModelIndex &cell, bool isService);
    int sortCol=6;
    int getInvestigationCount();//+services
    int getServicesCount();
    int scale;
    mRequestViewer requestViewer;
    mSettings& settings=mSettings::instance();

signals:
    void popUpMessage(QString,QString);
    void togglePrintButton();
    void selectLastInvRow();
    void toggleRemoveInvButton(bool);

protected:
    void keyPressEvent(QKeyEvent *e);
    bool eventFilter(QObject *o, QEvent *e);

};

#endif // INVESTTABLE_H
