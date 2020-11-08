#include "printdrugs.h"
#include "ui_printdrugs.h"

printDrugs::printDrugs(QWidget *parent) :
    QDialog(parent),
    printer ( new QPrinter(QPrinter::ScreenResolution)),
    dlg ( new QPrintDialog(printer,this)),
    cp ( new colorPicker(this)),
    wm_add2completer(new wm_add2Completer),
    ui(new Ui::printDrugs)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

    t.setInterval(600);//this timer to set limit to printing per second
    QSettings reg("HKEY_CURRENT_USER\\Software\\SmartClinicApp",QSettings::NativeFormat);

    connect(ui->setInkColor,SIGNAL(clicked(bool)),cp,SLOT(show()));
    connect(cp,SIGNAL(newColor(QColor)),this,SLOT(setInkColor(QColor)));
    connect(ui->point,SIGNAL(highlighted(QString)),this,SLOT(setDefaultFontPoint(QString)));
    connect(ui->point,SIGNAL(currentTextChanged(QString)),this,SLOT(setDefaultFontPoint(QString)));
    connect(ui->fontComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(setDefaultFont(QString)));
    connect(ui->fontComboBox,SIGNAL(highlighted(QString)),this,SLOT(setDefaultFont(QString)));
    connect(this,SIGNAL(loadPreview()),this,SLOT(refreshView()));
    connect(ui->bold,SIGNAL(toggled(bool)),this,SLOT(setDefaultBold(bool)),Qt::QueuedConnection);
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
}

printDrugs::~printDrugs()
{
    delete printer;
    delete dlg;
    delete cp;
    delete ui;
    delete wm_add2completer;
}

void printDrugs::showPrintDialog()
{
    setupPrinter(printer,grabPrintSettings());
    if ( dlg->exec() == QDialog::Accepted )
        printDoc(printer,ui->Roshetta->document());
}

void printDrugs::showPrintPreviewDialog()
{
    mPrintPreviewDialog previewDialog(this);
    pSettings = grabPrintSettings();
    previewDialog.setPageOrientation((pSettings.pageOrientation==0)? QPrinter::Portrait:QPrinter::Landscape);
    previewDialog.setWindowState(previewDialog.windowState() | Qt::WindowMaximized);
    connect(&previewDialog,SIGNAL(paintRequested(QPrinter*)),this,SLOT(makePrintPreview(QPrinter*)));
    previewDialog.exec();
}

void printDrugs::mPrint()
{
    setupPrinter(printer,grabPrintSettings());
    printDoc(printer,getDoc());
}

void printDrugs::savePrintSettings()
{
    if (!(lSettings == pSettings))  // check if settings have been changed or not
        settings.savePrintSettings(grabPrintSettings(),selectedPrintingProfile);// so dont cause useless writes to disk.
}

mSettings::prescriptionPrintSettings printDrugs::loadPrintSettings()
{
    mSettings::prescriptionPrintSettings printSettings = settings.getPrintSettings(selectedPrintingProfile);
    inkColor = QColor(printSettings.color);
    defaultFont = printSettings.font;
    defaultPoint = printSettings.point;
    defaultBold = printSettings.bold;
    ui->setInkColor->setColor(inkColor);
    ui->fontComboBox->setCurrentText(defaultFont);
    ui->point->setCurrentText(QString::number(defaultPoint));
    ui->bold->setChecked(printSettings.bold);
    ui->topMargin->setValue(printSettings.topMargin);
    ui->leftMargin->setValue(printSettings.leftMargin);
    ui->bottomMargin->setValue(printSettings.bottomMargin);
    ui->rightMargin->setValue(printSettings.rightMargin);
    ui->Orientation->setCurrentIndex(printSettings.pageOrientation);
    ui->pageWidth->setValue(printSettings.pageWidth);
    ui->pageHeight->setValue(printSettings.pageHeight);
    ui->tradeNameinBold->setChecked(printSettings.tradeNameinBold);
    ui->doseNewLine->setChecked(printSettings.doseinNewLine);
    ui->compactMode->setChecked(printSettings.compactMode);
    ui->noQty->setChecked(printSettings.noQty);
    ui->dietLeftPadding->setValue(printSettings.dietLeftPadding);
    ui->dietTopPadding->setValue(printSettings.dietTopPadding);
    ui->drugsColPerc->setValue(printSettings.drugsColPerc);
    ui->invPad->setValue(printSettings.invPad);
    ui->showInvs->setChecked(printSettings.showInvestigations);
    ui->dietWidth->setValue(printSettings.dietWidth);
    ui->showDrugs->setChecked(printSettings.showDrugs);
    ui->centerRequests->setChecked(printSettings.centerRequests);
    ui->centerDrugs->setChecked(printSettings.centerDrugs);
    ui->showBanner->setChecked(printSettings.showBanner);
    ui->showSeparator->setChecked(printSettings.showDrugsSeparator);
    ui->fullPage->setChecked(printSettings.fullPage);
    ui->bannerWidthPerc->setValue(printSettings.bannerWidth);
    ui->invWidth->setValue(printSettings.investigationsWidth);
    ui->showDrugsTitle->setChecked(printSettings.showDrugsTitle);
    ui->showDoseInEasternArabic->setChecked(printSettings.setEastArabicNumbers);
    return printSettings;
}

