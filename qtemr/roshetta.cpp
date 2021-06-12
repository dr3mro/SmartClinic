#include "roshetta.h"
#include <QApplication>
#include <QDesktopWidget>
Roshetta::Roshetta(QObject *parent) : QObject(parent),
    mRoshetta(new QTextDocument(this))
{

}

QTextDocument * Roshetta::createRoshetta(const mSettings::Roshetta &_Roshetta, const mSettings::prescriptionPrintSettings &_pSettings)
{
    // set roshetta settings
    roshettaSettings = _pSettings;

    //set global var Roshetta data for global use
    roshettaData = _Roshetta;

    // clear contents
    mRoshetta->clear();

    // set Roshetta Size
    setRoshettaSize();

    // set rootFrame parameters
    setRootFrame();

    // set header Format parameters
    makeHeader(_pSettings);

    // set banner Format parameters
    makeBanner();

    // set footer Format parameters
    makeFooter();

    // set body Format parameters
    makeBody();

    // create the base document frames
    stackFrames();

    // return the document
    return mRoshetta;
}

Roshetta::~Roshetta()
{
    delete mRoshetta;
}

void Roshetta::setRoshettaSize()
{
    double xMargins = inch2px(0.20) *2 ;
    double yMargins = inch2px(0.20) *2 ;
    QPageSize pageSize(QPageSize::A5);
    mWidth = pageSize.sizePixels(qApp->desktop()->logicalDpiX()).width() - xMargins;
    mHeight = pageSize.sizePixels(qApp->desktop()->logicalDpiX()).height() - yMargins;

    mRoshetta->setPageSize(QSize(mWidth,mHeight));// QPageSize::A5
}

void Roshetta::setRootFrame()
{
    QTextFrame* root = mRoshetta->rootFrame();
    rootFrameFormat = root->frameFormat();
    rootFrameFormat.setWidth(mWidth);
    rootFrameFormat.setHeight(mHeight*2);
    rootFrameFormat.setBorder(0);
    rootFrameFormat.setPadding(0);
    rootFrameFormat.setMargin(0);
    root->setFrameFormat(rootFrameFormat);
}

void Roshetta::stackFrames()
{  
    QTextCursor cursor(mRoshetta);
    cursor.movePosition(QTextCursor::Start);
    cursor.insertTable(1,2,headerFormat);
    if(roshettaSettings.showPrescriptionHeaderFooterLogo){
        cursor.insertHtml("<img src=\"logo.jpg\" width=72 alt=\"logo\" >");
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertHtml(QString::fromUtf8(dataIOhelper::readFile(HEADERFILE)));
    }
    else{
        cursor.movePosition(QTextCursor::NextCell);
    }

    cursor.movePosition(QTextCursor::NextBlock);

    //    QVector<QTextLength> bannertl = QVector<QTextLength>() << QTextLength(QTextLength::PercentageLength,44)
    //                                                           << QTextLength(QTextLength::PercentageLength,28)
    //                                                           << QTextLength(QTextLength::PercentageLength,28);

    cursor.insertFrame(bannerFrameFormat);

    //bannerFormat.setColumnWidthConstraints(bannertl);
    bannerTable = cursor.insertTable(2,3,bannerFormat);
    if(roshettaSettings.showBanner)
        fillBanner(cursor);
    else{
        cursor.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,5);
    }

    cursor.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,2);


    QVector<QTextLength> bodytl = QVector<QTextLength>() << QTextLength(QTextLength::PercentageLength,70)
                                                         << QTextLength(QTextLength::PercentageLength,30);
    bodyFormat.setColumnWidthConstraints(bodytl);
    cursor.insertTable(2,2,bodyFormat);

    fillBody(cursor);

    cursor.movePosition(QTextCursor::NextBlock);

    QTextTableFormat prefooterFormat;
    prefooterFormat.setBorder(0);
    prefooterFormat.setMargin(0);
    prefooterFormat.setWidth(mWidth);
    prefooterFormat.setHeight(20);
    cursor.insertTable(1,2,prefooterFormat);
    cursor.insertHtml("<b>Physician's Signature:</b>");
    cursor.movePosition(QTextCursor::NextCell);

    cursor.insertHtml(QString("<b>printed on:</b> %1").arg(roshettaData.printedinDate));
    cursor.movePosition(QTextCursor::NextBlock);

    if(roshettaSettings.showPrescriptionHeaderFooterLogo){
        cursor.insertFrame(footerFormat);
        QTextBlockFormat footerBlockFormat = cursor.blockFormat();
        footerBlockFormat.setAlignment(Qt::AlignCenter);
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.setBlockFormat(footerBlockFormat);

        cursor.insertHtml(QString(dataIOhelper::readFile(FOOTERFILE)));
    }
}

void Roshetta::makeHeader(const mSettings::prescriptionPrintSettings &_pSettings)
{
    headerFormat.setWidth(mWidth);
    headerFormat.setHeight(72);
    headerFormat.setBorder(0);
    headerFormat.setMargin(0);
}

