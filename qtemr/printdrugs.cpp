// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "printdrugs.h"
#include "ui_printdrugs.h"

printDrugs::printDrugs(QWidget *parent) :
    QDialog(parent),
    printer ( new QPrinter(QPrinter::HighResolution)),
    dlg ( new QPrintDialog(printer,this)),
    //cp ( new colorPicker(this)),
    wm_add2completer(new wm_add2Completer),
    ui(new Ui::printDrugs),
    m_roshetta(new QTextDocument(this))
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

    t.setInterval(600);//this timer to set limit to printing per second
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    connect(ui->logoSize,SIGNAL(currentTextChanged(QString)),ui->elementsTab,SLOT(refreshView(QString)));
    connect(this,SIGNAL(loadPreview()),this,SLOT(refreshView()));
    connect(ui->elementsTab,SIGNAL(refresh()),this,SLOT(refreshView()));
    connect(ui->paperPrefTab,SIGNAL(refresh()),this,SLOT(refreshView()));
    connect(ui->optionsTab,SIGNAL(refresh()),this,SLOT(refreshView()));

    connect(&t,SIGNAL(timeout()),&t,SLOT(stop()));

    ui->fastPrint->setFocus(Qt::OtherFocusReason);
    emit loadCompleters();

    ui->printerProfile->setCurrentIndex(reg.value("selectedPrintingProfile").toInt());
    selectedPrintingProfile = ui->printerProfile->currentText();
    lSettings = pSettings =  loadPrintSettings();
    setMinimumSize(800,600);
    this->setModal(true);
    ui->Roshetta->setPageFormat(PageMetrics::pageSizeIdFromString(pSettings.paperSizeId));
    ui->Roshetta->setPageMargins(QMarginsF(pSettings.leftMargin, pSettings.topMargin, pSettings.rightMargin, pSettings.bottomMargin));
    refreshView();


}

printDrugs::~printDrugs()
{
    delete printer;
    delete dlg;
    //delete cp;
    delete ui;
    delete wm_add2completer;
    delete m_roshetta;
}

void printDrugs::showPrintDialog()
{
    setupPrinter(printer,grabPrintSettings());
    if ( dlg->exec() == QDialog::Accepted )
        printDoc(printer,roshettaDoc);
}

void printDrugs::showPrintPreviewDialog()
{
    mPrintPreviewDialog previewDialog(this);
    pSettings = grabPrintSettings();
    //previewDialog.setPageOrientation(QPrinter::Portrait);
    previewDialog.setWindowState(previewDialog.windowState() | Qt::WindowMaximized);
    connect(&previewDialog,SIGNAL(paintRequested(QPrinter*)),this,SLOT(makePrintPreview(QPrinter*)));
    previewDialog.exec();
}

void printDrugs::mPrint()
{
    setupPrinter(printer,grabPrintSettings());
    printDoc(printer,roshettaDoc);
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

    ui->topMargin->setValue(printSettings.topMargin);
    ui->leftMargin->setValue(printSettings.leftMargin);
    ui->bottomMargin->setValue(printSettings.bottomMargin);
    ui->rightMargin->setValue(printSettings.rightMargin);

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
    return printSettings;
}