mSettings::prescriptionPrintSettings printDrugs::grabPrintSettings()
{
    mSettings::prescriptionPrintSettings printSettings;
    printSettings.bold = ui->bold->isChecked();
    printSettings.color = ui->setInkColor->getColor().name();
    printSettings.font = ui->fontComboBox->currentText();
    printSettings.point = ui->point->currentText().toInt();
    printSettings.pageOrientation =ui->Orientation->currentIndex();
    printSettings.topMargin = ui->topMargin->value();
    printSettings.rightMargin = ui->rightMargin->value();
    printSettings.bottomMargin = ui->bottomMargin->value();
    printSettings.leftMargin = ui->leftMargin->value();
    printSettings.pageWidth = ui->pageWidth->value();
    printSettings.pageHeight = ui->pageHeight->value();
    printSettings.tradeNameinBold = ui->tradeNameinBold->isChecked();
    printSettings.doseinNewLine = ui->doseNewLine->isChecked();
    printSettings.compactMode = ui->compactMode->isChecked();
    printSettings.noQty = ui->noQty->isChecked();
    printSettings.dietLeftPadding = ui->dietLeftPadding->value();
    printSettings.dietTopPadding = ui->dietTopPadding->value();
    printSettings.drugsColPerc = ui->drugsColPerc->value();
    printSettings.invPad = ui->invPad->value();
    printSettings.showInvestigations = ui->showInvs->isChecked();
    printSettings.dietWidth = ui->dietWidth->value();
    printSettings.showDrugs = ui->showDrugs->isChecked();
    printSettings.centerRequests = ui->centerRequests->isChecked();
    printSettings.centerDrugs = ui->centerDrugs->isChecked();
    printSettings.showBanner = ui->showBanner->isChecked();
    printSettings.showDrugsSeparator = ui->showSeparator->isChecked();
    printSettings.fullPage = ui->fullPage->isChecked();
    printSettings.bannerWidth = ui->bannerWidthPerc->value();
    printSettings.investigationsWidth = ui->invWidth->value();
    printSettings.showDrugsTitle = ui->showDrugsTitle->isChecked();
    printSettings.setEastArabicNumbers = ui->showDoseInEasternArabic->isChecked();
    return printSettings;
}

void printDrugs::saveRoshettaAutoComplete()
{
    QStringList dict = QStringList() << ui->Roshetta->toHtml();
    QtConcurrent::run(wm_add2completer,&wm_add2Completer::save2Dict,dict);
}

void printDrugs::loadDiets(QStringList diets)
{
    ui->diet->clear();
    ui->diet->insertItems(0,diets);
}

void printDrugs::on_Orientation_currentIndexChanged(int)
{  
    if(!ui->Orientation->hasFocus())
        return;

    setMaxValues();
    refreshView();
}

void printDrugs::setInkColor(QColor c)
{
    inkColor = c;
    ui->setInkColor->setColor(c);
    palette.setColor(QPalette::Text,c);
    ui->Roshetta->setPalette(palette);
}

void printDrugs::on_pageWidth_valueChanged(double)
{
    if(!ui->pageWidth->hasFocus())
        return;

    setMaxValues();
}