void Roshetta::makeBanner()
{
    if(roshettaSettings.showBanner){
        bannerFrameFormat.setBorder(1);
        bannerFrameFormat.setBorderBrush(QBrush(Qt::black));
    }
    else{
        bannerFrameFormat.setBorder(0);
        bannerFrameFormat.setBorderBrush(QBrush(Qt::white));
    }
    bannerFrameFormat.setHeight(42);


    bannerFormat.setAlignment(Qt::AlignCenter);
    bannerFormat.setWidth(mWidth);
    bannerFormat.setHeight(44);
    bannerFormat.setBorder(0);
//    bannerFormat.setMargin(0);
//    bannerFormat.setPadding(0);
//    bannerFormat.setCellPadding(0);
//    bannerFormat.setBorderCollapse(true);
}

void Roshetta::makeBody()
{
    double bodyHeight = mHeight -( 50 + 50 + 50 + 40);
    bodyFormat.setWidth(mWidth);
    bodyFormat.setHeight(bodyHeight);
    bodyFormat.setBorder(0);
    bodyFormat.setMargin(0);
    bodyFormat.setAlignment(Qt::AlignCenter);
}

void Roshetta::makeFooter()
{
    footerFormat.setWidth(mWidth);
    footerFormat.setHeight(40);
    footerFormat.setBorder(1);
    footerFormat.setMargin(0);
    footerFormat.setBorderBrush(QBrush(Qt::black));
}

void Roshetta::fillBanner(QTextCursor &c)
{
    c.insertHtml(QString("<b>NAME: </b>%1").arg(roshettaData.name));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<b>Age: </b>%1").arg(roshettaData.printableAge));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<b>Code: </b>%1%2%3").arg(roshettaData.ID , " ▶ " , roshettaData.visitSymbole));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<b>Diagnosis: </b>%1").arg(roshettaData.Diagnosis));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<b>Date: </b>%1").arg(roshettaData.visitDate));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<b>Next: </b>%1").arg(roshettaData.nextDate));
}

void Roshetta::fillBody(QTextCursor &c)
{
    QTextTableFormat drugsTableFormat;
    drugsTableFormat.setBorder(0);
    int rows = roshettaData.currentDrugsList.count() + roshettaData.baseDrugsList.count();

    rows+= roshettaSettings.showDrugsTitle? 2:0;

    CurrentDrugRow =0; // to follow filling of table current row

    c.insertTable(rows,1,drugsTableFormat);

    if(roshettaSettings.showDrugs){
        if(roshettaSettings.drugsPrintMode == mSettings::drugsPrintMode::both){
            fillCurrentDrugs(c,"PRESCRIPTION");
            fillBaseDrugs(c,"CHRONIC DRUGS");
            c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,2);
        }
        else {
            if(roshettaSettings.drugsPrintMode == mSettings::drugsPrintMode::visitOnly){
                fillCurrentDrugs(c,"PRESCRIPTION");
                c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,3);
            }

            if (roshettaSettings.drugsPrintMode == mSettings::drugsPrintMode::baseOnly){
                fillBaseDrugs(c,"CHRONIC DRUGS");
                c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,5);
            }
            if(roshettaSettings.showDrugsTitle){
                c.movePosition(QTextCursor::NextCell);
            }

        }
    }
    else{
        c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,7);
        if(roshettaSettings.showDrugsTitle){
            c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,2);
        }
    }

    if(roshettaSettings.showInvestigations)
        fillRequests(c);

    fillVitals(c);

}

void Roshetta::fillCurrentDrugs(QTextCursor &c, const QString &title)
{
    fillDrugs(c,roshettaData.currentDrugsList,title);
}

void Roshetta::fillBaseDrugs(QTextCursor &c, const QString &title)
{
    fillDrugs(c,roshettaData.baseDrugsList,title);
}

void Roshetta::fillDrugs(QTextCursor &c, QList<mSettings::drug> &drugs,const QString &title)
{
    QTextTableCellFormat drugsHeaderFormat;
    QTextBlockFormat drugsHeaderBlockFormat;

    if(roshettaSettings.showDrugsTitle){
        drugsHeaderFormat.setBackground(QBrush(QColor(176, 196, 222)));
        drugsHeaderFormat.setTopPadding(3);
        drugsHeaderBlockFormat.setAlignment(Qt::AlignCenter);
        c.insertHtml(QString("<h2><b>%1</b></h2>").arg(title));
        c.currentTable()->cellAt(CurrentDrugRow,0).setFormat(drugsHeaderFormat);
        c.currentTable()->cellAt(CurrentDrugRow,0).firstCursorPosition().setBlockFormat(drugsHeaderBlockFormat);
        c.movePosition(QTextCursor::NextCell);
    }



    QTextBlockFormat requestsBlockFormat;
    requestsBlockFormat.setNonBreakableLines(true);


    CurrentDrugRow++;
    foreach (const mSettings::drug & d, drugs) {
        c.insertHtml(QString("<div align=left dir=LTR >℞  <b>%1</b> %2 <i style=\"font-size:7px\"> %3 </i></div>").arg(d.TradeName," ▶ " ,d.StartDate));
        c.insertHtml("<br>");
        c.insertHtml(QString("<div align=left dir=RTL>%1</div>").arg(d.Dose));

        if(roshettaSettings.showDrugsSeparator)
            c.insertHtml("<hr>");

        c.movePosition(QTextCursor::NextCell);
        CurrentDrugRow++;
    }
}

