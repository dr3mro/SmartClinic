// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "msettings.h"
mSettings &mSettings::instance()
{
    static mSettings s_instance;
    return s_instance;
}

void mSettings::saveSettings(mSettings::pSettings &psets)
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

double mSettings::getVisitPrice(int visitType)
{
    double price = 0;
    clinicPrices prices = getClinicPrices();

    if ( visitType > getMaxFollowUpsPerProblem())
        return 0;

    switch (visitType)
    {
    case 0:
        price = prices.newVisit;
        break;
    case 1:
        price = prices.followUp1;
        break;
    case 2:
        price = prices.followUp2;
        break;
    case 3:
        price = prices.followUp3;
        break;
    case 4:
        price = prices.followUp4;
        break;
    default:
        break;
    }
    return price;
}

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
    //mPageSettings.color = settings.value(_inkColor,QVariant("#000000")).toString();
    mPageSettings.bold = settings.value(_inkBold,QVariant(false)).toBool();
    mPageSettings.font = settings.value(_inkFont,QVariant("Tahoma")).toString();
    mPageSettings.point = settings.value(_inkPoint,QVariant(8)).toInt();
    //mPageSettings.pageOrientation = settings.value(_printOrientation,QVariant(0)).toInt();
    mPageSettings.topMargin = settings.value(_topMargin,QVariant(0)).toDouble();
    mPageSettings.leftMargin = settings.value(_leftMargin,QVariant(0)).toDouble();
    mPageSettings.rightMargin = settings.value(_rightMargin,QVariant(0)).toDouble();
    mPageSettings.bottomMargin = settings.value(_bottomMargin,QVariant(0)).toDouble();
    mPageSettings.pageWidth = settings.value(_pageWidth,QVariant(7)).toDouble();
    mPageSettings.pageHeight = settings.value(_pageHeight,QVariant(9)).toDouble();
    mPageSettings.tradeNameinBold = settings.value(_tradeNameinBold,QVariant(false)).toBool();
    mPageSettings.doseinNewLine = settings.value(_doseinNewLine,QVariant(true)).toBool();
    mPageSettings.compactMode = settings.value(_compactMode,QVariant(false)).toBool();
    mPageSettings.noQty = settings.value(_noQty,QVariant(true)).toBool();
    mPageSettings.dietLeftPadding = settings.value(_dietLeftPadding,QVariant(0)).toDouble();
    mPageSettings.dietTopPadding = settings.value(_dietTopPadding,QVariant(0)).toDouble();
    mPageSettings.drugsColPerc = settings.value(_drugsColPerc,QVariant(30)).toDouble();
    mPageSettings.invPad = settings.value(_invPad,QVariant(0)).toDouble();
    mPageSettings.showInvestigations = settings.value(_showInvs,QVariant(true)).toBool();
    mPageSettings.dietWidth = settings.value(_dietWidth,QVariant(1)).toDouble();
    mPageSettings.showDrugs = settings.value(_showDrugs,QVariant(true)).toBool();
    mPageSettings.centerRequests = settings.value(_centerRequests,QVariant(false)).toBool();
    mPageSettings.centerDrugs = settings.value(_centerDrugs,QVariant(false)).toBool();
    mPageSettings.showBanner = settings.value(_showBanner,QVariant(true)).toBool();
    mPageSettings.showDrugsSeparator = settings.value(_showDrugsSeparator,QVariant(false)).toBool();
    //mPageSettings.fullPage = settings.value(_fullPage,QVariant(false)).toBool();
    mPageSettings.bannerWidth = settings.value(_bannerWidth,QVariant(80)).toInt();
    mPageSettings.investigationsWidth = settings.value(_investigationsWidth,QVariant(1.2)).toDouble();
    mPageSettings.showDrugsTitle = settings.value(_showDrugsTitle,QVariant(false)).toBool();
    mPageSettings.setEastArabicNumbers = settings.value(_setEastArabicNumbers,QVariant(false)).toBool();
    mPageSettings.showPrescriptionHeaderFooterLogo = settings.value(_showHeaderFooterLogo,QVariant(false)).toBool();
    mPageSettings.logoSize = settings.value(_logoSize,QVariant(64)).toInt();
    settings.endGroup();
    return mPageSettings;
}

void mSettings::savePrintSettings(mSettings::prescriptionPrintSettings mPageSettings, QString printProfile)
{
    QSettings settings("./settings.ini",QSettings::IniFormat);
    settings.beginGroup(printProfile);
    //settings.setValue(_inkColor,mPageSettings.color);
    settings.setValue(_inkBold,mPageSettings.bold);
    settings.setValue(_inkFont,mPageSettings.font);
    settings.setValue(_inkPoint,mPageSettings.point);
    //settings.setValue(_printOrientation,mPageSettings.pageOrientation);
    settings.setValue(_leftMargin,mPageSettings.leftMargin);
    settings.setValue(_rightMargin,mPageSettings.rightMargin);
    settings.setValue(_topMargin,mPageSettings.topMargin);
    settings.setValue(_bottomMargin,mPageSettings.bottomMargin);
    settings.setValue(_pageWidth,mPageSettings.pageWidth);
    settings.setValue(_pageHeight,mPageSettings.pageHeight);
    settings.setValue(_tradeNameinBold,mPageSettings.tradeNameinBold);
    settings.setValue(_doseinNewLine,mPageSettings.doseinNewLine);
    settings.setValue(_compactMode,mPageSettings.compactMode);
    settings.setValue(_noQty,mPageSettings.noQty);
    settings.setValue(_dietLeftPadding,mPageSettings.dietLeftPadding);
    settings.setValue(_dietTopPadding,mPageSettings.dietTopPadding);
    settings.setValue(_drugsColPerc,mPageSettings.drugsColPerc);
    settings.setValue(_invPad,mPageSettings.invPad);
    settings.setValue(_showInvs,mPageSettings.showInvestigations);
    settings.setValue(_dietWidth,mPageSettings.dietWidth);
    settings.setValue(_showDrugs,mPageSettings.showDrugs);
    settings.setValue(_centerRequests,mPageSettings.centerRequests);
    settings.setValue(_centerDrugs,mPageSettings.centerDrugs);
    settings.setValue(_showBanner,mPageSettings.showBanner);
    settings.setValue(_showDrugsSeparator,mPageSettings.showDrugsSeparator);
    //settings.setValue(_fullPage,mPageSettings.fullPage);
    settings.setValue(_bannerWidth,mPageSettings.bannerWidth);
    settings.setValue(_investigationsWidth,mPageSettings.investigationsWidth);
    settings.setValue(_showDrugsTitle,mPageSettings.showDrugsTitle);
    settings.setValue(_setEastArabicNumbers,mPageSettings.setEastArabicNumbers);
    settings.setValue(_showHeaderFooterLogo,mPageSettings.showPrescriptionHeaderFooterLogo);
    settings.setValue(_logoSize,mPageSettings.logoSize);
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
    mStyler::Style & style = getStyle();
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
