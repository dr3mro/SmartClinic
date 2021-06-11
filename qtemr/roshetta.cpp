#include "roshetta.h"
#include <QApplication>
#include <QDesktopWidget>
Roshetta::Roshetta(QObject *parent) : QObject(parent),
    mRoshetta(new QTextDocument(this))
{

}

QTextDocument * Roshetta::createRoshetta(const mSettings::Roshetta &_Roshetta, const mSettings::prescriptionPrintSettings &_pSettings)
{

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
    rootFrameFormat.setHeight(mHeight);
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
    cursor.insertHtml("<img src=\"logo.jpg\" width=72 alt=\"logo\" >");
    cursor.movePosition(QTextCursor::NextCell);
    cursor.insertHtml(QString::fromUtf8(dataIOhelper::readFile(HEADERFILE)));

    cursor.movePosition(QTextCursor::NextBlock);

//    QVector<QTextLength> bannertl = QVector<QTextLength>() << QTextLength(QTextLength::PercentageLength,44)
//                                                           << QTextLength(QTextLength::PercentageLength,28)
//                                                           << QTextLength(QTextLength::PercentageLength,28);

    cursor.insertFrame(bannerFrameFormat);

    //bannerFormat.setColumnWidthConstraints(bannertl);
    bannerTable = cursor.insertTable(2,3,bannerFormat);
    fillBanner(cursor);

    cursor.movePosition(QTextCursor::NextBlock);


    QVector<QTextLength> bodytl = QVector<QTextLength>() << QTextLength(QTextLength::PercentageLength,75)
                                                         << QTextLength(QTextLength::PercentageLength,25);
    bodyFormat.setColumnWidthConstraints(bodytl);
    cursor.insertTable(1,2,bodyFormat);
    fillBody(cursor);


    cursor.movePosition(QTextCursor::NextBlock);
    cursor.insertFrame(footerFormat);
    cursor.insertHtml(QString(dataIOhelper::readFile(FOOTERFILE)));
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
    bannerFrameFormat.setBorder(1);
    bannerFrameFormat.setBorderBrush(QBrush(Qt::black));
    bannerFrameFormat.setHeight(42);


    bannerFormat.setAlignment(Qt::AlignHCenter);
    bannerFormat.setWidth(mWidth);
    bannerFormat.setHeight(44);
//    bannerFormat.setBorder(0);
//    bannerFormat.setMargin(0);
//    bannerFormat.setPadding(0);
//    bannerFormat.setCellPadding(0);
//    bannerFormat.setBorderCollapse(true);
}

void Roshetta::makeBody()
{
    double bodyHeight = mHeight -( 50 + 50 + 42 + 30);
    bodyFormat.setWidth(mWidth);
    bodyFormat.setHeight(bodyHeight);
    bodyFormat.setBorder(1);
    bodyFormat.setMargin(0);
}

void Roshetta::makeFooter()
{
    footerFormat.setWidth(mWidth);
    footerFormat.setHeight(40);
    footerFormat.setBorder(1);
    footerFormat.setMargin(0);
    footerFormat.setBorderBrush(QBrush(Qt::black));
    //footerFormat.setBackground(QBrush(Qt::yellow));

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
    c.movePosition(QTextCursor::NextBlock);
}

void Roshetta::fillBody(QTextCursor &c)
{
    fillCurrentDrugs(c,"[PRESCRIPTION]");
    fillBaseDrugs(c,"[CHRONIC DRUGS]");
    c.movePosition(QTextCursor::NextBlock);
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
    c.insertHtml(QString("<h2 style=\"text-align: center;\"><span style=\"background-color: #808080; color: #ffffff;\"><strong>%1</strong></span></h2>").arg(title));
    c.insertHtml("<br>");
    foreach (const mSettings::drug & d, drugs) {
        c.insertHtml(QString("<div align=left dir=LTR >℞  <b>%1</b> %2 <i style=\"font-size:7px\"> %3 </i></div>").arg(d.TradeName," ▶ " ,d.StartDate));
        c.insertHtml("<br>");
        c.insertHtml(QString("<div align=left dir=RTL>%1</div>").arg(d.Dose));
        c.insertHtml("<br>");

    }
}

double Roshetta::inch2px(const qreal &x)
{
    return x * qApp->desktop()->logicalDpiX();
}
