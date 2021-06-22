#include "roshetta.h"
#include <QApplication>
#include <QDesktopWidget>
Roshetta::Roshetta(QObject *parent) : QObject(parent)
{

}

void Roshetta::setDocument(QTextDocument *doc)
{
    mRoshetta = doc;
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
    makeHeader();

    // set banner Format parameters
    makeBanner();

    // set footer Format parameters
    makeFooter();

    // set body Format parameters
    makeBody();

    // set drugs table parameters
    makeDrugs();

    // set requests parameter
    makeRequests();

    // set signature printted on parameters
    makeSignaturePrintedOn();

    //set vitals parameters
    makeVitals();

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
    double xMargins = PageMetrics::mmToPx(roshettaSettings.pageMargin*2) ;
    double yMargins = PageMetrics::mmToPx(roshettaSettings.pageMargin*2);
    QPageSize pageSize = QPageSize(PageMetrics::pageSizeIdFromString(roshettaSettings.paperSizeId));
    mWidth = pageSize.sizePixels(qApp->desktop()->logicalDpiX()).width() - xMargins;
    mHeight = pageSize.sizePixels(qApp->desktop()->logicalDpiX()).height() -yMargins;
    mRoshetta->setPageSize(QSizeF(mWidth,mHeight));// QPageSize::A5
}

void Roshetta::setRootFrame()
{
    QTextFrame* root = mRoshetta->rootFrame();
    rootFrameFormat = root->frameFormat();
    rootFrameFormat.setWidth(mWidth);

    if(roshettaData.diet.printRequired)
        rootFrameFormat.setHeight( PageMetrics::mmToPx(roshettaSettings.pageMargin*2)*2 + mHeight*2 );
    else
        rootFrameFormat.setHeight(mHeight);
    rootFrameFormat.setBorder(0);
    rootFrameFormat.setPadding(0);
    rootFrameFormat.setMargin(PageMetrics::mmToPx(roshettaSettings.pageMargin));
    root->setFrameFormat(rootFrameFormat);
}

void Roshetta::stackFrames()
{  
    QTextCursor cursor(mRoshetta);
    cursor.movePosition(QTextCursor::Start);
    cursor.insertTable(1,2,headerFormat);
    if(roshettaSettings.showPrescriptionHeaderFooterLogo)
        fillHeader(cursor);
    else
        cursor.movePosition(QTextCursor::NextCell);

    cursor.movePosition(QTextCursor::NextBlock);

    cursor.insertFrame(bannerFrameFormat);


    if(roshettaSettings.showBanner)
        fillBanner(cursor);
    else{
        cursor.movePosition(QTextCursor::NextBlock);
    }

    cursor.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,2);

    fillBody(cursor);

    cursor.movePosition(QTextCursor::NextBlock);

    fillSignaturePrintedOn(cursor);

    cursor.movePosition(QTextCursor::NextBlock);

    fillFooter(cursor);

    cursor.movePosition(QTextCursor::NextBlock);

    if(roshettaData.diet.printRequired)
        fillDiet(cursor);
}

void Roshetta::makeHeader()
{
    headerFormat.setWidth(mWidth);
    headerFormat.setHeight((mHeight*roshettaSettings.headerHeightPercent)/100);
    headerFormat.setBorder(0);
    headerFormat.setMargin(0);
}

void Roshetta::makeBanner()
{
    if(roshettaSettings.showBanner){
        bannerFrameFormat.setBorder(1);
        bannerFrameFormat.setBorderBrush(QBrush(Qt::lightGray));
        bannerFrameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    }
    else{
        bannerFrameFormat.setBorder(0);
        bannerFrameFormat.setBorderBrush(QBrush(Qt::white));
    }
    bannerFrameFormat.setHeight((mHeight*roshettaSettings.bannerHeightPercent)/100);


    bannerFormat.setAlignment(Qt::AlignCenter);
    bannerFormat.setWidth(mWidth);
    bannerFormat.setHeight(44);
    bannerFormat.setBorder(0);

    QVector<QTextLength> bannertl = QVector<QTextLength>() << QTextLength(QTextLength::PercentageLength,50)
                                                         << QTextLength(QTextLength::PercentageLength,25)
                                                         << QTextLength(QTextLength::PercentageLength,25);
    bannerFormat.setColumnWidthConstraints(bannertl);
//    bannerFormat.setMargin(0);
//    bannerFormat.setPadding(0);
//    bannerFormat.setCellPadding(0);
//    bannerFormat.setBorderCollapse(true);
}

