// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MSETTINGS_H
#define MSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QApplication>
#include "mdebug.h"
#include "globalvariables.h"
#include "staticstrings.h"
#include "mstyler.h"

class mSettings : public QObject
{
    Q_OBJECT
public:
    // this is data structure to hold the vitals for printing

    struct Vitals{
        int pulse;
        QString BP;
        int RR;
        double T;
        double weight;
        double height;
        int sPo2;
        int RBS;

        void clear(){
            pulse=-1;
            BP="-1";
            RR=-1;
            T=-1;;
            weight=-1;
            height=-1;
            sPo2=-1;
            RBS=-1;
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
            if(RBS != 0)
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

    // this is data structure to hold the roshetta for printing
    struct Roshetta
    {
        QString getVisitSymbole(const int & _i){
            QStringList visitSymbole = QStringList() << "Ⓝ" << "①" << "②" << "③" << "④" << "Ⓕ";
            return visitSymbole.at(_i);
        }

        QString ID;
        QString name;
        QString printableAge;
        QString Diagnosis;
        Vitals vitals;
        QString visitDate;
        QString printedinDate;
        QString nextDate;
        QString visitSymbole;
        QList<drug> currentDrugsList;
        QList<drug> baseDrugsList;
        QStringList requests;
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
        int fontSize;
        QString fontName;
        bool fontBold;
        bool italic;
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
        QString paperSizeId;
        double pageMargin;
        bool showBanner;
        bool showDrugs;
        bool showInvestigations;
        bool showMeasurments;
        bool showDrugsSeparator;
        drugsPrintMode drugsPrintMode;
        bool showDrugsTitle;
        bool showPrescriptionHeaderFooterLogo;
        int logoSize;

        int headerHeightPercent;
        int footerHeightPercent;
        int bannerHeightPercent;
        roshettaFont bannerFont;
        roshettaFont roshettaFont;
        bool showDrugsInitDate;
        bool showSignaturePrintedOn;

        bool operator==(const prescriptionPrintSettings& prescriptionprintsettings) const
        {
            return std::tie(paperSizeId,
                            pageMargin,
                            showBanner,
                            showDrugs,
                            showInvestigations,
                            showMeasurments,
                            showDrugsSeparator,
                            drugsPrintMode,
                            showDrugsTitle,
                            showPrescriptionHeaderFooterLogo,
                            logoSize,
                            headerHeightPercent,
                            footerHeightPercent,
                            bannerHeightPercent,
                            bannerFont,
                            roshettaFont,
                            showDrugsInitDate,
                            showSignaturePrintedOn
                            ) == std::tie(
                        prescriptionprintsettings.paperSizeId,
                        prescriptionprintsettings.pageMargin,
                        prescriptionprintsettings.showBanner,
                        prescriptionprintsettings.showDrugs,
                        prescriptionprintsettings.showInvestigations,
                        prescriptionprintsettings.showMeasurments,
                        prescriptionprintsettings.showDrugsSeparator,
                        prescriptionprintsettings.drugsPrintMode,
                        prescriptionprintsettings.showDrugsTitle,
                        prescriptionprintsettings.showPrescriptionHeaderFooterLogo,
                        prescriptionprintsettings.logoSize,
                        prescriptionprintsettings.headerHeightPercent,
                        prescriptionprintsettings.footerHeightPercent,
                        prescriptionprintsettings.bannerHeightPercent,
                        prescriptionprintsettings.bannerFont,
                        prescriptionprintsettings.roshettaFont,
                        prescriptionprintsettings.showDrugsInitDate,
                        prescriptionprintsettings.showSignaturePrintedOn); }
    };
    struct lineStyle
    {
        QString errorStylesheet;
        QString warningStylesheet;
        QString normalStylesheet;
    };
    static mSettings &instance();
    void saveSettings(pSettings &psets);
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
