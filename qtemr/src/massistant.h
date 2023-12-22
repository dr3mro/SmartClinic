// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MASSISTANT_H
#define MASSISTANT_H

#include <QDialog>
#include <QCalendarWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QShortcut>
#include "msettings.h"
#include "sqlbase.h"
#include "sqlextra.h"
#include "mcalendarwidget.h"
#include "mlabelmsg.h"
#include "mdialog.h"
#include "expecteddeliveries.h"

namespace Ui {
class mAssistant;
}

class mAssistant : public mDialog
{
    Q_OBJECT

public:
    explicit mAssistant(mLabelMsg &labelMsg, QWidget *parent, bool & eMode);
    void load();
    ~mAssistant();

signals:
    void loadThisPatient(int);
    void toggleEditMode(bool);

private slots:
    void on_closeButton_clicked();
    void on_goButton_clicked();
    void on_fromDate_dateChanged(const QDate &fromDate);
    void on_toDate_dateChanged(const QDate &toDate);
    void on_fromTime_timeChanged(const QTime &fromTime);
    void on_toTime_timeChanged(const QTime &toTime);
    void on_btnCheckout_clicked();
    void loadCheckout();
    void on_cbSinceLastCheckout_toggled(bool checked);
    void on_cashCalendar_clicked(const QDate &date);
    void on_agendaCalendar_clicked(const QDate &date);
    void LoadPatient(const QModelIndex &modelIndex);
    void loadDeliveries();
    void onEddModelLoaded();
    void onAgendaModelLoaded();
    void onCashModelLoaded();
    void goExpectedDeliveriesTab();
    void doCalcs();
private:
    mLabelMsg& labelMsg;
    bool & editingMode;
    sqlBase *sqlbase;
    sqlExtra *sqlextra;
    QStandardItemModel *calcModel;
    QStandardItemModel *agendaModel;
    QStandardItemModel *myRegisterModel;
    QStandardItemModel *eddModel;
    QFuture<QStandardItemModel*> eddModelFuture;
    QFutureWatcher<QStandardItemModel*> eddModelFutureWatcher;
    QFuture<QStandardItemModel*> agendaModelFuture;
    QFutureWatcher<QStandardItemModel*> agendaModelFutureWatcher;
    QFuture<void> agendaModelAttendedFuture;
//    QFuture<void> registerServiceLoaderFuture;
//    QFutureWatcher<void> registerServiceLoaderFutureWatcher;
    QFuture<QStandardItemModel*> calcModelFuture;
    QFuture<QStandardItemModel*> cashModelFuture;
    QFutureWatcher<QStandardItemModel*> cashModelFutureWatcher;
    Ui::mAssistant *ui;
    mCalendarWidget *fromCalWidget;
    mCalendarWidget *toCalWidget;
    mSettings& settings = mSettings::instance();
    ExpectedDeliveries expectedDeliveries;
    QCalendarWidget *calendar;

    void loadCurrentSelectedAgenda();
    void tweakRegisterTable();
    void loadRegister();
    void loadAgenda();
    void setTimePeriod();
    void setcheckoutTooltip();
    bool ignoreKeyEvents=false;


protected:
    void keyPressEvent(QKeyEvent *event)override;
    void keyReleaseEvent(QKeyEvent *event)override;
    void showEvent(QShowEvent *e)override;
    void closeEvent(QCloseEvent *e) override;

};

#endif // MASSISTANT_H
