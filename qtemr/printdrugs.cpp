// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "printdrugs.h"
#include "ui_printdrugs.h"

printDrugs::printDrugs(QWidget *parent) :
    QDialog(parent),
    printer ( new QPrinter(QPrinter::HighResolution)),
    dlg ( new QPrintDialog(printer,this)),
    wm_add2completer(new wm_add2Completer),
    ui(new Ui::printDrugs)
{
    ui->setupUi(this);
    m_roshetta = ui->Roshetta->document();
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
    setMinimumSize(800,600);

    ui->fastPrint->setFocus(Qt::OtherFocusReason);

    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    ui->printerProfile->setCurrentIndex(reg.value("selectedPrintingProfile").toInt());

    t.setInterval(600);//this timer to set limit to printing per second
    connect(&t,SIGNAL(timeout()),&t,SLOT(stop()));

    selectedPrintingProfile = ui->printerProfile->currentText();
    lSettings = pSettings =  loadPrintSettings();

    connect(ui->printerProfile,QOverload<int>::of(&QComboBox::activated),this,&printDrugs::printerProfile_activated);
    connect(ui->showInvs,&Switch::clicked,this,&printDrugs::showInvs_clicked);
    connect(ui->drugsMode,QOverload<int>::of(&QComboBox::activated),this,&printDrugs::drugsMode_activated);
    connect(ui->drugsMode,QOverload<int>::of(&QComboBox::highlighted),this,&printDrugs::drugsMode_activated);
    connect(ui->bannerFontName,&QFontComboBox::textActivated,this,&printDrugs::bannerFontName_activated);
    connect(ui->bannerFontName,&QFontComboBox::textHighlighted,this,&printDrugs::bannerFontName_activated);
    connect(ui->bannerFontSize,&QComboBox::textActivated,this,&printDrugs::bannerFontSize_activated);
    connect(ui->bannerFontSize,&QComboBox::textHighlighted,this,&printDrugs::bannerFontSize_activated);
    connect(ui->bannerFontBold,&QToolButton::clicked,this,&printDrugs::bannerFontBold_clicked);

    connect(ui->roshettaFontName,&QFontComboBox::textActivated,this,&printDrugs::roshettaFontName_activated);
    connect(ui->roshettaFontName,&QFontComboBox::textHighlighted,this,&printDrugs::roshettaFontName_activated);
    connect(ui->roshettaFontSize,&QComboBox::textActivated,this,&printDrugs::roshettaFontSize_activated);
    connect(ui->roshettaFontSize,&QComboBox::textHighlighted,this,&printDrugs::roshettaFontSize_activated);
    connect(ui->roshettaFontBold,&QToolButton::clicked,this,&printDrugs::roshettaFontBold_clicked);

    connect(ui->doseFontName,&QFontComboBox::textActivated,this,&printDrugs::doseFontName_activated);
    connect(ui->doseFontName,&QFontComboBox::textHighlighted,this,&printDrugs::doseFontName_activated);
    connect(ui->doseFontSize,&QComboBox::textActivated,this,&printDrugs::doseFontSize_activated);
    connect(ui->doseFontSize,&QComboBox::textHighlighted,this,&printDrugs::doseFontSize_activated);
    connect(ui->doseFontBold,&QToolButton::clicked,this,&printDrugs::doseFontBold_clicked);

    connect(ui->headerHeightPercent,QOverload<int>::of(&QSpinBox::valueChanged),this,&printDrugs::headerHeightPercent_valueChanged);
    connect(ui->bannerHeightPercent,QOverload<int>::of(&QSpinBox::valueChanged),this,&printDrugs::bannerHeightPercent_valueChanged);
    connect(ui->footerHeightPercent,QOverload<int>::of(&QSpinBox::valueChanged),this,&printDrugs::footerHeightPercent_valueChanged);

    connect(ui->Header,&PagesTextEdit::textChanged,this,&printDrugs::header_textChanged);
    connect(ui->Footer,&PagesTextEdit::textChanged,this,&printDrugs::footer_textChanged);

    connect(ui->paperSizeId,&QComboBox::textActivated,this,&printDrugs::paperSizeId_activated);
    connect(ui->paperSizeId,&QComboBox::textHighlighted,this,&printDrugs::paperSizeId_activated);

    connect(ui->SignaturePrintedOn,&Switch::clicked,this,&printDrugs::SignaturePrintedOn_clicked);
    connect(ui->drugsInitDate,&Switch::clicked,this,&printDrugs::drugsInitDate_clicked);
    connect(ui->showHeaderFooterLogo,&Switch::clicked,this,&printDrugs::showHeaderFooterLogo_clicked);
    connect(ui->showDrugs,&Switch::clicked,this,&printDrugs::showDrugs_clicked);
    connect(ui->showMesurements,&Switch::clicked,this,&printDrugs::showMesurements_clicked);
    connect(ui->showDrugsTableOutline,&Switch::clicked,this,&printDrugs::showDrugsTableOutline_clicked);
    connect(ui->showDrugsTitle,&Switch::clicked,this,&printDrugs::showDrugsTitle_clicked);
    connect(ui->showBanner,&Switch::clicked,this,&printDrugs::showBanner_clicked);
    connect(ui->showOnlyNewlyModifiedAddedDrugs,&Switch::clicked,this,&printDrugs::showOnlyNewlyModifiedAddedDrugs_clicked);
    connect(ui->showTradeNamesBold,&Switch::clicked,this,&printDrugs::showTradeNamesBold_clicked);
    connect(ui->showDoseNewLine,&Switch::clicked,this,&printDrugs::showDoseNewLine_clicked);

    connect(ui->pageMargin,QOverload<int>::of(&QSpinBox::valueChanged),this,&printDrugs::pageMargin_valueChanged);
    connect(ui->logoSize,&QComboBox::textActivated,this,&printDrugs::logoSize_activated);
    connect(ui->logoSize,&QComboBox::textHighlighted,this,&printDrugs::logoSize_activated);

    connect(ui->ButtonRefresh,&QToolButton::clicked,this,&printDrugs::ButtonRefresh_clicked);
    connect(ui->lockUnlockButton,&QToolButton::toggled,this,&printDrugs::lockUnlockButton_toggled);

    this->setModal(true);
}

