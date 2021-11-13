// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "msettings.h"
#include "datahelper.h"

mSettings &mSettings::instance()
{
    static mSettings s_instance;
    return s_instance;
}

void mSettings::saveSettings(const mSettings::pSettings &psets)
{
    QSettings && settings = QSettings("./settings.ini",QSettings::IniFormat);
    psettings = psets;
    settings.setValue(_speciality,psettings.speciality);
    settings.setValue(_autoCompleteByWord,psettings.autoCompleteByWord);
    settings.setValue(_showChronicConditions,psettings.showChronicConditions);
    settings.setValue(_showNavArrows,psettings.showNavArrows);
    settings.setValue(_smallScreenMode,psettings.smallScreenMode);
    settings.setValue(_simpleExamination,psettings.simpleExamination);
    settings.setValue(_alwaysSave,psettings.alwaysSave);
    settings.setValue(_inLinePatientList,psettings.inLinePatientList);
    settings.setValue(_autosaveinterval,psettings.autosaveinterval);
    settings.setValue(_autoSave,psettings.autoSave);
    settings.setValue(_minimizeToTray,psettings.minimizeToTray);
    settings.setValue(_enableVisualEffects,psettings.enableVisualEffects);
    settings.setValue(_autoClosePrintDlg,psettings.autoClosePrintDlg);
    settings.setValue(_updateNotify,psettings.updateNotify);
    settings.setValue(_useToast,psettings.useToast);
    settings.setValue(_usePhotoViewer,psettings.usePhotoViewer);
    settings.setValue(_remmberLastFollowupDate,psettings.remmberLastFollowupDate);
    settings.setValue(_selectedTheme,psettings.selectedTheme);

    settings.beginGroup(_clinic);
    settings.setValue(_maxFollowUps,psettings.maxFollowUps);
    settings.setValue(_maxFollowUpsPerProblem,psettings.maxFollowUpsPerProblem);
    settings.setValue(_autoSetnewAfterMaxPerProblemIsReached,psettings.autoSetnewAfterMaxPerProblemIsReached);
    settings.setValue(_workingDays,psettings.workingdays);
    settings.endGroup();

    settings.beginGroup(_Prices);
    settings.setValue(_newVisitPrice,psettings.newVisitPrice);
    settings.setValue(_followVisitprice1,psettings.followVisitprice1);
    settings.setValue(_followVisitprice2,psettings.followVisitprice2);
    settings.setValue(_followVisitprice3,psettings.followVisitprice3);
    settings.setValue(_followVisitprice4,psettings.followVisitprice4);
    settings.endGroup();

    settings.beginGroup(_Fonts);
    settings.setValue(_defaultFont,psettings.defaultFont);
    settings.setValue(_defaultFontSize,psettings.defaultFontSize);
    settings.setValue(_defaultFontBold,psettings.defaultFontBold);
    settings.setValue(_textboxFont,psettings.textboxFont);
    settings.setValue(_textboxFontSize,psettings.textboxFontSize);
    settings.setValue(_textboxFontBold,psettings.textboxFontBold);
    settings.endGroup();
}

