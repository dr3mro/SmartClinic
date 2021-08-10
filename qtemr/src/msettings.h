// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
#ifndef MSETTINGS_H
#define MSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QApplication>
#include <QList>
#include <QPair>
#include "mdebug.h"
#include "globalvariables.h"
#include "staticstrings.h"
#include "mstyler.h"
#include "datahelper.h"
#include <math.h>
class dataHelper;

class mSettings : public QObject
{
    Q_OBJECT
public:
    // this is data structure to hold the vitals for printing

    struct Vitals{
        int pulse=-1;
        QString BP="";
        int RR=-1;
        double T=-1.0;
        double weight=-1.0;
        double height=-1.0;
        int sPo2=-1;
        QString RBS="-1";

        void clear(){
            pulse=-1;
            BP="-1";
            RR=-1;
            T=-1;;
            weight=-1;
            height=-1;
            sPo2=-1;
            RBS="-1";
        }
        int getRows()
        {
            int rows = 0;
            if(weight != 0)
                rows++;
            if(height != 0)
                rows++;
            if(sPo2 != 0)
                rows++;
            if(RBS != "")
                rows++;
            if(pulse != 0)
                rows++;
            if(RR != 0)
                rows++;
            if(BP != "")
                rows++;
            if(T != 0)
                rows++;

            return rows;
        }

        bool operator==(const Vitals& vitals) const
        {
            return std::tie(
                        pulse,
                        BP,
                        RR,
                        T,
                        weight,
                        height,
                        sPo2,
                        RBS
                        ) ==
                    std::tie(
                        vitals.pulse,
                        vitals.BP,
                        vitals.RR,
                        vitals.T,
                        vitals.weight,
                        vitals.height,
                        vitals.sPo2,
                        vitals.RBS
                        );
        }
    };
    // this is data structure to hold the drug for printing
    struct drug{
        QString TradeName;
        QString Dose;
        QString StartDate;
    };

    enum mSex{
        male,
        female
    };

    struct mDiet{
        bool printRequired=false;
        QString contents="";
    };

    // this is data structure to hold the roshetta for printing
    struct Roshetta
    {
        QString getVisitSymbole(const int & _i){
            QStringList _visitSymboleList = QStringList() << "Ⓝ" << "①" << "②" << "③" << "④" << "Ⓕ";
            return _visitSymboleList.at(_i);
        }

        QString getNextFromJulian(const qint64& nextDateJulian){
            QVector<QPair<QString,int> > options { {"",0},
                                                 {"أسبوع",1},
                                                 {"أسبوعين",2},
                                                 {"٣أسابيع",3},
                                                 {"شهر",4},
                                                 {"شهر",5},
                                                 {"شهر و نصف",6},
                                                 {"شهر و نصف",7},
                                                 {"شهرين",8},
                                                 {"شهرين",9},
                                                 {"شهرين",10},
                                                 {"٣ شهور",11},
                                                 {"٣ شهور",12},
                                                 {"٣ شهور",13},
                                                 {"٣ شهور",14},
                                                 {"٣ شهور",15},
                                                 {"٤ شهور",16},
                                                 {"٤ شهور",17},
                                                 {"٤ شهور",18},
                                                 {"٤ شهور",19},
                                                 {"٥ شهور",20},
                                                 {"٥ شهور",21},
                                                 {"٥ شهور",22},
                                                 {"٥ شهور",23},
                                                 {"٦ شهور",24} };
            qint64 julianToday = QDate::currentDate().toJulianDay();
            qint64 remainingDays = nextDateJulian - julianToday;
            qint64 remainingWeeks = round(remainingDays / 7 );

            for(const auto &x:options){
                if(x.second == remainingWeeks)
                    return x.first;
                else if(x.second < remainingWeeks)
                    continue;
                else
                    return x.first;
            }
            return options.last().first;



        }

        QString ID;
        QString name;
        mSex sex;
        int age;
        QString Diagnosis;
        Vitals vitals;
        QDate visitDate;
        QDate nextDate;
        dataHelper::AgeStyle ageStyle;
        QDateTime printedinDate;
        bool caseClosed;
        QString visitSymbole;
        QList<drug> currentDrugsList;
        QList<drug> baseDrugsList;
        QList<drug> currentAlteredDrugsList;
        QList<drug> baseAlteredDrugsList;
        QStringList requests;
        mDiet diet;
    };