printDrugs::~printDrugs()
{
    delete printer;
    delete dlg;
    delete ui;
    delete wm_add2completer;
}

void printDrugs::showPrintDialog()
{
    setupPrinter(printer);
    if ( dlg->exec() == QDialog::Accepted )
        printDoc(printer,m_roshetta);
}

void printDrugs::showPrintPreviewDialog()
{
    mPrintPreviewDialog previewDialog(this);
    previewDialog.setWindowState(previewDialog.windowState() | Qt::WindowMaximized);
    connect(&previewDialog,SIGNAL(paintRequested(QPrinter*)),this,SLOT(makePrintPreview(QPrinter*)));
    previewDialog.exec();
}

void printDrugs::mPrint()
{
    pSettings = grabPrintSettings();
    applyPageSizeParamaters();
    refreshView();
    setupPrinter(printer);
    printDoc(printer,m_roshetta);
}

void printDrugs::savePrintSettings()
{
    if (!(lSettings == pSettings))  // check if settings have been changed or not
        settings.savePrintSettings(grabPrintSettings(),selectedPrintingProfile);// so dont cause useless writes to disk.
}

mSettings::prescriptionPrintSettings printDrugs::loadPrintSettings()
{
    mSettings::prescriptionPrintSettings printSettings = settings.getPrintSettings(selectedPrintingProfile);
    ui->paperSizeId->setCurrentText(printSettings.paperSizeId);
    ui->pageMargin->setValue(printSettings.pageMargin);
    ui->showBanner->setChecked(printSettings.showBanner);
    ui->showDrugs->setChecked(printSettings.showDrugs);
    ui->showInvs->setChecked(printSettings.showInvestigations);
    ui->showMesurements->setChecked(printSettings.showMeasurments);
    ui->showDrugsTableOutline->setChecked(printSettings.showDrugsTableOutline);
    ui->drugsMode->setCurrentIndex(printSettings.drugsPrintMode);
    ui->showDrugsTitle->setChecked(printSettings.showDrugsTitle);
    ui->showHeaderFooterLogo->setChecked(printSettings.showPrescriptionHeaderFooterLogo);
    ui->logoSize->setCurrentText(QString::number(printSettings.logoSize));
    ui->headerHeightPercent->setValue(printSettings.headerHeightPercent);
    ui->footerHeightPercent->setValue(printSettings.footerHeightPercent);
    ui->bannerHeightPercent->setValue(printSettings.bannerHeightPercent);
    ui->bannerFontName->setCurrentFont(QFont(printSettings.bannerFont.fontName));
    ui->bannerFontSize->setCurrentText(QString::number(printSettings.bannerFont.fontSize));
    ui->bannerFontBold->setChecked(printSettings.bannerFont.fontBold);
    ui->roshettaFontName->setCurrentFont(QFont(printSettings.roshettaFont.fontName));
    ui->roshettaFontSize->setCurrentText(QString::number(printSettings.roshettaFont.fontSize));
    ui->roshettaFontBold->setChecked(printSettings.roshettaFont.fontBold);
    ui->doseFontName->setCurrentFont(QFont(printSettings.doseFont.fontName));
    ui->doseFontSize->setCurrentText(QString::number(printSettings.doseFont.fontSize));
    ui->doseFontBold->setChecked(printSettings.doseFont.fontBold);
    ui->drugsInitDate->setChecked(printSettings.showDrugsInitDate);
    ui->SignaturePrintedOn->setChecked(printSettings.showSignaturePrintedOn);
    ui->showOnlyNewlyModifiedAddedDrugs->setChecked(printSettings.showOnlyNewlyModifiedAddedDrugs);
    ui->showTradeNamesBold->setChecked(printSettings.showTradeNamesBold);
    ui->showDoseNewLine->setChecked(printSettings.showDoseNewLine);
    ui->Header->setHtml(dataIOhelper::readFile(HEADERFILE));
    ui->Footer->setHtml(dataIOhelper::readFile(FOOTERFILE));
    return printSettings;
}

