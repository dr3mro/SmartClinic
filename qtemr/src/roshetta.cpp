#include "roshetta.h"
#include <QApplication>
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

    // set Spacer factor
    setSpacingFactor();

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
    mWidth = pageSize.sizePixels(qApp->primaryScreen()->logicalDotsPerInchX()).width() - xMargins;
    mHeight = pageSize.sizePixels(qApp->primaryScreen()->logicalDotsPerInchX()).height() - yMargins;
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

    fillHeader(cursor);

    cursor.movePosition(QTextCursor::NextBlock);

    cursor.insertFrame(bannerFrameFormat);


    if(roshettaSettings.showBanner
            && roshettaSettings.prescriptionBannerStyle == mSettings::bannerStyle::belowHeader)
        fillBanner(cursor);
    else{
        cursor.movePosition(QTextCursor::NextBlock);
    }

    if(/*roshettaSettings.showHorizontalLineBelowHeader &&
            */roshettaSettings.prescriptionBannerStyle == mSettings::bannerStyle::replaceLogo){
        drawHorizontalLineBelowHeader(cursor);
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
    if(roshettaSettings.showBanner && roshettaSettings.prescriptionBannerStyle==mSettings::bannerStyle::belowHeader){
        bannerFrameFormat.setBorder(1);
        bannerFrameFormat.setBorderBrush(QBrush(Qt::lightGray));
        bannerFrameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    }
    else{
        bannerFrameFormat.setBorder(0);
        bannerFrameFormat.setBorderBrush(QBrush(Qt::white));
    }

    if(roshettaSettings.showBanner &&
            roshettaSettings.prescriptionBannerStyle==mSettings::bannerStyle::belowHeader){
        bannerFrameFormat.setHeight((mHeight*roshettaSettings.bannerHeightPercent)/100);


        bannerFormat.setAlignment(Qt::AlignCenter);
        bannerFormat.setWidth(mWidth);
        bannerFormat.setHeight(44);
        bannerFormat.setBorder(0);
        bannerFormat.setLayoutDirection(roshettaSettings.preferArabic? Qt::RightToLeft : Qt::LeftToRight);

        QVector<QTextLength> bannertl = QVector<QTextLength>() << QTextLength(QTextLength::PercentageLength,48)
                                                             << QTextLength(QTextLength::PercentageLength,18)
                                                             << QTextLength(QTextLength::PercentageLength,34);
        bannerFormat.setColumnWidthConstraints(bannertl);
    }else{
        bannerFrameFormat.setHeight(0);
    }

//    bannerFormat.setMargin(0);
//    bannerFormat.setPadding(0);
//    bannerFormat.setCellPadding(0);
//    bannerFormat.setBorderCollapse(true);
}

void Roshetta::makeBody()
{

    double bodyHeight;

    if(roshettaSettings.prescriptionBannerStyle == mSettings::bannerStyle::belowHeader){
        bodyHeight = mHeight -
                ((roshettaSettings.headerHeightPercent +
                  roshettaSettings.footerHeightPercent +
                  roshettaSettings.bannerHeightPercent)*mHeight)/100;
    }else{
        bodyHeight = mHeight -
                ( (roshettaSettings.headerHeightPercent + roshettaSettings.footerHeightPercent + roshettaSettings.bannerHeightPercent  - 3 ) * mHeight )/100;
    }


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
    footerFormat.setBorder(roshettaSettings.showPrescriptionFooter);
    footerFormat.setMargin(0);
    footerFormat.setBorderBrush(QBrush(Qt::darkGray));
    footerFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
}

void Roshetta::fillHeader(QTextCursor &c)
{
    if(roshettaSettings.showPrescriptionLogo
            && roshettaSettings.prescriptionBannerStyle == mSettings::bannerStyle::belowHeader)
        c.insertHtml(QString("<img src=\"logo.jpg\" width=%1 alt=\"logo\" >").arg(roshettaSettings.logoSize));
    else if( roshettaSettings.showBanner &&
            roshettaSettings.prescriptionBannerStyle == mSettings::bannerStyle::replaceLogo){
        fillAltBanner(c);
    }
    c.movePosition(QTextCursor::NextCell);

    if(roshettaSettings.showPrescriptionHeader)
        c.insertHtml(QString::fromUtf8(dataIOhelper::readFile(HEADERFILE)));
}

