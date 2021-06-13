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
    void on_printerProfile_activated(const QString &arg1);
    void on_showInvs_toggled(bool checked);
    void on_paperSizeId_currentIndexChanged(const QString &arg1);
    void on_drugsMode_activated(int index);
    void on_bannerFont_currentIndexChanged(const QString &arg1);


    void on_bannerFontSize_currentIndexChanged(const QString &arg1);

    void on_bannerFontBold_toggled(bool checked);

    void on_bannerFont_highlighted(const QString &arg1);

    void on_roshettaFont_currentIndexChanged(const QString &arg1);

    void on_roshettaFont_highlighted(const QString &arg1);

    void on_roshettaFontSize_currentIndexChanged(const QString &arg1);

    void on_roshettaFontBold_toggled(bool checked);

    void on_headerHeightPercent_valueChanged(int arg1);

    void on_bannerHeightPercent_valueChanged(int arg1);

    void on_footerHeightPercent_valueChanged(int arg1);

private:
    void tweakRoshetta();
    void setupPrinter(QPrinter *p,const mSettings::prescriptionPrintSettings &pSettings, bool preview=false);
    void printDoc(QPrinter *p, QTextDocument *doc, bool preview=false);
    QTextDocument *getDoc();
    QPrinter *printer;
    QPrintDialog *dlg;
    QTextDocument *doc;
    //colorPicker *cp;
    mSettings& settings = mSettings::instance();
    mSettings::prescriptionPrintSettings pSettings;
    mSettings::prescriptionPrintSettings lSettings;
    QTimer t;
    QString selectedPrintingProfile;
    wm_add2Completer *wm_add2completer;
    Ui::printDrugs *ui;
    QTextDocument *m_roshetta;

    Roshetta roshettaMaker;
    QTextDocument *roshettaDoc;
    mSettings::Roshetta roshettaData;


signals:
    void add2AutoComplete(QString w);
    QString refreshRoshetta(mSettings::prescriptionPrintSettings,QString,int);
    void loadCompleters();
    void message(QString title,QString message);
    void loadPreview();

protected:
    void closeEvent(QCloseEvent *e);

};

#endif // PRINTDRUGS_H