mSettings::prescriptionPrintSettings printDrugs::grabPrintSettings()
{
    mSettings::prescriptionPrintSettings printSettings;
    printSettings.paperSizeId = ui->paperSizeId->currentText();
    printSettings.pageMargin = ui->pageMargin->value();
    printSettings.showBanner = ui->showBanner->isChecked();
    printSettings.showDrugs = ui->showDrugs->isChecked();
    printSettings.showInvestigations = ui->showInvs->isChecked();
    printSettings.showMeasurments = ui->showMesurements->isChecked();
    printSettings.showDrugsTableOutline = ui->showDrugsTableOutline->isChecked();
    printSettings.drugsPrintMode = (mSettings::drugsPrintMode) ui->drugsMode->currentIndex();
    printSettings.showDrugsTitle = ui->showDrugsTitle->isChecked();
    printSettings.showPrescriptionHeaderFooterLogo = ui->showHeaderFooterLogo->isChecked();
    printSettings.logoSize = ui->logoSize->currentText().toInt();
    printSettings.headerHeightPercent = ui->headerHeightPercent->value();
    printSettings.footerHeightPercent = ui->footerHeightPercent->value();
    printSettings.bannerHeightPercent = ui->bannerHeightPercent->value();
    printSettings.bannerFont.fontName = ui->bannerFontName->currentText();
    printSettings.bannerFont.fontSize = ui->bannerFontSize->currentText().toInt();
    printSettings.bannerFont.fontBold = ui->bannerFontBold->isChecked();
    printSettings.roshettaFont.fontName = ui->roshettaFontName->currentText();;
    printSettings.roshettaFont.fontSize = ui->roshettaFontSize->currentText().toInt();
    printSettings.roshettaFont.fontBold = ui->roshettaFontBold->isChecked();
    printSettings.doseFont.fontName = ui->doseFontName->currentText();;
    printSettings.doseFont.fontSize = ui->doseFontSize->currentText().toInt();
    printSettings.doseFont.fontBold = ui->doseFontBold->isChecked();
    printSettings.showDrugsInitDate = ui->drugsInitDate->isChecked();
    printSettings.showSignaturePrintedOn = ui->SignaturePrintedOn->isChecked();
    printSettings.showOnlyNewlyModifiedAddedDrugs = ui->showOnlyNewlyModifiedAddedDrugs->isChecked();
    printSettings.showTradeNamesBold = ui->showTradeNamesBold->isChecked();
    printSettings.showDoseNewLine = ui->showDoseNewLine->isChecked();
    return printSettings;
}

void printDrugs::saveRoshettaAutoComplete()
{
    QStringList dict = QStringList() << ui->Roshetta->toHtml();
    QtConcurrent::run(wm_add2completer,&wm_add2Completer::save2Dict,dict);
}

void printDrugs::refreshView()
{
    m_roshetta = roshettaMaker.createRoshetta(roshettaData,pSettings);
    ui->Roshetta->setDocument(m_roshetta);
}

