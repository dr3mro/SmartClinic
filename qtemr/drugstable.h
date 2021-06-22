// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef DRUGSTABLE_H
#define DRUGSTABLE_H

#include <QObject>
#include <QStandardItem>
#include <QGridLayout>
#include <QMenu>
#include <QAction>
#include <QHeaderView>
#include <QEvent>
#include <QMouseEvent>
#include <QRegExp>
#include <QLabel>

#include <QFuture>
#include <QtConcurrent>

#include "setdosedrugnamewidget.h"
#include "sqlextra.h"
#include "genericlineedit.h"
#include "wm_drugmodelloader.h"
#include "ztableview.h"
#include "showaltdrugs.h"
#include "genericonlinesearch.h"
#include "mymessagebox.h"
#include "expandeasyeditor.h"


class drugsTable : public zTableView
{
    Q_OBJECT

public slots:
    void DrugSyncWithVisit(QList<QStringList> array,bool sync);
    void clearDrugs();
    void clear();
    void clearInactiveDrugs();
    void replaceDrug(QString newDrug);
    void removeCurrentSelectedDrugFromList();
    DrugsItemModel *getDrugsModel();
    bool isWorking();

public:
    explicit drugsTable(QWidget *parent=nullptr);
    bool addDrug2DrugList(QString newDrug);
    void addDrug2DrugListByStringList(QStringList stringList);
    bool isThereActiveDrugs();

    void loadPatientDrugsModel(int ID, int julianDate, bool syncLoader=false);
    DrugsItemModel *drugsModel;

    ~drugsTable();

private slots:
    void setDose();
    void showContextMenu(const QPoint &pos);
    void showContextMenu();
    void clearDefaultDose();
    void checkPrice();
    void drugsModelLoaded();
    void removeFromAutoComplete();
    void addToAutoComplete();
    void show_setDose();
    void resume_drug();
    void stop_drug();
    void drugsTableSort();
    void removeItemFromCompleter(QString item, QString tableName);
    void findSameTradename();
    void findSameGeneric();
    void findSameIndication();
    void findSameGroup();
    void searchGenricNameOnline();
    void copy2pDrugsList();
    void toggleAllDrugs();
    void calculateRxCosts();
    void Sync2Patient();
    void showExpanderEasyEdit();
    void resetExpander();

signals:
    void drugTableItemChanged();
    void showRxCost(double,bool);
    void popUpMessage(QString,QString);
    void saveDrugs();
    void loadCompleted();
    void reloadDrugsLineAutoComplete();
    void loadCompleters();
    void setFindDrugsModel(QStandardItemModel*);
    void setFindDrugsLabel(QString);
    void syncDrugs(QList<QStringList>,bool);
    void SyncToVisit();
    void SyncToPatient(bool);
    void SyncLastVisit();
    int doeshaveDrugsInPatient();
    int doesHaveDrugsInLastVisit();

private:
    QWidget w_setDose;
    showAltDrugs *altDrugs;
    genericOnlineSearch *genericSearch;
    QGridLayout *lo_setDose;
    genericLineEdit *le_setDose;
    QMenu *m_drugs;
    QMenu *altDrugsMenu;
    QAction *a_stop;
    QAction *a_resume;
    QAction *a_setDose;
    QAction *a_genericInfo;
    QAction *a_clearDefaultDose;
    QAction *a_checkPrice;
    QAction *a_rAutoComp;
    QAction *a_aAutoComp;
    QAction *a_clear;
    QAction *a_delete;
    QAction *a_stopAll;
    QAction *a_resumeAll;
    QAction *a_clearInactive;
    QAction *a_copy2pWin;
    QAction *a_ShowAltDrugsSameTrade;
    QAction *a_ShowAltDrugsSameGeneric;
    QAction *a_ShowAltDrugsSameIndication;
    QAction *a_ShowAltDrugsSameGroup;
    QAction *a_EditExpander;
    QAction *a_ResetExpander;
    QMenu *cpDrugsMenu;
    QAction *a_updateAll2PWin;
    QAction *a_cp4rmPWin;
    QAction *a_overWrite2pWin;
    QAction *a_cp4rmLastVisit;
    sqlExtra *sqlextra;
    sqlCore *sqlcore;
    QStandardItemModel *findModel;
    QString getSelectedDrugTradeName();
    void findAltDrug(QString col, QStringList filters);
    QStringList coreDrugs;
    bool drugsSyncLoadingOperation=false;
    void createDrugsModel();
    void createDrugsTableConMenu();
    void tweakDrugsTable();
    void genDrugTableToolTip();
    bool isThereInactiveDrugs();
    bool isTradeNameinAutocomplete(QString tradeName);
    bool isPriceEqual(int row, QString tradeName);
    wm_drugModelLoader *worker;
    QString exConName;
    QString coConName;
    setDoseDrugNameWidget selectedDrugLabel;
    int insertUnknownDrugCounter=0;
    QString insertUnknownDrugName;
    int showMessageBox(QString message);
    QFuture<DrugsItemModel*> future;
    QFutureWatcher<DrugsItemModel*> watcher;
    int sortCol=5;
    bool working=false;


protected:
    bool eventFilter(QObject *o, QEvent *e);
    void keyPressEvent(QKeyEvent *keyEvent);

};

#endif // DRUGSTABLE_H