void Roshetta::makeBody()
{

    double bodyHeight = mHeight - ((roshettaSettings.headerHeightPercent + roshettaSettings.footerHeightPercent + roshettaSettings.bannerHeightPercent)*mHeight)/100;
    //mDebug() << "body" << bodyHeight;
    bodyFormat.setWidth(mWidth);
    bodyFormat.setHeight(bodyHeight);
    bodyFormat.setBorder(0);
    bodyFormat.setMargin(0);
    bodyFormat.setAlignment(Qt::AlignCenter);

    QVector<QTextLength> bodytl = QVector<QTextLength>() << QTextLength(QTextLength::PercentageLength,70)
                                                         << QTextLength(QTextLength::PercentageLength,30);
    bodyFormat.setColumnWidthConstraints(bodytl);

}

void Roshetta::makeDrugs()
{
    drugsTableFormat.setBorder(roshettaSettings.showDrugsTableOutline);
    drugsTableFormat.setBorderStyle(QTextTableFormat::BorderStyle_Inset);
    drugsTableFormat.setBorderBrush(QBrush(Qt::lightGray));
    drugsTableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 70));
}

void Roshetta::makeRequests()
{
    requestsTableFormat.setBorder(0);
    requestsTableFormat.setMargin(10);
    requestsTableFormat.setBackground(QBrush(QColor(240, 248, 255)));
    requestsTableFormat.setWidth(mWidth*0.3);
    requestsHeaderFormat.setBackground(QBrush(QColor(176, 196, 222)));
    requestsHeaderBlockFormat.setAlignment(Qt::AlignCenter);
    requestsBlockFormat.setNonBreakableLines(true);
}

void Roshetta::makeVitals()
{
    QVector<QTextLength> vitalstl = QVector<QTextLength>() << QTextLength(QTextLength::PercentageLength,30)
                                                         << QTextLength(QTextLength::PercentageLength,70);

    vitalsTableFormat.setBorder(1);
    vitalsTableFormat.setBorderStyle(QTextTableFormat::BorderStyle_Inset);
    vitalsTableFormat.setBorderBrush(QBrush(Qt::lightGray));
    vitalsTableFormat.setMargin(5);
    vitalsTableFormat.setColumnWidthConstraints(vitalstl);
    headerCellFormat.setBackground(QBrush(QColor(176, 196, 222)));
    headerBlockFormat.setAlignment(Qt::AlignCenter);

}

void Roshetta::makeSignaturePrintedOn()
{
    prefooterFormat.setBorder(0);
    prefooterFormat.setMargin(0);
    prefooterFormat.setWidth(mWidth);
    prefooterFormat.setHeight(20);
}

void Roshetta::makeFooter()
{
    footerFormat.setWidth(mWidth);
    footerFormat.setHeight((mHeight*roshettaSettings.footerHeightPercent)/100);
    footerFormat.setBorder(roshettaSettings.showPrescriptionHeaderFooterLogo);
    footerFormat.setMargin(0);
    footerFormat.setBorderBrush(QBrush(Qt::darkGray));
    footerFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
}

void Roshetta::fillHeader(QTextCursor &c)
{
    c.insertHtml(QString("<img src=\"logo.jpg\" width=%1 alt=\"logo\" >").arg(roshettaSettings.logoSize));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString::fromUtf8(dataIOhelper::readFile(HEADERFILE)));
}

void Roshetta::fillBanner(QTextCursor &c)
{
    bannerTable = c.insertTable(2,3,bannerFormat);
    QString style = QString(" style=\"font-family:%1;font-size: %2px;font-weight: %3;\" ")
            .arg(roshettaSettings.bannerFont.fontName,
                 QString::number(roshettaSettings.bannerFont.fontSize),
                 roshettaSettings.bannerFont.fontBold? "bold":"normal");

    c.insertHtml(QString("<div %2><b>NAME: </b>%1</div>").arg(roshettaData.name,style));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<div %2><b>Age: </b>%1</div>").arg(roshettaData.printableAge,style));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<div %4><b>Code: </b>%1%2%3</div>").arg(roshettaData.ID , " ▶ " , roshettaData.visitSymbole,style));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<div %2><b>Diagnosis: </b>%1</div>").arg(roshettaData.Diagnosis,style));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<div %2><b>Date: </b>%1</div>").arg(roshettaData.visitDate,style));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<div %2><b>Next: </b>%1</div>").arg(roshettaData.nextDate,style));
}