void printDrugs::reset()
{

    ui->drugsMode->setCurrentIndex(0);
//    ui->diet->setCurrentIndex(0);
//    selectedDiet="-";
}

void printDrugs::setRoshettaData(const mSettings::Roshetta &_roshetta)
{
    roshettaData = _roshetta;
}

void printDrugs::showEvent(QShowEvent *e)
{
    ui->lockUnlockButton->setChecked(true);
    ui->Roshetta->setReadOnly(true);
    pSettings = grabPrintSettings();
    applyPageSizeParamaters();
    refreshView();
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    restoreGeometry(reg.value("printWindowGeometry").toByteArray());
    QDialog::showEvent(e);
    setupPrinter(printer);
}

void printDrugs::makePrintPreview(QPrinter *preview)
{
    pSettings = grabPrintSettings();
    applyPageSizeParamaters();
    refreshView();
    setupPrinter(preview);
    printDoc(preview,m_roshetta,true);
}

void printDrugs::setupPrinter(QPrinter *p)
{
    QPageLayout m_layout;
    QPageSize pageSize(PageMetrics::pageSizeIdFromString(pSettings.paperSizeId));
    m_layout.setPageSize(pageSize,QMarginsF(pSettings.pageMargin,pSettings.pageMargin,pSettings.pageMargin,pSettings.pageMargin));
    m_layout.setOrientation(QPageLayout::Orientation::Portrait);
    m_layout.setMode(QPageLayout::Mode::StandardMode);
    p->setPageLayout(m_layout);
}

void printDrugs::printDoc(QPrinter *p,QTextDocument *_doc,bool preview)
{
    int reply=0;
    _doc->setPageSize((QSizeF) p->pageLayout().pageSize().sizePoints());
    if (_doc->pageCount() > 1 && !preview)
        reply = QMessageBox::question(nullptr,"Warning","Your print might be splitted over more than one page."
                                                  " please recheck your print preview. Are you sure?",
                                      QMessageBox::Yes,
                                      QMessageBox::No);

    if (reply ==  QMessageBox::No)
        return;

    bool isPrinting=false;

    if(!t.isActive())
    {
        _doc->print(p);
        isPrinting=true;
    }

    if(!preview)
        t.start();

    if (!preview && isPrinting)
    {
        emit message("Message","Print job is being sent to your Default Printer.");

        if (settings.alwaysClosePrintDlgAfterClick() && isVisible())
            this->close();
    }
}

void printDrugs::applyPageSizeParamaters()
{
    ui->Roshetta->setPageFormat(PageMetrics::pageSizeIdFromString(pSettings.paperSizeId));
    ui->Roshetta->setPageMargins(QMarginsF(pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin));
}

void printDrugs::closeEvent(QCloseEvent *e)
{
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    reg.setValue("selectedPrintingProfile", ui->printerProfile->currentIndex());
    reg.setValue("printWindowGeometry",saveGeometry());
    pSettings = grabPrintSettings();
    saveRoshettaAutoComplete();
    savePrintSettings();
    reset();
    QDialog::closeEvent(e);
}


///////////////////////////////////////////////// Slots //////////////////////////////////////////////
void printDrugs::printerProfile_activated(int index)
{
    ui->printerProfile->setEnabled(false);
    savePrintSettings();
    selectedPrintingProfile = ui->printerProfile->itemText(index);
    lSettings = pSettings = loadPrintSettings();
    refreshView();
    ui->printerProfile->setEnabled(true);
}

void printDrugs::showInvs_clicked(bool checked)
{
    pSettings.showInvestigations = checked;
    refreshView();
}

void printDrugs::drugsMode_activated(int index)
{
    pSettings.drugsPrintMode = (mSettings::drugsPrintMode) index;
    refreshView();
}

void printDrugs::bannerFontName_activated(const QString &arg1)
{
    pSettings.bannerFont.fontName =arg1;
    refreshView();
}

void printDrugs::bannerFontSize_activated(const QString &arg1)
{
    pSettings.bannerFont.fontSize =arg1.toInt();
    refreshView();
}


void printDrugs::bannerFontBold_clicked(bool checked)
{
    pSettings.bannerFont.fontBold =checked;
    refreshView();
}

void printDrugs::roshettaFontName_activated(const QString &arg1)
{
    pSettings.roshettaFont.fontName =arg1;
    refreshView();
}


void printDrugs::roshettaFontSize_activated(const QString &arg1)
{
    pSettings.roshettaFont.fontSize =arg1.toInt();
    refreshView();
}