mSettings::pSettings mSettings::readSettings()
{
    QSettings settings("./settings.ini",QSettings::IniFormat);
    psettings.speciality = settings.value(_speciality,QVariant(0)).toInt();
    psettings.autoCompleteByWord = settings.value(_autoCompleteByWord,QVariant(true)).toBool();
    psettings.showChronicConditions = settings.value(_showChronicConditions,QVariant(true)).toBool();
    psettings.showNavArrows = settings.value(_showNavArrows,QVariant(true)).toBool();
    psettings.smallScreenMode = settings.value(_smallScreenMode,QVariant(false)).toBool();
    psettings.simpleExamination = settings.value(_simpleExamination,QVariant(false)).toBool();
    psettings.alwaysSave = settings.value(_alwaysSave,QVariant(true)).toBool();
    psettings.inLinePatientList = settings.value(_inLinePatientList,QVariant(true)).toBool();
    psettings.autosaveinterval = settings.value(_autosaveinterval,QVariant(60)).toInt();
    psettings.autoSave = settings.value(_autoSave,QVariant(true)).toBool();
    psettings.minimizeToTray = settings.value(_minimizeToTray,QVariant(true)).toBool();
    psettings.autoClosePrintDlg = settings.value(_autoClosePrintDlg,QVariant(true)).toBool();
    psettings.enableVisualEffects = settings.value(_enableVisualEffects,QVariant(false)).toBool();
    psettings.updateNotify = settings.value(_updateNotify,QVariant(true)).toBool();
    psettings.useToast = settings.value(_useToast,QVariant(true)).toBool();
    psettings.usePhotoViewer = settings.value(_usePhotoViewer,QVariant(true)).toBool();
    psettings.remmberLastFollowupDate = settings.value(_remmberLastFollowupDate,QVariant(false)).toBool();
    psettings.selectedTheme = settings.value(_selectedTheme).toString();

    settings.beginGroup(_clinic);
    psettings.maxFollowUps = settings.value(_maxFollowUps,QVariant(7)).toInt();
    psettings.maxFollowUpsPerProblem = settings.value(_maxFollowUpsPerProblem,QVariant(4)).toInt();
    psettings.autoSetnewAfterMaxPerProblemIsReached = settings.value(_autoSetnewAfterMaxPerProblemIsReached,QVariant(false)).toBool();
    psettings.workingdays = settings.value(_workingDays,QVariant(222)).toInt();//friday

    settings.endGroup();

    settings.beginGroup(_Prices);
    psettings.newVisitPrice = settings.value(_newVisitPrice).toDouble();
    psettings.followVisitprice1 = settings.value(_followVisitprice1).toDouble();
    psettings.followVisitprice2 = settings.value(_followVisitprice2).toDouble();
    psettings.followVisitprice3 = settings.value(_followVisitprice3).toDouble();
    psettings.followVisitprice4 = settings.value(_followVisitprice4).toDouble();
    settings.endGroup();

    settings.beginGroup(_Fonts);
    psettings.defaultFont = settings.value(_defaultFont,QVariant("Tahome")).toString();
    psettings.defaultFontSize = settings.value(_defaultFontSize,QVariant(8)).toDouble();
    psettings.defaultFontBold = settings.value(_defaultFontBold,QVariant(false)).toBool();
    psettings.textboxFont = settings.value(_textboxFont,QVariant("Tahoma")).toString();
    psettings.textboxFontSize = settings.value(_textboxFontSize,QVariant(8)).toDouble();
    psettings.textboxFontBold = settings.value(_textboxFontBold,QVariant(false)).toBool();
    settings.endGroup();

    return psettings;
}

QString mSettings::themeMaker()
{
    styler.setStyle(getSelectedTheme());
    return styler.getStyleSheet();
}

//double mSettings::getVisitPrice(int visitType)
//{
//    double price = 0;
//    clinicPrices prices = getClinicPrices();

//    if ( visitType > getMaxFollowUpsPerProblem())
//        return 0;

//    switch (visitType)
//    {
//    case 0:
//        price = prices.newVisit;
//        break;
//    case 1:
//        price = prices.followUp1;
//        break;
//    case 2:
//        price = prices.followUp2;
//        break;
//    case 3:
//        price = prices.followUp3;
//        break;
//    case 4:
//        price = prices.followUp4;
//        break;
//    default:
//        break;
//    }
//    return price;
//}

mSettings::clinicPrices mSettings::getClinicPrices()
{
    clinicPrices prices;
    prices.newVisit = psettings.newVisitPrice;
    prices.followUp1 = psettings.followVisitprice1;
    prices.followUp2 = psettings.followVisitprice2;
    prices.followUp3 = psettings.followVisitprice3;
    prices.followUp4 = psettings.followVisitprice4;
    return prices;
}

mSettings::checkout mSettings::getCheckout()
{
    checkout chkout;
    QSettings settings("./settings.ini",QSettings::IniFormat);
    settings.beginGroup(_checkOut);
    chkout.date = settings.value(_checkoutDate).toInt();
    chkout.time = settings.value(_checkoutTime).toInt();
    settings.endGroup();
    return chkout;
}

void mSettings::setCheckout(qint64 date, qint64 time)
{
    QSettings settings("./settings.ini",QSettings::IniFormat);
    settings.beginGroup(_checkOut);
    settings.setValue(_checkoutDate,date);
    settings.setValue(_checkoutTime,time);
    settings.endGroup();
}

