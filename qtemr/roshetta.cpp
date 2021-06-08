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
    cursor.insertFrame(bannerFrameFormat);
    bannerTable = cursor.insertTable(2,6,bannerFormat);
    fillBanner(cursor);
    cursor.movePosition(QTextCursor::NextBlock);
    cursor.insertTable(1,1,bodyFormat);
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

    bannerFormat.setWidth(mWidth);
    bannerFormat.setHeight(44);
    bannerFormat.setBorder(0);
    bannerFormat.setMargin(0);
    bannerFormat.setPadding(0);
}

void Roshetta::makeBody()
{
    double bodyHeight = mHeight -( 50 + 50 + 42 + 30);
    bodyFormat.setWidth(mWidth);
    bodyFormat.setHeight(bodyHeight);
    bodyFormat.setBorder(0);
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
    c.insertHtml("<b>NAME:</b>");
    c.movePosition(QTextCursor::NextCell);
    c.insertText(roshettaData.name);
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml("<b>AGE:</b>");
    c.movePosition(QTextCursor::NextCell);
    c.insertText(roshettaData.printableAge);
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml("<b>CODE:</b>");
    c.movePosition(QTextCursor::NextCell);
    c.insertText(roshettaData.ID);
    c.insertText("▶");
    c.insertText(roshettaData.visitSymbole);
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml("<b>DIAGNOSIS:</b>");
    c.movePosition(QTextCursor::NextCell);
    c.insertText(roshettaData.Diagnosis);
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml("<b>DATE:</b>");
    c.movePosition(QTextCursor::NextCell);
    c.insertText(roshettaData.visitDate);
    c.movePosition(QTextCursor::NextCell);
    c.insertHtml("<b>NEXT:</b>");
    c.movePosition(QTextCursor::NextCell);
    c.insertText(roshettaData.nextDate);
    c.movePosition(QTextCursor::NextBlock);
}

double Roshetta::inch2px(const qreal &x)
{
    return x * qApp->desktop()->logicalDpiX();
}