void printDrugs::roshettaFontBold_clicked(bool checked)
{
    pSettings.roshettaFont.fontBold =checked;
    refreshView();
}


void printDrugs::doseFontName_activated(const QString &arg1)
{
    pSettings.doseFont.fontName =arg1;
    refreshView();
}


void printDrugs::doseFontSize_activated(const QString &arg1)
{
    pSettings.doseFont.fontSize =arg1.toInt();
    refreshView();
}


void printDrugs::doseFontBold_clicked(bool checked)
{
    pSettings.doseFont.fontBold =checked;
    refreshView();
}

void printDrugs::headerHeightPercent_valueChanged(int arg1)
{
    if(!ui->headerHeightPercent->hasFocus())
        return;
    pSettings.headerHeightPercent = arg1;
    refreshView();
}


void printDrugs::bannerHeightPercent_valueChanged(int arg1)
{
    if(!ui->bannerHeightPercent->hasFocus())
        return;
    pSettings.bannerHeightPercent = arg1;
    refreshView();
}


void printDrugs::footerHeightPercent_valueChanged(int arg1)
{
    if(!ui->footerHeightPercent->hasFocus())
        return;
    pSettings.footerHeightPercent = arg1;
    refreshView();
}

void printDrugs::header_textChanged()
{
    if(!ui->Header->hasFocus())
        return;
    dataIOhelper::saveFile(HEADERFILE,ui->Header->toHtml().toUtf8());
    refreshView();
}

void printDrugs::footer_textChanged()
{
    if(!ui->Footer->hasFocus())
        return;
    dataIOhelper::saveFile(FOOTERFILE,ui->Footer->toHtml().toUtf8());
    refreshView();
}

void printDrugs::paperSizeId_activated(const QString &arg1)
{
    pSettings.paperSizeId = arg1;
    applyPageSizeParamaters();
    refreshView();
}

void printDrugs::SignaturePrintedOn_clicked(bool checked)
{
    pSettings.showSignaturePrintedOn = checked;
    refreshView();
}



void printDrugs::drugsInitDate_clicked(bool checked)
{
    pSettings.showDrugsInitDate = checked;
    refreshView();
}


void printDrugs::showHeaderFooterLogo_clicked(bool checked)
{
    pSettings.showPrescriptionHeaderFooterLogo = checked;
    refreshView();
}


void printDrugs::showDrugs_clicked(bool checked)
{
    pSettings.showDrugs = checked;
    refreshView();
}


void printDrugs::showMesurements_clicked(bool checked)
{
    pSettings.showMeasurments = checked;
    refreshView();
}


void printDrugs::showDrugsTableOutline_clicked(bool checked)
{
    pSettings.showDrugsTableOutline = checked;
    refreshView();
}


void printDrugs::showDrugsTitle_clicked(bool checked)
{
    pSettings.showDrugsTitle = checked;
    refreshView();
}


void printDrugs::showBanner_clicked(bool checked)
{
    pSettings.showBanner = checked;
    refreshView();
}

void printDrugs::showOnlyNewlyModifiedAddedDrugs_clicked(bool checked)
{
    pSettings.showOnlyNewlyModifiedAddedDrugs = checked;
    refreshView();
}


void printDrugs::showTradeNamesBold_clicked(bool checked)
{
    pSettings.showTradeNamesBold = checked;
    refreshView();
}


void printDrugs::showDoseNewLine_clicked(bool checked)
{
    pSettings.showDoseNewLine = checked;
    refreshView();
}

void printDrugs::pageMargin_valueChanged(int arg1)
{
    if(!ui->pageMargin->hasFocus())
        return;
    pSettings.pageMargin = arg1;
    applyPageSizeParamaters();
    refreshView();
}

void printDrugs::logoSize_activated(const QString &arg1)
{
    pSettings.logoSize = arg1.toInt();
    refreshView();
}

void printDrugs::lockUnlockButton_toggled(bool checked)
{
    ui->Roshetta->setReadOnly(checked);
    ui->lockUnlockButton->setIcon(QIcon(checked? ":/Graphics/lock":":/Graphics/unlock"));
}


void printDrugs::ButtonRefresh_clicked()
{
    pSettings = grabPrintSettings();
    applyPageSizeParamaters();
    m_roshetta = roshettaMaker.createRoshetta(roshettaData,pSettings);
    ui->Roshetta->setDocument(m_roshetta);
    ui->lockUnlockButton->setChecked(true);
}