mSettings::prescriptionPrintSettings mSettings::getPrintSettings(QString printProfile)
{
    prescriptionPrintSettings mPageSettings;
    QSettings settings("./settings.ini",QSettings::IniFormat);
    settings.beginGroup(printProfile);
    mPageSettings.paperSizeId = settings.value(_paperSizeId,QVariant("A5")).toString();
    mPageSettings.pageMargin = settings.value(_pageMargin,QVariant(5)).toDouble();
    mPageSettings.showBanner = settings.value(_showBanner,QVariant(true)).toBool();
    mPageSettings.showDrugs = settings.value(_showDrugs,QVariant(true)).toBool();
    mPageSettings.showInvestigations = settings.value(_showInvsestigations,QVariant(true)).toBool();
    mPageSettings.showMeasurments = settings.value(_showMeasurments,QVariant(true)).toBool();
    mPageSettings.showDrugsTableOutline = settings.value(_showDrugsTableOutline,QVariant(false)).toBool();
    mPageSettings.drugsPrintMode = (mSettings::drugsPrintMode) settings.value(_drugsPrintMode,QVariant(0)).toInt();
    mPageSettings.showDrugsTitle = settings.value(_showDrugsTitle,QVariant(false)).toBool();

    mPageSettings.showPrescriptionHeader = settings.value(_showHeader,QVariant(false)).toBool();
    mPageSettings.showPrescriptionFooter = settings.value(_showFooter,QVariant(false)).toBool();
    mPageSettings.showPrescriptionLogo = settings.value(_showLogo,QVariant(false)).toBool();
    mPageSettings.prescriptionBannerStyle = static_cast<mSettings::bannerStyle>(settings.value(_bannerStyle,QVariant(0)).toInt());

    mPageSettings.logoSize = settings.value(_logoSize,QVariant(64)).toInt();

    mPageSettings.headerHeightPercent = settings.value(_headerHeightPercent,QVariant(10)).toInt();
    mPageSettings.footerHeightPercent = settings.value(_footerHeightPercent,QVariant(5)).toInt();
    mPageSettings.bannerHeightPercent = settings.value(_bannerHeightPercent,QVariant(5)).toInt();

    mPageSettings.bannerFont.fontName = settings.value(_bannerFont,QVariant("Tahoma")).toString();
    mPageSettings.bannerFont.fontSize = settings.value(_bannerFontSize,QVariant(8)).toInt();
    mPageSettings.bannerFont.fontBold = settings.value(_bannerFontBold,QVariant(false)).toBool();

    mPageSettings.roshettaFont.fontName = settings.value(_roshettaFont,QVariant("Tahoma")).toString();
    mPageSettings.roshettaFont.fontSize = settings.value(_roshettaFontSize,QVariant(8)).toInt();
    mPageSettings.roshettaFont.fontBold = settings.value(_roshettaFontBold,QVariant(false)).toBool();

    mPageSettings.doseFont.fontName = settings.value(_doseFont,QVariant("Tahoma")).toString();
    mPageSettings.doseFont.fontSize = settings.value(_doseFontSize,QVariant(8)).toInt();
    mPageSettings.doseFont.fontBold = settings.value(_doseFontBold,QVariant(false)).toBool();

    mPageSettings.requestsFont.fontName = settings.value(_requestsFont,QVariant("Tahoma")).toString();
    mPageSettings.requestsFont.fontSize = settings.value(_requestsFontSize,QVariant(8)).toInt();
    mPageSettings.requestsFont.fontBold = settings.value(_requestsFontBold,QVariant(false)).toBool();

    mPageSettings.measurementsFont.fontName = settings.value(_measurementsFont,QVariant("Tahoma")).toString();
    mPageSettings.measurementsFont.fontSize = settings.value(_measurementsFontSize,QVariant(8)).toInt();
    mPageSettings.measurementsFont.fontBold = settings.value(_measurementsFontBold,QVariant(false)).toBool();

    mPageSettings.signatureFont.fontName = settings.value(_signatureFont,QVariant("Tahoma")).toString();
    mPageSettings.signatureFont.fontSize = settings.value(_signatureFontSize,QVariant(8)).toInt();
    mPageSettings.signatureFont.fontBold = settings.value(_signatureFontBold,QVariant(false)).toBool();

    mPageSettings.showDrugsInitDate = settings.value(_showDrugsInitDate,QVariant(true)).toBool();
    mPageSettings.showSignaturePrintedOn = settings.value(_showSignaturePrintedOn,QVariant(true)).toBool();

    mPageSettings.showOnlyNewlyModifiedAddedDrugs = settings.value(_showOnlyNewlyModifiedAddedDrugs,QVariant(false)).toBool();
    mPageSettings.showTradeNamesBold = settings.value(_showTradeNamesBold,QVariant(false)).toBool();
    mPageSettings.showDoseNewLine = settings.value(_showDoseNewLine,QVariant(false)).toBool();

    mPageSettings.preferArabic = settings.value(_preferArabic,QVariant(true)).toBool();
    //mPageSettings.showStartDate = settings.value(_showStartDate,QVariant(true)).toBool();
    //mPageSettings.showHorizontalLineBelowHeader = settings.value(_showHorizontalLineBelowHeader,QVariant(false)).toBool();
    mPageSettings.enableFullPage = settings.value(_enableFullPage,QVariant(false)).toBool();
    mPageSettings.enableBodyHeaderSeparator = settings.value(_enableBodyHeaderSeparator,QVariant(false)).toBool();
    mPageSettings.compactMode = settings.value(_compactMode,QVariant(true)).toBool();
    mPageSettings.clearDuplicateDrugs = settings.value(_clearDuplicateDrugs,QVariant(false)).toBool();
    settings.endGroup();
    return mPageSettings;
}

