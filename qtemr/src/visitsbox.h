// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef VISITSBOX_H
#define VISITSBOX_H

#include <QDialog>
#include <QMessageBox>
#include <QLocale>
#include <QCompleter>
#include <QList>
#include <QPair>
#include <QComboBox>
#include <QFileDialog>
#include <QMenu>
#include <QTextEdit>
#include <QAction>
#include <QApplication>
#include <QCalendarWidget>
#include <QShortcut>
#include <QMainWindow>
#include "windowmanager.h"
#include "mymessagebox.h"
#include "textedit.h"
#include "visitslist.h"
#include "QLineEdit"
#include "printdrugs.h"
#include "sqlbase.h"
#include "sqlextra.h"
#include "mcompleter.h"
#include "datahelper.h"
#include "dataiohelper.h"
#include "msettings.h"
#include "inveslist.h"
#include "mcalendarwidget.h"
#include "wm_visitsaver.h"
#include "wm_add2completer.h"
#include "mdialog.h"
#include "datahelper.h"
#include "visittypes.h"
namespace Ui {
class visitsBox;
}

class visitsBox : public mDialog
{
    Q_OBJECT

public:

    struct mPatientBasicDetails{
        int ID = 0;
        int age = 0;
        mSettings::mSex sex = mSettings::mSex::male;
        QString Name = "null";
        QString fPal = "0-0-0-0";
    };

    explicit visitsBox(QWidget *parent = nullptr);
    sqlBase::Visit grabVisit();
    void fillVisit(const sqlBase::Visit &visit);
    void clearVisit();
    void updateVisitAge();
    void enableEditMode(bool vEditMode);
    void setPatient(const mPatientBasicDetails &_patientBasicDetails);
    void tweakui();
    ~visitsBox();

public slots:
    void grabSave();
    void onDrugLoadCompleted();
    void add2RoshettaAutoComplete(QString w);
    void popUpMessage(QString title,QString message);
    void isCompleterPopupVisible(bool v);
    void removeItemFromCompleter(QString item,QString table);
    void removeItemFromDictionary(QString item, int row);
    void finishedSavingVisit(bool state);
    void navButtonsLeftClicked();
    void navButtonsRightClicked();
    mSettings::defaultFont getDefaultFont();
    bool isCompleteByWord();
    void setSuggestedVisitType(const int & _visitType);

private slots:
    void on_ButtonNew_clicked();
    void on_ButtonSave_clicked();
    void on_ButtonDel_clicked();
    void on_visitLists_currentIndexChanged(const QString &arg1);
    void on_buttonAddDrug_clicked();
    void on_buttonRemoveDrug_clicked();
    void on_drugLine_returnPressed();
    void on_buttonAddInvestigations_clicked();
    void on_buttonRemoveInvestigations_clicked();
    void on_investigationsLine_returnPressed();
    void save(sqlBase::Visit visit,bool threading = true);
    void on_ButtonVisit_clicked();
    void on_CheckButtonCaseClose_toggled(bool checked);
    void on_toolButtonRefresh_clicked();
    void toggleEditMode();
    void on_buttonInvest_clicked();
    void autosave();
    void on_investigationsLine_textChanged(const QString &arg1);
    void on_drugLine_textChanged(const QString &arg1);
    void SyncToPatient(bool sync);
    void SyncToVisit();
    void SyncLastVisit();
    void on_comboVisitType_currentIndexChanged(int index);
    void on_closeButton_clicked();
    void addNewInvestigation(QString newInvName);
    void addNewDrug(QString newDrugName);
    void on_fastPrint_leftButtonClicked();
    void on_fastPrint_rightButtonClicked();
    void on_fastPrint_middleButtonClicked();
    void enableRemoveDrugButton();
    void on_InvestigationsTable_clicked(const QModelIndex &index);
    bool mSave(const sqlBase::Visit &visit,const bool &threading=true);
    void toggleSyncPrintButtons();
    void on_lmpDate_userDateChanged(const QDate &date);
    void on_lineEditWeight_textChanged(const QString &arg1);
    void on_weight_textChanged(const QString &arg1);
    void on_checkBoxAntenatal_clicked(bool checked);
    void toggleContollers();
    void followUpDateChanged(const QDate &date);
    void onShift_pageUp();
    void onShift_pageDown();
    void selectLastInvRow();
    void showCosts(double est, bool percision);
    void toggleDrugsAlteredStatus(bool b);
    int getDrugsCountForVists(int _id, int julianDate);
    int getPatientsDrugsCount(int _id);
    bool doesHaveDrugsInLastVisit();
    bool doeshaveDrugsInPatient();
    void toggleDateFollowup();