void Roshetta::fillBanner(QTextCursor &c)
{
    QLocale loc = roshettaSettings.preferArabic ? QLocale(QLocale::Arabic,QLocale::Egypt):QLocale(QLocale::English,QLocale::UnitedStates);
    QString datefmt = roshettaSettings.preferArabic ? "ddd yyyy/MM/dd":"ddd dd/MM/yyyy";
    QString nextDate,visitDate;

    QString patient_age_sex = QString("%2%1")
            .arg(roshettaData.sex == mSettings::mSex::male ? "m":"f",
                 dataHelper::julianToAge(QDate::currentDate().toJulianDay() - roshettaData.age,
                                         roshettaData.ageStyle));
    if(roshettaData.caseClosed || roshettaData.printedinDate.date() == roshettaData.nextDate)
        nextDate = roshettaData.getNextFromJulian(roshettaData.nextDate.toJulianDay());
    else
        nextDate = loc.toString(roshettaData.nextDate,datefmt);


    visitDate = loc.toString(roshettaData.visitDate,datefmt);

    bannerTable = c.insertTable(2,3,bannerFormat);
    QString style = QString(" style=\"font-family:%1;font-size: %2px;font-weight: %3;\" ")
            .arg(roshettaSettings.bannerFont.fontName,
                 QString::number(roshettaSettings.bannerFont.fontSize),
                 roshettaSettings.bannerFont.fontBold? "bold":"normal");

    c.insertHtml(QString("<div %2><b>Nx:</b>%1</div>").arg(roshettaData.name,style));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<div %2><b>ASx:</b>%1</div>").arg(patient_age_sex,style));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<div %2><b>eDt:</b>%1</div>").arg(visitDate,style));
    c.movePosition(QTextCursor::NextCell);

    c.insertHtml(QString("<div %2><b>Dx:</b>%1</div>").arg(roshettaData.Diagnosis,style));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<div %3><b>ID:</b>%1</div>").arg(roshettaData.ID,style));
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml(QString("<div %2><b>fDt:</b>%1 %3</div>").arg(nextDate,style,roshettaData.visitSymbole));

}