    struct dbOptions
    {
        QString autovacuum="NONE";
        bool optimize=false;
        bool shrinkMem=false;
        QString WAL_CheckPoint="OFF";
        QString shared_cache="SHARED";
        QString temp_store="DEFAULT";
        QString synchronous="NORMAL";
        QString journal_mode="DELETE";
        QString locking_mode="NORMAL"; // exclusive was removed as it crashes the application
        int cache_size=2000;
        int page_size=4096;

        void clear()
        {
            autovacuum="NONE";
            optimize=false;
            shrinkMem=false;
            WAL_CheckPoint="OFF";
            shared_cache="SHARED";
            temp_store="DEFAULT";
            synchronous="NORMAL";
            journal_mode="DELETE";
            locking_mode="NORMAL";
            cache_size=2000;
            page_size=4096;
        }
        bool operator!=(const dbOptions& dboptions) const
        {
            return std::tie
                    (autovacuum,
                     optimize,
                     shrinkMem,
                     WAL_CheckPoint,
                     shared_cache,
                     temp_store,
                     synchronous,
                     journal_mode,
                     locking_mode,
                     cache_size,
                     page_size
                     )
                    !=std::tie
                    (
                        dboptions.autovacuum,
                        dboptions.optimize,
                        dboptions.shrinkMem,
                        dboptions.WAL_CheckPoint,
                        dboptions.shared_cache,
                        dboptions.temp_store,
                        dboptions.synchronous,
                        dboptions.journal_mode,
                        dboptions.locking_mode,
                        dboptions.cache_size,
                        dboptions.page_size
                        );
        }
    };
    struct pSettings
    {
        int speciality;
        bool autoCompleteByWord;
        bool showChronicConditions;
        bool showNavArrows;
        bool smallScreenMode;
        bool simpleExamination;
        bool alwaysSave;
        bool inLinePatientList;
        int autosaveinterval;
        bool autoSave;
        bool minimizeToTray;
        bool autoClosePrintDlg;
        bool enableVisualEffects;
        bool updateNotify;
        bool useToast;
        bool usePhotoViewer;

        double newVisitPrice;
        double followVisitprice1;
        double followVisitprice2;
        double followVisitprice3;
        double followVisitprice4;

        QString selectedTheme;
        QString defaultFont;
        double defaultFontSize;
        bool defaultFontBold;
        QString textboxFont;
        double textboxFontSize;
        bool textboxFontBold;

        int maxFollowUps;
        int maxFollowUpsPerProblem;
        bool autoSetnewAfterMaxPerProblemIsReached;
        bool remmberLastFollowupDate;


