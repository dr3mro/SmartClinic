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
    void loadDiets(QStringList diets);
    void reset();
    void setRoshettaData(const mSettings::Roshetta & _roshetta);
    ~printDrugs();

public slots:
    void showPrintDialog();
    void showPrintPreviewDialog();
    void mPrint();
    void refreshView();

private slots:
//    void on_Orientation_currentIndexChanged(int);
    void setInkColor(QColor c);
    void on_pageWidth_valueChanged(double);
    void setDefaultFontPoint(const QString &arg1);
    void setDefaultFont(const QString &arg1);
    void setDefaultBold(bool bold);
    void on_drugsColPerc_valueChanged(double value);
    void showEvent(QShowEvent *e);
    void makePrintPreview(QPrinter *preview);
    void on_diet_activated(const QString &arg1);
    void on_drugsMode_activated(int index);
    void on_bannerWidthPerc_valueChanged(int);
    void on_pageHeight_valueChanged(double);
    void on_printerProfile_activated(const QString &arg1);
    void on_invPad_editingFinished();
    void on_invWidth_editingFinished();
    void on_showInvs_toggled(bool checked);

private:
    void tweakRoshetta();
    void setMaxValues();
    void resetMaxValues();
    void setupPrinter(QPrinter *p,const mSettings::prescriptionPrintSettings &pSettings, bool preview=false);
    void printDoc(QPrinter *p, QTextDocument *doc, bool preview=false);
    QTextDocument *getDoc();
    QPrinter *printer;
    QPrintDialog *dlg;
    QTextDocument *doc;
    colorPicker *cp;
    mSettings& settings = mSettings::instance();
    QColor inkColor;
    QString defaultFont;
    int defaultPoint;
    bool defaultBold;
    QPalette palette;
    mSettings::prescriptionPrintSettings pSettings;
    mSettings::prescriptionPrintSettings lSettings;
    QString selectedDiet="-";
    QTimer t;
    QString selectedPrintingProfile;
    wm_add2Completer *wm_add2completer;
    Ui::printDrugs *ui;
    QTextDocument *m_roshetta;
    //neo code
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