void mSettings::savePrintSettings(mSettings::prescriptionPrintSettings mPageSettings, QString printProfile)
{
    QSettings settings("./settings.ini",QSettings::IniFormat);
    settings.beginGroup(printProfile);
    settings.setValue(_paperSizeId,mPageSettings.paperSizeId);
    settings.setValue(_pageMargin,mPageSettings.pageMargin);
    settings.setValue(_showBanner,mPageSettings.showBanner);
    settings.setValue(_showDrugs,mPageSettings.showDrugs);
    settings.setValue(_showInvsestigations,mPageSettings.showInvestigations);
    settings.setValue(_showMeasurments,mPageSettings.showMeasurments);
    settings.setValue(_showDrugsTableOutline,mPageSettings.showDrugsTableOutline);
    settings.setValue(_drugsPrintMode,mPageSettings.drugsPrintMode);
    settings.setValue(_showDrugsTitle,mPageSettings.showDrugsTitle);

    settings.setValue(_showHeader,mPageSettings.showPrescriptionHeader);
    settings.setValue(_showFooter,mPageSettings.showPrescriptionFooter);
    settings.setValue(_showLogo,mPageSettings.showPrescriptionLogo);

    settings.setValue(_bannerStyle,mPageSettings.prescriptionBannerStyle);

    settings.setValue(_logoSize,mPageSettings.logoSize);

    settings.setValue(_headerHeightPercent,mPageSettings.headerHeightPercent);
    settings.setValue(_footerHeightPercent,mPageSettings.footerHeightPercent);
    settings.setValue(_bannerHeightPercent,mPageSettings.bannerHeightPercent);

    settings.setValue(_bannerFont,mPageSettings.bannerFont.fontName);
    settings.setValue(_bannerFontSize,mPageSettings.bannerFont.fontSize);
    settings.setValue(_bannerFontBold,mPageSettings.bannerFont.fontBold);

    settings.setValue(_roshettaFont,mPageSettings.roshettaFont.fontName);
    settings.setValue(_roshettaFontSize,mPageSettings.roshettaFont.fontSize);
    settings.setValue(_roshettaFontBold,mPageSettings.roshettaFont.fontBold);

    settings.setValue(_doseFont,mPageSettings.doseFont.fontName);
    settings.setValue(_doseFontSize,mPageSettings.doseFont.fontSize);
    settings.setValue(_doseFontBold,mPageSettings.doseFont.fontBold);

    settings.setValue(_requestsFont,mPageSettings.requestsFont.fontName);
    settings.setValue(_requestsFontSize,mPageSettings.requestsFont.fontSize);
    settings.setValue(_requestsFontBold,mPageSettings.requestsFont.fontBold);

    settings.setValue(_measurementsFont,mPageSettings.measurementsFont.fontName);
    settings.setValue(_measurementsFontSize,mPageSettings.measurementsFont.fontSize);
    settings.setValue(_measurementsFontBold,mPageSettings.measurementsFont.fontBold);

    settings.setValue(_signatureFont,mPageSettings.signatureFont.fontName);
    settings.setValue(_signatureFontSize,mPageSettings.signatureFont.fontSize);
    settings.setValue(_signatureFontBold,mPageSettings.signatureFont.fontBold);

    settings.setValue(_showDrugsInitDate,mPageSettings.showDrugsInitDate);
    settings.setValue(_showSignaturePrintedOn,mPageSettings.showSignaturePrintedOn);

    settings.setValue(_showOnlyNewlyModifiedAddedDrugs,mPageSettings.showOnlyNewlyModifiedAddedDrugs);
    settings.setValue(_showTradeNamesBold,mPageSettings.showTradeNamesBold);
    settings.setValue(_showDoseNewLine,mPageSettings.showDoseNewLine);

    settings.setValue(_preferArabic,mPageSettings.preferArabic);
    //settings.setValue(_showStartDate,mPageSettings.showStartDate);
    //settings.setValue(_showHorizontalLineBelowHeader,mPageSettings.showHorizontalLineBelowHeader);
    settings.setValue(_enableFullPage,mPageSettings.enableFullPage);
    settings.setValue(_enableBodyHeaderSeparator,mPageSettings.enableBodyHeaderSeparator);
    settings.setValue(_compactMode,mPageSettings.compactMode);
    settings.setValue(_clearDuplicateDrugs,mPageSettings.clearDuplicateDrugs);
    settings.endGroup();
}