        bool operator==(const pSettings& psettings) const
        {
            return std::tie(
                        speciality,
                        autoCompleteByWord,
                        showChronicConditions,
                        showNavArrows,
                        smallScreenMode,
                        simpleExamination,
                        alwaysSave,
                        inLinePatientList,
                        newVisitPrice,
                        followVisitprice1,
                        followVisitprice2,
                        followVisitprice3,
                        followVisitprice4,
                        autosaveinterval,
                        autoSave ,
                        minimizeToTray,
                        selectedTheme,
                        defaultFont,
                        defaultFontSize,
                        defaultFontBold,
                        textboxFont,
                        textboxFontSize,
                        textboxFontBold,
                        maxFollowUps,
                        autoClosePrintDlg,
                        maxFollowUpsPerProblem,
                        autoSetnewAfterMaxPerProblemIsReached,
                        enableVisualEffects,
                        updateNotify,
                        useToast,
                        usePhotoViewer,
                        remmberLastFollowupDate) ==
                    std::tie(psettings.speciality,
                             psettings.autoCompleteByWord,
                             psettings.showChronicConditions,
                             psettings.showNavArrows,
                             psettings.smallScreenMode,
                             psettings.simpleExamination,
                             psettings.alwaysSave,
                             psettings.inLinePatientList,
                             psettings.newVisitPrice,
                             psettings.followVisitprice1,
                             psettings.followVisitprice2,
                             psettings.followVisitprice3,
                             psettings.followVisitprice4,
                             psettings.autosaveinterval,
                             psettings.autoSave ,
                             psettings.minimizeToTray,
                             psettings.selectedTheme,
                             psettings.defaultFont,
                             psettings.defaultFontSize,
                             psettings.defaultFontBold,
                             psettings.textboxFont,
                             psettings.textboxFontSize,
                             psettings.textboxFontBold,
                             psettings.maxFollowUps,
                             psettings.autoClosePrintDlg,
                             psettings.maxFollowUpsPerProblem,
                             psettings.autoSetnewAfterMaxPerProblemIsReached,
                             psettings.enableVisualEffects,
                             psettings.updateNotify,
                             psettings.useToast,
                             psettings.usePhotoViewer,
                             psettings.remmberLastFollowupDate);
        }

    };
    struct checkout
    {
        int time;
        int date;
    };
    struct clinicPrices
    {
        double newVisit;
        double followUp1;
        double followUp2;
        double followUp3;
        double followUp4;
    };
    struct clinicSystem
    {
        int MaxfollowUps;
        bool autoNewVisit;
    };
    struct textboxFont // why is twice ?
    {
        double fontSize;
        QString fontName;
        bool fontBold;

        bool operator==(const textboxFont& _font) const
        {
            return std::tie(
                        fontSize,
                        fontName,
                        fontBold
                        ) == std::tie(
                        _font.fontSize,
                        _font.fontName,
                        _font.fontBold);

        };
    };

    struct defaultFont // why is twice ?
    {
        double fontSize;
        QString fontName;
        bool fontBold;

        bool operator==(const defaultFont& _font) const
        {
            return std::tie(
                        fontSize,
                        fontName,
                        fontBold
                        ) == std::tie(
                        _font.fontSize,
                        _font.fontName,
                        _font.fontBold);

        };
    };


    struct roshettaFont
    {
        int fontSize=10;
        QString fontName="tahoma";
        bool fontBold=false;
        bool italic=false;
        bool operator==(const roshettaFont& _font) const
        {
            return std::tie(
                        fontSize,
                        fontName,
                        fontBold,
                        italic
                        ) == std::tie(
                        _font.fontSize,
                        _font.fontName,
                        _font.fontBold,
                        _font.italic);

        };
    };

    enum drugsPrintMode{
        visitOnly=0,baseOnly=1,both=2
    };
    struct prescriptionPrintSettings
    {
        QString paperSizeId="A5";
        int pageMargin=5;
        bool showBanner=true;
        bool showDrugs=true;
        bool showInvestigations=true;
        bool showMeasurments=true;
        bool showDrugsTableOutline=true;
        drugsPrintMode drugsPrintMode=drugsPrintMode::visitOnly;
        bool showDrugsTitle=true;
        bool showPrescriptionHeaderFooterLogo=true;
        int logoSize=72;

        int headerHeightPercent=10;
        int footerHeightPercent=5;
        int bannerHeightPercent=5;

        struct roshettaFont doseFont{10,"Tahoma",false,false};
        struct roshettaFont bannerFont{10,"Tahoma",false,false};
        struct roshettaFont roshettaFont{10,"Tahoma",false,false};
        struct roshettaFont requestsFont{10,"Tahoma",false,false};
        struct roshettaFont measurementsFont{10,"Tahoma",false,false};


        bool showDrugsInitDate=true;
        bool showSignaturePrintedOn=true;

        bool showOnlyNewlyModifiedAddedDrugs=false;
        bool showTradeNamesBold=false;
        bool showDoseNewLine=true;

        bool preferArabic=true;
        bool showStartDate=true;

