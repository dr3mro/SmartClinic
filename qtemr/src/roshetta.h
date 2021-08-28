#ifndef ROSHETTA_H
#define ROSHETTA_H

#include <QObject>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextFrameFormat>
#include <QTextFrame>
#include <QTextTable>
#include <QTextListFormat>
#include "staticstrings.h"
#include "dataiohelper.h"
#include "datahelper.h"
#include "msettings.h"
#include "3rdparty/pagedTextEdit/PageMetrics.h"

class Roshetta : public QObject
{
    Q_OBJECT
public:
    explicit Roshetta(QObject *parent = nullptr);
    void setDocument(QTextDocument *doc);
    QTextDocument * createRoshetta(const mSettings::Roshetta & _Roshetta,const mSettings::prescriptionPrintSettings & _pSettings);
    ~Roshetta();
private:
    mSettings & settings = mSettings::instance();
    void setRoshettaSize();
    void setRootFrame();
    void stackFrames();
    void makeHeader();
    void makeBanner();
    void makeBody();
    void makeDrugs();
    void makeRequests();
    void makeVitals();
    void makeSignaturePrintedOn();
    void makeFooter();
    void fillHeader(QTextCursor &c);
    void fillBanner(QTextCursor &c);
    void fillBody(QTextCursor &c);
    void fillCurrentDrugs(QTextCursor &c, const QString &title);
    void fillBaseDrugs(QTextCursor &c, const QString &title);
    void fillDrugs(QTextCursor &c, QList<mSettings::drug> &drugs, const QString &title);
    void fillRequests(QTextCursor &c);
    void fillSignaturePrintedOn(QTextCursor &c);
    void fillVitals(QTextCursor &c);
    void fillFooter(QTextCursor &c);
    void fillDiet(QTextCursor &c);
    void fillAltBanner(QTextCursor&c);
    void drawHorizontalLineBelowHeader(QTextCursor &c);
    double mWidth;
    double mHeight;

    mSettings::Roshetta roshettaData;
    QTextDocument *mRoshetta;

    QTextFrameFormat rootFrameFormat;

    QTextTableFormat headerFormat;
    QTextTableFormat headerTableFormat;

    QTextFrameFormat bannerFrameFormat;
    QTextTableFormat bannerFormat;

    QTextTableFormat bodyFormat;
    QTextTableFormat bodyTableFormat;

    QTextTableFormat drugsTableFormat;

    QTextTableFormat requestsTableFormat;
    QTextTableCellFormat requestsHeaderFormat;
    QTextBlockFormat requestsBlockFormat;
    QTextBlockFormat requestsHeaderBlockFormat;

    QTextTableFormat vitalsTableFormat;
    QTextTableCellFormat headerCellFormat;
    QTextBlockFormat headerBlockFormat;

    QTextTableFormat prefooterFormat;
    QTextFrameFormat footerFormat;

    QTextFrameFormat drawHorizontalLineBelowHeaderFrameFormat;

    QTextTable *bannerTable;
    int CurrentDrugRow=0;
    mSettings::prescriptionPrintSettings roshettaSettings;

};

#endif // ROSHETTA_H
