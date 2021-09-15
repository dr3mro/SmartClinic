// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QCalendarWidget>
#include <QGridLayout>
#include <QMouseEvent>
#include <QEvent>
#include <QSystemTrayIcon>
#include <QLocale>
#include <QGraphicsBlurEffect>
#include <QShortcut>
#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>
#include <QTime>
#include "mdebug.h"
#include "regapp.h"
#include "patientlist.h"
#include "visitsbox.h"
#include "userpass.h"
#include "listeditor.h"
#include "inveslist.h"
#include "mymessagebox.h"
#include "textedit.h"
#include "drugindex.h"
#include "backup.h"
#include "apptrayicon.h"
#include "sqlbase.h"
#include "mcompleter.h"
#include "sqlextra.h"
#include "sqlcore.h"
#include "datahelper.h"
#include "dataiohelper.h"
#include "massistant.h"
#include "globalvariables.h"
#include "mcheckbox.h"
#include "surgicalnotes.h"
#include "mship.h"
#include "drugexapnder.h"
#include "mcalendarwidget.h"
#include "mlabelmsg.h"
#include "miniupdater.h"
#include "settingsclass.h"
#include "aboutwindow.h"
#include "emptyprofiles.h"
#include "squeeze.h"
#include "favouritedrugseditor.h"
#include "conditionsedit.h"
#include "errorlogviewer.h"
#include "settingsclass.h"
#include "microupdater.h"
#include "dboptimizer.h"
#include "toast.h"
#include "notifications.h"
#include "dieteditor.h"
#include "mergedlg.h"
#include "mdebug.h"
#include "remoteassist.h"
#include "netserver.h"
#include "m_ClickableLabel.h"
#include "3rdparty/feedback/feedback.h"
#ifdef __GNUC__
#define NO_RETURN __attribute__((noreturn))
#elif __clang__
#define NO_RETURN __attribute__((noreturn))
#elif _MSC_VER
#define NO_RETURN __declspec(noreturn)
#endif

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void boot();
    void grabPatient();
    void fillPatient(const sqlBase::Patient &patient);
    void addSurgicalNotes(int ID, QString surgeryID, int julianDate, QString opName, QString opReport);
    ~MainWindow();

public slots:
    void applyBlurEffect();
    void removeBlurEffect();
    void show_about_win();
    void show_settings_win();
    void show_gen_win();
    void show_listEdit_win();
    void show_favouritesDrugs_win();
    void show_backup_win();
    void show_update_win();
    void show_commonConditionsEdit();
    void showMergedlg();
    void updateSettings();
    void fixDatabase();
    void closeDataBase();
    void reOpenDataBase();
    void toggleWindow(QSystemTrayIcon::ActivationReason reason=QSystemTrayIcon::DoubleClick);
    void showMainwindowIfMinimizedToTray();
    NO_RETURN void showHelloPirate();
    void showWorkingWindow(QString message);
    void hideWorkingWindow();
    void show_expand_win();
    void showDieteditWin();
    void exportPatientList();
    void popUpMessage(QString title, QString Message );
    void afterAddItemxListWidget(QString tn, QString newItemText);
    void navButtonsLeftClicked();
    void navButtonsRightClicked();
    void removeItemFromCompleter(QString item,QString table);
    void removeItemFromDictionary(QString item, int row);
    void on_PatientSelected(int _id );
    void show_feedback_win();