void Roshetta::fillBody(QTextCursor &c)
{
    c.insertTable(1,2,bodyFormat);

    CurrentDrugRow =0; // to follow filling of table current row

    if(roshettaSettings.showDrugs){
        int rows=0;

        if(roshettaSettings.drugsPrintMode == mSettings::drugsPrintMode::both){
            if(roshettaSettings.showOnlyNewlyModifiedAddedDrugs){
                rows+= roshettaData.currentAlteredDrugsList.count()+roshettaData.baseAlteredDrugsList.count();
                rows+= roshettaSettings.showDrugsTitle? 2:0;
            }else{
                rows+= roshettaData.currentDrugsList.count()+roshettaData.baseDrugsList.count();
                rows+= roshettaSettings.showDrugsTitle? 2:0;
            }
        }
        else if (roshettaSettings.drugsPrintMode == mSettings::drugsPrintMode::visitOnly){
            if(roshettaSettings.showOnlyNewlyModifiedAddedDrugs){
                rows+= roshettaData.currentAlteredDrugsList.count();
                rows+= roshettaSettings.showDrugsTitle? 1:0;
            }else{
                rows+= roshettaData.currentDrugsList.count();
                rows+= roshettaSettings.showDrugsTitle? 1:0;
            }
        }
        else if (roshettaSettings.drugsPrintMode == mSettings::drugsPrintMode::baseOnly){
            if(roshettaSettings.showOnlyNewlyModifiedAddedDrugs){
                rows+= roshettaData.baseAlteredDrugsList.count();
                rows+= roshettaSettings.showDrugsTitle? 1:0;
            }else{
                rows+= roshettaData.baseDrugsList.count();
                rows+= roshettaSettings.showDrugsTitle? 1:0;
            }
        }

        if(rows > 0 ){
            if(roshettaSettings.showDoseNewLine)
                c.insertTable(rows,1,drugsTableFormat);
            else
                c.insertTable(rows,2,drugsTableFormat);

            if(roshettaSettings.drugsPrintMode == mSettings::drugsPrintMode::both){
                fillCurrentDrugs(c,"PRESCRIPTION");
                fillBaseDrugs(c,"CHRONIC DRUGS");
                c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,2);
            }
            else {
                if(roshettaSettings.drugsPrintMode == mSettings::drugsPrintMode::visitOnly){
                    fillCurrentDrugs(c,"PRESCRIPTION");
                    c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,2);
                }

                if (roshettaSettings.drugsPrintMode == mSettings::drugsPrintMode::baseOnly){
                    fillBaseDrugs(c,"CHRONIC DRUGS");
                    c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,2);
                }
            }
        }
        else{
            c.movePosition(QTextCursor::NextCell);
        }
    }
    else{
        c.movePosition(QTextCursor::NextBlock);
    }

    if(roshettaSettings.showInvestigations)
        fillRequests(c);

    if(roshettaSettings.showMeasurments)
        fillVitals(c);
    else
        c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,2);

}

void Roshetta::fillCurrentDrugs(QTextCursor &c, const QString &title)
{
    if(roshettaSettings.showOnlyNewlyModifiedAddedDrugs)
        fillDrugs(c,roshettaData.currentAlteredDrugsList,title);
    else
        fillDrugs(c,roshettaData.currentDrugsList,title);
}

void Roshetta::fillBaseDrugs(QTextCursor &c, const QString &title)
{
    if(roshettaSettings.showOnlyNewlyModifiedAddedDrugs)
        fillDrugs(c,roshettaData.baseAlteredDrugsList,title);
    else
        fillDrugs(c,roshettaData.baseDrugsList,title);
}

