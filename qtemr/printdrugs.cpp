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
    ui->Roshetta->setPageFormat(PageMetrics::pageSizeIdFromString(pSettings.paperSizeId));
    ui->Roshetta->setPageMargins(QMarginsF(pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin));
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
    ui->showSeparator->setChecked(printSettings.showDrugsSeparator);
    ui->drugsMode->setCurrentIndex(printSettings.drugsPrintMode);
    ui->showDrugsTitle->setChecked(printSettings.showDrugsTitle);
    ui->showHeaderFooterLogo->setChecked(printSettings.showPrescriptionHeaderFooterLogo);
    ui->logoSize->setCurrentText(QString::number(printSettings.logoSize));
    ui->headerHeightPercent->setValue(printSettings.headerHeightPercent);
    ui->footerHeightPercent->setValue(printSettings.footerHeightPercent);
    ui->bannerHeightPercent->setValue(printSettings.bannerHeightPercent);
    ui->bannerFont->setCurrentFont(QFont(printSettings.bannerFont.fontName));
    ui->bannerFontSize->setCurrentText(QString::number(printSettings.bannerFont.fontSize));
    ui->bannerFontBold->setChecked(printSettings.bannerFont.fontBold);
    ui->roshettaFont->setCurrentFont(QFont(printSettings.roshettaFont.fontName));
    ui->roshettaFontSize->setCurrentText(QString::number(printSettings.roshettaFont.fontSize));
    ui->roshettaFontBold->setChecked(printSettings.roshettaFont.fontBold);
    ui->drugsInitDate->setChecked(printSettings.showDrugsInitDate);
    ui->SignaturePrintedOn->setChecked(printSettings.showSignaturePrintedOn);
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
    printSettings.showDrugsSeparator = ui->showSeparator->isChecked();
    printSettings.drugsPrintMode = (mSettings::drugsPrintMode) ui->drugsMode->currentIndex();
    printSettings.showDrugsTitle = ui->showDrugsTitle->isChecked();
    printSettings.showPrescriptionHeaderFooterLogo = ui->showHeaderFooterLogo->isChecked();
    printSettings.logoSize = ui->logoSize->currentText().toInt();
    printSettings.headerHeightPercent = ui->headerHeightPercent->value();
    printSettings.footerHeightPercent = ui->footerHeightPercent->value();
    printSettings.bannerHeightPercent = ui->bannerHeightPercent->value();
    printSettings.bannerFont.fontName = ui->bannerFont->currentText();
    printSettings.bannerFont.fontSize = ui->bannerFontSize->currentText().toInt();
    printSettings.bannerFont.fontBold = ui->bannerFontBold->isChecked();
    printSettings.roshettaFont.fontName = ui->roshettaFont->currentText();;
    printSettings.roshettaFont.fontSize = ui->roshettaFontSize->currentText().toInt();
    printSettings.roshettaFont.fontBold = ui->roshettaFontBold->isChecked();
    printSettings.showDrugsInitDate = ui->drugsInitDate->isChecked();
    printSettings.showSignaturePrintedOn = ui->SignaturePrintedOn->isChecked();
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
    pSettings = grabPrintSettings();
    ui->Roshetta->setPageFormat(PageMetrics::pageSizeIdFromString(pSettings.paperSizeId));
    ui->Roshetta->setPageMargins(QMarginsF(pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin));
    refreshView();
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    restoreGeometry(reg.value("printWindowGeometry").toByteArray());
    QDialog::showEvent(e);
    setupPrinter(printer);
}

