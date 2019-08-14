/********************************************************************************
** Form generated from reading UI file 'printdrugs.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINTDRUGS_H
#define UI_PRINTDRUGS_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include "colorbutton.h"
#include "mfontcombobox.h"
#include "printbutton.h"
#include "printdialogtab.h"
#include "psdoublespinbox.h"
#include "switch.h"
#include "textedit.h"

QT_BEGIN_NAMESPACE

class Ui_printDrugs
{
public:
    QGridLayout *gridLayout_4;
    QSplitter *splitter_8;
    printButton *fastPrint;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    mFontComboBox *fontComboBox;
    QHBoxLayout *horizontalLayout_13;
    QSplitter *splitter_9;
    QLabel *label_3;
    colorButton *setInkColor;
    QSpacerItem *horizontalSpacer;
    QComboBox *point;
    QToolButton *bold;
    QTabWidget *optionsTabWidget;
    printDialogTab *optionsTab;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_12;
    Switch *tradeNameinBold;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_13;
    Switch *doseNewLine;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_15;
    Switch *noQty;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_30;
    Switch *showDrugsTitle;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_25;
    Switch *centerDrugs;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_18;
    Switch *centerRequests;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_17;
    Switch *showInvs;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_16;
    Switch *showDrugs;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_19;
    Switch *showBanner;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_24;
    Switch *showSeparator;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_14;
    Switch *compactMode;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_31;
    Switch *showDoseInEasternArabic;
    QSpacerItem *verticalSpacer_4;
    printDialogTab *elementsTab;
    QGridLayout *gridLayout;
    QSplitter *splitter_14;
    QLabel *label_20;
    QComboBox *drugsMode;
    QSplitter *splitter_12;
    QLabel *label_10;
    QComboBox *diet;
    QSplitter *splitter_13;
    QLabel *label_11;
    psDoubleSpinBox *dietWidth;
    QSplitter *splitter_5;
    QLabel *label_6;
    psDoubleSpinBox *dietLeftPadding;
    QSplitter *splitter_11;
    QLabel *label_9;
    psDoubleSpinBox *dietTopPadding;
    QSplitter *splitter_6;
    QLabel *label_7;
    QDoubleSpinBox *drugsColPerc;
    QSplitter *splitter_7;
    QLabel *label_8;
    psDoubleSpinBox *invPad;
    QSplitter *splitter_10;
    QLabel *label_29;
    psDoubleSpinBox *invWidth;
    QSplitter *splitter_18;
    QLabel *label_27;
    QSpinBox *bannerWidthPerc;
    QSpacerItem *verticalSpacer_2;
    printDialogTab *paperPrefTab;
    QGridLayout *gridLayout_5;
    QSplitter *splitter_3;
    QLabel *label_2;
    psDoubleSpinBox *leftMargin;
    QSplitter *splitter_15;
    QLabel *label_21;
    psDoubleSpinBox *rightMargin;
    QSplitter *splitter_2;
    QLabel *label;
    psDoubleSpinBox *topMargin;
    QSplitter *splitter_4;
    QLabel *label_5;
    psDoubleSpinBox *pageWidth;
    QSplitter *splitter;
    QLabel *label_4;
    QComboBox *Orientation;
    QSplitter *splitter_17;
    QLabel *label_23;
    psDoubleSpinBox *bottomMargin;
    QSplitter *splitter_16;
    QLabel *label_22;
    psDoubleSpinBox *pageHeight;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_26;
    Switch *fullPage;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_28;
    QComboBox *printerProfile;
    QSpacerItem *verticalSpacer;
    TextEdit *Roshetta;

    void setupUi(QDialog *printDrugs)
    {
        if (printDrugs->objectName().isEmpty())
            printDrugs->setObjectName(QString::fromUtf8("printDrugs"));
        printDrugs->setWindowModality(Qt::NonModal);
        printDrugs->resize(790, 491);
        printDrugs->setMinimumSize(QSize(0, 0));
        gridLayout_4 = new QGridLayout(printDrugs);
        gridLayout_4->setSpacing(3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(3, 3, 3, 3);
        splitter_8 = new QSplitter(printDrugs);
        splitter_8->setObjectName(QString::fromUtf8("splitter_8"));
        splitter_8->setMaximumSize(QSize(230, 16777215));
        splitter_8->setOrientation(Qt::Horizontal);
        fastPrint = new printButton(splitter_8);
        fastPrint->setObjectName(QString::fromUtf8("fastPrint"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fastPrint->sizePolicy().hasHeightForWidth());
        fastPrint->setSizePolicy(sizePolicy);
        fastPrint->setMaximumSize(QSize(230, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Graphics/print"), QSize(), QIcon::Normal, QIcon::Off);
        fastPrint->setIcon(icon);
        fastPrint->setAutoDefault(true);
        splitter_8->addWidget(fastPrint);

        gridLayout_4->addWidget(splitter_8, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(printDrugs);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(230, 16777215));
        groupBox_2->setAlignment(Qt::AlignCenter);
        groupBox_2->setFlat(false);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(3, 3, 3, 3);
        fontComboBox = new mFontComboBox(groupBox_2);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));
        fontComboBox->setEditable(false);

        gridLayout_2->addWidget(fontComboBox, 0, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        splitter_9 = new QSplitter(groupBox_2);
        splitter_9->setObjectName(QString::fromUtf8("splitter_9"));
        splitter_9->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(splitter_9);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        splitter_9->addWidget(label_3);
        setInkColor = new colorButton(splitter_9);
        setInkColor->setObjectName(QString::fromUtf8("setInkColor"));
        setInkColor->setAutoRaise(true);
        splitter_9->addWidget(setInkColor);

        horizontalLayout_13->addWidget(splitter_9);

        horizontalSpacer = new QSpacerItem(38, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer);

        point = new QComboBox(groupBox_2);
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->setObjectName(QString::fromUtf8("point"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(point->sizePolicy().hasHeightForWidth());
        point->setSizePolicy(sizePolicy1);
        point->setMaximumSize(QSize(50, 16777215));
        point->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_13->addWidget(point);

        bold = new QToolButton(groupBox_2);
        bold->setObjectName(QString::fromUtf8("bold"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Graphics/bold"), QSize(), QIcon::Normal, QIcon::Off);
        bold->setIcon(icon1);
        bold->setCheckable(true);
        bold->setAutoRaise(true);

        horizontalLayout_13->addWidget(bold);


        gridLayout_2->addLayout(horizontalLayout_13, 1, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 1, 1, 1, 1);

        optionsTabWidget = new QTabWidget(printDrugs);
        optionsTabWidget->setObjectName(QString::fromUtf8("optionsTabWidget"));
        sizePolicy.setHeightForWidth(optionsTabWidget->sizePolicy().hasHeightForWidth());
        optionsTabWidget->setSizePolicy(sizePolicy);
        optionsTabWidget->setMaximumSize(QSize(230, 16777215));
        optionsTabWidget->setAutoFillBackground(true);
        optionsTabWidget->setStyleSheet(QString::fromUtf8(""));
        optionsTabWidget->setElideMode(Qt::ElideLeft);
        optionsTabWidget->setUsesScrollButtons(false);
        optionsTab = new printDialogTab();
        optionsTab->setObjectName(QString::fromUtf8("optionsTab"));
        gridLayout_3 = new QGridLayout(optionsTab);
        gridLayout_3->setSpacing(1);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(3, 3, 3, 3);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_12 = new QLabel(optionsTab);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout->addWidget(label_12);

        tradeNameinBold = new Switch(optionsTab);
        tradeNameinBold->setObjectName(QString::fromUtf8("tradeNameinBold"));
        sizePolicy1.setHeightForWidth(tradeNameinBold->sizePolicy().hasHeightForWidth());
        tradeNameinBold->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        tradeNameinBold->setFont(font);

        horizontalLayout->addWidget(tradeNameinBold);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_13 = new QLabel(optionsTab);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_2->addWidget(label_13);

        doseNewLine = new Switch(optionsTab);
        doseNewLine->setObjectName(QString::fromUtf8("doseNewLine"));
        sizePolicy1.setHeightForWidth(doseNewLine->sizePolicy().hasHeightForWidth());
        doseNewLine->setSizePolicy(sizePolicy1);
        doseNewLine->setFont(font);

        horizontalLayout_2->addWidget(doseNewLine);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_15 = new QLabel(optionsTab);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_4->addWidget(label_15);

        noQty = new Switch(optionsTab);
        noQty->setObjectName(QString::fromUtf8("noQty"));
        sizePolicy1.setHeightForWidth(noQty->sizePolicy().hasHeightForWidth());
        noQty->setSizePolicy(sizePolicy1);
        noQty->setFont(font);

        horizontalLayout_4->addWidget(noQty);


        gridLayout_3->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_30 = new QLabel(optionsTab);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        horizontalLayout_14->addWidget(label_30);

        showDrugsTitle = new Switch(optionsTab);
        showDrugsTitle->setObjectName(QString::fromUtf8("showDrugsTitle"));
        sizePolicy1.setHeightForWidth(showDrugsTitle->sizePolicy().hasHeightForWidth());
        showDrugsTitle->setSizePolicy(sizePolicy1);
        showDrugsTitle->setFont(font);

        horizontalLayout_14->addWidget(showDrugsTitle);


        gridLayout_3->addLayout(horizontalLayout_14, 3, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_25 = new QLabel(optionsTab);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        horizontalLayout_10->addWidget(label_25);

        centerDrugs = new Switch(optionsTab);
        centerDrugs->setObjectName(QString::fromUtf8("centerDrugs"));
        sizePolicy1.setHeightForWidth(centerDrugs->sizePolicy().hasHeightForWidth());
        centerDrugs->setSizePolicy(sizePolicy1);

        horizontalLayout_10->addWidget(centerDrugs);


        gridLayout_3->addLayout(horizontalLayout_10, 4, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_18 = new QLabel(optionsTab);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_7->addWidget(label_18);

        centerRequests = new Switch(optionsTab);
        centerRequests->setObjectName(QString::fromUtf8("centerRequests"));
        sizePolicy1.setHeightForWidth(centerRequests->sizePolicy().hasHeightForWidth());
        centerRequests->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(centerRequests);


        gridLayout_3->addLayout(horizontalLayout_7, 5, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_17 = new QLabel(optionsTab);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_6->addWidget(label_17);

        showInvs = new Switch(optionsTab);
        showInvs->setObjectName(QString::fromUtf8("showInvs"));
        sizePolicy1.setHeightForWidth(showInvs->sizePolicy().hasHeightForWidth());
        showInvs->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(showInvs);


        gridLayout_3->addLayout(horizontalLayout_6, 6, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_16 = new QLabel(optionsTab);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_5->addWidget(label_16);

        showDrugs = new Switch(optionsTab);
        showDrugs->setObjectName(QString::fromUtf8("showDrugs"));
        sizePolicy1.setHeightForWidth(showDrugs->sizePolicy().hasHeightForWidth());
        showDrugs->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(showDrugs);


        gridLayout_3->addLayout(horizontalLayout_5, 7, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_19 = new QLabel(optionsTab);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_8->addWidget(label_19);

        showBanner = new Switch(optionsTab);
        showBanner->setObjectName(QString::fromUtf8("showBanner"));
        sizePolicy1.setHeightForWidth(showBanner->sizePolicy().hasHeightForWidth());
        showBanner->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(showBanner);


        gridLayout_3->addLayout(horizontalLayout_8, 8, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_24 = new QLabel(optionsTab);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        horizontalLayout_9->addWidget(label_24);

        showSeparator = new Switch(optionsTab);
        showSeparator->setObjectName(QString::fromUtf8("showSeparator"));
        sizePolicy1.setHeightForWidth(showSeparator->sizePolicy().hasHeightForWidth());
        showSeparator->setSizePolicy(sizePolicy1);

        horizontalLayout_9->addWidget(showSeparator);


        gridLayout_3->addLayout(horizontalLayout_9, 9, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_14 = new QLabel(optionsTab);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_3->addWidget(label_14);

        compactMode = new Switch(optionsTab);
        compactMode->setObjectName(QString::fromUtf8("compactMode"));
        sizePolicy1.setHeightForWidth(compactMode->sizePolicy().hasHeightForWidth());
        compactMode->setSizePolicy(sizePolicy1);
        compactMode->setFont(font);

        horizontalLayout_3->addWidget(compactMode);


        gridLayout_3->addLayout(horizontalLayout_3, 10, 0, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_31 = new QLabel(optionsTab);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        horizontalLayout_15->addWidget(label_31);

        showDoseInEasternArabic = new Switch(optionsTab);
        showDoseInEasternArabic->setObjectName(QString::fromUtf8("showDoseInEasternArabic"));
        sizePolicy1.setHeightForWidth(showDoseInEasternArabic->sizePolicy().hasHeightForWidth());
        showDoseInEasternArabic->setSizePolicy(sizePolicy1);
        showDoseInEasternArabic->setFont(font);

        horizontalLayout_15->addWidget(showDoseInEasternArabic);


        gridLayout_3->addLayout(horizontalLayout_15, 11, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 12, 0, 1, 1);

        optionsTabWidget->addTab(optionsTab, QString());
        elementsTab = new printDialogTab();
        elementsTab->setObjectName(QString::fromUtf8("elementsTab"));
        gridLayout = new QGridLayout(elementsTab);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        splitter_14 = new QSplitter(elementsTab);
        splitter_14->setObjectName(QString::fromUtf8("splitter_14"));
        splitter_14->setOrientation(Qt::Horizontal);
        splitter_14->setHandleWidth(0);
        label_20 = new QLabel(splitter_14);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        splitter_14->addWidget(label_20);
        drugsMode = new QComboBox(splitter_14);
        drugsMode->addItem(QString());
        drugsMode->addItem(QString());
        drugsMode->addItem(QString());
        drugsMode->setObjectName(QString::fromUtf8("drugsMode"));
        drugsMode->setMaximumSize(QSize(100, 16777215));
        splitter_14->addWidget(drugsMode);

        gridLayout->addWidget(splitter_14, 0, 0, 1, 1);

        splitter_12 = new QSplitter(elementsTab);
        splitter_12->setObjectName(QString::fromUtf8("splitter_12"));
        splitter_12->setOrientation(Qt::Horizontal);
        splitter_12->setHandleWidth(0);
        label_10 = new QLabel(splitter_12);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        splitter_12->addWidget(label_10);
        diet = new QComboBox(splitter_12);
        diet->setObjectName(QString::fromUtf8("diet"));
        diet->setMinimumSize(QSize(100, 0));
        diet->setMaximumSize(QSize(100, 16777215));
        splitter_12->addWidget(diet);

        gridLayout->addWidget(splitter_12, 1, 0, 1, 1);

        splitter_13 = new QSplitter(elementsTab);
        splitter_13->setObjectName(QString::fromUtf8("splitter_13"));
        splitter_13->setOrientation(Qt::Horizontal);
        splitter_13->setHandleWidth(0);
        label_11 = new QLabel(splitter_13);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        splitter_13->addWidget(label_11);
        dietWidth = new psDoubleSpinBox(splitter_13);
        dietWidth->setObjectName(QString::fromUtf8("dietWidth"));
        dietWidth->setMinimumSize(QSize(50, 0));
        dietWidth->setMaximumSize(QSize(50, 16777215));
        dietWidth->setAlignment(Qt::AlignCenter);
        dietWidth->setMinimum(1.000000000000000);
        dietWidth->setMaximum(12.000000000000000);
        dietWidth->setSingleStep(0.100000000000000);
        splitter_13->addWidget(dietWidth);

        gridLayout->addWidget(splitter_13, 2, 0, 1, 1);

        splitter_5 = new QSplitter(elementsTab);
        splitter_5->setObjectName(QString::fromUtf8("splitter_5"));
        splitter_5->setOrientation(Qt::Horizontal);
        splitter_5->setHandleWidth(0);
        label_6 = new QLabel(splitter_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        splitter_5->addWidget(label_6);
        dietLeftPadding = new psDoubleSpinBox(splitter_5);
        dietLeftPadding->setObjectName(QString::fromUtf8("dietLeftPadding"));
        dietLeftPadding->setMinimumSize(QSize(50, 0));
        dietLeftPadding->setMaximumSize(QSize(50, 16777215));
        dietLeftPadding->setAlignment(Qt::AlignCenter);
        dietLeftPadding->setMinimum(-6.000000000000000);
        dietLeftPadding->setMaximum(6.000000000000000);
        dietLeftPadding->setSingleStep(0.050000000000000);
        dietLeftPadding->setValue(0.000000000000000);
        splitter_5->addWidget(dietLeftPadding);

        gridLayout->addWidget(splitter_5, 3, 0, 1, 1);

        splitter_11 = new QSplitter(elementsTab);
        splitter_11->setObjectName(QString::fromUtf8("splitter_11"));
        splitter_11->setOrientation(Qt::Horizontal);
        splitter_11->setHandleWidth(0);
        label_9 = new QLabel(splitter_11);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        splitter_11->addWidget(label_9);
        dietTopPadding = new psDoubleSpinBox(splitter_11);
        dietTopPadding->setObjectName(QString::fromUtf8("dietTopPadding"));
        dietTopPadding->setMinimumSize(QSize(50, 0));
        dietTopPadding->setMaximumSize(QSize(50, 16777215));
        dietTopPadding->setAlignment(Qt::AlignCenter);
        dietTopPadding->setMinimum(-6.000000000000000);
        dietTopPadding->setMaximum(6.000000000000000);
        dietTopPadding->setSingleStep(0.050000000000000);
        dietTopPadding->setValue(0.000000000000000);
        splitter_11->addWidget(dietTopPadding);

        gridLayout->addWidget(splitter_11, 4, 0, 1, 1);

        splitter_6 = new QSplitter(elementsTab);
        splitter_6->setObjectName(QString::fromUtf8("splitter_6"));
        splitter_6->setOrientation(Qt::Horizontal);
        splitter_6->setHandleWidth(0);
        label_7 = new QLabel(splitter_6);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        splitter_6->addWidget(label_7);
        drugsColPerc = new QDoubleSpinBox(splitter_6);
        drugsColPerc->setObjectName(QString::fromUtf8("drugsColPerc"));
        drugsColPerc->setMinimumSize(QSize(50, 0));
        drugsColPerc->setMaximumSize(QSize(50, 16777215));
        drugsColPerc->setAlignment(Qt::AlignCenter);
        drugsColPerc->setMinimum(33.000000000000000);
        drugsColPerc->setMaximum(100.000000000000000);
        splitter_6->addWidget(drugsColPerc);

        gridLayout->addWidget(splitter_6, 5, 0, 1, 1);

        splitter_7 = new QSplitter(elementsTab);
        splitter_7->setObjectName(QString::fromUtf8("splitter_7"));
        splitter_7->setOrientation(Qt::Horizontal);
        splitter_7->setHandleWidth(0);
        label_8 = new QLabel(splitter_7);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        splitter_7->addWidget(label_8);
        invPad = new psDoubleSpinBox(splitter_7);
        invPad->setObjectName(QString::fromUtf8("invPad"));
        invPad->setMinimumSize(QSize(50, 0));
        invPad->setMaximumSize(QSize(50, 16777215));
        invPad->setAlignment(Qt::AlignCenter);
        invPad->setMinimum(0.100000000000000);
        invPad->setMaximum(7.000000000000000);
        invPad->setSingleStep(0.100000000000000);
        splitter_7->addWidget(invPad);

        gridLayout->addWidget(splitter_7, 6, 0, 1, 1);

        splitter_10 = new QSplitter(elementsTab);
        splitter_10->setObjectName(QString::fromUtf8("splitter_10"));
        splitter_10->setOrientation(Qt::Horizontal);
        splitter_10->setHandleWidth(0);
        label_29 = new QLabel(splitter_10);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        splitter_10->addWidget(label_29);
        invWidth = new psDoubleSpinBox(splitter_10);
        invWidth->setObjectName(QString::fromUtf8("invWidth"));
        invWidth->setMinimumSize(QSize(50, 0));
        invWidth->setMaximumSize(QSize(50, 16777215));
        invWidth->setAlignment(Qt::AlignCenter);
        invWidth->setMinimum(0.100000000000000);
        invWidth->setMaximum(7.000000000000000);
        invWidth->setSingleStep(0.100000000000000);
        splitter_10->addWidget(invWidth);

        gridLayout->addWidget(splitter_10, 7, 0, 1, 1);

        splitter_18 = new QSplitter(elementsTab);
        splitter_18->setObjectName(QString::fromUtf8("splitter_18"));
        splitter_18->setOrientation(Qt::Horizontal);
        splitter_18->setHandleWidth(0);
        label_27 = new QLabel(splitter_18);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        splitter_18->addWidget(label_27);
        bannerWidthPerc = new QSpinBox(splitter_18);
        bannerWidthPerc->setObjectName(QString::fromUtf8("bannerWidthPerc"));
        bannerWidthPerc->setMinimumSize(QSize(50, 0));
        bannerWidthPerc->setMaximumSize(QSize(50, 16777215));
        bannerWidthPerc->setAlignment(Qt::AlignCenter);
        bannerWidthPerc->setMinimum(30);
        bannerWidthPerc->setMaximum(100);
        splitter_18->addWidget(bannerWidthPerc);

        gridLayout->addWidget(splitter_18, 8, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 9, 0, 1, 1);

        optionsTabWidget->addTab(elementsTab, QString());
        splitter_7->raise();
        splitter_11->raise();
        splitter_13->raise();
        splitter_5->raise();
        splitter_12->raise();
        splitter_6->raise();
        splitter_14->raise();
        splitter_18->raise();
        splitter_10->raise();
        paperPrefTab = new printDialogTab();
        paperPrefTab->setObjectName(QString::fromUtf8("paperPrefTab"));
        gridLayout_5 = new QGridLayout(paperPrefTab);
        gridLayout_5->setSpacing(3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(3, 3, 3, 3);
        splitter_3 = new QSplitter(paperPrefTab);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        splitter_3->setHandleWidth(0);
        label_2 = new QLabel(splitter_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        splitter_3->addWidget(label_2);
        leftMargin = new psDoubleSpinBox(splitter_3);
        leftMargin->setObjectName(QString::fromUtf8("leftMargin"));
        leftMargin->setMinimumSize(QSize(50, 0));
        leftMargin->setMaximumSize(QSize(50, 16777215));
        leftMargin->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        leftMargin->setSingleStep(0.010000000000000);
        splitter_3->addWidget(leftMargin);

        gridLayout_5->addWidget(splitter_3, 4, 0, 1, 1);

        splitter_15 = new QSplitter(paperPrefTab);
        splitter_15->setObjectName(QString::fromUtf8("splitter_15"));
        splitter_15->setOrientation(Qt::Horizontal);
        splitter_15->setHandleWidth(0);
        label_21 = new QLabel(splitter_15);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        splitter_15->addWidget(label_21);
        rightMargin = new psDoubleSpinBox(splitter_15);
        rightMargin->setObjectName(QString::fromUtf8("rightMargin"));
        rightMargin->setMinimumSize(QSize(50, 0));
        rightMargin->setMaximumSize(QSize(50, 16777215));
        rightMargin->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        rightMargin->setSingleStep(0.010000000000000);
        splitter_15->addWidget(rightMargin);

        gridLayout_5->addWidget(splitter_15, 6, 0, 1, 1);

        splitter_2 = new QSplitter(paperPrefTab);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_2->setHandleWidth(0);
        label = new QLabel(splitter_2);
        label->setObjectName(QString::fromUtf8("label"));
        splitter_2->addWidget(label);
        topMargin = new psDoubleSpinBox(splitter_2);
        topMargin->setObjectName(QString::fromUtf8("topMargin"));
        topMargin->setMinimumSize(QSize(50, 0));
        topMargin->setMaximumSize(QSize(50, 16777215));
        topMargin->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        topMargin->setDecimals(2);
        topMargin->setSingleStep(0.010000000000000);
        splitter_2->addWidget(topMargin);

        gridLayout_5->addWidget(splitter_2, 3, 0, 1, 1);

        splitter_4 = new QSplitter(paperPrefTab);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setOrientation(Qt::Horizontal);
        splitter_4->setHandleWidth(0);
        label_5 = new QLabel(splitter_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        splitter_4->addWidget(label_5);
        pageWidth = new psDoubleSpinBox(splitter_4);
        pageWidth->setObjectName(QString::fromUtf8("pageWidth"));
        pageWidth->setMinimumSize(QSize(50, 0));
        pageWidth->setMaximumSize(QSize(50, 16777215));
        pageWidth->setSingleStep(0.100000000000000);
        splitter_4->addWidget(pageWidth);

        gridLayout_5->addWidget(splitter_4, 1, 0, 1, 1);

        splitter = new QSplitter(paperPrefTab);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(0);
        label_4 = new QLabel(splitter);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        splitter->addWidget(label_4);
        Orientation = new QComboBox(splitter);
        Orientation->addItem(QString());
        Orientation->addItem(QString());
        Orientation->setObjectName(QString::fromUtf8("Orientation"));
        Orientation->setMinimumSize(QSize(100, 0));
        Orientation->setMaximumSize(QSize(100, 16777215));
        splitter->addWidget(Orientation);

        gridLayout_5->addWidget(splitter, 0, 0, 1, 1);

        splitter_17 = new QSplitter(paperPrefTab);
        splitter_17->setObjectName(QString::fromUtf8("splitter_17"));
        splitter_17->setOrientation(Qt::Horizontal);
        splitter_17->setHandleWidth(0);
        label_23 = new QLabel(splitter_17);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        splitter_17->addWidget(label_23);
        bottomMargin = new psDoubleSpinBox(splitter_17);
        bottomMargin->setObjectName(QString::fromUtf8("bottomMargin"));
        bottomMargin->setMinimumSize(QSize(50, 0));
        bottomMargin->setMaximumSize(QSize(50, 16777215));
        bottomMargin->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        bottomMargin->setDecimals(2);
        bottomMargin->setSingleStep(0.010000000000000);
        splitter_17->addWidget(bottomMargin);

        gridLayout_5->addWidget(splitter_17, 5, 0, 1, 1);

        splitter_16 = new QSplitter(paperPrefTab);
        splitter_16->setObjectName(QString::fromUtf8("splitter_16"));
        splitter_16->setOrientation(Qt::Horizontal);
        splitter_16->setHandleWidth(0);
        label_22 = new QLabel(splitter_16);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        splitter_16->addWidget(label_22);
        pageHeight = new psDoubleSpinBox(splitter_16);
        pageHeight->setObjectName(QString::fromUtf8("pageHeight"));
        pageHeight->setMinimumSize(QSize(50, 0));
        pageHeight->setMaximumSize(QSize(50, 16777215));
        pageHeight->setSingleStep(0.100000000000000);
        splitter_16->addWidget(pageHeight);

        gridLayout_5->addWidget(splitter_16, 2, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_26 = new QLabel(paperPrefTab);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        horizontalLayout_11->addWidget(label_26);

        fullPage = new Switch(paperPrefTab);
        fullPage->setObjectName(QString::fromUtf8("fullPage"));
        sizePolicy1.setHeightForWidth(fullPage->sizePolicy().hasHeightForWidth());
        fullPage->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(fullPage);


        gridLayout_5->addLayout(horizontalLayout_11, 7, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_3, 8, 0, 1, 1);

        optionsTabWidget->addTab(paperPrefTab, QString());
        splitter->raise();
        splitter_2->raise();
        splitter_3->raise();
        splitter_17->raise();
        splitter_16->raise();
        splitter_4->raise();
        splitter_15->raise();

        gridLayout_4->addWidget(optionsTabWidget, 2, 1, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_28 = new QLabel(printDrugs);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        sizePolicy1.setHeightForWidth(label_28->sizePolicy().hasHeightForWidth());
        label_28->setSizePolicy(sizePolicy1);

        horizontalLayout_12->addWidget(label_28);

        printerProfile = new QComboBox(printDrugs);
        printerProfile->addItem(QString());
        printerProfile->addItem(QString());
        printerProfile->addItem(QString());
        printerProfile->addItem(QString());
        printerProfile->setObjectName(QString::fromUtf8("printerProfile"));
        sizePolicy.setHeightForWidth(printerProfile->sizePolicy().hasHeightForWidth());
        printerProfile->setSizePolicy(sizePolicy);

        horizontalLayout_12->addWidget(printerProfile);


        gridLayout_4->addLayout(horizontalLayout_12, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 4, 1, 1, 1);

        Roshetta = new TextEdit(printDrugs);
        Roshetta->setObjectName(QString::fromUtf8("Roshetta"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Impact"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        Roshetta->setFont(font1);
        Roshetta->setLayoutDirection(Qt::LeftToRight);
        Roshetta->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(Roshetta, 0, 0, 5, 1);

        QWidget::setTabOrder(fastPrint, fontComboBox);
        QWidget::setTabOrder(fontComboBox, bold);
        QWidget::setTabOrder(bold, point);
        QWidget::setTabOrder(point, setInkColor);
        QWidget::setTabOrder(setInkColor, optionsTabWidget);
        QWidget::setTabOrder(optionsTabWidget, tradeNameinBold);
        QWidget::setTabOrder(tradeNameinBold, doseNewLine);
        QWidget::setTabOrder(doseNewLine, noQty);
        QWidget::setTabOrder(noQty, centerDrugs);
        QWidget::setTabOrder(centerDrugs, centerRequests);
        QWidget::setTabOrder(centerRequests, showInvs);
        QWidget::setTabOrder(showInvs, showDrugs);
        QWidget::setTabOrder(showDrugs, showBanner);
        QWidget::setTabOrder(showBanner, showSeparator);
        QWidget::setTabOrder(showSeparator, compactMode);
        QWidget::setTabOrder(compactMode, drugsMode);
        QWidget::setTabOrder(drugsMode, diet);
        QWidget::setTabOrder(diet, dietWidth);
        QWidget::setTabOrder(dietWidth, dietLeftPadding);
        QWidget::setTabOrder(dietLeftPadding, dietTopPadding);
        QWidget::setTabOrder(dietTopPadding, drugsColPerc);
        QWidget::setTabOrder(drugsColPerc, invPad);
        QWidget::setTabOrder(invPad, bannerWidthPerc);
        QWidget::setTabOrder(bannerWidthPerc, Orientation);
        QWidget::setTabOrder(Orientation, pageWidth);
        QWidget::setTabOrder(pageWidth, pageHeight);
        QWidget::setTabOrder(pageHeight, topMargin);
        QWidget::setTabOrder(topMargin, leftMargin);
        QWidget::setTabOrder(leftMargin, bottomMargin);
        QWidget::setTabOrder(bottomMargin, rightMargin);
        QWidget::setTabOrder(rightMargin, fullPage);
        QWidget::setTabOrder(fullPage, Roshetta);

        retranslateUi(printDrugs);

        fastPrint->setDefault(true);
        optionsTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(printDrugs);
    } // setupUi

    void retranslateUi(QDialog *printDrugs)
    {
        printDrugs->setWindowTitle(QApplication::translate("printDrugs", "Print", nullptr));
#ifndef QT_NO_TOOLTIP
        fastPrint->setToolTip(QApplication::translate("printDrugs", "<html><head/><body><p>Click <span style=\" font-weight:400;\">to Print . (ALT+P)</span></p><p>Press SHIFT key while Clicking <span style=\" font-weight:400;\">to Show Advanced Print Dialog.</span></p><p>Press CTRL key while clicking <span style=\" font-weight:400;\">to show Print preview.</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        fastPrint->setText(QApplication::translate("printDrugs", "Print", nullptr));
#ifndef QT_NO_SHORTCUT
        fastPrint->setShortcut(QApplication::translate("printDrugs", "Alt+P", nullptr));
#endif // QT_NO_SHORTCUT
        groupBox_2->setTitle(QApplication::translate("printDrugs", "Font Settings", nullptr));
        label_3->setText(QApplication::translate("printDrugs", "<html><head/><body><p>Ink Color:</p></body></html>", nullptr));
        setInkColor->setText(QString());
        point->setItemText(0, QApplication::translate("printDrugs", "8", nullptr));
        point->setItemText(1, QApplication::translate("printDrugs", "9", nullptr));
        point->setItemText(2, QApplication::translate("printDrugs", "10", nullptr));
        point->setItemText(3, QApplication::translate("printDrugs", "11", nullptr));
        point->setItemText(4, QApplication::translate("printDrugs", "12", nullptr));
        point->setItemText(5, QApplication::translate("printDrugs", "14", nullptr));
        point->setItemText(6, QApplication::translate("printDrugs", "16", nullptr));
        point->setItemText(7, QApplication::translate("printDrugs", "18", nullptr));
        point->setItemText(8, QApplication::translate("printDrugs", "20", nullptr));
        point->setItemText(9, QApplication::translate("printDrugs", "22", nullptr));
        point->setItemText(10, QApplication::translate("printDrugs", "24", nullptr));
        point->setItemText(11, QApplication::translate("printDrugs", "36", nullptr));

#ifndef QT_NO_TOOLTIP
        bold->setToolTip(QApplication::translate("printDrugs", "Bold", nullptr));
#endif // QT_NO_TOOLTIP
        bold->setText(QApplication::translate("printDrugs", "...", nullptr));
        label_12->setText(QApplication::translate("printDrugs", "Trade names are in bold.", nullptr));
        tradeNameinBold->setText(QString());
        label_13->setText(QApplication::translate("printDrugs", "Doses are in a new line.", nullptr));
        doseNewLine->setText(QString());
        label_15->setText(QApplication::translate("printDrugs", "Clean drugs names.", nullptr));
        noQty->setText(QString());
        label_30->setText(QApplication::translate("printDrugs", "Show drugs title.", nullptr));
        showDrugsTitle->setText(QString());
        label_25->setText(QApplication::translate("printDrugs", "Align drugs to center.", nullptr));
        centerDrugs->setText(QString());
        label_18->setText(QApplication::translate("printDrugs", "Align requests to center.", nullptr));
        centerRequests->setText(QString());
        label_17->setText(QApplication::translate("printDrugs", "Show requests.", nullptr));
        showInvs->setText(QString());
        label_16->setText(QApplication::translate("printDrugs", "Show drugs.", nullptr));
        showDrugs->setText(QString());
        label_19->setText(QApplication::translate("printDrugs", "Show prescription banner.", nullptr));
        showBanner->setText(QString());
        label_24->setText(QApplication::translate("printDrugs", "Show drugs separator.", nullptr));
        showSeparator->setText(QString());
        label_14->setText(QApplication::translate("printDrugs", "Compact mode.", nullptr));
        compactMode->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_31->setToolTip(QApplication::translate("printDrugs", "<html><head/><body><p>use '\331\240 \331\241 \331\242 \331\243 \331\244 \331\245 \331\246 \331\247 \331\250 \331\251 ' instead of  '0 1 2 3 4 5 6 7 8 9' in dosage</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_31->setText(QApplication::translate("printDrugs", "East Arabic Number", nullptr));
        showDoseInEasternArabic->setText(QString());
        optionsTabWidget->setTabText(optionsTabWidget->indexOf(optionsTab), QApplication::translate("printDrugs", "Options", nullptr));
        label_20->setText(QApplication::translate("printDrugs", "Drugs Mode:", nullptr));
        drugsMode->setItemText(0, QApplication::translate("printDrugs", "Visits Only", nullptr));
        drugsMode->setItemText(1, QApplication::translate("printDrugs", "Basal Only", nullptr));
        drugsMode->setItemText(2, QApplication::translate("printDrugs", "Both", nullptr));

        label_10->setText(QApplication::translate("printDrugs", "Diet:", nullptr));
        label_11->setText(QApplication::translate("printDrugs", "Diet width in inches:", nullptr));
        label_6->setText(QApplication::translate("printDrugs", "Diet left margin in inches:", nullptr));
        label_9->setText(QApplication::translate("printDrugs", "Diet top margin in Inches:", nullptr));
        label_7->setText(QApplication::translate("printDrugs", "Drugs % of page width:", nullptr));
        label_8->setText(QApplication::translate("printDrugs", "Investigations left margin:", nullptr));
        label_29->setText(QApplication::translate("printDrugs", "Investigations Width:", nullptr));
        label_27->setText(QApplication::translate("printDrugs", "Banner %", nullptr));
        optionsTabWidget->setTabText(optionsTabWidget->indexOf(elementsTab), QApplication::translate("printDrugs", "Elements", nullptr));
        label_2->setText(QApplication::translate("printDrugs", "Left Margin:", nullptr));
#ifndef QT_NO_TOOLTIP
        leftMargin->setToolTip(QApplication::translate("printDrugs", "<html><head/><body><p>INCH</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_21->setText(QApplication::translate("printDrugs", "Right Margin:", nullptr));
#ifndef QT_NO_TOOLTIP
        rightMargin->setToolTip(QApplication::translate("printDrugs", "<html><head/><body><p>INCH</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("printDrugs", "Top Margin:", nullptr));
#ifndef QT_NO_TOOLTIP
        topMargin->setToolTip(QApplication::translate("printDrugs", "<html><head/><body><p>INCH</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("printDrugs", "Page width in inches:", nullptr));
        label_4->setText(QApplication::translate("printDrugs", "Orientation:", nullptr));
        Orientation->setItemText(0, QApplication::translate("printDrugs", "Portrait", nullptr));
        Orientation->setItemText(1, QApplication::translate("printDrugs", "Landscape", nullptr));

        label_23->setText(QApplication::translate("printDrugs", "Bottom Margin:", nullptr));
#ifndef QT_NO_TOOLTIP
        bottomMargin->setToolTip(QApplication::translate("printDrugs", "<html><head/><body><p>INCH</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_22->setText(QApplication::translate("printDrugs", "Page height in inches:", nullptr));
        label_26->setText(QApplication::translate("printDrugs", "Print on full page.", nullptr));
        fullPage->setText(QString());
        optionsTabWidget->setTabText(optionsTabWidget->indexOf(paperPrefTab), QApplication::translate("printDrugs", "Paper", nullptr));
        label_28->setText(QApplication::translate("printDrugs", "Profile:", nullptr));
        printerProfile->setItemText(0, QApplication::translate("printDrugs", "Profile1", nullptr));
        printerProfile->setItemText(1, QApplication::translate("printDrugs", "Profile2", nullptr));
        printerProfile->setItemText(2, QApplication::translate("printDrugs", "Profile3", nullptr));
        printerProfile->setItemText(3, QApplication::translate("printDrugs", "Profile4", nullptr));

    } // retranslateUi

};

namespace Ui {
    class printDrugs: public Ui_printDrugs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINTDRUGS_H