private slots:
    void reloadMainWindow();
    void on_ButtonSaveEdit_clicked();
    void tweakui();
    void on_ButtonDelete_clicked();
    void setCompleters();
    void on_ButtonVisit_clicked();
    void clear();
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *e);
    void on_ButtonAgeCal_clicked();
    void on_birthDateClicked(const QDate &birthDate);
    void on_patientName_returnPressed();
    void on_buttonRemoveDrug_clicked();
    void addDrug();
    void addAllergy();
    void AddOperation();
    void on_buttonRemoveAllergy_clicked();
    void on_buttonAgenda_clicked();
    void showRemoteAssistWin();
    void on_buttonRemoveOP_clicked();
    void on_buttonPatientList_clicked();
    void loadThisPatient(int ID);
    void on_ButtonRefresh_clicked();
    NO_RETURN void quitApp();
    void registeration();
    bool appLocked();
    void toggleEditMODE(bool pEditMODE);
    bool save();
    void on_buttonNewCancel_clicked();
    void on_buttonInvestigations_clicked();
    void on_spinBoxAge_valueChanged(int arg1);
    void on_drugLine_textChanged(const QString &arg1);
    void on_allergyLine_textChanged(const QString &arg1);
    void on_opAdLine_textChanged(const QString &arg1);
    void loadTheme();
    void on_ExitButton_clicked();
    void on_minimizeButton_clicked();
    void on_drugIndexButton_clicked();
    void toggleBlur(bool b);
    void loadFirstPatient();
    void enableRemoveDrugButton();
    bool saveDrugs();
    void on_settingButton_clicked();
    void addToMyCompleters();
    void appendCheckBoxTextToPastHx(QString text);
    void on_buttonSuricalNotes_clicked();
    void addsNoteSlot(QString surgeryID ,int julianDate , QString opName, QString opReport);
    void savesNoteSlot(QString surgeryID ,int julianDate , QString opName, QString opReport);
    void deleteNoteSlot(QString surgeryID);
    void createVisitBox();
    void setDefaultAppFont();
    void bugTicker();
    void on_crashTool_clicked();
    void showNotifywidget();
    void on_patientMobile_textChanged(const QString &arg1);
    void toggleDrugsAlteredStatus(bool b);
    void reloadTheme();
    void loadThemeWatcher();
    void newPatientWithData(const remoteAssist::Visitor &visitor);
    void WAaction_clicked();

signals:
    void clearDrugLineSignal();
    void clearPatientName();
    void toggleTrayMenuActions(bool b);
    void reloadSurgeryNotes(int ID);
    void updateTextFont();
    void loadCompleters();
    void loadPatient();
    void setReadWrite(bool b);
    void reloadCompleter();
    void removeFromCompleter(int);
    void insertUniqueItem(QString,QString);
    void insertDrug2Visit(QString,QString);

private:
    mSettings& settings=mSettings::instance();
    Ui::MainWindow *ui;
    wm_add2Completer *add2CompleterWorker;
    sqlBase *sqlbase;
    sqlExtra *sqlextra;
    sqlCore *sqlcore;
    settingsClass *gSettings;
    mCalendarWidget *calWidget;
    drugIndex *drugindex;
    mLabelMsg labelMsg;
    bool pEditingMode;
    mAssistant *assistant;
    mShip *mship;
    myMessageBox *msgbox;
    appTrayIcon *trayIcon;
    QShortcut *QuitShortcut;
    QShortcut *settingsShortcut;
    QShortcut *menuShortcut;
    QShortcut *remoteAssistShortcut;
    visitsBox *visitsbox;
    microUpdater *microupdater;
    QGraphicsBlurEffect *blureffect;
    void passwordPopup();
    void checkDatabaseCompatibility();
    bool editing=false;
    void setAgeCalButtonToolTip();
    void deleteLockFile();
    bool isErrorLogEmpty();
    int getCenterPos();
    bool personalHistoryEditChecker();
    bool personalHistoryEmptyChecker();
    bool isHistoryEditExtraChecker();
    sqlBase::Patient patient; //
    int ID;
    bool eval_copy;
    
    bool reg_status;
    regApp regMyApp;
    QWidget BirthDateWindow ;
    QGridLayout layoutCal;
    EmptyProfiles *generator;
    miniUpdater *miniupdater;
    QDateTime datetime;
    int indexLength;
    int user_speciality;
    QDate selected_date;
    errorLogViewer errViewer;
    QTimer t_bugTicker;
    toast tNotify;
    QStringList notificationsList;
    notifications notifyWidget;
    QRegularExpressionValidator phoneValidator;
    bool drugsAltered=false;
    bool allergiesAltered=false;
    bool opAdAltered=false;
    QFuture<QString> themeFuture;
    QFutureWatcher<QString> themeFutureWatcher;
    QTimer clickTimer;
    remoteAssist *rAssistant;
    NetServer netserver;
    QString lcdID;
    QWidget *WA_widget;
    QVBoxLayout *WA_vLayout;
    QLabel *WA_title;
    visitsBox::mPatientBasicDetails patientBasicDetails;
    FeedBack fb;

};
#endif // MAINWINDOW_H