bool mSettings::isAutoCompleteByWord()
{
    return psettings.autoCompleteByWord;
}

int mSettings::userSpeciality()
{
    return psettings.speciality;
}

bool mSettings::showChronicBox()
{
    return psettings.showChronicConditions;
}

bool mSettings::showNavigation()
{
    return psettings.showNavArrows;
}

bool mSettings::isMinimizedToTray()
{
    return psettings.minimizeToTray;
}

bool mSettings::getScreenMode()
{
    return psettings.smallScreenMode;
}

bool mSettings::isVisualEffectsEnabled()
{
    return psettings.enableVisualEffects;
}

bool mSettings::isAlwaysSave()
{
    return psettings.alwaysSave;
}

bool mSettings::isAutoSave()
{
    return psettings.autoSave;
}

bool mSettings::alwaysClosePrintDlgAfterClick()
{
    return psettings.autoClosePrintDlg;
}

bool mSettings::isUpdateNotify()
{
    return psettings.updateNotify;
}

bool mSettings::isUseToast()
{
    return psettings.useToast;
}

bool mSettings::isUseNativePhotoViewer()
{
  return psettings.usePhotoViewer;
}

bool mSettings::isRemmberlastFollowupDate()
{
    return  psettings.remmberLastFollowupDate;
}

int mSettings::getWorkingDays() const
{
    return psettings.workingdays;
}

int mSettings::getAutoSaveInterval()
{
    return psettings.autosaveinterval;
}

QString mSettings::getSelectedTheme()
{
    QString selectedTheme = psettings.selectedTheme;
    if(!styler.getNonPackagedThemes().contains(selectedTheme))
        selectedTheme = styler.getPackagedThemes().at(0);
    return selectedTheme;
}

void mSettings::setSelectedTheme(QString t)
{
    QSettings settings("./settings.ini",QSettings::IniFormat);
    settings.setValue(_selectedTheme,t);
    psettings.selectedTheme = t;
}

mSettings::mSettings()
{

}

bool mSettings::isInLinePatientList()
{
    return psettings.inLinePatientList;
}

bool mSettings::isSimpleExamination()
{
    return psettings.simpleExamination;
}

int mSettings::getMaxFollowUps()
{
    return psettings.maxFollowUps;
}

int mSettings::getMaxFollowUpsPerProblem()
{
    return psettings.maxFollowUpsPerProblem;
}

bool mSettings::autoSetNewAfterMaxFollowUpsPerProblem()
{
    return psettings.autoSetnewAfterMaxPerProblemIsReached;
}

mSettings::textboxFont mSettings::getTextboxFont()
{
    textboxFont tboxFont;
    tboxFont.fontName = psettings.textboxFont;
    tboxFont.fontSize = psettings.textboxFontSize;
    tboxFont.fontBold = psettings.textboxFontBold;
    return tboxFont;
}

mSettings::defaultFont mSettings::getDefaultFont()
{
    defaultFont defaultfont;
    defaultfont.fontName =  psettings.defaultFont;
    defaultfont.fontSize = psettings.defaultFontSize;
    defaultfont.fontBold = psettings.defaultFontBold;
    return defaultfont;
}

