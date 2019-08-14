/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "conditionswidget.h"
#include "drugsline.h"
#include "drugstable.h"
#include "genericlineedit.h"
#include "mpushbutton.h"
#include "navarrows.h"
#include "patientnamelineedit.h"
#include "patientnumber.h"
#include "searchwidget.h"
#include "textedit.h"
#include "w_development.h"
#include "w_obgyn.h"
#include "w_perinatal.h"
#include "xcheckbox.h"
#include "xcombobox.h"
#include "xdatetimeedit.h"
#include "xlineedit.h"
#include "xlistwidget.h"
#include "xspinbox.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *crashTool;
    QToolButton *minimizeButton;
    QToolButton *ExitButton;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_8;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_21;
    navArrows *goLowerID;
    patientNumber *patientnumber;
    navArrows *goHigherID;
    QToolButton *buttonAgenda;
    QToolButton *ButtonRefresh;
    QSpacerItem *horizontalSpacer_3;
    mPushButton *ButtonSaveEdit;
    QPushButton *ButtonVisit;
    QPushButton *ButtonDelete;
    mPushButton *buttonNewCancel;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *settingButton;
    QToolButton *buttonPatientList;
    QToolButton *drugIndexButton;
    xDateTimeEdit *DateTimeEdit;
    QWidget *widget_3;
    QGridLayout *gridLayout_7;
    QWidget *widget_4;
    QGridLayout *gridLayout_6;
    w_obGyn *ObstWidget;
    QGroupBox *groupBoxDev;
    QGridLayout *gridLayout_4;
    w_development *dev;
    w_perinatal *perinatal;
    QGroupBox *condGroupBox;
    QGridLayout *gridLayout_15;
    QSpacerItem *horizontalSpacer_11;
    conditionsWidget *conditionswidget;
    QSpacerItem *horizontalSpacer_12;
    QFrame *framePersonalHistory;
    QGridLayout *gridLayout_2;
    QWidget *widgetSmokeAlcohol;
    QGridLayout *gridLayout_10;
    QHBoxLayout *horizontalLayout_18;
    xCheckBox *checkBoxSmoker;
    xSpinBox *spinBoxCigarettesPerDay;
    QLabel *labelCigarettsPerDay;
    xSpinBox *spinBoxSmokingYears;
    QLabel *labelSmokingYear;
    xCheckBox *checkBoxAlcohol;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_12;
    xComboBox *ABO;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelResidence;
    genericLineEdit *patientResidence;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelName;
    patientNameLineEdit *patientName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelAge;
    QToolButton *ButtonAgeCal;
    QLineEdit *patientAge;
    xSpinBox *spinBoxAge;
    QLabel *labelYears;
    xComboBox *patientGender;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelPlaceOfBirth;
    genericLineEdit *patientPlaceBirth;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelOccupation;
    genericLineEdit *patientOccupation;
    xComboBox *comboBoxMaritalStatus;
    QToolButton *buttonInvestigations;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labelMobile;
    xLineEdit *patientMobile;
    QToolButton *buttonSuricalNotes;
    QFrame *frameMedicalHx;
    QGridLayout *gridLayout_3;
    QLabel *labelPastHisotry;
    QLabel *labelFamilyHx;
    QLabel *lablelNotes;
    TextEdit *PastHx;
    TextEdit *familyHx;
    TextEdit *Notes;
    QLabel *labelDrugs;
    QLabel *labelAllergy;
    QLabel *labelOpAdmission;
    drugsTable *pDrugsTable;
    xListWidget *allergyList;
    xListWidget *opAdmissionsList;
    QHBoxLayout *horizontalLayout_11;
    QToolButton *buttonAddDrug;
    QToolButton *buttonRemoveDrug;
    drugsLine *drugLine;
    QHBoxLayout *horizontalLayout_7;
    QToolButton *buttonAddAllergy;
    QToolButton *buttonRemoveAllergy;
    genericLineEdit *allergyLine;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *buttonAddOP;
    QToolButton *buttonRemoveOP;
    genericLineEdit *opAdLine;
    searchWidget *searchWidgetx;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1203, 689);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(1);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(1, 0, 1, 1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(22, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        crashTool = new QToolButton(centralWidget);
        crashTool->setObjectName(QString::fromUtf8("crashTool"));
        crashTool->setMaximumSize(QSize(16777215, 18));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ionicons/bug"), QSize(), QIcon::Normal, QIcon::Off);
        crashTool->setIcon(icon);
        crashTool->setAutoRaise(true);

        horizontalLayout->addWidget(crashTool);

        minimizeButton = new QToolButton(centralWidget);
        minimizeButton->setObjectName(QString::fromUtf8("minimizeButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Graphics/chevBot"), QSize(), QIcon::Normal, QIcon::Off);
        minimizeButton->setIcon(icon1);

        horizontalLayout->addWidget(minimizeButton);

        ExitButton = new QToolButton(centralWidget);
        ExitButton->setObjectName(QString::fromUtf8("ExitButton"));

        horizontalLayout->addWidget(ExitButton);


        gridLayout_5->addLayout(horizontalLayout, 0, 0, 1, 2);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        horizontalLayout_8 = new QHBoxLayout(widget1);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(widget1);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_21 = new QHBoxLayout(widget);
        horizontalLayout_21->setSpacing(1);
        horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalLayout_21->setContentsMargins(0, 0, 0, 0);
        goLowerID = new navArrows(widget);
        goLowerID->setObjectName(QString::fromUtf8("goLowerID"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Graphics/back"), QSize(), QIcon::Normal, QIcon::Off);
        goLowerID->setIcon(icon2);
        goLowerID->setAutoRaise(true);

        horizontalLayout_21->addWidget(goLowerID);

        patientnumber = new patientNumber(widget);
        patientnumber->setObjectName(QString::fromUtf8("patientnumber"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(patientnumber->sizePolicy().hasHeightForWidth());
        patientnumber->setSizePolicy(sizePolicy1);
        patientnumber->setMinimumSize(QSize(90, 25));
        patientnumber->setFrameShape(QFrame::Box);
        patientnumber->setFrameShadow(QFrame::Raised);
        patientnumber->setLineWidth(1);
        patientnumber->setMidLineWidth(0);
        patientnumber->setDigitCount(6);
        patientnumber->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_21->addWidget(patientnumber);

        goHigherID = new navArrows(widget);
        goHigherID->setObjectName(QString::fromUtf8("goHigherID"));
        goHigherID->setEnabled(false);
        goHigherID->setStyleSheet(QString::fromUtf8(""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Graphics/forward"), QSize(), QIcon::Normal, QIcon::Off);
        goHigherID->setIcon(icon3);
        goHigherID->setAutoRaise(true);

        horizontalLayout_21->addWidget(goHigherID);

        buttonAgenda = new QToolButton(widget);
        buttonAgenda->setObjectName(QString::fromUtf8("buttonAgenda"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Graphics/person"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAgenda->setIcon(icon4);
        buttonAgenda->setAutoRaise(false);

        horizontalLayout_21->addWidget(buttonAgenda);

        ButtonRefresh = new QToolButton(widget);
        ButtonRefresh->setObjectName(QString::fromUtf8("ButtonRefresh"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Graphics/refresh"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonRefresh->setIcon(icon5);
        ButtonRefresh->setIconSize(QSize(16, 16));
        ButtonRefresh->setAutoRaise(false);

        horizontalLayout_21->addWidget(ButtonRefresh);

        horizontalSpacer_3 = new QSpacerItem(241, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_3);

        ButtonSaveEdit = new mPushButton(widget);
        ButtonSaveEdit->setObjectName(QString::fromUtf8("ButtonSaveEdit"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Graphics/ok"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonSaveEdit->setIcon(icon6);

        horizontalLayout_21->addWidget(ButtonSaveEdit);

        ButtonVisit = new QPushButton(widget);
        ButtonVisit->setObjectName(QString::fromUtf8("ButtonVisit"));
        ButtonVisit->setEnabled(false);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Graphics/control"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonVisit->setIcon(icon7);

        horizontalLayout_21->addWidget(ButtonVisit);

        ButtonDelete = new QPushButton(widget);
        ButtonDelete->setObjectName(QString::fromUtf8("ButtonDelete"));
        ButtonDelete->setEnabled(false);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/ionicons/close"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonDelete->setIcon(icon8);

        horizontalLayout_21->addWidget(ButtonDelete);

        buttonNewCancel = new mPushButton(widget);
        buttonNewCancel->setObjectName(QString::fromUtf8("buttonNewCancel"));
        buttonNewCancel->setIcon(icon4);

        horizontalLayout_21->addWidget(buttonNewCancel);

        horizontalSpacer_4 = new QSpacerItem(240, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_4);

        settingButton = new QToolButton(widget);
        settingButton->setObjectName(QString::fromUtf8("settingButton"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Graphics/settings"), QSize(), QIcon::Normal, QIcon::Off);
        settingButton->setIcon(icon9);

        horizontalLayout_21->addWidget(settingButton);

        buttonPatientList = new QToolButton(widget);
        buttonPatientList->setObjectName(QString::fromUtf8("buttonPatientList"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Graphics/search"), QSize(), QIcon::Normal, QIcon::Off);
        buttonPatientList->setIcon(icon10);
        buttonPatientList->setIconSize(QSize(16, 16));
        buttonPatientList->setAutoRaise(false);

        horizontalLayout_21->addWidget(buttonPatientList);

        drugIndexButton = new QToolButton(widget);
        drugIndexButton->setObjectName(QString::fromUtf8("drugIndexButton"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Graphics/beaker"), QSize(), QIcon::Normal, QIcon::Off);
        drugIndexButton->setIcon(icon11);

        horizontalLayout_21->addWidget(drugIndexButton);


        horizontalLayout_8->addWidget(widget);

        DateTimeEdit = new xDateTimeEdit(widget1);
        DateTimeEdit->setObjectName(QString::fromUtf8("DateTimeEdit"));
        DateTimeEdit->setMaximumSize(QSize(160, 16777215));
        DateTimeEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        DateTimeEdit->setWrapping(false);
        DateTimeEdit->setCurrentSection(QDateTimeEdit::MinuteSection);
        DateTimeEdit->setCalendarPopup(true);

        horizontalLayout_8->addWidget(DateTimeEdit);


        gridLayout_5->addWidget(widget1, 1, 0, 1, 2);

        widget_3 = new QWidget(centralWidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_7 = new QGridLayout(widget_3);
        gridLayout_7->setSpacing(1);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(1, 1, 1, 1);
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        gridLayout_6 = new QGridLayout(widget_4);
        gridLayout_6->setSpacing(1);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(1, 1, 1, 1);
        ObstWidget = new w_obGyn(widget_4);
        ObstWidget->setObjectName(QString::fromUtf8("ObstWidget"));
        ObstWidget->setMinimumSize(QSize(0, 100));

        gridLayout_6->addWidget(ObstWidget, 3, 0, 1, 1);

        groupBoxDev = new QGroupBox(widget_4);
        groupBoxDev->setObjectName(QString::fromUtf8("groupBoxDev"));
        groupBoxDev->setMinimumSize(QSize(0, 150));
        groupBoxDev->setAlignment(Qt::AlignCenter);
        gridLayout_4 = new QGridLayout(groupBoxDev);
        gridLayout_4->setSpacing(1);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(1, 1, 1, 1);
        dev = new w_development(groupBoxDev);
        dev->setObjectName(QString::fromUtf8("dev"));

        gridLayout_4->addWidget(dev, 0, 0, 1, 1);

        perinatal = new w_perinatal(groupBoxDev);
        perinatal->setObjectName(QString::fromUtf8("perinatal"));

        gridLayout_4->addWidget(perinatal, 0, 1, 1, 1);


        gridLayout_6->addWidget(groupBoxDev, 2, 0, 1, 1);

        condGroupBox = new QGroupBox(widget_4);
        condGroupBox->setObjectName(QString::fromUtf8("condGroupBox"));
        condGroupBox->setAlignment(Qt::AlignCenter);
        gridLayout_15 = new QGridLayout(condGroupBox);
        gridLayout_15->setSpacing(1);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_15->setContentsMargins(1, 1, 1, 1);
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_11, 0, 0, 1, 1);

        conditionswidget = new conditionsWidget(condGroupBox);
        conditionswidget->setObjectName(QString::fromUtf8("conditionswidget"));

        gridLayout_15->addWidget(conditionswidget, 0, 1, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_12, 0, 2, 1, 1);


        gridLayout_6->addWidget(condGroupBox, 1, 0, 1, 1);

        framePersonalHistory = new QFrame(widget_4);
        framePersonalHistory->setObjectName(QString::fromUtf8("framePersonalHistory"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(framePersonalHistory->sizePolicy().hasHeightForWidth());
        framePersonalHistory->setSizePolicy(sizePolicy2);
        gridLayout_2 = new QGridLayout(framePersonalHistory);
        gridLayout_2->setSpacing(3);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(3, 3, 3, 3);
        widgetSmokeAlcohol = new QWidget(framePersonalHistory);
        widgetSmokeAlcohol->setObjectName(QString::fromUtf8("widgetSmokeAlcohol"));
        gridLayout_10 = new QGridLayout(widgetSmokeAlcohol);
        gridLayout_10->setSpacing(0);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        checkBoxSmoker = new xCheckBox(widgetSmokeAlcohol);
        checkBoxSmoker->setObjectName(QString::fromUtf8("checkBoxSmoker"));
        sizePolicy1.setHeightForWidth(checkBoxSmoker->sizePolicy().hasHeightForWidth());
        checkBoxSmoker->setSizePolicy(sizePolicy1);

        horizontalLayout_18->addWidget(checkBoxSmoker);

        spinBoxCigarettesPerDay = new xSpinBox(widgetSmokeAlcohol);
        spinBoxCigarettesPerDay->setObjectName(QString::fromUtf8("spinBoxCigarettesPerDay"));
        sizePolicy1.setHeightForWidth(spinBoxCigarettesPerDay->sizePolicy().hasHeightForWidth());
        spinBoxCigarettesPerDay->setSizePolicy(sizePolicy1);
        spinBoxCigarettesPerDay->setMinimumSize(QSize(0, 18));

        horizontalLayout_18->addWidget(spinBoxCigarettesPerDay);

        labelCigarettsPerDay = new QLabel(widgetSmokeAlcohol);
        labelCigarettsPerDay->setObjectName(QString::fromUtf8("labelCigarettsPerDay"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelCigarettsPerDay->sizePolicy().hasHeightForWidth());
        labelCigarettsPerDay->setSizePolicy(sizePolicy3);

        horizontalLayout_18->addWidget(labelCigarettsPerDay);

        spinBoxSmokingYears = new xSpinBox(widgetSmokeAlcohol);
        spinBoxSmokingYears->setObjectName(QString::fromUtf8("spinBoxSmokingYears"));
        sizePolicy1.setHeightForWidth(spinBoxSmokingYears->sizePolicy().hasHeightForWidth());
        spinBoxSmokingYears->setSizePolicy(sizePolicy1);
        spinBoxSmokingYears->setMinimumSize(QSize(0, 18));

        horizontalLayout_18->addWidget(spinBoxSmokingYears);

        labelSmokingYear = new QLabel(widgetSmokeAlcohol);
        labelSmokingYear->setObjectName(QString::fromUtf8("labelSmokingYear"));
        sizePolicy3.setHeightForWidth(labelSmokingYear->sizePolicy().hasHeightForWidth());
        labelSmokingYear->setSizePolicy(sizePolicy3);

        horizontalLayout_18->addWidget(labelSmokingYear);

        checkBoxAlcohol = new xCheckBox(widgetSmokeAlcohol);
        checkBoxAlcohol->setObjectName(QString::fromUtf8("checkBoxAlcohol"));

        horizontalLayout_18->addWidget(checkBoxAlcohol);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_8);

        label_12 = new QLabel(widgetSmokeAlcohol);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_18->addWidget(label_12);

        ABO = new xComboBox(widgetSmokeAlcohol);
        ABO->addItem(QString());
        ABO->addItem(QString());
        ABO->addItem(QString());
        ABO->addItem(QString());
        ABO->addItem(QString());
        ABO->addItem(QString());
        ABO->addItem(QString());
        ABO->addItem(QString());
        ABO->addItem(QString());
        ABO->addItem(QString());
        ABO->addItem(QString());
        ABO->setObjectName(QString::fromUtf8("ABO"));

        horizontalLayout_18->addWidget(ABO);


        gridLayout_10->addLayout(horizontalLayout_18, 0, 0, 1, 1);


        gridLayout_2->addWidget(widgetSmokeAlcohol, 2, 2, 1, 4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        labelResidence = new QLabel(framePersonalHistory);
        labelResidence->setObjectName(QString::fromUtf8("labelResidence"));
        sizePolicy1.setHeightForWidth(labelResidence->sizePolicy().hasHeightForWidth());
        labelResidence->setSizePolicy(sizePolicy1);
        labelResidence->setMinimumSize(QSize(70, 0));
        labelResidence->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_9->addWidget(labelResidence);

        patientResidence = new genericLineEdit(framePersonalHistory);
        patientResidence->setObjectName(QString::fromUtf8("patientResidence"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(patientResidence->sizePolicy().hasHeightForWidth());
        patientResidence->setSizePolicy(sizePolicy4);
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        patientResidence->setFont(font1);

        horizontalLayout_9->addWidget(patientResidence);


        gridLayout_2->addLayout(horizontalLayout_9, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelName = new QLabel(framePersonalHistory);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        sizePolicy1.setHeightForWidth(labelName->sizePolicy().hasHeightForWidth());
        labelName->setSizePolicy(sizePolicy1);
        labelName->setMinimumSize(QSize(70, 0));
        labelName->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(labelName);

        patientName = new patientNameLineEdit(framePersonalHistory);
        patientName->setObjectName(QString::fromUtf8("patientName"));
        sizePolicy4.setHeightForWidth(patientName->sizePolicy().hasHeightForWidth());
        patientName->setSizePolicy(sizePolicy4);
        patientName->setFont(font1);
        patientName->setClearButtonEnabled(true);

        horizontalLayout_3->addWidget(patientName);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 0, 1, 4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelAge = new QLabel(framePersonalHistory);
        labelAge->setObjectName(QString::fromUtf8("labelAge"));
        sizePolicy1.setHeightForWidth(labelAge->sizePolicy().hasHeightForWidth());
        labelAge->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(labelAge);

        ButtonAgeCal = new QToolButton(framePersonalHistory);
        ButtonAgeCal->setObjectName(QString::fromUtf8("ButtonAgeCal"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Graphics/sptreadsheet"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonAgeCal->setIcon(icon12);
        ButtonAgeCal->setAutoRaise(true);

        horizontalLayout_2->addWidget(ButtonAgeCal);

        patientAge = new QLineEdit(framePersonalHistory);
        patientAge->setObjectName(QString::fromUtf8("patientAge"));
        sizePolicy4.setHeightForWidth(patientAge->sizePolicy().hasHeightForWidth());
        patientAge->setSizePolicy(sizePolicy4);
        patientAge->setMinimumSize(QSize(190, 0));
        patientAge->setFont(font1);
        patientAge->setReadOnly(true);

        horizontalLayout_2->addWidget(patientAge);

        spinBoxAge = new xSpinBox(framePersonalHistory);
        spinBoxAge->setObjectName(QString::fromUtf8("spinBoxAge"));
        sizePolicy1.setHeightForWidth(spinBoxAge->sizePolicy().hasHeightForWidth());
        spinBoxAge->setSizePolicy(sizePolicy1);
        spinBoxAge->setMinimumSize(QSize(0, 18));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        spinBoxAge->setFont(font2);
        spinBoxAge->setMaximum(300);

        horizontalLayout_2->addWidget(spinBoxAge);

        labelYears = new QLabel(framePersonalHistory);
        labelYears->setObjectName(QString::fromUtf8("labelYears"));

        horizontalLayout_2->addWidget(labelYears);

        patientGender = new xComboBox(framePersonalHistory);
        patientGender->addItem(QString());
        patientGender->addItem(QString());
        patientGender->setObjectName(QString::fromUtf8("patientGender"));
        sizePolicy1.setHeightForWidth(patientGender->sizePolicy().hasHeightForWidth());
        patientGender->setSizePolicy(sizePolicy1);
        patientGender->setMinimumSize(QSize(79, 0));
        patientGender->setFont(font2);
        patientGender->setFrame(true);

        horizontalLayout_2->addWidget(patientGender);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 4, 1, 7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        labelPlaceOfBirth = new QLabel(framePersonalHistory);
        labelPlaceOfBirth->setObjectName(QString::fromUtf8("labelPlaceOfBirth"));
        sizePolicy1.setHeightForWidth(labelPlaceOfBirth->sizePolicy().hasHeightForWidth());
        labelPlaceOfBirth->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(labelPlaceOfBirth);

        patientPlaceBirth = new genericLineEdit(framePersonalHistory);
        patientPlaceBirth->setObjectName(QString::fromUtf8("patientPlaceBirth"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(patientPlaceBirth->sizePolicy().hasHeightForWidth());
        patientPlaceBirth->setSizePolicy(sizePolicy5);
        patientPlaceBirth->setFont(font1);

        horizontalLayout_5->addWidget(patientPlaceBirth);


        gridLayout_2->addLayout(horizontalLayout_5, 1, 2, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labelOccupation = new QLabel(framePersonalHistory);
        labelOccupation->setObjectName(QString::fromUtf8("labelOccupation"));

        horizontalLayout_4->addWidget(labelOccupation);

        patientOccupation = new genericLineEdit(framePersonalHistory);
        patientOccupation->setObjectName(QString::fromUtf8("patientOccupation"));
        patientOccupation->setFont(font1);

        horizontalLayout_4->addWidget(patientOccupation);

        comboBoxMaritalStatus = new xComboBox(framePersonalHistory);
        comboBoxMaritalStatus->addItem(QString());
        comboBoxMaritalStatus->addItem(QString());
        comboBoxMaritalStatus->addItem(QString());
        comboBoxMaritalStatus->addItem(QString());
        comboBoxMaritalStatus->setObjectName(QString::fromUtf8("comboBoxMaritalStatus"));
        sizePolicy1.setHeightForWidth(comboBoxMaritalStatus->sizePolicy().hasHeightForWidth());
        comboBoxMaritalStatus->setSizePolicy(sizePolicy1);
        comboBoxMaritalStatus->setFont(font2);

        horizontalLayout_4->addWidget(comboBoxMaritalStatus);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 4, 1, 7);

        buttonInvestigations = new QToolButton(framePersonalHistory);
        buttonInvestigations->setObjectName(QString::fromUtf8("buttonInvestigations"));
        buttonInvestigations->setEnabled(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Graphics/paperClip"), QSize(), QIcon::Normal, QIcon::Off);
        buttonInvestigations->setIcon(icon13);

        gridLayout_2->addWidget(buttonInvestigations, 2, 10, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        labelMobile = new QLabel(framePersonalHistory);
        labelMobile->setObjectName(QString::fromUtf8("labelMobile"));
        sizePolicy1.setHeightForWidth(labelMobile->sizePolicy().hasHeightForWidth());
        labelMobile->setSizePolicy(sizePolicy1);
        labelMobile->setMinimumSize(QSize(70, 0));
        labelMobile->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_10->addWidget(labelMobile);

        patientMobile = new xLineEdit(framePersonalHistory);
        patientMobile->setObjectName(QString::fromUtf8("patientMobile"));

        horizontalLayout_10->addWidget(patientMobile);


        gridLayout_2->addLayout(horizontalLayout_10, 2, 0, 1, 1);

        buttonSuricalNotes = new QToolButton(framePersonalHistory);
        buttonSuricalNotes->setObjectName(QString::fromUtf8("buttonSuricalNotes"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Graphics/doc"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSuricalNotes->setIcon(icon14);

        gridLayout_2->addWidget(buttonSuricalNotes, 2, 9, 1, 1);


        gridLayout_6->addWidget(framePersonalHistory, 0, 0, 1, 1);


        gridLayout_7->addWidget(widget_4, 0, 0, 1, 1);

        frameMedicalHx = new QFrame(widget_3);
        frameMedicalHx->setObjectName(QString::fromUtf8("frameMedicalHx"));
        gridLayout_3 = new QGridLayout(frameMedicalHx);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(1);
        gridLayout_3->setVerticalSpacing(0);
        gridLayout_3->setContentsMargins(1, 1, 1, 1);
        labelPastHisotry = new QLabel(frameMedicalHx);
        labelPastHisotry->setObjectName(QString::fromUtf8("labelPastHisotry"));
        labelPastHisotry->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(labelPastHisotry, 0, 0, 1, 1);

        labelFamilyHx = new QLabel(frameMedicalHx);
        labelFamilyHx->setObjectName(QString::fromUtf8("labelFamilyHx"));
        labelFamilyHx->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(labelFamilyHx, 0, 1, 1, 1);

        lablelNotes = new QLabel(frameMedicalHx);
        lablelNotes->setObjectName(QString::fromUtf8("lablelNotes"));
        lablelNotes->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lablelNotes, 0, 2, 1, 1);

        PastHx = new TextEdit(frameMedicalHx);
        PastHx->setObjectName(QString::fromUtf8("PastHx"));
        PastHx->setTabChangesFocus(true);

        gridLayout_3->addWidget(PastHx, 1, 0, 1, 1);

        familyHx = new TextEdit(frameMedicalHx);
        familyHx->setObjectName(QString::fromUtf8("familyHx"));
        familyHx->setTabChangesFocus(true);

        gridLayout_3->addWidget(familyHx, 1, 1, 1, 1);

        Notes = new TextEdit(frameMedicalHx);
        Notes->setObjectName(QString::fromUtf8("Notes"));
        Notes->setTabChangesFocus(true);

        gridLayout_3->addWidget(Notes, 1, 2, 1, 1);

        labelDrugs = new QLabel(frameMedicalHx);
        labelDrugs->setObjectName(QString::fromUtf8("labelDrugs"));
        labelDrugs->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(labelDrugs, 2, 0, 1, 1);

        labelAllergy = new QLabel(frameMedicalHx);
        labelAllergy->setObjectName(QString::fromUtf8("labelAllergy"));
        labelAllergy->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(labelAllergy, 2, 1, 1, 1);

        labelOpAdmission = new QLabel(frameMedicalHx);
        labelOpAdmission->setObjectName(QString::fromUtf8("labelOpAdmission"));
        labelOpAdmission->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(labelOpAdmission, 2, 2, 1, 1);

        pDrugsTable = new drugsTable(frameMedicalHx);
        pDrugsTable->setObjectName(QString::fromUtf8("pDrugsTable"));
        pDrugsTable->setShowGrid(false);
        pDrugsTable->setGridStyle(Qt::NoPen);
        pDrugsTable->setSortingEnabled(false);
        pDrugsTable->setWordWrap(false);
        pDrugsTable->setCornerButtonEnabled(false);
        pDrugsTable->horizontalHeader()->setVisible(false);
        pDrugsTable->horizontalHeader()->setMinimumSectionSize(20);
        pDrugsTable->horizontalHeader()->setHighlightSections(false);
        pDrugsTable->verticalHeader()->setVisible(false);
        pDrugsTable->verticalHeader()->setMinimumSectionSize(20);
        pDrugsTable->verticalHeader()->setDefaultSectionSize(20);
        pDrugsTable->verticalHeader()->setHighlightSections(false);

        gridLayout_3->addWidget(pDrugsTable, 3, 0, 1, 1);

        allergyList = new xListWidget(frameMedicalHx);
        allergyList->setObjectName(QString::fromUtf8("allergyList"));
        allergyList->setFont(font1);
        allergyList->setGridSize(QSize(0, 20));

        gridLayout_3->addWidget(allergyList, 3, 1, 1, 1);

        opAdmissionsList = new xListWidget(frameMedicalHx);
        opAdmissionsList->setObjectName(QString::fromUtf8("opAdmissionsList"));
        opAdmissionsList->setFont(font1);

        gridLayout_3->addWidget(opAdmissionsList, 3, 2, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        buttonAddDrug = new QToolButton(frameMedicalHx);
        buttonAddDrug->setObjectName(QString::fromUtf8("buttonAddDrug"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Graphics/add"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAddDrug->setIcon(icon15);
        buttonAddDrug->setAutoRaise(true);

        horizontalLayout_11->addWidget(buttonAddDrug);

        buttonRemoveDrug = new QToolButton(frameMedicalHx);
        buttonRemoveDrug->setObjectName(QString::fromUtf8("buttonRemoveDrug"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/Graphics/minus"), QSize(), QIcon::Normal, QIcon::Off);
        buttonRemoveDrug->setIcon(icon16);
        buttonRemoveDrug->setAutoRaise(true);

        horizontalLayout_11->addWidget(buttonRemoveDrug);

        drugLine = new drugsLine(frameMedicalHx);
        drugLine->setObjectName(QString::fromUtf8("drugLine"));
        drugLine->setClearButtonEnabled(true);

        horizontalLayout_11->addWidget(drugLine);


        gridLayout_3->addLayout(horizontalLayout_11, 4, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        buttonAddAllergy = new QToolButton(frameMedicalHx);
        buttonAddAllergy->setObjectName(QString::fromUtf8("buttonAddAllergy"));
        buttonAddAllergy->setIcon(icon15);
        buttonAddAllergy->setAutoRaise(true);

        horizontalLayout_7->addWidget(buttonAddAllergy);

        buttonRemoveAllergy = new QToolButton(frameMedicalHx);
        buttonRemoveAllergy->setObjectName(QString::fromUtf8("buttonRemoveAllergy"));
        buttonRemoveAllergy->setIcon(icon16);
        buttonRemoveAllergy->setAutoRaise(true);

        horizontalLayout_7->addWidget(buttonRemoveAllergy);

        allergyLine = new genericLineEdit(frameMedicalHx);
        allergyLine->setObjectName(QString::fromUtf8("allergyLine"));
        allergyLine->setClearButtonEnabled(true);

        horizontalLayout_7->addWidget(allergyLine);


        gridLayout_3->addLayout(horizontalLayout_7, 4, 1, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        buttonAddOP = new QToolButton(frameMedicalHx);
        buttonAddOP->setObjectName(QString::fromUtf8("buttonAddOP"));
        buttonAddOP->setIcon(icon15);
        buttonAddOP->setAutoRaise(true);

        horizontalLayout_6->addWidget(buttonAddOP);

        buttonRemoveOP = new QToolButton(frameMedicalHx);
        buttonRemoveOP->setObjectName(QString::fromUtf8("buttonRemoveOP"));
        buttonRemoveOP->setIcon(icon16);
        buttonRemoveOP->setAutoRaise(true);

        horizontalLayout_6->addWidget(buttonRemoveOP);

        opAdLine = new genericLineEdit(frameMedicalHx);
        opAdLine->setObjectName(QString::fromUtf8("opAdLine"));
        opAdLine->setClearButtonEnabled(true);

        horizontalLayout_6->addWidget(opAdLine);


        gridLayout_3->addLayout(horizontalLayout_6, 4, 2, 1, 1);


        gridLayout_7->addWidget(frameMedicalHx, 1, 0, 1, 1);


        gridLayout_5->addWidget(widget_3, 2, 0, 1, 1);

        searchWidgetx = new searchWidget(centralWidget);
        searchWidgetx->setObjectName(QString::fromUtf8("searchWidgetx"));
        searchWidgetx->setMinimumSize(QSize(200, 0));
        searchWidgetx->setMaximumSize(QSize(300, 16777215));

        gridLayout_5->addWidget(searchWidgetx, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        widget1->raise();
        searchWidgetx->raise();
        widget_3->raise();
        QWidget::setTabOrder(patientName, ButtonAgeCal);
        QWidget::setTabOrder(ButtonAgeCal, patientAge);
        QWidget::setTabOrder(patientAge, spinBoxAge);
        QWidget::setTabOrder(spinBoxAge, patientGender);
        QWidget::setTabOrder(patientGender, patientResidence);
        QWidget::setTabOrder(patientResidence, patientPlaceBirth);
        QWidget::setTabOrder(patientPlaceBirth, patientOccupation);
        QWidget::setTabOrder(patientOccupation, comboBoxMaritalStatus);
        QWidget::setTabOrder(comboBoxMaritalStatus, patientMobile);
        QWidget::setTabOrder(patientMobile, checkBoxSmoker);
        QWidget::setTabOrder(checkBoxSmoker, spinBoxCigarettesPerDay);
        QWidget::setTabOrder(spinBoxCigarettesPerDay, spinBoxSmokingYears);
        QWidget::setTabOrder(spinBoxSmokingYears, checkBoxAlcohol);
        QWidget::setTabOrder(checkBoxAlcohol, PastHx);
        QWidget::setTabOrder(PastHx, familyHx);
        QWidget::setTabOrder(familyHx, drugLine);
        QWidget::setTabOrder(drugLine, allergyLine);
        QWidget::setTabOrder(allergyLine, opAdLine);
        QWidget::setTabOrder(opAdLine, opAdmissionsList);
        QWidget::setTabOrder(opAdmissionsList, buttonAddDrug);
        QWidget::setTabOrder(buttonAddDrug, buttonRemoveDrug);
        QWidget::setTabOrder(buttonRemoveDrug, buttonAddAllergy);
        QWidget::setTabOrder(buttonAddAllergy, buttonRemoveAllergy);
        QWidget::setTabOrder(buttonRemoveAllergy, buttonAddOP);
        QWidget::setTabOrder(buttonAddOP, buttonRemoveOP);
        QWidget::setTabOrder(buttonRemoveOP, buttonInvestigations);
        QWidget::setTabOrder(buttonInvestigations, ButtonSaveEdit);
        QWidget::setTabOrder(ButtonSaveEdit, ButtonVisit);
        QWidget::setTabOrder(ButtonVisit, ButtonDelete);
        QWidget::setTabOrder(ButtonDelete, buttonNewCancel);
        QWidget::setTabOrder(buttonNewCancel, buttonAgenda);
        QWidget::setTabOrder(buttonAgenda, DateTimeEdit);
        QWidget::setTabOrder(DateTimeEdit, goLowerID);
        QWidget::setTabOrder(goLowerID, goHigherID);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Smart Clinic", nullptr));
#ifndef QT_NO_TOOLTIP
        crashTool->setToolTip(QApplication::translate("MainWindow", "Check error log", nullptr));
#endif // QT_NO_TOOLTIP
        crashTool->setText(QString());
        minimizeButton->setText(QApplication::translate("MainWindow", "...", nullptr));
        ExitButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        goLowerID->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Previous Patient Record </p><p>PgDn</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        goLowerID->setText(QApplication::translate("MainWindow", "<", nullptr));
#ifndef QT_NO_SHORTCUT
        goLowerID->setShortcut(QApplication::translate("MainWindow", "PgDown", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        patientnumber->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Current Patient Number</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        goHigherID->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Next Patient Record </p><p>PgUp</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        goHigherID->setText(QApplication::translate("MainWindow", ">", nullptr));
#ifndef QT_NO_SHORTCUT
        goHigherID->setShortcut(QApplication::translate("MainWindow", "PgUp", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        buttonAgenda->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>my Assistant</p><p>F3</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonAgenda->setText(QApplication::translate("MainWindow", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        buttonAgenda->setShortcut(QApplication::translate("MainWindow", "F3", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        ButtonRefresh->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Refresh</p><p>F4</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        ButtonRefresh->setText(QApplication::translate("MainWindow", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        ButtonRefresh->setShortcut(QApplication::translate("MainWindow", "F4", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        ButtonSaveEdit->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Save current patient</p><p>F5</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        ButtonSaveEdit->setText(QApplication::translate("MainWindow", "&Save", nullptr));
#ifndef QT_NO_SHORTCUT
        ButtonSaveEdit->setShortcut(QApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        ButtonVisit->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Show The current patient Visits</p><p>F6</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        ButtonVisit->setText(QApplication::translate("MainWindow", "Visi&ts", nullptr));
#ifndef QT_NO_SHORTCUT
        ButtonVisit->setShortcut(QApplication::translate("MainWindow", "F6", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        ButtonDelete->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Delete This Patient</p><p>F7</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        ButtonDelete->setText(QApplication::translate("MainWindow", "&Delete", nullptr));
#ifndef QT_NO_SHORTCUT
        ButtonDelete->setShortcut(QApplication::translate("MainWindow", "F7", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        buttonNewCancel->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Exit edit Mode</p><p>F8</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonNewCancel->setText(QApplication::translate("MainWindow", "&Cancel", nullptr));
#ifndef QT_NO_SHORTCUT
        buttonNewCancel->setShortcut(QApplication::translate("MainWindow", "F8", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        settingButton->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Settings F9</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        settingButton->setText(QApplication::translate("MainWindow", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        buttonPatientList->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>search Patient records</p><p>F2</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonPatientList->setText(QApplication::translate("MainWindow", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        buttonPatientList->setShortcut(QApplication::translate("MainWindow", "F2", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        drugIndexButton->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Drugs Index</p><p>F10</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        drugIndexButton->setText(QApplication::translate("MainWindow", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        drugIndexButton->setShortcut(QApplication::translate("MainWindow", "F10", nullptr));
#endif // QT_NO_SHORTCUT
        groupBoxDev->setTitle(QApplication::translate("MainWindow", "Development", nullptr));
        condGroupBox->setTitle(QApplication::translate("MainWindow", "Common Conditions", nullptr));
        checkBoxSmoker->setText(QApplication::translate("MainWindow", "Smoker", nullptr));
        labelCigarettsPerDay->setText(QApplication::translate("MainWindow", "Cigarettes per day for ", nullptr));
        labelSmokingYear->setText(QApplication::translate("MainWindow", "Year(s)", nullptr));
        checkBoxAlcohol->setText(QApplication::translate("MainWindow", "Alcohol", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "ABO Rh", nullptr));
        ABO->setItemText(0, QApplication::translate("MainWindow", "?", nullptr));
        ABO->setItemText(1, QApplication::translate("MainWindow", "A+", nullptr));
        ABO->setItemText(2, QApplication::translate("MainWindow", "A-", nullptr));
        ABO->setItemText(3, QApplication::translate("MainWindow", "B+", nullptr));
        ABO->setItemText(4, QApplication::translate("MainWindow", "B-", nullptr));
        ABO->setItemText(5, QApplication::translate("MainWindow", "AB+", nullptr));
        ABO->setItemText(6, QApplication::translate("MainWindow", "AB-", nullptr));
        ABO->setItemText(7, QApplication::translate("MainWindow", "O+", nullptr));
        ABO->setItemText(8, QApplication::translate("MainWindow", "O-", nullptr));
        ABO->setItemText(9, QApplication::translate("MainWindow", "?+", nullptr));
        ABO->setItemText(10, QApplication::translate("MainWindow", "?-", nullptr));

        labelResidence->setText(QApplication::translate("MainWindow", "Residence:", nullptr));
        labelName->setText(QApplication::translate("MainWindow", "Name:        ", nullptr));
#ifndef QT_NO_TOOLTIP
        patientName->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>F1</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        patientName->setInputMask(QString());
        patientName->setText(QString());
        labelAge->setText(QApplication::translate("MainWindow", "Age:   ", nullptr));
        ButtonAgeCal->setText(QApplication::translate("MainWindow", "...", nullptr));
        labelYears->setText(QApplication::translate("MainWindow", "Years", nullptr));
        patientGender->setItemText(0, QApplication::translate("MainWindow", "Male", nullptr));
        patientGender->setItemText(1, QApplication::translate("MainWindow", "Female", nullptr));

        labelPlaceOfBirth->setText(QApplication::translate("MainWindow", "Place of Birth:", nullptr));
        labelOccupation->setText(QApplication::translate("MainWindow", "Occupation:", nullptr));
        comboBoxMaritalStatus->setItemText(0, QApplication::translate("MainWindow", "Single", nullptr));
        comboBoxMaritalStatus->setItemText(1, QApplication::translate("MainWindow", "Married", nullptr));
        comboBoxMaritalStatus->setItemText(2, QApplication::translate("MainWindow", "Widowed", nullptr));
        comboBoxMaritalStatus->setItemText(3, QApplication::translate("MainWindow", "Divorced", nullptr));

#ifndef QT_NO_TOOLTIP
        buttonInvestigations->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Investigations</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonInvestigations->setText(QApplication::translate("MainWindow", "...", nullptr));
        labelMobile->setText(QApplication::translate("MainWindow", "Mobile:      ", nullptr));
        patientMobile->setInputMask(QString());
#ifndef QT_NO_TOOLTIP
        buttonSuricalNotes->setToolTip(QApplication::translate("MainWindow", "Surgical Notes", nullptr));
#endif // QT_NO_TOOLTIP
        buttonSuricalNotes->setText(QApplication::translate("MainWindow", "...", nullptr));
        labelPastHisotry->setText(QApplication::translate("MainWindow", "Past History", nullptr));
        labelFamilyHx->setText(QApplication::translate("MainWindow", "Family History", nullptr));
        lablelNotes->setText(QApplication::translate("MainWindow", "Notes", nullptr));
        labelDrugs->setText(QApplication::translate("MainWindow", "Drugs", nullptr));
        labelAllergy->setText(QApplication::translate("MainWindow", "Allergies", nullptr));
        labelOpAdmission->setText(QApplication::translate("MainWindow", "Operations and Hospital Admissions", nullptr));
#ifndef QT_NO_TOOLTIP
        buttonAddDrug->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Add This Drug</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonAddDrug->setText(QApplication::translate("MainWindow", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        buttonRemoveDrug->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Remove current selection</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonRemoveDrug->setText(QApplication::translate("MainWindow", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        drugLine->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        drugLine->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        drugLine->setText(QString());
        drugLine->setPlaceholderText(QApplication::translate("MainWindow", "enter drug name here - All drugs", nullptr));
#ifndef QT_NO_TOOLTIP
        buttonAddAllergy->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Add This Allergy</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonAddAllergy->setText(QApplication::translate("MainWindow", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        buttonRemoveAllergy->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Remove current selection</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonRemoveAllergy->setText(QApplication::translate("MainWindow", "...", nullptr));
        allergyLine->setPlaceholderText(QApplication::translate("MainWindow", "enter allergy item here", nullptr));
#ifndef QT_NO_TOOLTIP
        buttonAddOP->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Add This event</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonAddOP->setText(QApplication::translate("MainWindow", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        buttonRemoveOP->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Remove current selection</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonRemoveOP->setText(QApplication::translate("MainWindow", "...", nullptr));
        opAdLine->setPlaceholderText(QApplication::translate("MainWindow", "enter operation or incident here", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
