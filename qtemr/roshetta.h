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
    void makeHeader();
    void makeBanner();
    void makeBody();
    void makeFooter();
    void fillBanner(QTextCursor &c);
    void fillBody(QTextCursor &c);
    void fillCurrentDrugs(QTextCursor &c, const QString &title);
    void fillBaseDrugs(QTextCursor &c, const QString &title);
    void fillDrugs(QTextCursor &c, QList<mSettings::drug> &drugs, const QString &title);
    void fillRequests(QTextCursor &c);
    void fillVitals(QTextCursor &c);
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
    QTextTableFormat requestsTableFormat;
    QTextTable *bannerTable;
    int CurrentDrugRow=0;
    mSettings::prescriptionPrintSettings roshettaSettings;

};

#endif // ROSHETTA_H