void Roshetta::fillDrugs(QTextCursor &c, QList<mSettings::drug> &drugs,const QString &title)
{
    QTextTableCellFormat drugsHeaderFormat;
    QTextBlockFormat drugsHeaderBlockFormat;

    QString roshettaStyle = QString(" style=\"font-family:%1;font-size: %2px;font-weight: %3;\" ")
            .arg(roshettaSettings.roshettaFont.fontName,
                 QString::number(roshettaSettings.roshettaFont.fontSize),
                 roshettaSettings.roshettaFont.fontBold? "bold":"normal");

    QString tradeNameStyle = QString(" style=\"font-family:%1;font-size: %2px;font-weight: %3;\" ")
            .arg(roshettaSettings.roshettaFont.fontName,
                 QString::number(roshettaSettings.roshettaFont.fontSize),
                 (roshettaSettings.roshettaFont.fontBold|roshettaSettings.showTradeNamesBold)? "bold":"normal");

    QString doseStyle = QString(" style=\"font-family:%1;font-size: %2px;font-weight: %3;\" ")
            .arg(roshettaSettings.doseFont.fontName,
                 QString::number(roshettaSettings.doseFont.fontSize),
                 (roshettaSettings.doseFont.fontBold | (roshettaSettings.doseFont.fontBold && roshettaSettings.roshettaFont.fontBold))? "bold":"normal");

    if(roshettaSettings.showDrugsTitle){
        drugsHeaderFormat.setBackground(QBrush(QColor(176, 196, 222)));
        //drugsHeaderFormat.setTopPadding(3);
        drugsHeaderBlockFormat.setAlignment(Qt::AlignCenter);
        c.insertHtml(QString("<div %1><b>%2</b></div>").arg(roshettaStyle,title));
        c.currentTable()->cellAt(CurrentDrugRow,0).setFormat(drugsHeaderFormat);
        c.currentTable()->cellAt(CurrentDrugRow,0).firstCursorPosition().setBlockFormat(drugsHeaderBlockFormat);
        c.currentTable()->mergeCells(CurrentDrugRow,0,1,2);
        c.movePosition(QTextCursor::NextCell);
    }

    CurrentDrugRow++;
    foreach (const mSettings::drug & d, drugs) {
        if(roshettaSettings.showDrugsInitDate && roshettaSettings.showDoseNewLine){
            c.insertHtml(QString("<div align=left dir=LTR %4>%1 %2 <i style=\"font-size:7px\"> %3 </i></div>")
                         .arg(d.TradeName," ▶ ",d.StartDate,tradeNameStyle));
        }else{
            c.insertHtml(QString("<div align=left dir=LTR %2>%1</div>")
                         .arg(d.TradeName,tradeNameStyle));
        }

        if(roshettaSettings.showDoseNewLine){
            c.insertHtml("<br>");
            c.insertHtml(QString("<div align=left dir=RTL %2>%1</div>").arg(d.Dose,doseStyle));
        }else{
            c.movePosition(QTextCursor::NextCell);
            c.insertHtml(QString("<div align=right dir=RTL %2>%1</div>").arg(d.Dose,doseStyle));
        }

        c.movePosition(QTextCursor::NextCell);
        CurrentDrugRow++;
    }
}

void Roshetta::fillRequests(QTextCursor &c)
{
    if ( roshettaData.requests.count() == 0 )
        return;


    QString style = QString(" style=\"font-family:%1;font-size: %2px;font-weight: %3;\" ")
            .arg(roshettaSettings.requestsFont.fontName,
                 QString::number(roshettaSettings.requestsFont.fontSize),
                 roshettaSettings.requestsFont.fontBold? "bold":"normal");

    c.insertTable(roshettaData.requests.count()+1,1,requestsTableFormat);

    c.insertHtml(QString("<div %1><b>REQUESTS</b></div>").arg(style));
    c.currentTable()->cellAt(0,0).setFormat(requestsHeaderFormat);
    c.currentTable()->cellAt(0,0).firstCursorPosition().setBlockFormat(requestsHeaderBlockFormat);

    c.movePosition(QTextCursor::NextCell);

    foreach (const QString & req, roshettaData.requests) {
        c.setBlockFormat(requestsBlockFormat);
        c.insertText("✻ ");
        c.insertHtml(QString("<div %1>%2</div>").arg(style,req));
        c.movePosition(QTextCursor::NextCell);
    }
    c.movePosition(QTextCursor::NextBlock);
}