mSettings::prescriptionPrintSettings printDrugs::grabPrintSettings()
{
    mSettings::prescriptionPrintSettings printSettings;
    printSettings.paperSizeId = ui->paperSizeId->currentText();
    printSettings.topMargin = ui->topMargin->value();


    printSettings.leftMargin = ui->leftMargin->value();
    printSettings.bottomMargin = ui->bottomMargin->value();
    printSettings.rightMargin = ui->rightMargin->value();

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

//void printDrugs::loadDiets(QStringList diets)
//{
//    ui->diet->clear();
//    ui->diet->insertItems(0,diets);
//}

//void printDrugs::on_Orientation_currentIndexChanged(int)
//{
//    if(!ui->Orientation->hasFocus())
//        return;

//    setMaxValues();
//    refreshView();
//}

//void printDrugs::setInkColor(QColor c)
//{
//    inkColor = c;
//    //ui->setInkColor->setColor(c);
//    palette.setColor(QPalette::Text,c);
//    ui->Roshetta->setPalette(palette);
//}

//void printDrugs::on_pageWidth_valueChanged(double)
//{
//    if(!ui->pageWidth->hasFocus())
//        return;

//    setMaxValues();
//}

//void printDrugs::setDefaultFontPoint(const QString &arg1)
//{
//    defaultPoint = arg1.toInt();
//    QString style= QString("QTextEdit{font:%1 %2pt \"%3\";}").arg(defaultBold? "bold":"").arg(defaultPoint).arg(defaultFont);
//    ui->Roshetta->setStyleSheet(style);
//    QTextCursor cursor = ui->Roshetta->textCursor();
//    ui->Roshetta->selectAll();
//    ui->Roshetta->setFontPointSize(defaultPoint);
//    ui->Roshetta->setTextCursor(cursor);
//    ui->Roshetta->setPalette(palette);
//    m_roshetta->setPageSize((QSizeF) printer->pageLayout().pageSize().sizePoints());
//    refreshView();

//}

//void printDrugs::setDefaultFont(const QString &arg1)
//{
//    defaultFont= arg1;
//    QString style= QString("QTextEdit{font:%1 %2pt \"%3\";}").arg(defaultBold? "bold":"").arg(defaultPoint).arg(defaultFont);
//    ui->Roshetta->setStyleSheet(style);
//    QTextCursor cursor = ui->Roshetta->textCursor();
//    ui->Roshetta->selectAll();
//    ui->Roshetta->setFontFamily(arg1);
//    ui->Roshetta->setTextCursor(cursor);
//    ui->Roshetta->setPalette(palette);
//    ui->Roshetta->setInkFont(arg1);
//    m_roshetta->setPageSize((QSizeF) printer->pageLayout().pageSize().sizePoints());

//}

//void printDrugs::setDefaultBold(bool bold)
//{
//    QTextCursor cursor = ui->Roshetta->textCursor();
//    ui->Roshetta->selectAll();
//    ui->Roshetta->setFontWeight(bold? QFont::Bold:QFont::Normal);
//    ui->Roshetta->setTextCursor(cursor);
//    defaultBold = bold;
//    refreshView();
//}

void printDrugs::refreshView()
{
    pSettings = grabPrintSettings();

    roshettaDoc = roshettaMaker.createRoshetta(roshettaData,pSettings);
    ui->Roshetta->setDocument(roshettaDoc);
    //QString HTML = emit refreshRoshetta(pSettings,selectedDiet,drugsMode);


    //QTextCursor cursor(m_roshetta);
    //QTextFrameFormat fmt;
    //fmt.setHeight(1000);
    //fmt.setWidth(1000);
    //ui->Roshetta->setHtml(HTML);
    //cursor.insertFrame(fmt);
    //cursor.insertHtml(HTML);
    //cursor.movePosition(QTextCursor::End);
    //cursor.insertText("FOOTER");
    //mDebug() << m_roshetta->toHtml();
    //ui->Roshetta->setPageFormat(QPageSize::A5);
    //ui->Roshetta->setPageMargins(QMarginsF(5, 5, 5, 5));
    //ui->Roshetta->setUsePageMode(true);
    //ui->Roshetta->setPageNumbersAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    //m_roshetta->setPageSize(printer->pageLayout().pageSize().sizePoints());
    //tweakRoshetta();
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


//void printDrugs::on_drugsColPerc_valueChanged(double value)
//{
//    double investigationWidth = pSettings.showInvestigations? pSettings.investigationsWidth:0.0;
//    double pageWidth = pSettings.pageWidth;
//    int maxDrugsWidth = static_cast<int> (((pageWidth - investigationWidth)/pageWidth)*100);

//    if (ui->drugsColPerc->hasFocus())
//    {
//        if (value > maxDrugsWidth )
//            ui->drugsColPerc->setMaximum(maxDrugsWidth);


//        double old_prcnt = pSettings.drugsColPerc;
//        double new_prcnt = value;

//        if ( pSettings.showInvestigations && pSettings.invPad <= 0.1 && new_prcnt >= old_prcnt )
//        {
//            ui->drugsColPerc->setValue(old_prcnt);
//            return;
//        }

//        double widthCorrection =pSettings.leftMargin + pSettings.rightMargin;
//        pageWidth -= widthCorrection;

//        double delta = ( new_prcnt - old_prcnt ) * pageWidth/100.0 ;
//        double oldInvPad = pSettings.invPad;
//        double newInvPad = oldInvPad - delta;

//        ui->invPad->setValue(newInvPad);
//        setMaxValues();
//        refreshView();
//    }

//}

void printDrugs::showEvent(QShowEvent *e)
{
    //setMaxValues();
    emit loadPreview();
    ui->optionsTabWidget->setCurrentIndex(0);
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);
    restoreGeometry(reg.value("printWindowGeometry").toByteArray());
    QDialog::showEvent(e);
    tweakRoshetta();
}

void printDrugs::makePrintPreview(QPrinter *preview)
{
    setupPrinter(preview,grabPrintSettings(),true);
    printDoc(preview,roshettaDoc,true);
}

void printDrugs::tweakRoshetta(){
    setupPrinter(printer,pSettings);
    //double pageWidth = (pSettings.pageOrientation == 0)? pSettings.pageWidth :pSettings.pageHeight;
    //int WidthPixels = static_cast<int>(pageWidth) * logicalDpiY();
    //setInkColor(inkColor);
    //setDefaultFont(defaultFont);
    //ui->Roshetta->setLineWrapMode(QTextEdit::FixedPixelWidth);
    //ui->Roshetta->setLineWrapColumnOrWidth(WidthPixels);
    //ui->Roshetta->setReadOnly(pSettings.showInvestigations);

    //m_roshetta->setPageSize((QSizeF) printer->pageLayout().pageSize().sizePoints());
}

//void printDrugs::setMaxValues()
//{
//    pSettings = grabPrintSettings();
//    double pageWidth = pSettings.pageWidth;
//    double pageHeight = pSettings.pageHeight;
//    double widthCorrection =pSettings.leftMargin + pSettings.rightMargin;

//    pageWidth -= widthCorrection;

//    double factor = 0.05;
//    double drugsWidth = static_cast<double>(pageWidth*pSettings.drugsColPerc) / static_cast<double>(100.00);
//    double maxRequestMargin =  pageWidth - drugsWidth - pSettings.investigationsWidth - factor;
//    double maxInvestigationsWidth = pageWidth - drugsWidth - pSettings.invPad - factor;
//    double maxDietTopMargin = pageHeight ;

//    if (maxRequestMargin <=0.1)
//        maxRequestMargin = 0.1;
//    ui->invPad->setMaximum(maxRequestMargin);
//    ui->invWidth->setMaximum((maxInvestigationsWidth<0)? 0.0:maxInvestigationsWidth);
//    ui->dietTopPadding->setMaximum(maxDietTopMargin);

//}

//void printDrugs::resetMaxValues()
//{
//    ui->invPad->setMaximum(100);
//    ui->invWidth->setMaximum(100);
//    ui->dietTopPadding->setMaximum(100);
//}

void printDrugs::setupPrinter(QPrinter *p,const mSettings::prescriptionPrintSettings &_pSettings, bool preview)
{
    QPageLayout m_layout;
    QPageSize pageSize(PageMetrics::pageSizeIdFromString(_pSettings.paperSizeId));
    m_layout.setPageSize(pageSize,QMarginsF(_pSettings.leftMargin,_pSettings.topMargin, _pSettings.rightMargin,_pSettings.bottomMargin));
    m_layout.setOrientation(QPageLayout::Orientation::Portrait);
    m_layout.setMode(QPageLayout::Mode::StandardMode);
    p->setPageLayout(m_layout);
    //p->setFullPage(_pSettings.fullPage);
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

QTextDocument *printDrugs::getDoc()
{

    refreshView();
    return m_roshetta;
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


//void printDrugs::on_diet_activated(const QString &arg1)
//{
//    selectedDiet = arg1;
//    refreshView();

//}

void printDrugs::on_drugsMode_activated(int index)
{
    Q_UNUSED(index)
//    pSettings.drugsPrintMode = index;
//    savePrintSettings();
    refreshView();
}

//void printDrugs::on_bannerWidthPerc_valueChanged(int)
//{
//    if (ui->bannerWidthPerc->hasFocus())
//        refreshView();
//}

//void printDrugs::on_pageHeight_valueChanged(double)
//{
//    if (!ui->pageHeight->hasFocus())
//        return;

//    setMaxValues();
//}


void printDrugs::on_printerProfile_activated(const QString &arg1)
{
    ui->printerProfile->setEnabled(false);
    savePrintSettings();
    //resetMaxValues();
    selectedPrintingProfile = arg1;
    lSettings = pSettings = loadPrintSettings();
    refreshView();
    //setMaxValues();
    ui->printerProfile->setEnabled(true);
}

//void printDrugs::on_invPad_editingFinished()
//{
//    setMaxValues();
//}

//void printDrugs::on_invWidth_editingFinished()
//{
//    setMaxValues();
//}

void printDrugs::on_showInvs_toggled(bool checked)
{
//    double max = checked? 66.0:100;
//   ui->drugsColPerc->setMaximum(max);
    refreshView();
}

void printDrugs::on_paperSizeId_currentIndexChanged(const QString &arg1)
{
    pSettings.paperSizeId = arg1;
    ui->Roshetta->setPageFormat(PageMetrics::pageSizeIdFromString(pSettings.paperSizeId));
    ui->Roshetta->setPageMargins(QMarginsF(pSettings.leftMargin, pSettings.topMargin, pSettings.rightMargin, pSettings.bottomMargin));
    refreshView();
}


void printDrugs::on_bannerFont_currentIndexChanged(const QString &arg1)
{
    pSettings.bannerFont.fontName =arg1;
    refreshView();
}




void printDrugs::on_bannerFontSize_currentIndexChanged(const QString &arg1)
{
    pSettings.bannerFont.fontSize =arg1.toInt();
    refreshView();
}


void printDrugs::on_bannerFontBold_toggled(bool checked)
{
    pSettings.bannerFont.fontBold =checked;
    refreshView();
}


void printDrugs::on_bannerFont_highlighted(const QString &arg1)
{
    pSettings.bannerFont.fontName =arg1;
    roshettaDoc = roshettaMaker.createRoshetta(roshettaData,pSettings);
    ui->Roshetta->setDocument(roshettaDoc);
}


void printDrugs::on_roshettaFont_currentIndexChanged(const QString &arg1)
{
    pSettings.roshettaFont.fontName =arg1;
    refreshView();
}


void printDrugs::on_roshettaFont_highlighted(const QString &arg1)
{
    pSettings.roshettaFont.fontName =arg1;
    roshettaDoc = roshettaMaker.createRoshetta(roshettaData,pSettings);
    ui->Roshetta->setDocument(roshettaDoc);
}


void printDrugs::on_roshettaFontSize_currentIndexChanged(const QString &arg1)
{
    pSettings.roshettaFont.fontSize =arg1.toInt();
    refreshView();
}


void printDrugs::on_roshettaFontBold_toggled(bool checked)
{
    pSettings.roshettaFont.fontBold =checked;
    refreshView();
}


void printDrugs::on_headerHeightPercent_valueChanged(int arg1)
{
    pSettings.headerHeightPercent = arg1;
    refreshView();
}


void printDrugs::on_bannerHeightPercent_valueChanged(int arg1)
{
    pSettings.bannerHeightPercent = arg1;
    refreshView();
}


void printDrugs::on_footerHeightPercent_valueChanged(int arg1)
{
    pSettings.footerHeightPercent = arg1;
    refreshView();
}

