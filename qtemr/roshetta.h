#ifndef ROSHETTA_H
#define ROSHETTA_H

#include <QObject>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextFrameFormat>
#include <QTextFrame>
#include <QTextTable>
#include "staticstrings.h"
#include "dataiohelper.h"
#include "msettings.h"
#include "PageMetrics.h"

class Roshetta : public QObject
{
    Q_OBJECT
public:
    explicit Roshetta(QObject *parent = nullptr);
    QTextDocument * createRoshetta(const mSettings::Roshetta & _Roshetta,const mSettings::prescriptionPrintSettings & _pSettings);
    ~Roshetta();
private:
    mSettings & settings = mSettings::instance();
    void setRoshettaSize();
    void setRootFrame();
    void stackFrames();
    void makeHeader(const mSettings::prescriptionPrintSettings & _pSettings);
    void makeBanner();
    void makeBody();
    void makeFooter();
    void fillBanner(QTextCursor &c);

    double inch2px(const qreal & x );
    double mWidth;
    double mHeight;


    mSettings::Roshetta roshettaData;
    QTextDocument *mRoshetta;
    QTextFrameFormat rootFrameFormat;
    QTextTableFormat headerFormat;
    QTextFrameFormat bannerFrameFormat;
    QTextTableFormat bannerFormat;
    QTextTableFormat bodyFormat;
    QTextFrameFormat footerFormat;
    QTextTableFormat headerTableFormat;
    QTextTableFormat bodyTableFormat;

    QTextTable *bannerTable;

};

#endif // ROSHETTA_H