    void on_lineEditLength_textChanged(const QString &arg1);

    void on_height_textChanged(const QString &arg1);

signals:
    void newMessage(QString,QString);
    void syncDrugs(QList<QStringList>,bool);
    void toggleBlur(bool b);
    void clearInvLine();
    void clearDrugLine();
    void syncLMPDateWithPatients(QDate date);
    void loadCompleters();
    void reloadCompleter();
    void reloadMWCompleter();
    void setReadWrite(bool b);
    void updateTextFont();
    void onVisitBoxClose();
    void removeFromCompleter(int);
    void insertUniqueItem(QString,QString);
    void insertDrug2Patient(QString,QString);
    void updateDrugsCompleter();
    DrugsItemModel* getDrugsModel();
    void showPreview();
    void styleVitals(mSettings&);

private:
    Ui::visitsBox *ui;
    myMessageBox *msgbox;
    sqlBase *sqlbase;
    sqlExtra *sqlextra;
    QTimer *autoSaveTimer;
    wm_add2Completer *add2CompleterWorker;
    wm_visitSaver *visitSaverWorker;
    printDrugs *print;
    QShortcut *shift_pageUp;
    QShortcut *shift_pageDown;
    QShortcut *printShortcut;
    QShortcut *easyPrintShortcut;
    QShortcut *printPreviewShortcut;
    QShortcut *toggleFollowupDate;
    QShortcut *vTypeUp;
    QShortcut *vTypeDown;
    int visitDateTime2JulianDate();
    void connectSignals(QWidget *parent);
    //void initializeVariables();
    void addThisToCompleter(const sqlBase::Visit& visit);
    void toggleAntenatal(bool checked);
    void initializeAutoSave();
    bool isVisitModified();
    void setFollowDateTooltip(const int &selectedDateFollowUps,const QDate& date);
    void goSaveVisit(int index);
    void goFirstVisit();
    void goLastVisit();
    void goPreviousVisit();
    void goNextVisit();
    int followNotify(const QDate &date);
    bool visitLoaded=false;
    bool alwaysSave;
    bool autoSave;
    bool screenMode;
    bool simpleExamination;
    bool autoSetNewAfterMaxFollow;
    bool autoCompleteByWord;
    int autosaveint;
    int speciality;
    int maxFollows;
    int maxFollowUps;
    bool mLineEditPopUpVisible=false;
    int lastInvestigationRow=0;
    bool newVisitCreationInProgress=false;
    sqlBase::Visit loadedVisit;
    bool drugsAltered=false;
    mSettings& settings = mSettings::instance();
    VisitTypes & visitTypes = VisitTypes::instance();
    int visitindex;
    bool vEditMode;
    QString comboSelectedDataTime ;
    QString visitAge;
    QString currentVisitDateTime;
    QLocale curLocale;
    bool saving=false;
    bool drugLoadCompleted=false;
    QString printableAge;
    bool aboutToClose=false;
    QDate lastSelectedFollowupDate=QDate::currentDate();
    QDate visitFollowupDate=QDate::currentDate();
    int suggestedVisitType=0;//for remote assistant created patient to modify this
    mSettings::Roshetta getRoshetta();
    void roshettaDrugsfiller(QList<mSettings::drug> &drugs, DrugsItemModel *drugsModel, bool alteredDrugsOnly);
    void roshettaVitalsFiller(mSettings::Vitals &vitals);
    void setVitalsPlaceHolderText();
    mPatientBasicDetails patientBasicDetails;


protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *e)override;
    void keyReleaseEvent(QKeyEvent *e)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

};

#endif // VISITSBOX_H
