#ifndef ROSHETTA_H
#define ROSHETTA_H

#if defined __GNUC__
#define GNUINLINE __attribute__((__always_inline__))
#elif defined _MSC_VER
#define GNUINLINE
#endif

#include <QObject>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QTextListFormat>
#include <QTextTable>

#include "3rdparty/pagedTextEdit/PageMetrics.h"
#include "datahelper.h"
#include "dataiohelper.h"
#include "msettings.h"
#include "staticstrings.h"

class Roshetta : public QObject {
  Q_OBJECT
 public:
  explicit Roshetta(QObject *parent = nullptr);
  void setDocument(QTextDocument *doc);
  QTextDocument *createRoshetta(
      const mSettings::Roshetta &_Roshetta,
      const mSettings::prescriptionPrintSettings &_pSettings);
  bool getIsDrugsOutOfRange();
  ~Roshetta();

 private:
  mSettings &settings = mSettings::instance();
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
  inline void fillCurrentDrugs(QTextCursor &c, const QString &title) GNUINLINE;
  inline void fillBaseDrugs(QTextCursor &c, const QString &title) GNUINLINE;
  inline void fillDrugs(QTextCursor &c, QList<mSettings::drug> &drugs,
                        const QString &title) GNUINLINE;
  void fillRequests(QTextCursor &c);
  void fillSignaturePrintedOn(QTextCursor &c);
  void fillVitals(QTextCursor &c);
  void fillFooter(QTextCursor &c);
  void fillDiet(QTextCursor &c);
  void fillAltBanner(QTextCursor &c);
  void drawHorizontalLineBelowHeader(QTextCursor &c);
  void setSpacingFactor();
  double mWidth;
  double mHeight;
  QStringList parsedDrugsList;

  uint spacerfactor1 = 0, spacerfactor2 = 0, spacerfactor3 = 0;
  uint allDrugsCount = 0;
  mSettings::Roshetta roshettaData;
  QTextDocument *mRoshetta;

  QTextFrameFormat rootFrameFormat;

  QTextTableFormat headerFormat;
  QTextTableFormat headerTableFormat;

  QTextFrameFormat bannerFrameFormat;
  QTextTableFormat bannerFormat;
  double bodyHeight;
  double mDrugsTableHeight;

  QTextTableFormat bodyFormat;

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

  int CurrentDrugRow = 0;  // not breaks only cells
  int spacerFactor = 0;
  bool isDrugsOutOfRange = false;
  bool lessExpanded = false;
  const QString lineBreak = "<br>";
  mSettings::prescriptionPrintSettings roshettaSettings;
};

#endif  // ROSHETTA_H