bool mSettings::isDeviceBlocked()
{
    QSettings reg(blockregPath,QSettings::NativeFormat);
    return reg.value(blockRegKey).toBool();
}

bool mSettings::isDeviceActivated()
{
    QSettings reg(blockregPath,QSettings::NativeFormat);
    return reg.value(activateRegKey).toBool();
}

mSettings::dbOptions mSettings::readDbOptions()
{
    if(dbOptionsInit)
        return dboptions;

    QSettings settings("./settings.ini",QSettings::IniFormat);
    settings.beginGroup(_dbOptions);
    dboptions.autovacuum = settings.value(_autovacuum,"NONE").toString();
    dboptions.optimize = settings.value(_optimize,false).toBool();
    dboptions.shrinkMem = settings.value(_shrinkMemory,false).toBool();
    dboptions.WAL_CheckPoint = settings.value(_WAL_checkPoint,"OFF").toString();
    dboptions.shared_cache = settings.value(_shared_cache,"SHARED").toString();
    dboptions.temp_store = settings.value(_temp_store,"DEFAULT").toString();
    dboptions.synchronous = settings.value(_synchronous,"NORMAL").toString();
    dboptions.journal_mode = settings.value(_journal_mode,"DELETE").toString();
    dboptions.locking_mode = settings.value(_locking_mode,"NORMAL").toString();
    dboptions.cache_size = settings.value(_cache_size,2000).toInt();
    dboptions.page_size = settings.value(_page_size,4096).toInt();
    settings.endGroup();
    dbOptionsInit = true;
    return dboptions;
}

void mSettings::saveDbOptions(const mSettings::dbOptions &options)
{
    QSettings settings("./settings.ini",QSettings::IniFormat);
    settings.beginGroup(_dbOptions);
    settings.setValue(_autovacuum,options.autovacuum);
    settings.setValue(_optimize,options.optimize);
    settings.setValue(_shrinkMemory,options.shrinkMem);
    settings.setValue(_WAL_checkPoint,options.WAL_CheckPoint);
    settings.setValue(_shared_cache,options.shared_cache);
    settings.setValue(_temp_store,options.temp_store);
    settings.setValue(_synchronous,options.synchronous);
    settings.setValue(_journal_mode,options.journal_mode);
    settings.setValue(_locking_mode,options.locking_mode);
    settings.setValue(_cache_size,options.cache_size);
    settings.setValue(_page_size,options.page_size);
    settings.endGroup();
    dboptions=options;
}

mSettings::~mSettings()
{
}

mStyler::Style &mSettings::getStyle()
{
    return styler.getLoadedStyle();
}

mSettings::lineStyle mSettings::getLineStylesheet()
{
    const mStyler::Style & style = getStyle();
    QString normalTextColor = style.inputText.color_normal;
    QString warningTextColor = style.inputText.color_warning;
    QString errorTextColor = style.inputText.color_error;
    QString normalBackgroundColor = style.input.color_normal;
    QString warningBackgroundColor = style.input.color_warning;
    QString errorBackgroundColor = style.input.color_error;

    lineStyle linestyle;

    linestyle.errorStylesheet = QString("QLineEdit{background-color: %1; color:%2;}").arg(errorBackgroundColor).arg(errorTextColor);
    linestyle.warningStylesheet = QString("QLineEdit{background-color: %1; color:%2;}").arg(warningBackgroundColor).arg(warningTextColor);
    linestyle.normalStylesheet = QString("QLineEdit{background-color: %1; color:%2;}").arg(normalBackgroundColor).arg(normalTextColor);

    return linestyle;
}

void mSettings::saveLastSelectedFollowUpDate(const QDate &date)
{
    QSettings settings("./settings.ini",QSettings::IniFormat);
    settings.beginGroup(_clinic);
    settings.setValue(_lastSelectedFollowUpDate,date.toJulianDay());
    settings.endGroup();
}

int mSettings::getLastSelectedFollowUpDate()
{
    QSettings settings("./settings.ini",QSettings::IniFormat);
    settings.beginGroup(_clinic);
    int lastSelectedFollowUpDate = settings.value(_lastSelectedFollowUpDate,QVariant(QDate::currentDate().toJulianDay())).toInt();
    settings.endGroup();
    return lastSelectedFollowUpDate;

}