void printDrugs::makePrintPreview(QPrinter *preview)
{
    pSettings = grabPrintSettings();
    ui->Roshetta->setPageFormat(PageMetrics::pageSizeIdFromString(pSettings.paperSizeId));
    ui->Roshetta->setPageMargins(QMarginsF(pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin));
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

void printDrugs::on_drugsMode_activated(int index)
{
    pSettings.drugsPrintMode = (mSettings::drugsPrintMode) index;
    refreshView();
}


void printDrugs::on_printerProfile_activated(const QString &arg1)
{
    ui->printerProfile->setEnabled(false);
    savePrintSettings();
    selectedPrintingProfile = arg1;
    lSettings = pSettings = loadPrintSettings();
    refreshView();
    ui->printerProfile->setEnabled(true);
}

void printDrugs::on_showInvs_clicked(bool checked)
{
    pSettings.showInvestigations = checked;
    refreshView();
}

//void printDrugs::on_paperSizeId_currentIndexChanged(const QString &arg1)
//{
//    pSettings.paperSizeId = arg1;
//    ui->Roshetta->setPageFormat(PageMetrics::pageSizeIdFromString(pSettings.paperSizeId));
//    ui->Roshetta->setPageMargins(QMarginsF(pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin));
//    refreshView();
//}


void printDrugs::on_bannerFont_activated(const QString &arg1)
{
    pSettings.bannerFont.fontName =arg1;
    refreshView();
}

void printDrugs::on_bannerFontSize_activated(const QString &arg1)
{
    pSettings.bannerFont.fontSize =arg1.toInt();
    refreshView();
}


void printDrugs::on_bannerFontBold_clicked(bool checked)
{
    pSettings.bannerFont.fontBold =checked;
    refreshView();
}


void printDrugs::on_bannerFont_highlighted(const QString &arg1)
{
    pSettings.bannerFont.fontName =arg1;
    refreshView();
}


void printDrugs::on_roshettaFont_activated(const QString &arg1)
{
    pSettings.roshettaFont.fontName =arg1;
    refreshView();
}


void printDrugs::on_roshettaFont_highlighted(const QString &arg1)
{
    pSettings.roshettaFont.fontName =arg1;
    refreshView();
}


void printDrugs::on_roshettaFontSize_activated(const QString &arg1)
{
    pSettings.roshettaFont.fontSize =arg1.toInt();
    refreshView();
}


void printDrugs::on_roshettaFontBold_clicked(bool checked)
{
    pSettings.roshettaFont.fontBold =checked;
    refreshView();
}


void printDrugs::on_headerHeightPercent_valueChanged(int arg1)
{
    if(!ui->headerHeightPercent->hasFocus())
        return;
    pSettings.headerHeightPercent = arg1;
    refreshView();
}


void printDrugs::on_bannerHeightPercent_valueChanged(int arg1)
{
    if(!ui->bannerHeightPercent->hasFocus())
        return;
    pSettings.bannerHeightPercent = arg1;
    refreshView();
}


void printDrugs::on_footerHeightPercent_valueChanged(int arg1)
{
    if(!ui->footerHeightPercent->hasFocus())
        return;
    pSettings.footerHeightPercent = arg1;
    refreshView();
}

void printDrugs::on_Header_textChanged()
{
    if(!ui->Header->hasFocus())
        return;
    dataIOhelper::saveFile(HEADERFILE,ui->Header->toHtml().toUtf8());
    refreshView();
}

void printDrugs::on_Footer_textChanged()
{
    if(!ui->Footer->hasFocus())
        return;
    dataIOhelper::saveFile(FOOTERFILE,ui->Footer->toHtml().toUtf8());
    refreshView();
}

void printDrugs::on_SignaturePrintedOn_clicked(bool checked)
{
    pSettings.showSignaturePrintedOn = checked;
    refreshView();
}


void printDrugs::on_drugsInitDate_clicked(bool checked)
{
    pSettings.showDrugsInitDate = checked;
    refreshView();
}


void printDrugs::on_showHeaderFooterLogo_clicked(bool checked)
{
    pSettings.showPrescriptionHeaderFooterLogo = checked;
    refreshView();
}


void printDrugs::on_showDrugs_clicked(bool checked)
{
    pSettings.showDrugs = checked;
    refreshView();
}


void printDrugs::on_showMesurements_clicked(bool checked)
{
    pSettings.showMeasurments = checked;
    refreshView();
}


void printDrugs::on_showSeparator_clicked(bool checked)
{
    pSettings.showDrugsSeparator = checked;
    refreshView();
}


void printDrugs::on_showDrugsTitle_clicked(bool checked)
{
    pSettings.showDrugsTitle = checked;
    refreshView();
}


void printDrugs::on_showBanner_clicked(bool checked)
{
    pSettings.showBanner = checked;
    refreshView();
}


void printDrugs::on_pageMargin_valueChanged(int arg1)
{
    if(!ui->pageMargin->hasFocus())
        return;
    pSettings.pageMargin = arg1;
    ui->Roshetta->setPageFormat(PageMetrics::pageSizeIdFromString(pSettings.paperSizeId));
    ui->Roshetta->setPageMargins(QMarginsF(pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin));
    refreshView();
}

void printDrugs::on_logoSize_activated(const QString &arg1)
{
    pSettings.logoSize = arg1.toInt();
    refreshView();
}


void printDrugs::on_paperSizeId_activated(const QString &arg1)
{
    pSettings.paperSizeId = arg1;
    ui->Roshetta->setPageFormat(PageMetrics::pageSizeIdFromString(pSettings.paperSizeId));
    ui->Roshetta->setPageMargins(QMarginsF(pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin, pSettings.pageMargin));
    refreshView();
}