void printDrugs::setDefaultFontPoint(const QString &arg1)
{
    defaultPoint = arg1.toInt();
    QString style= QString("QTextEdit{font:%1 %2pt \"%3\";}").arg(defaultBold? "bold":"").arg(defaultPoint).arg(defaultFont);
    ui->Roshetta->setStyleSheet(style);
    QTextCursor cursor = ui->Roshetta->textCursor();
    ui->Roshetta->selectAll();
    ui->Roshetta->setFontPointSize(defaultPoint);
    ui->Roshetta->setTextCursor(cursor);
    ui->Roshetta->setPalette(palette);
    ui->Roshetta->document()->setPageSize((QSizeF) printer->pageLayout().pageSize().sizePoints());

}

void printDrugs::setDefaultFont(const QString &arg1)
{
    defaultFont= arg1;
    QString style= QString("QTextEdit{font:%1 %2pt \"%3\";}").arg(defaultBold? "bold":"").arg(defaultPoint).arg(defaultFont);
    ui->Roshetta->setStyleSheet(style);
    QTextCursor cursor = ui->Roshetta->textCursor();
    ui->Roshetta->selectAll();
    ui->Roshetta->setFontFamily(arg1);
    ui->Roshetta->setTextCursor(cursor);
    ui->Roshetta->setPalette(palette);
    ui->Roshetta->setInkFont(arg1);
    ui->Roshetta->document()->setPageSize((QSizeF) printer->pageLayout().pageSize().sizePoints());
}

void printDrugs::setDefaultBold(bool bold)
{
    QTextCursor cursor = ui->Roshetta->textCursor();
    ui->Roshetta->selectAll();
    ui->Roshetta->setFontWeight(bold? QFont::Bold:QFont::Normal);
    ui->Roshetta->setTextCursor(cursor);
    defaultBold = bold;
    refreshView();
}

void printDrugs::refreshView()
{
    pSettings = grabPrintSettings();

    QString HTML = refreshRoshetta(pSettings,selectedDiet,drugsMode);

    ui->Roshetta->setHtml(HTML);

    tweakRoshetta();

}

void printDrugs::reset()
{
    ui->drugsMode->setCurrentIndex(0);
    ui->diet->setCurrentIndex(0);
    drugsMode=0;
    selectedDiet="-";
}


void printDrugs::on_drugsColPerc_valueChanged(double value)
{
    double investigationWidth = pSettings.showInvestigations? pSettings.investigationsWidth:0.0;
    double pageWidth = (pSettings.pageOrientation == 0)? pSettings.pageWidth :pSettings.pageHeight;
    int maxDrugsWidth = static_cast<int> (((pageWidth - investigationWidth)/pageWidth)*100);

    if (ui->drugsColPerc->hasFocus())
    {
        if (value > maxDrugsWidth )
            ui->drugsColPerc->setMaximum(maxDrugsWidth);


        double old_prcnt = pSettings.drugsColPerc;
        double new_prcnt = value;

        if ( pSettings.showInvestigations && pSettings.invPad <= 0.1 && new_prcnt >= old_prcnt )
        {
            ui->drugsColPerc->setValue(old_prcnt);
            return;
        }

        double widthCorrection =pSettings.leftMargin + pSettings.rightMargin;
        pageWidth -= widthCorrection;

        double delta = ( new_prcnt - old_prcnt ) * pageWidth/100.0 ;
        double oldInvPad = pSettings.invPad;
        double newInvPad = oldInvPad - delta;

        ui->invPad->setValue(newInvPad);
        setMaxValues();
        refreshView();
    }

}

void printDrugs::showEvent(QShowEvent *e)
{
    setMaxValues();
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
    printDoc(preview,getDoc(),true);
}

void printDrugs::tweakRoshetta()
{
    double pageWidth = (pSettings.pageOrientation == 0)? pSettings.pageWidth :pSettings.pageHeight;
    int WidthPixels = static_cast<int>(pageWidth) * logicalDpiY();
    setInkColor(inkColor);
    setDefaultFont(defaultFont);
    ui->Roshetta->setLineWrapMode(QTextEdit::FixedPixelWidth);
    ui->Roshetta->setLineWrapColumnOrWidth(WidthPixels);
    ui->Roshetta->setReadOnly(pSettings.showInvestigations);
    setupPrinter(printer,pSettings);
    ui->Roshetta->document()->setPageSize((QSizeF) printer->pageLayout().pageSize().sizePoints());
}