        bool operator==(const prescriptionPrintSettings& prescriptionprintsettings) const
        {
            return std::tie(paperSizeId,
                            pageMargin,
                            showBanner,
                            showDrugs,
                            showInvestigations,
                            showMeasurments,
                            showDrugsTableOutline,
                            drugsPrintMode,
                            showDrugsTitle,
                            showPrescriptionHeaderFooterLogo,
                            logoSize,
                            headerHeightPercent,
                            footerHeightPercent,
                            bannerHeightPercent,
                            bannerFont,
                            roshettaFont,
                            doseFont,
                            requestsFont,
                            measurementsFont,
                            showDrugsInitDate,
                            showSignaturePrintedOn,
                            showOnlyNewlyModifiedAddedDrugs,
                            showTradeNamesBold,
                            showDoseNewLine,
                            preferArabic,
                            showStartDate
                            ) == std::tie(
                        prescriptionprintsettings.paperSizeId,
                        prescriptionprintsettings.pageMargin,
                        prescriptionprintsettings.showBanner,
                        prescriptionprintsettings.showDrugs,
                        prescriptionprintsettings.showInvestigations,
                        prescriptionprintsettings.showMeasurments,
                        prescriptionprintsettings.showDrugsTableOutline,
                        prescriptionprintsettings.drugsPrintMode,
                        prescriptionprintsettings.showDrugsTitle,
                        prescriptionprintsettings.showPrescriptionHeaderFooterLogo,
                        prescriptionprintsettings.logoSize,
                        prescriptionprintsettings.headerHeightPercent,
                        prescriptionprintsettings.footerHeightPercent,
                        prescriptionprintsettings.bannerHeightPercent,
                        prescriptionprintsettings.bannerFont,
                        prescriptionprintsettings.roshettaFont,
                        prescriptionprintsettings.doseFont,
                        prescriptionprintsettings.requestsFont,
                        prescriptionprintsettings.measurementsFont,
                        prescriptionprintsettings.showDrugsInitDate,
                        prescriptionprintsettings.showSignaturePrintedOn,
                        prescriptionprintsettings.showOnlyNewlyModifiedAddedDrugs,
                        prescriptionprintsettings.showTradeNamesBold,
                        prescriptionprintsettings.showDoseNewLine,
                        prescriptionprintsettings.preferArabic,
                        prescriptionprintsettings.showStartDate); }
    };
    struct lineStyle
    {
        QString errorStylesheet;
        QString warningStylesheet;
        QString normalStylesheet;
    };
    static mSettings &instance();
    void saveSettings(const pSettings &psets);
    pSettings readSettings();
    QString themeMaker();
    double getVisitPrice(int visitType);
    mSettings::clinicPrices getClinicPrices();
    checkout getCheckout();
    void setCheckout(qint64 date, qint64 time);
    prescriptionPrintSettings getPrintSettings(QString printProfile);
    void savePrintSettings(prescriptionPrintSettings mPageSettings,QString printProfile);
    bool isAutoCompleteByWord();
    int userSpeciality();
    bool showChronicBox();
    bool showNavigation();
    bool isMinimizedToTray();
    bool getScreenMode();
    bool isVisualEffectsEnabled();
    bool isAlwaysSave();
    bool isAutoSave();
    bool alwaysClosePrintDlgAfterClick();
    bool isUpdateNotify();
    bool isUseToast();
    bool isUseNativePhotoViewer();
    bool isRemmberlastFollowupDate();
    int getAutoSaveInterval();
    QString getSelectedTheme();
    bool isInLinePatientList();
    bool isSimpleExamination();
    int getMaxFollowUps();
    int getMaxFollowUpsPerProblem();
    bool autoSetNewAfterMaxFollowUpsPerProblem();
    textboxFont getTextboxFont();
    defaultFont getDefaultFont();
    bool isDeviceBlocked();
    bool isDeviceActivated();
    dbOptions readDbOptions();
    void saveDbOptions(const dbOptions &options);
    mStyler::Style &getStyle();
    lineStyle getLineStylesheet();

public slots:
    void setSelectedTheme(QString t);
private:
    mSettings();
    mSettings(const mSettings&);
    ~mSettings();
    mSettings & operator = (const mSettings&);
    mStyler styler;
    dbOptions dboptions;
    pSettings psettings;
    bool dbOptionsInit=false;
};

#endif // MSETTINGS_H
