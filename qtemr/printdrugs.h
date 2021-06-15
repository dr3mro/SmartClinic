// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef PRINTDRUGS_H
#define PRINTDRUGS_H

#include <QDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QCloseEvent>
#include <QTimer>
#include "mprintpreviewdialog.h"
#include "msettings.h"
#include "roshetta.h"
#include "colorpicker.h"
#include <QSizeF>
#include "wm_add2completer.h"
#include <QtConcurrentRun>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QPageLayout>
namespace Ui {
class printDrugs;
}

class printDrugs : public QDialog
{
    Q_OBJECT

public:
    explicit printDrugs(QWidget *parent = nullptr);
    void savePrintSettings();
    mSettings::prescriptionPrintSettings loadPrintSettings();
    mSettings::prescriptionPrintSettings grabPrintSettings();
    void saveRoshettaAutoComplete();
    void reset();
    void setRoshettaData(const mSettings::Roshetta & _roshetta);
    ~printDrugs();

public slots:
    void showPrintDialog();
    void showPrintPreviewDialog();
    void mPrint();
    void refreshView();

private slots:
    void showEvent(QShowEvent *e);
    void makePrintPreview(QPrinter *preview);

    void printerProfile_activated(int index);
    void showInvs_clicked(bool checked);
    void drugsMode_activated(int index);
    void bannerFontName_activated(const QString &arg1);
    void bannerFontSize_activated(const QString &arg1);
    void bannerFontBold_clicked(bool checked);
    void roshettaFontName_activated(const QString &arg1);
    void roshettaFontSize_activated(const QString &arg1);
    void roshettaFontBold_clicked(bool checked);
    void doseFontName_activated(const QString &arg1);
    void doseFontSize_activated(const QString &arg1);
    void doseFontBold_clicked(bool checked);
    void headerHeightPercent_valueChanged(int arg1);
    void bannerHeightPercent_valueChanged(int arg1);
    void footerHeightPercent_valueChanged(int arg1);
    void header_textChanged();
    void footer_textChanged();
    void paperSizeId_activated(const QString &arg1);
    void SignaturePrintedOn_clicked(bool checked);
    void drugsInitDate_clicked(bool checked);
    void showHeaderFooterLogo_clicked(bool checked);
    void showDrugs_clicked(bool checked);
    void showMesurements_clicked(bool checked);
    void showDrugsTableOutline_clicked(bool checked);
    void showDrugsTitle_clicked(bool checked);
    void showBanner_clicked(bool checked);
    void showOnlyNewlyModifiedAddedDrugs_clicked(bool checked);
    void showTradeNamesBold_clicked(bool checked);
    void showDoseNewLine_clicked(bool checked);
    void pageMargin_valueChanged(int arg1);
    void logoSize_activated(const QString &arg1);
    void lockUnlockButton_toggled(bool checked);
    void ButtonRefresh_clicked();
    void setLogo();
    void resetLogo();

private:
    void setupPrinter(QPrinter *p);
    void printDoc(QPrinter *p, QTextDocument *doc, bool preview=false);
    void applyPageSizeParamaters();
    QPrinter *printer;
    QPrintDialog *dlg;
    mSettings& settings = mSettings::instance();
    mSettings::prescriptionPrintSettings pSettings;
    mSettings::prescriptionPrintSettings lSettings;
    QTimer t;
    QString selectedPrintingProfile;
    wm_add2Completer *wm_add2completer;
    Ui::printDrugs *ui;
    QTextDocument *m_roshetta;
    Roshetta roshettaMaker;
    mSettings::Roshetta roshettaData;


signals:
    void add2AutoComplete(QString w);
    QString refreshRoshetta(mSettings::prescriptionPrintSettings,QString,int);
    void loadCompleters();
    void message(QString title,QString message);

protected:
    void closeEvent(QCloseEvent *e);

};


#endif // PRINTDRUGS_H