void Roshetta::fillRequests(QTextCursor &c)
{
    if ( roshettaData.requests.count() == 0 )
        return;


    requestsTableFormat.setBorder(0);
    requestsTableFormat.setMargin(10);
    requestsTableFormat.setBackground(QBrush(QColor(240, 248, 255)));
    c.insertTable(roshettaData.requests.count()+1,1,requestsTableFormat);

    QTextTableCellFormat requestsHeaderFormat;
    requestsHeaderFormat.setBackground(QBrush(QColor(176, 196, 222)));
    requestsHeaderFormat.setTopPadding(3);

    QTextBlockFormat requestsHeaderBlockFormat;
    requestsHeaderBlockFormat.setAlignment(Qt::AlignCenter);

    QTextBlockFormat requestsBlockFormat;
    requestsBlockFormat.setNonBreakableLines(true);

    c.insertHtml("<h3><b>REQUESTS</b></h3");
    c.currentTable()->cellAt(0,0).setFormat(requestsHeaderFormat);
    c.currentTable()->cellAt(0,0).firstCursorPosition().setBlockFormat(requestsHeaderBlockFormat);

    c.movePosition(QTextCursor::NextCell);

    foreach (const QString & req, roshettaData.requests) {
        c.setBlockFormat(requestsBlockFormat);
        c.insertText("⬤ ");
        c.insertText(req);
        c.movePosition(QTextCursor::NextCell);
    }
    c.movePosition(QTextCursor::NextBlock);
}

void Roshetta::fillVitals(QTextCursor &c)
{
    int rows = roshettaData.vitals.getRows();
    if(rows ==0){
        c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,2);
        return;
    }


    QTextTableFormat vitalsTableFormat;
    vitalsTableFormat.setBorderStyle(QTextTableFormat::BorderStyle_None);
    vitalsTableFormat.setMargin(10);

    QTextTableCellFormat headerCellFormat;
    headerCellFormat.setBackground(QBrush(QColor(176, 196, 222)));
    headerCellFormat.setTopPadding(3);

    QTextBlockFormat headerBlockFormat;
    headerBlockFormat.setAlignment(Qt::AlignCenter);


    c.insertTable(rows+1,2,vitalsTableFormat);

    c.insertHtml("<b>MEASURMENTS</b>");
    c.currentTable()->cellAt(0,0).setFormat(headerCellFormat);
    c.currentTable()->cellAt(0,0).firstCursorPosition().setBlockFormat(headerBlockFormat);

    c.movePosition(QTextCursor::NextCell,QTextCursor::MoveAnchor,2);
    if(roshettaData.vitals.weight != 0){
        c.insertText("W");
        c.movePosition(QTextCursor::NextCell);
        c.insertText(QString(": %1 KG").arg(roshettaData.vitals.weight));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.height != 0){
        c.insertText("Height");
        c.movePosition(QTextCursor::NextCell);
        c.insertText(QString(": %1 CM").arg(roshettaData.vitals.height));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.sPo2 != 0){
        c.insertText("sPo2");
        c.movePosition(QTextCursor::NextCell);
        c.insertText(QString(": %1 %").arg(roshettaData.vitals.sPo2));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.RBS != 0){
        c.insertText("RBS");
        c.movePosition(QTextCursor::NextCell);
        c.insertText(QString(": %1 mg/dl").arg(roshettaData.vitals.RBS));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.pulse != 0){
        c.insertText("Pulse");
        c.movePosition(QTextCursor::NextCell);
        c.insertText(QString(": %1 bpm").arg(roshettaData.vitals.pulse));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.RR != 0){
        c.insertText("RR");
        c.movePosition(QTextCursor::NextCell);
        c.insertText(QString(": %1 cpm").arg(roshettaData.vitals.RR));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.BP != ""){
        c.insertText("BP");
        c.movePosition(QTextCursor::NextCell);
        c.insertText(QString(": %1 mmgh").arg(roshettaData.vitals.BP));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.T != 0){
        c.insertText("T");
        c.movePosition(QTextCursor::NextCell);
        c.insertText(QString(": %1 C").arg(roshettaData.vitals.T));
        c.movePosition(QTextCursor::NextCell);
    }
    c.currentTable()->mergeCells(0,0,1,2);
    c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,3);
}

double Roshetta::inch2px(const qreal &x)
{
    return x * qApp->desktop()->logicalDpiX();
}