void printDrugs::setMaxValues()
{
    pSettings = grabPrintSettings();
    double pageWidth = (pSettings.pageOrientation == 0)? pSettings.pageWidth :pSettings.pageHeight;
    double pageHeight = (pSettings.pageOrientation == 0)? pSettings.pageHeight :pSettings.pageWidth;
    double widthCorrection =pSettings.leftMargin + pSettings.rightMargin;

    pageWidth -= widthCorrection;

    double factor = 0.05;
    double drugsWidth = static_cast<double>(pageWidth*pSettings.drugsColPerc) / static_cast<double>(100.00);
    double maxRequestMargin =  pageWidth - drugsWidth - pSettings.investigationsWidth - factor;
    double maxInvestigationsWidth = pageWidth - drugsWidth - pSettings.invPad - factor;
    double maxDietTopMargin = pageHeight ;

    if (maxRequestMargin <=0.1)
        maxRequestMargin = 0.1;
    ui->invPad->setMaximum(maxRequestMargin);
    ui->invWidth->setMaximum((maxInvestigationsWidth<0)? 0.0:maxInvestigationsWidth);
    ui->dietTopPadding->setMaximum(maxDietTopMargin);

}

void printDrugs::resetMaxValues()
{
    ui->invPad->setMaximum(100);
    ui->invWidth->setMaximum(100);
    ui->dietTopPadding->setMaximum(100);
}

void printDrugs::setupPrinter(QPrinter *p,mSettings::prescriptionPrintSettings pSettings, bool preview)
{
    double left = pSettings.leftMargin;
    double top = pSettings.topMargin;
    double right = pSettings.rightMargin;
    double bottom = pSettings.bottomMargin;
    p->setPaperSize(QSizeF(pSettings.pageWidth,pSettings.pageHeight),QPrinter::Inch);
    p->setPageMargins(left,top,right,bottom,QPrinter::Inch);
    p->setFullPage(pSettings.fullPage);
    if(!preview)
        p->setOrientation((pSettings.pageOrientation==0)? QPrinter::Portrait:QPrinter::Landscape);
}

void printDrugs::printDoc(QPrinter *p,QTextDocument *doc,bool preview)
{
    int reply=0;
    doc->setPageSize((QSizeF) p->pageLayout().pageSize().sizePoints());
    if (doc->pageCount() > 1 && !preview)
        reply = QMessageBox::question(nullptr,"Warning","Your print might be splitted over more than one page."
                                                  " please recheck your print preview. Are you sure?",
                                      QMessageBox::Yes,
                                      QMessageBox::No);

    if (reply ==  QMessageBox::No)
        return;

    bool isPrinting=false;

    if(!t.isActive())
    {
        doc->print(p);
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
    QTextDocument *doc = ui->Roshetta->document();
    //doc->setHtml(refreshRoshetta(pSettings,selectedDiet,drugsMode));
    return doc;
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


void printDrugs::on_diet_activated(const QString &arg1)
{
    selectedDiet = arg1;
    refreshView();

}

void printDrugs::on_drugsMode_activated(int index)
{
    drugsMode = index;
    refreshView();
}

void printDrugs::on_bannerWidthPerc_valueChanged(int)
{
    if (ui->bannerWidthPerc->hasFocus())
        refreshView();
}

void printDrugs::on_pageHeight_valueChanged(double)
{
    if (!ui->pageHeight->hasFocus())
        return;

    setMaxValues();
}


void printDrugs::on_printerProfile_activated(const QString &arg1)
{
    ui->printerProfile->setEnabled(false);
    savePrintSettings();
    resetMaxValues();
    selectedPrintingProfile = arg1;
    lSettings = pSettings = loadPrintSettings();
    refreshView();
    setMaxValues();
    ui->printerProfile->setEnabled(true);
}

void printDrugs::on_invPad_editingFinished()
{
    setMaxValues();
}

void printDrugs::on_invWidth_editingFinished()
{
    setMaxValues();
}

void printDrugs::on_showInvs_toggled(bool checked)
{
    double max = checked? 66.0:100;
    ui->drugsColPerc->setMaximum(max);
    refreshView();
}