void Roshetta::fillBody(QTextCursor &c)
{
    c.insertTable(1,2,bodyFormat);

    CurrentDrugRow =0; // to follow filling of table current row

    if(roshettaSettings.showDrugs){
        int rows=0;

        if(roshettaSettings.drugsPrintMode == mSettings::drugsPrintMode::both){
            if(roshettaSettings.showOnlyNewlyModifiedAddedDrugs){
                rows+= roshettaData.currentAlteredDrugsList.count();
                rows+= roshettaData.baseAlteredDrugsList.count();
                allDrugsCount = rows;
                rows+= (roshettaSettings.showDrugsTitle && roshettaData.currentAlteredDrugsList.count() > 0)? 1:0;
                rows+= (roshettaSettings.showDrugsTitle && roshettaData.baseAlteredDrugsList.count() > 0)? 1:0;
            }else{
                rows+= roshettaData.currentDrugsList.count();
                rows+= roshettaData.baseDrugsList.count();
                allDrugsCount = rows;
                rows+= (roshettaSettings.showDrugsTitle && roshettaData.currentDrugsList.count() > 0)? 1:0;
                rows+= (roshettaSettings.showDrugsTitle && roshettaData.baseDrugsList.count() > 0)? 1:0;

            }
        }
        else if (roshettaSettings.drugsPrintMode == mSettings::drugsPrintMode::visitOnly){
            if(roshettaSettings.showOnlyNewlyModifiedAddedDrugs){
                rows+= roshettaData.currentAlteredDrugsList.count();
                allDrugsCount = rows;
                rows+= (roshettaSettings.showDrugsTitle && roshettaData.currentAlteredDrugsList.count() > 0)? 1:0;
            }else{
                rows+= roshettaData.currentDrugsList.count();
                allDrugsCount = rows;
                rows+= (roshettaSettings.showDrugsTitle && roshettaData.currentDrugsList.count() > 0)? 1:0;
            }
        }
        else if (roshettaSettings.drugsPrintMode == mSettings::drugsPrintMode::baseOnly){
            if(roshettaSettings.showOnlyNewlyModifiedAddedDrugs){
                rows+= roshettaData.baseAlteredDrugsList.count();
                allDrugsCount = rows;
                rows+= (roshettaSettings.showDrugsTitle && roshettaData.baseAlteredDrugsList.count() > 0)? 1:0;
            }else{
                rows+= roshettaData.baseDrugsList.count();
                allDrugsCount = rows;
                rows+= (roshettaSettings.showDrugsTitle && roshettaData.baseDrugsList.count() > 0)? 1:0;
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
    if(drugs.count() == 0)
        return;

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
        QString dose = d.Dose;

        if(roshettaSettings.preferArabic)
            dataHelper::switchToEasternArabic(dose);

        if(roshettaSettings.showDrugsInitDate && roshettaSettings.showDoseNewLine){
            c.insertHtml(QString("<div align=left dir=LTR %4>%1 %2 <i style=\"font-size:7px\"> %3 </i></div>")
                         .arg(d.TradeName,roshettaSettings.showStartDate ? " ▶ ":"",roshettaSettings.showStartDate ?d.StartDate:"",tradeNameStyle));
        }else{
            c.insertHtml(QString("<div align=left dir=LTR %2>%1</div>")
                         .arg(d.TradeName,tradeNameStyle));
        }

        if(roshettaSettings.showDoseNewLine){
            c.insertHtml("<br>");
            c.insertHtml(QString("<div align=left dir=RTL %2>%1</div>").arg(dose,doseStyle));
        }else{
            c.movePosition(QTextCursor::NextCell);
            c.insertHtml(QString("<div align=right dir=RTL %2>%1</div>").arg(dose,doseStyle));
        }


        if(!roshettaSettings.compactMode)
        {
            if(allDrugsCount > spacerfactor1 )
                c.insertHtml("");
            else if(allDrugsCount > spacerfactor2 )
                c.insertHtml("<br>");
            else
                c.insertHtml("<br><br>");
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
    QString printedinDate = QDateTime::currentDateTime().toString("dddd dd/MM/yyyy hh:mm AP");
    QString style = QString(" style=\"font-family:%1;font-size: %2px;font-weight: %3;\" ")
            .arg(roshettaSettings.signatureFont.fontName,
                 QString::number(roshettaSettings.signatureFont.fontSize),
                 roshettaSettings.signatureFont.fontBold? "bold":"normal");

    c.insertTable(1,2,prefooterFormat);

    if (roshettaSettings.showSignaturePrintedOn){
        c.insertHtml(QString("<div %2><b>printed on:</b> %1</div>").arg(printedinDate,style));
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
        c.insertHtml(QString("<div %2> %1 KG</div>").arg(QString::number(roshettaData.vitals.weight),style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.height != 0){
        c.insertHtml(QString("<div %1>H</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2> %1 CM</div>").arg(QString::number(roshettaData.vitals.height),style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.sPo2 != 0){
        c.insertHtml(QString("<div %1>sPo2</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2> %1 %</div>").arg(QString::number(roshettaData.vitals.sPo2),style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.RBS != ""){
        c.insertHtml(QString("<div %1>RBS</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2> %1 mg/dl</div>").arg(roshettaData.vitals.RBS,style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.pulse != 0){
        c.insertHtml(QString("<div %1>PR</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2> %1 bpm</div>").arg(QString::number(roshettaData.vitals.pulse),style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.RR != 0){
        c.insertHtml(QString("<div %1>RR</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2> %1 cpm</div>").arg(QString::number(roshettaData.vitals.RR),style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.BP != ""){
        c.insertHtml(QString("<div %1>BP</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2> %1 mmHg</div>").arg(roshettaData.vitals.BP,style));
        c.movePosition(QTextCursor::NextCell);
    }
    if(roshettaData.vitals.T != 0){
        c.insertHtml(QString("<div %1>T</div>").arg(style));
        c.movePosition(QTextCursor::NextCell);
        c.insertHtml(QString("<div %2> %1 C</div>").arg(QString::number(roshettaData.vitals.T),style));
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

    if(roshettaSettings.showPrescriptionFooter)
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

void Roshetta::fillAltBanner(QTextCursor &c)
{
    QString altBannerTemplate = QString(dataIOhelper::readFile(BANNERFILE));
    QLocale loc = roshettaSettings.preferArabic ? QLocale(QLocale::Arabic,QLocale::Egypt):QLocale(QLocale::English,QLocale::UnitedStates);
    QString datefmt = roshettaSettings.preferArabic ? "ddd yyyy/MM/dd":"ddd dd/MM/yyyy";
    QString nextDate,visitDate;
    QString patient_age_sex = QString("%2%1")
            .arg(roshettaData.sex == mSettings::mSex::male ? "m":"f",
                 dataHelper::julianToAge(QDate::currentDate().toJulianDay() - roshettaData.age,
                                         roshettaData.ageStyle));
    if(roshettaData.caseClosed || roshettaData.printedinDate.date() == roshettaData.nextDate)
        nextDate = roshettaData.getNextFromJulian(roshettaData.nextDate.toJulianDay());
    else
        nextDate = loc.toString(roshettaData.nextDate,datefmt);


    visitDate = loc.toString(roshettaData.visitDate,datefmt);

    altBannerTemplate.replace("{name}",roshettaData.name);
    altBannerTemplate.replace("{age}",patient_age_sex);
    altBannerTemplate.replace("{visitDate}",visitDate);
    altBannerTemplate.replace("{diagnosis}",roshettaData.Diagnosis);
    altBannerTemplate.replace("{code}",roshettaData.ID);
    altBannerTemplate.replace("{followDate}",nextDate);
    altBannerTemplate.replace("{visitIcon}",roshettaData.visitSymbole);

    altBannerTemplate.replace(QRegularExpression("font-size: ?\\d{1,2}pt;"),QString("font-size: %1pt;").arg(roshettaSettings.bannerFont.fontSize));
    altBannerTemplate.replace(QRegularExpression("font-family:\\s*'([^']*)';"),QString("font-family:'%1';").arg(roshettaSettings.bannerFont.fontName));
    altBannerTemplate.replace(QRegularExpression("font-weight:?\\d{3};"),QString("font-weight:%1;").arg(roshettaSettings.bannerFont.fontBold? 600:400));

    c.insertHtml(altBannerTemplate);
}

void Roshetta::drawHorizontalLineBelowHeader(QTextCursor &c)
{
    drawHorizontalLineBelowHeaderFrameFormat.setHeight(1);
    drawHorizontalLineBelowHeaderFrameFormat.setWidth(mWidth);
    drawHorizontalLineBelowHeaderFrameFormat.setBackground( roshettaSettings.enableBodyHeaderSeparator? Qt::darkGray:Qt::transparent);
    c.insertFrame(drawHorizontalLineBelowHeaderFrameFormat);
}

void Roshetta::setSpacingFactor()
{
    uint paperSize_int = QString(roshettaSettings.paperSizeId.at(1)).toUInt();

    if(!roshettaSettings.compactMode){
        switch (paperSize_int) {
        case 4:
            spacerfactor1 = 9;
            spacerfactor2 = 5;
            break;
        case 5:
            spacerfactor1 = 7;
            spacerfactor2 = 4;
            break;
        case 6:
            spacerfactor1 = 5;
            spacerfactor2 = 3;
            break;
        }
    }
}
