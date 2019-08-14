/********************************************************************************
** Form generated from reading UI file 'visitsbox.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISITSBOX_H
#define UI_VISITSBOX_H

#include <QtCore/QDate>
#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "drugsline.h"
#include "drugstable.h"
#include "genericlineedit.h"
#include "investtable.h"
#include "navarrows.h"
#include "textedit.h"
#include "visitboxswitch.h"
#include "visitslist.h"
#include "vitalbox.h"
#include "vprintbutton.h"
#include "vtypecombobox.h"
#include "xcheckbox.h"
#include "xlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_visitsBox
{
public:
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_9;
    vTypeComboBox *comboVisitType;
    QToolButton *ButtonNew;
    QToolButton *ButtonVisit;
    QToolButton *ButtonDel;
    QSpacerItem *horizontalSpacer_60;
    navArrows *preVisit;
    visitsList *visitLists;
    navArrows *nexVisit;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *lockUnlockButton;
    QToolButton *toolButtonRefresh;
    QToolButton *buttonInvest;
    QToolButton *ButtonSave;
    QSpacerItem *horizontalSpacer;
    QToolButton *closeButton;
    QGroupBox *addVisitGroupBox;
    QGridLayout *gridLayout_6;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *pNameLabel;
    QLabel *patientName;
    QSpacerItem *horizontalSpacer_5;
    QLabel *pAgeLabel;
    QLabel *patientAge;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPresentation;
    genericLineEdit *presentation;
    QLabel *labelPresenationAnalysis;
    TextEdit *presentationAnalysis;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QLabel *labelInvestResult;
    investTable *InvestigationsTable;
    TextEdit *investigationsResults;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *buttonAddInvestigations;
    QToolButton *buttonRemoveInvestigations;
    genericLineEdit *investigationsLine;
    QHBoxLayout *horizontalLayout_11;
    QLabel *labelDx;
    genericLineEdit *Diagnosis;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelTreatment;
    QLabel *rxCost;
    drugsTable *vDrugsTable;
    QHBoxLayout *horizontalLayout;
    QToolButton *buttonAddDrug;
    QToolButton *buttonRemoveDrug;
    drugsLine *drugLine;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelFollowUP;
    QDateEdit *dateFollowUp;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_4;
    visitBoxSwitch *CheckButtonCaseClose;
    vPrintButton *fastPrint;
    QWidget *widget2;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_3;
    QLabel *labelAbdomenBack;
    QLabel *LabelLL;
    QLabel *labelGeneral;
    QLabel *labelHeartnLungs;
    QLabel *labelObstUS;
    QLabel *fpalLabel;
    QLabel *notesLabel;
    QLabel *fpal;
    TextEdit *patientGeneralEx;
    TextEdit *patientObstUS;
    TextEdit *patientLL;
    TextEdit *patientHeartLungEx;
    TextEdit *patientAbdomentBack;
    TextEdit *plaintextNotes;
    QLabel *labelPelvic;
    TextEdit *patientPelvicExam;
    QWidget *widgetVitals;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_2;
    QLabel *labelPulse;
    QLabel *labelRR;
    vitalBox *pRR;
    QLabel *labelBP;
    vitalBox *pPulse;
    vitalBox *pBP;
    vitalBox *pTemp;
    QLabel *labelTemp;
    QWidget *widgetBaby;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_baby;
    QLabel *labelWeight;
    xLineEdit *lineEditWeight;
    QLabel *labelLength;
    xLineEdit *lineEditLength;
    QLabel *labelHead;
    xLineEdit *lineEditHead;
    QWidget *ObstWidget;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_2;
    xLineEdit *obstWeight;
    QLabel *label_3;
    QDateEdit *lmpDate;
    QFrame *frame_2;
    QLabel *labelEDD;
    QDateEdit *eddDate;
    QSpacerItem *horizontalSpacer_9;
    xCheckBox *checkBoxAntenatal;

    void setupUi(QDialog *visitsBox)
    {
        if (visitsBox->objectName().isEmpty())
            visitsBox->setObjectName(QString::fromUtf8("visitsBox"));
        visitsBox->resize(784, 806);
        visitsBox->setStyleSheet(QString::fromUtf8(""));
        layoutWidget1 = new QWidget(visitsBox);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 100, 30));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        layoutWidget = new QWidget(visitsBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 100, 30));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_8 = new QGridLayout(visitsBox);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        comboVisitType = new vTypeComboBox(visitsBox);
        comboVisitType->setObjectName(QString::fromUtf8("comboVisitType"));
        comboVisitType->setMinimumSize(QSize(90, 0));
        comboVisitType->setMaximumSize(QSize(100, 16777215));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        comboVisitType->setFont(font);
        comboVisitType->setFrame(true);

        horizontalLayout_9->addWidget(comboVisitType);

        ButtonNew = new QToolButton(visitsBox);
        ButtonNew->setObjectName(QString::fromUtf8("ButtonNew"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ButtonNew->sizePolicy().hasHeightForWidth());
        ButtonNew->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Graphics/add"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonNew->setIcon(icon);

        horizontalLayout_9->addWidget(ButtonNew);

        ButtonVisit = new QToolButton(visitsBox);
        ButtonVisit->setObjectName(QString::fromUtf8("ButtonVisit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Graphics/circle"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonVisit->setIcon(icon1);

        horizontalLayout_9->addWidget(ButtonVisit);

        ButtonDel = new QToolButton(visitsBox);
        ButtonDel->setObjectName(QString::fromUtf8("ButtonDel"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Graphics/minus"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonDel->setIcon(icon2);

        horizontalLayout_9->addWidget(ButtonDel);

        horizontalSpacer_60 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_60);

        preVisit = new navArrows(visitsBox);
        preVisit->setObjectName(QString::fromUtf8("preVisit"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Graphics/back"), QSize(), QIcon::Normal, QIcon::Off);
        preVisit->setIcon(icon3);
        preVisit->setAutoRaise(true);

        horizontalLayout_9->addWidget(preVisit);

        visitLists = new visitsList(visitsBox);
        visitLists->setObjectName(QString::fromUtf8("visitLists"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(visitLists->sizePolicy().hasHeightForWidth());
        visitLists->setSizePolicy(sizePolicy1);
        visitLists->setMinimumSize(QSize(220, 0));
        visitLists->setMaximumSize(QSize(220, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        visitLists->setFont(font1);
        visitLists->setStyleSheet(QString::fromUtf8(""));
        visitLists->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        horizontalLayout_9->addWidget(visitLists);

        nexVisit = new navArrows(visitsBox);
        nexVisit->setObjectName(QString::fromUtf8("nexVisit"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Graphics/forward"), QSize(), QIcon::Normal, QIcon::Off);
        nexVisit->setIcon(icon4);
        nexVisit->setAutoRaise(true);

        horizontalLayout_9->addWidget(nexVisit);

        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);

        lockUnlockButton = new QToolButton(visitsBox);
        lockUnlockButton->setObjectName(QString::fromUtf8("lockUnlockButton"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Graphics/lock"), QSize(), QIcon::Normal, QIcon::Off);
        lockUnlockButton->setIcon(icon5);
        lockUnlockButton->setCheckable(false);

        horizontalLayout_9->addWidget(lockUnlockButton);

        toolButtonRefresh = new QToolButton(visitsBox);
        toolButtonRefresh->setObjectName(QString::fromUtf8("toolButtonRefresh"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Graphics/refresh"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRefresh->setIcon(icon6);

        horizontalLayout_9->addWidget(toolButtonRefresh);

        buttonInvest = new QToolButton(visitsBox);
        buttonInvest->setObjectName(QString::fromUtf8("buttonInvest"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Graphics/paperClip"), QSize(), QIcon::Normal, QIcon::Off);
        buttonInvest->setIcon(icon7);

        horizontalLayout_9->addWidget(buttonInvest);

        ButtonSave = new QToolButton(visitsBox);
        ButtonSave->setObjectName(QString::fromUtf8("ButtonSave"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Graphics/arrow_bottom"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonSave->setIcon(icon8);

        horizontalLayout_9->addWidget(ButtonSave);

        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        closeButton = new QToolButton(visitsBox);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout_9->addWidget(closeButton);


        gridLayout_8->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        addVisitGroupBox = new QGroupBox(visitsBox);
        addVisitGroupBox->setObjectName(QString::fromUtf8("addVisitGroupBox"));
        addVisitGroupBox->setAlignment(Qt::AlignCenter);
        addVisitGroupBox->setFlat(true);
        gridLayout_6 = new QGridLayout(addVisitGroupBox);
        gridLayout_6->setSpacing(0);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(addVisitGroupBox);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy2);
        frame->setMinimumSize(QSize(410, 0));
        frame->setMaximumSize(QSize(410, 16777215));
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 6, 0, 6);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pNameLabel = new QLabel(frame);
        pNameLabel->setObjectName(QString::fromUtf8("pNameLabel"));
        pNameLabel->setFont(font);

        horizontalLayout_3->addWidget(pNameLabel);

        patientName = new QLabel(frame);
        patientName->setObjectName(QString::fromUtf8("patientName"));
        sizePolicy1.setHeightForWidth(patientName->sizePolicy().hasHeightForWidth());
        patientName->setSizePolicy(sizePolicy1);
        patientName->setFont(font);
        patientName->setLayoutDirection(Qt::LeftToRight);
        patientName->setStyleSheet(QString::fromUtf8(""));
        patientName->setTextFormat(Qt::RichText);
        patientName->setScaledContents(true);
        patientName->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        patientName->setMargin(2);
        patientName->setIndent(1);

        horizontalLayout_3->addWidget(patientName);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        pAgeLabel = new QLabel(frame);
        pAgeLabel->setObjectName(QString::fromUtf8("pAgeLabel"));
        pAgeLabel->setFont(font);

        horizontalLayout_3->addWidget(pAgeLabel);

        patientAge = new QLabel(frame);
        patientAge->setObjectName(QString::fromUtf8("patientAge"));

        horizontalLayout_3->addWidget(patientAge);


        gridLayout_5->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(8);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelPresentation = new QLabel(frame);
        labelPresentation->setObjectName(QString::fromUtf8("labelPresentation"));
        labelPresentation->setFont(font);

        horizontalLayout_2->addWidget(labelPresentation);

        presentation = new genericLineEdit(frame);
        presentation->setObjectName(QString::fromUtf8("presentation"));
        presentation->setClearButtonEnabled(true);

        horizontalLayout_2->addWidget(presentation);


        verticalLayout->addLayout(horizontalLayout_2);

        labelPresenationAnalysis = new QLabel(frame);
        labelPresenationAnalysis->setObjectName(QString::fromUtf8("labelPresenationAnalysis"));
        labelPresenationAnalysis->setFont(font);

        verticalLayout->addWidget(labelPresenationAnalysis);

        presentationAnalysis = new TextEdit(frame);
        presentationAnalysis->setObjectName(QString::fromUtf8("presentationAnalysis"));
        sizePolicy1.setHeightForWidth(presentationAnalysis->sizePolicy().hasHeightForWidth());
        presentationAnalysis->setSizePolicy(sizePolicy1);
        presentationAnalysis->setTabChangesFocus(true);

        verticalLayout->addWidget(presentationAnalysis);


        gridLayout_5->addLayout(verticalLayout, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, 2, -1, 2);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout_7->addWidget(label);

        labelInvestResult = new QLabel(frame);
        labelInvestResult->setObjectName(QString::fromUtf8("labelInvestResult"));
        labelInvestResult->setFont(font);

        horizontalLayout_7->addWidget(labelInvestResult);


        gridLayout->addLayout(horizontalLayout_7, 0, 0, 1, 2);

        InvestigationsTable = new investTable(frame);
        InvestigationsTable->setObjectName(QString::fromUtf8("InvestigationsTable"));
        sizePolicy1.setHeightForWidth(InvestigationsTable->sizePolicy().hasHeightForWidth());
        InvestigationsTable->setSizePolicy(sizePolicy1);
        InvestigationsTable->setAlternatingRowColors(false);
        InvestigationsTable->setSelectionBehavior(QAbstractItemView::SelectItems);
        InvestigationsTable->setShowGrid(false);
        InvestigationsTable->setGridStyle(Qt::SolidLine);
        InvestigationsTable->setWordWrap(false);
        InvestigationsTable->setCornerButtonEnabled(false);
        InvestigationsTable->horizontalHeader()->setVisible(false);
        InvestigationsTable->horizontalHeader()->setMinimumSectionSize(20);
        InvestigationsTable->horizontalHeader()->setHighlightSections(false);
        InvestigationsTable->verticalHeader()->setVisible(false);
        InvestigationsTable->verticalHeader()->setMinimumSectionSize(20);
        InvestigationsTable->verticalHeader()->setDefaultSectionSize(20);
        InvestigationsTable->verticalHeader()->setHighlightSections(true);

        gridLayout->addWidget(InvestigationsTable, 1, 0, 1, 1);

        investigationsResults = new TextEdit(frame);
        investigationsResults->setObjectName(QString::fromUtf8("investigationsResults"));
        sizePolicy1.setHeightForWidth(investigationsResults->sizePolicy().hasHeightForWidth());
        investigationsResults->setSizePolicy(sizePolicy1);
        investigationsResults->setTabChangesFocus(true);

        gridLayout->addWidget(investigationsResults, 1, 1, 2, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        buttonAddInvestigations = new QToolButton(frame);
        buttonAddInvestigations->setObjectName(QString::fromUtf8("buttonAddInvestigations"));
        buttonAddInvestigations->setIcon(icon);
        buttonAddInvestigations->setAutoRaise(true);

        horizontalLayout_6->addWidget(buttonAddInvestigations);

        buttonRemoveInvestigations = new QToolButton(frame);
        buttonRemoveInvestigations->setObjectName(QString::fromUtf8("buttonRemoveInvestigations"));
        buttonRemoveInvestigations->setEnabled(false);
        buttonRemoveInvestigations->setIcon(icon2);
        buttonRemoveInvestigations->setAutoRaise(true);

        horizontalLayout_6->addWidget(buttonRemoveInvestigations);

        investigationsLine = new genericLineEdit(frame);
        investigationsLine->setObjectName(QString::fromUtf8("investigationsLine"));
        sizePolicy1.setHeightForWidth(investigationsLine->sizePolicy().hasHeightForWidth());
        investigationsLine->setSizePolicy(sizePolicy1);
        investigationsLine->setClearButtonEnabled(true);

        horizontalLayout_6->addWidget(investigationsLine);


        gridLayout->addLayout(horizontalLayout_6, 2, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout, 2, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(-1, 0, -1, -1);
        labelDx = new QLabel(frame);
        labelDx->setObjectName(QString::fromUtf8("labelDx"));
        labelDx->setFont(font);

        horizontalLayout_11->addWidget(labelDx);

        Diagnosis = new genericLineEdit(frame);
        Diagnosis->setObjectName(QString::fromUtf8("Diagnosis"));
        Diagnosis->setClearButtonEnabled(true);

        horizontalLayout_11->addWidget(Diagnosis);


        gridLayout_5->addLayout(horizontalLayout_11, 3, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 2, -1, 2);
        labelTreatment = new QLabel(frame);
        labelTreatment->setObjectName(QString::fromUtf8("labelTreatment"));
        labelTreatment->setFont(font);

        horizontalLayout_5->addWidget(labelTreatment);

        rxCost = new QLabel(frame);
        rxCost->setObjectName(QString::fromUtf8("rxCost"));
        rxCost->setFont(font);
        rxCost->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(rxCost);


        verticalLayout_2->addLayout(horizontalLayout_5);

        vDrugsTable = new drugsTable(frame);
        vDrugsTable->setObjectName(QString::fromUtf8("vDrugsTable"));
        vDrugsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        vDrugsTable->setShowGrid(false);
        vDrugsTable->setWordWrap(false);
        vDrugsTable->setCornerButtonEnabled(false);
        vDrugsTable->horizontalHeader()->setVisible(false);
        vDrugsTable->horizontalHeader()->setMinimumSectionSize(20);
        vDrugsTable->horizontalHeader()->setHighlightSections(false);
        vDrugsTable->verticalHeader()->setVisible(false);
        vDrugsTable->verticalHeader()->setMinimumSectionSize(20);
        vDrugsTable->verticalHeader()->setDefaultSectionSize(20);
        vDrugsTable->verticalHeader()->setHighlightSections(false);

        verticalLayout_2->addWidget(vDrugsTable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        buttonAddDrug = new QToolButton(frame);
        buttonAddDrug->setObjectName(QString::fromUtf8("buttonAddDrug"));
        buttonAddDrug->setIcon(icon);
        buttonAddDrug->setAutoRaise(true);

        horizontalLayout->addWidget(buttonAddDrug);

        buttonRemoveDrug = new QToolButton(frame);
        buttonRemoveDrug->setObjectName(QString::fromUtf8("buttonRemoveDrug"));
        buttonRemoveDrug->setIcon(icon2);
        buttonRemoveDrug->setAutoRaise(true);

        horizontalLayout->addWidget(buttonRemoveDrug);

        drugLine = new drugsLine(frame);
        drugLine->setObjectName(QString::fromUtf8("drugLine"));
        drugLine->setClearButtonEnabled(true);

        horizontalLayout->addWidget(drugLine);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_5->addLayout(verticalLayout_2, 4, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(5);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 2, -1, -1);
        labelFollowUP = new QLabel(frame);
        labelFollowUP->setObjectName(QString::fromUtf8("labelFollowUP"));
        sizePolicy2.setHeightForWidth(labelFollowUP->sizePolicy().hasHeightForWidth());
        labelFollowUP->setSizePolicy(sizePolicy2);
        labelFollowUP->setFont(font);

        horizontalLayout_4->addWidget(labelFollowUP);

        dateFollowUp = new QDateEdit(frame);
        dateFollowUp->setObjectName(QString::fromUtf8("dateFollowUp"));
        dateFollowUp->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        dateFollowUp->setReadOnly(false);
        dateFollowUp->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        dateFollowUp->setDateTime(QDateTime(QDate(2014, 1, 1), QTime(0, 0, 0)));
        dateFollowUp->setCalendarPopup(true);

        horizontalLayout_4->addWidget(dateFollowUp);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        CheckButtonCaseClose = new visitBoxSwitch(frame);
        CheckButtonCaseClose->setObjectName(QString::fromUtf8("CheckButtonCaseClose"));
        sizePolicy.setHeightForWidth(CheckButtonCaseClose->sizePolicy().hasHeightForWidth());
        CheckButtonCaseClose->setSizePolicy(sizePolicy);
        CheckButtonCaseClose->setFont(font);
        CheckButtonCaseClose->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(CheckButtonCaseClose);

        fastPrint = new vPrintButton(frame);
        fastPrint->setObjectName(QString::fromUtf8("fastPrint"));
        fastPrint->setEnabled(true);
        sizePolicy1.setHeightForWidth(fastPrint->sizePolicy().hasHeightForWidth());
        fastPrint->setSizePolicy(sizePolicy1);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Graphics/print"), QSize(), QIcon::Normal, QIcon::Off);
        fastPrint->setIcon(icon9);

        horizontalLayout_4->addWidget(fastPrint);


        gridLayout_5->addLayout(horizontalLayout_4, 5, 0, 1, 1);


        gridLayout_6->addWidget(frame, 0, 0, 2, 1);

        widget2 = new QWidget(addVisitGroupBox);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        sizePolicy1.setHeightForWidth(widget2->sizePolicy().hasHeightForWidth());
        widget2->setSizePolicy(sizePolicy1);
        widget2->setMinimumSize(QSize(350, 0));
        widget2->setMaximumSize(QSize(350, 16777215));
        gridLayout_7 = new QGridLayout(widget2);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(9, 2, 0, 6);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        labelAbdomenBack = new QLabel(widget2);
        labelAbdomenBack->setObjectName(QString::fromUtf8("labelAbdomenBack"));
        labelAbdomenBack->setFont(font);

        gridLayout_3->addWidget(labelAbdomenBack, 9, 1, 1, 1);

        LabelLL = new QLabel(widget2);
        LabelLL->setObjectName(QString::fromUtf8("LabelLL"));
        LabelLL->setFont(font);

        gridLayout_3->addWidget(LabelLL, 11, 1, 1, 1);

        labelGeneral = new QLabel(widget2);
        labelGeneral->setObjectName(QString::fromUtf8("labelGeneral"));
        labelGeneral->setFont(font);

        gridLayout_3->addWidget(labelGeneral, 5, 1, 1, 1);

        labelHeartnLungs = new QLabel(widget2);
        labelHeartnLungs->setObjectName(QString::fromUtf8("labelHeartnLungs"));
        labelHeartnLungs->setFont(font);

        gridLayout_3->addWidget(labelHeartnLungs, 7, 1, 1, 1);

        labelObstUS = new QLabel(widget2);
        labelObstUS->setObjectName(QString::fromUtf8("labelObstUS"));
        labelObstUS->setFont(font);

        gridLayout_3->addWidget(labelObstUS, 0, 1, 1, 1);

        fpalLabel = new QLabel(widget2);
        fpalLabel->setObjectName(QString::fromUtf8("fpalLabel"));
        sizePolicy2.setHeightForWidth(fpalLabel->sizePolicy().hasHeightForWidth());
        fpalLabel->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(fpalLabel, 0, 2, 1, 1);

        notesLabel = new QLabel(widget2);
        notesLabel->setObjectName(QString::fromUtf8("notesLabel"));
        notesLabel->setFont(font);

        gridLayout_3->addWidget(notesLabel, 13, 1, 1, 1);

        fpal = new QLabel(widget2);
        fpal->setObjectName(QString::fromUtf8("fpal"));
        sizePolicy2.setHeightForWidth(fpal->sizePolicy().hasHeightForWidth());
        fpal->setSizePolicy(sizePolicy2);
        fpal->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(fpal, 0, 3, 1, 1);

        patientGeneralEx = new TextEdit(widget2);
        patientGeneralEx->setObjectName(QString::fromUtf8("patientGeneralEx"));
        patientGeneralEx->setTabChangesFocus(true);

        gridLayout_3->addWidget(patientGeneralEx, 6, 1, 1, 3);

        patientObstUS = new TextEdit(widget2);
        patientObstUS->setObjectName(QString::fromUtf8("patientObstUS"));

        gridLayout_3->addWidget(patientObstUS, 2, 1, 1, 3);

        patientLL = new TextEdit(widget2);
        patientLL->setObjectName(QString::fromUtf8("patientLL"));
        patientLL->setTabChangesFocus(true);

        gridLayout_3->addWidget(patientLL, 12, 1, 1, 3);

        patientHeartLungEx = new TextEdit(widget2);
        patientHeartLungEx->setObjectName(QString::fromUtf8("patientHeartLungEx"));
        patientHeartLungEx->setTabChangesFocus(true);

        gridLayout_3->addWidget(patientHeartLungEx, 8, 1, 1, 3);

        patientAbdomentBack = new TextEdit(widget2);
        patientAbdomentBack->setObjectName(QString::fromUtf8("patientAbdomentBack"));
        patientAbdomentBack->setTabChangesFocus(true);

        gridLayout_3->addWidget(patientAbdomentBack, 10, 1, 1, 3);

        plaintextNotes = new TextEdit(widget2);
        plaintextNotes->setObjectName(QString::fromUtf8("plaintextNotes"));
        plaintextNotes->setMaximumSize(QSize(16777215, 80));
        plaintextNotes->setTabChangesFocus(true);

        gridLayout_3->addWidget(plaintextNotes, 14, 1, 1, 3);

        labelPelvic = new QLabel(widget2);
        labelPelvic->setObjectName(QString::fromUtf8("labelPelvic"));
        labelPelvic->setFont(font);

        gridLayout_3->addWidget(labelPelvic, 3, 1, 1, 1);

        patientPelvicExam = new TextEdit(widget2);
        patientPelvicExam->setObjectName(QString::fromUtf8("patientPelvicExam"));

        gridLayout_3->addWidget(patientPelvicExam, 4, 1, 1, 3);


        gridLayout_7->addLayout(gridLayout_3, 1, 0, 1, 1);

        widgetVitals = new QWidget(widget2);
        widgetVitals->setObjectName(QString::fromUtf8("widgetVitals"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widgetVitals->sizePolicy().hasHeightForWidth());
        widgetVitals->setSizePolicy(sizePolicy3);
        widgetVitals->setMinimumSize(QSize(0, 0));
        gridLayout_9 = new QGridLayout(widgetVitals);
        gridLayout_9->setSpacing(3);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(3, 3, 3, 3);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelPulse = new QLabel(widgetVitals);
        labelPulse->setObjectName(QString::fromUtf8("labelPulse"));

        gridLayout_2->addWidget(labelPulse, 0, 0, 1, 1);

        labelRR = new QLabel(widgetVitals);
        labelRR->setObjectName(QString::fromUtf8("labelRR"));

        gridLayout_2->addWidget(labelRR, 0, 2, 1, 1);

        pRR = new vitalBox(widgetVitals);
        pRR->setObjectName(QString::fromUtf8("pRR"));
        pRR->setInputMethodHints(Qt::ImhNone);
        pRR->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(pRR, 0, 3, 1, 1);

        labelBP = new QLabel(widgetVitals);
        labelBP->setObjectName(QString::fromUtf8("labelBP"));

        gridLayout_2->addWidget(labelBP, 0, 4, 1, 1);

        pPulse = new vitalBox(widgetVitals);
        pPulse->setObjectName(QString::fromUtf8("pPulse"));
        pPulse->setInputMethodHints(Qt::ImhNone);
        pPulse->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(pPulse, 0, 1, 1, 1);

        pBP = new vitalBox(widgetVitals);
        pBP->setObjectName(QString::fromUtf8("pBP"));
        pBP->setMinimumSize(QSize(75, 0));
        pBP->setInputMethodHints(Qt::ImhDigitsOnly);
        pBP->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(pBP, 0, 5, 1, 1);

        pTemp = new vitalBox(widgetVitals);
        pTemp->setObjectName(QString::fromUtf8("pTemp"));
        pTemp->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(pTemp, 0, 8, 1, 1);

        labelTemp = new QLabel(widgetVitals);
        labelTemp->setObjectName(QString::fromUtf8("labelTemp"));
        labelTemp->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(labelTemp, 0, 6, 1, 1);


        gridLayout_9->addLayout(gridLayout_2, 3, 0, 1, 1);

        widgetBaby = new QWidget(widgetVitals);
        widgetBaby->setObjectName(QString::fromUtf8("widgetBaby"));
        gridLayout_4 = new QGridLayout(widgetBaby);
        gridLayout_4->setSpacing(1);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_baby = new QHBoxLayout();
        horizontalLayout_baby->setSpacing(6);
        horizontalLayout_baby->setObjectName(QString::fromUtf8("horizontalLayout_baby"));
        labelWeight = new QLabel(widgetBaby);
        labelWeight->setObjectName(QString::fromUtf8("labelWeight"));

        horizontalLayout_baby->addWidget(labelWeight);

        lineEditWeight = new xLineEdit(widgetBaby);
        lineEditWeight->setObjectName(QString::fromUtf8("lineEditWeight"));

        horizontalLayout_baby->addWidget(lineEditWeight);

        labelLength = new QLabel(widgetBaby);
        labelLength->setObjectName(QString::fromUtf8("labelLength"));

        horizontalLayout_baby->addWidget(labelLength);

        lineEditLength = new xLineEdit(widgetBaby);
        lineEditLength->setObjectName(QString::fromUtf8("lineEditLength"));

        horizontalLayout_baby->addWidget(lineEditLength);

        labelHead = new QLabel(widgetBaby);
        labelHead->setObjectName(QString::fromUtf8("labelHead"));

        horizontalLayout_baby->addWidget(labelHead);

        lineEditHead = new xLineEdit(widgetBaby);
        lineEditHead->setObjectName(QString::fromUtf8("lineEditHead"));

        horizontalLayout_baby->addWidget(lineEditHead);


        gridLayout_4->addLayout(horizontalLayout_baby, 0, 0, 1, 1);


        gridLayout_9->addWidget(widgetBaby, 2, 0, 1, 1);

        ObstWidget = new QWidget(widgetVitals);
        ObstWidget->setObjectName(QString::fromUtf8("ObstWidget"));
        horizontalLayout_10 = new QHBoxLayout(ObstWidget);
        horizontalLayout_10->setSpacing(3);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(3, 3, 3, 3);
        label_2 = new QLabel(ObstWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_10->addWidget(label_2);

        obstWeight = new xLineEdit(ObstWidget);
        obstWeight->setObjectName(QString::fromUtf8("obstWeight"));
        sizePolicy.setHeightForWidth(obstWeight->sizePolicy().hasHeightForWidth());
        obstWeight->setSizePolicy(sizePolicy);
        obstWeight->setMinimumSize(QSize(41, 0));
        obstWeight->setMaximumSize(QSize(41, 16777215));

        horizontalLayout_10->addWidget(obstWeight);

        label_3 = new QLabel(ObstWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_10->addWidget(label_3);

        lmpDate = new QDateEdit(ObstWidget);
        lmpDate->setObjectName(QString::fromUtf8("lmpDate"));
        lmpDate->setMinimumDate(QDate(2010, 1, 1));
        lmpDate->setCalendarPopup(true);
        lmpDate->setDate(QDate(2010, 1, 1));

        horizontalLayout_10->addWidget(lmpDate);

        frame_2 = new QFrame(ObstWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);

        horizontalLayout_10->addWidget(frame_2);

        labelEDD = new QLabel(ObstWidget);
        labelEDD->setObjectName(QString::fromUtf8("labelEDD"));

        horizontalLayout_10->addWidget(labelEDD);

        eddDate = new QDateEdit(ObstWidget);
        eddDate->setObjectName(QString::fromUtf8("eddDate"));
        eddDate->setReadOnly(true);
        eddDate->setMinimumDate(QDate(2010, 1, 1));
        eddDate->setCalendarPopup(true);
        eddDate->setDate(QDate(2015, 1, 1));

        horizontalLayout_10->addWidget(eddDate);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_9);

        checkBoxAntenatal = new xCheckBox(ObstWidget);
        checkBoxAntenatal->setObjectName(QString::fromUtf8("checkBoxAntenatal"));

        horizontalLayout_10->addWidget(checkBoxAntenatal);


        gridLayout_9->addWidget(ObstWidget, 4, 0, 1, 1);


        gridLayout_7->addWidget(widgetVitals, 0, 0, 1, 1);


        gridLayout_6->addWidget(widget2, 1, 1, 1, 1);


        gridLayout_8->addWidget(addVisitGroupBox, 1, 0, 1, 1);

        QWidget::setTabOrder(presentation, presentationAnalysis);
        QWidget::setTabOrder(presentationAnalysis, Diagnosis);
        QWidget::setTabOrder(Diagnosis, pPulse);
        QWidget::setTabOrder(pPulse, pRR);
        QWidget::setTabOrder(pRR, pBP);
        QWidget::setTabOrder(pBP, pTemp);
        QWidget::setTabOrder(pTemp, fastPrint);
        QWidget::setTabOrder(fastPrint, comboVisitType);
        QWidget::setTabOrder(comboVisitType, ButtonNew);
        QWidget::setTabOrder(ButtonNew, ButtonVisit);
        QWidget::setTabOrder(ButtonVisit, ButtonDel);
        QWidget::setTabOrder(ButtonDel, toolButtonRefresh);
        QWidget::setTabOrder(toolButtonRefresh, buttonInvest);
        QWidget::setTabOrder(buttonInvest, ButtonSave);
        QWidget::setTabOrder(ButtonSave, patientObstUS);
        QWidget::setTabOrder(patientObstUS, patientPelvicExam);
        QWidget::setTabOrder(patientPelvicExam, patientGeneralEx);
        QWidget::setTabOrder(patientGeneralEx, patientHeartLungEx);
        QWidget::setTabOrder(patientHeartLungEx, patientAbdomentBack);
        QWidget::setTabOrder(patientAbdomentBack, patientLL);
        QWidget::setTabOrder(patientLL, plaintextNotes);
        QWidget::setTabOrder(plaintextNotes, lineEditWeight);
        QWidget::setTabOrder(lineEditWeight, lineEditLength);
        QWidget::setTabOrder(lineEditLength, lineEditHead);
        QWidget::setTabOrder(lineEditHead, obstWeight);
        QWidget::setTabOrder(obstWeight, lmpDate);
        QWidget::setTabOrder(lmpDate, eddDate);
        QWidget::setTabOrder(eddDate, checkBoxAntenatal);
        QWidget::setTabOrder(checkBoxAntenatal, preVisit);
        QWidget::setTabOrder(preVisit, visitLists);
        QWidget::setTabOrder(visitLists, nexVisit);
        QWidget::setTabOrder(nexVisit, investigationsResults);
        QWidget::setTabOrder(investigationsResults, dateFollowUp);
        QWidget::setTabOrder(dateFollowUp, CheckButtonCaseClose);
        QWidget::setTabOrder(CheckButtonCaseClose, closeButton);

        retranslateUi(visitsBox);

        QMetaObject::connectSlotsByName(visitsBox);
    } // setupUi

    void retranslateUi(QDialog *visitsBox)
    {
        visitsBox->setWindowTitle(QApplication::translate("visitsBox", "Patient's Visits", nullptr));
#ifndef QT_NO_TOOLTIP
        comboVisitType->setToolTip(QApplication::translate("visitsBox", "<html><head/><body><p>Visit Type</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        ButtonNew->setToolTip(QApplication::translate("visitsBox", "<html><head/><body><p>Add a New Visit</p><p>F2</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        ButtonNew->setText(QApplication::translate("visitsBox", "+", nullptr));
#ifndef QT_NO_SHORTCUT
        ButtonNew->setShortcut(QApplication::translate("visitsBox", "F2", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        ButtonVisit->setToolTip(QApplication::translate("visitsBox", "<html><head/><body><p>Add a follow up visit</p><p>F3</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        ButtonVisit->setText(QApplication::translate("visitsBox", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        ButtonVisit->setShortcut(QApplication::translate("visitsBox", "F3", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        ButtonDel->setToolTip(QApplication::translate("visitsBox", "<html><head/><body><p>Delete Active Visit</p><p>F4</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        ButtonDel->setText(QApplication::translate("visitsBox", " - ", nullptr));
#ifndef QT_NO_SHORTCUT
        ButtonDel->setShortcut(QApplication::translate("visitsBox", "F4", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        preVisit->setToolTip(QApplication::translate("visitsBox", "<html><head/><body><p>Previous Visit</p><p>PgDn</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        preVisit->setText(QApplication::translate("visitsBox", "<", nullptr));
#ifndef QT_NO_SHORTCUT
        preVisit->setShortcut(QApplication::translate("visitsBox", "PgDown", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        visitLists->setToolTip(QApplication::translate("visitsBox", "Active Visit", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        nexVisit->setToolTip(QApplication::translate("visitsBox", "<html><head/><body><p>Next Visit</p><p>PgUp</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        nexVisit->setText(QApplication::translate("visitsBox", ">", nullptr));
#ifndef QT_NO_SHORTCUT
        nexVisit->setShortcut(QApplication::translate("visitsBox", "PgUp", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        lockUnlockButton->setToolTip(QApplication::translate("visitsBox", "<html><head/><body><p>Toogle ReadOnly Mode [F8] It's Automaticaly locked when this visit is not today to protect you from modifying older visits by mistake.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lockUnlockButton->setText(QApplication::translate("visitsBox", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        lockUnlockButton->setShortcut(QApplication::translate("visitsBox", "F8", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        toolButtonRefresh->setToolTip(QApplication::translate("visitsBox", "<html><head/><body><p>Reload visit data from storage</p><p>F10</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        toolButtonRefresh->setText(QApplication::translate("visitsBox", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        toolButtonRefresh->setShortcut(QApplication::translate("visitsBox", "F10", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        buttonInvest->setToolTip(QApplication::translate("visitsBox", "<html><head/><body><p>investigations</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonInvest->setText(QApplication::translate("visitsBox", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        ButtonSave->setToolTip(QApplication::translate("visitsBox", "<html><head/><body><p>Save Visit Data</p><p>F5</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        ButtonSave->setText(QApplication::translate("visitsBox", "Save", nullptr));
#ifndef QT_NO_SHORTCUT
        ButtonSave->setShortcut(QApplication::translate("visitsBox", "F5", nullptr));
#endif // QT_NO_SHORTCUT
        closeButton->setText(QString());
        addVisitGroupBox->setTitle(QString());
        pNameLabel->setText(QApplication::translate("visitsBox", "Name:", nullptr));
        patientName->setText(QApplication::translate("visitsBox", "ABC DEFG HIJKL MNO PQRS TUVWXYZ", nullptr));
        pAgeLabel->setText(QApplication::translate("visitsBox", "Age:", nullptr));
        patientAge->setText(QApplication::translate("visitsBox", "99 Years old", nullptr));
        labelPresentation->setText(QApplication::translate("visitsBox", "<html><head/><body><p>Cx</p></body></html>", nullptr));
        presentation->setPlaceholderText(QApplication::translate("visitsBox", "Main complaint", nullptr));
        labelPresenationAnalysis->setText(QApplication::translate("visitsBox", "<html><head/><body><p>Present Hx &amp; Cx Analysis</p></body></html>", nullptr));
        label->setText(QApplication::translate("visitsBox", "<html><head/><body><p>Investigations &amp; Services</p></body></html>", nullptr));
        labelInvestResult->setText(QApplication::translate("visitsBox", "<html><head/><body><p>Results</p></body></html>", nullptr));
        buttonAddInvestigations->setText(QApplication::translate("visitsBox", "...", nullptr));
        buttonRemoveInvestigations->setText(QApplication::translate("visitsBox", "...", nullptr));
        investigationsLine->setPlaceholderText(QApplication::translate("visitsBox", "enter investigation", nullptr));
        labelDx->setText(QApplication::translate("visitsBox", "Dx", nullptr));
        Diagnosis->setPlaceholderText(QApplication::translate("visitsBox", "type diagnosises", nullptr));
        labelTreatment->setText(QApplication::translate("visitsBox", "Rx", nullptr));
        rxCost->setText(QApplication::translate("visitsBox", "est. Cost : 000.00 LE.", nullptr));
        buttonAddDrug->setText(QApplication::translate("visitsBox", "...", nullptr));
        buttonRemoveDrug->setText(QApplication::translate("visitsBox", "...", nullptr));
        drugLine->setPlaceholderText(QApplication::translate("visitsBox", "enter drug name here - All drugs", nullptr));
        labelFollowUP->setText(QApplication::translate("visitsBox", "Follow Up", nullptr));
        dateFollowUp->setDisplayFormat(QApplication::translate("visitsBox", "dd/MM/yyyy", nullptr));
        label_4->setText(QApplication::translate("visitsBox", "End Case", nullptr));
#ifndef QT_NO_TOOLTIP
        CheckButtonCaseClose->setToolTip(QApplication::translate("visitsBox", "<html><head/><body><p>End case, It's used when you want to state that there is no more follow ups is needed for this case complaint so then next visit is a new visit and no agenda entry will be saved for this visit.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        CheckButtonCaseClose->setText(QString());
#ifndef QT_NO_SHORTCUT
        CheckButtonCaseClose->setShortcut(QApplication::translate("visitsBox", "Ctrl+E", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        fastPrint->setToolTip(QApplication::translate("visitsBox", "Left Click (CTRL+P): Shows print dialog.\n"
"Right Click (CTRL+I): Shows print preview dialog.\n"
"Middle Click (CTRL+O) : Prints immediately.", nullptr));
#endif // QT_NO_TOOLTIP
        fastPrint->setText(QApplication::translate("visitsBox", "Print", nullptr));
        labelAbdomenBack->setText(QApplication::translate("visitsBox", "Abdomen And Back", nullptr));
        LabelLL->setText(QApplication::translate("visitsBox", "Upper & Lower Limbs", nullptr));
        labelGeneral->setText(QApplication::translate("visitsBox", "General Examination", nullptr));
        labelHeartnLungs->setText(QApplication::translate("visitsBox", "Heart And Lungs", nullptr));
        labelObstUS->setText(QApplication::translate("visitsBox", "Obstetric U/S", nullptr));
        fpalLabel->setText(QApplication::translate("visitsBox", "<html><head/><body><p><span style=\" font-weight:600;\">FPAL:</span></p></body></html>", nullptr));
        notesLabel->setText(QApplication::translate("visitsBox", "Notes", nullptr));
        fpal->setText(QApplication::translate("visitsBox", "  0-0-0-0  ", nullptr));
        labelPelvic->setText(QApplication::translate("visitsBox", "Pelvic Examination", nullptr));
        labelPulse->setText(QApplication::translate("visitsBox", " P ", nullptr));
        labelRR->setText(QApplication::translate("visitsBox", "RR", nullptr));
        labelBP->setText(QApplication::translate("visitsBox", "BP", nullptr));
        pBP->setText(QString());
        labelTemp->setText(QApplication::translate("visitsBox", " T ", nullptr));
        labelWeight->setText(QApplication::translate("visitsBox", "Weight", nullptr));
        labelLength->setText(QApplication::translate("visitsBox", "Length", nullptr));
        labelHead->setText(QApplication::translate("visitsBox", "Head Cir.", nullptr));
        label_2->setText(QApplication::translate("visitsBox", "Wt", nullptr));
        label_3->setText(QApplication::translate("visitsBox", "LMP", nullptr));
        lmpDate->setDisplayFormat(QApplication::translate("visitsBox", "dd/MM/yyyy", nullptr));
        labelEDD->setText(QApplication::translate("visitsBox", "EDD", nullptr));
        eddDate->setDisplayFormat(QApplication::translate("visitsBox", "dd/MM/yyyy", nullptr));
        checkBoxAntenatal->setText(QApplication::translate("visitsBox", "Antenatal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class visitsBox: public Ui_visitsBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISITSBOX_H