void Roshetta::fillSignaturePrintedOn(QTextCursor &c)
{
    QString style = QString(" style=\"font-family:%1;font-size: %2px;font-weight: %3;\" ")
            .arg(roshettaSettings.roshettaFont.fontName,
                 QString::number((int)(roshettaSettings.roshettaFont.fontSize - 0.2 *roshettaSettings.roshettaFont.fontSize)),
                 roshettaSettings.roshettaFont.fontBold? "bold":"normal");

    c.insertTable(1,2,prefooterFormat);

    if (roshettaSettings.showSignaturePrintedOn){
        c.insertHtml(QString("<div %2><b>printed on:</b> %1</div>").arg(roshettaData.printedinDate,style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %1><b>Physician's Signature:</b></div>").arg(style));
    }else{
        c.movePosition(QTextCursor::NextCell);
    }

}

void Roshetta::fillVitals(QTextCursor &c)
{
    int rows = roshettaData.vitals.getRows();
    if(rows ==0){
        c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,2);
        return;
    }

    c.insertTable(rows+1,2,vitalsTableFormat);

    QString style = QString(" style=\"font-family:%1;font-size: %2px;font-weight: %3;\" ")
            .arg(roshettaSettings.measurementsFont.fontName,
                 QString::number(roshettaSettings.measurementsFont.fontSize),
                 roshettaSettings.measurementsFont.fontBold? "bold":"normal");

    c.insertHtml(QString("<div %1><b>MEASUREMENTS</b></div>").arg(style));
    c.currentTable()->cellAt(0,0).setFormat(headerCellFormat);
    c.currentTable()->cellAt(0,0).firstCursorPosition().setBlockFormat(headerBlockFormat);

    c.movePosition(QTextCursor::NextCell,QTextCursor::MoveAnchor,2);




    if(roshettaData.vitals.weight != 0){
        c.insertHtml(QString("<div %1>W</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2>: %1 KG</div>").arg(QString::number(roshettaData.vitals.weight),style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.height != 0){
        c.insertHtml(QString("<div %1>H</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2>: %1 CM</div>").arg(QString::number(roshettaData.vitals.height),style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.sPo2 != 0){
        c.insertHtml(QString("<div %1>sPo2</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2>: %1 %</div>").arg(QString::number(roshettaData.vitals.sPo2),style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.RBS != ""){
        c.insertHtml(QString("<div %1>RBS</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2>: %1 mg/dl</div>").arg(roshettaData.vitals.RBS,style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.pulse != 0){
        c.insertHtml(QString("<div %1>PR</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2>: %1 bpm</div>").arg(QString::number(roshettaData.vitals.pulse),style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.RR != 0){
        c.insertHtml(QString("<div %1>RR</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2>: %1 cpm</div>").arg(QString::number(roshettaData.vitals.RR),style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.BP != ""){
        c.insertHtml(QString("<div %1>BP</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2>: %1 mmgh</div>").arg(roshettaData.vitals.BP,style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.T != 0){
        c.insertHtml(QString("<div %1>T</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2>: %1 C</div>").arg(QString::number(roshettaData.vitals.T),style));
        c.movePosition(QTextCursor::NextCell);
    }
    c.currentTable()->mergeCells(0,0,1,2);
    c.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,3);
}

void Roshetta::fillFooter(QTextCursor &c)
{
    c.insertFrame(footerFormat);
    QTextBlockFormat footerBlockFormat = c.blockFormat();
    footerBlockFormat.setAlignment(Qt::AlignCenter);
    c.select(QTextCursor::BlockUnderCursor);
    c.setBlockFormat(footerBlockFormat);

    if(roshettaSettings.showPrescriptionHeaderFooterLogo)
        c.insertHtml(QString(dataIOhelper::readFile(FOOTERFILE)));
}

void Roshetta::fillDiet(QTextCursor &c)
{
    QTextTableFormat dietTableFormat;
    dietTableFormat.setWidth(mWidth);
    dietTableFormat.setBorder(0);
    c.insertTable(1,1,dietTableFormat);
    c.insertHtml(roshettaData.diet.contents);
}