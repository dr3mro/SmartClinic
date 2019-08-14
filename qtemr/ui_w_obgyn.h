/********************************************************************************
** Form generated from reading UI file 'w_obgyn.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_OBGYN_H
#define UI_W_OBGYN_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "msiblings.h"
#include "textedit.h"
#include "xcheckbox.h"
#include "xcombobox.h"
#include "xlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_w_obGyn
{
public:
    QGridLayout *gridLayout;
    QGroupBox *ObstGroupBox;
    QGridLayout *gridLayout_12;
    xLineEdit *fpal;
    QLabel *label_15;
    QToolButton *removeSiblings;
    mSiblings *siblings;
    QLabel *label_13;
    TextEdit *husband;
    QLabel *label_9;
    QToolButton *addSiblings;
    QSpacerItem *horizontalSpacer_2;
    xLineEdit *gpa;
    QToolButton *editSiblingButton;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_10;
    QFrame *MestrualHistoryWidget;
    QGridLayout *gridLayout_13;
    QLabel *label_8;
    QLabel *label_7;
    xCheckBox *checkBoxCyclePain;
    xLineEdit *every;
    QDateEdit *LMP;
    QLabel *label_3;
    xCheckBox *checkBoxMenoPause;
    QLabel *label_2;
    xLineEdit *menarche;
    QLabel *label_4;
    QLabel *label;
    xLineEdit *lastsfor;
    xComboBox *cycle;
    QLabel *label_11;
    QLabel *label_6;
    QSpacerItem *verticalSpacer;
    QToolButton *fpalCalButton;

    void setupUi(QWidget *w_obGyn)
    {
        if (w_obGyn->objectName().isEmpty())
            w_obGyn->setObjectName(QString::fromUtf8("w_obGyn"));
        w_obGyn->resize(794, 195);
        gridLayout = new QGridLayout(w_obGyn);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ObstGroupBox = new QGroupBox(w_obGyn);
        ObstGroupBox->setObjectName(QString::fromUtf8("ObstGroupBox"));
        ObstGroupBox->setAlignment(Qt::AlignCenter);
        ObstGroupBox->setFlat(false);
        gridLayout_12 = new QGridLayout(ObstGroupBox);
        gridLayout_12->setSpacing(3);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_12->setContentsMargins(0, 0, 0, 3);
        fpal = new xLineEdit(ObstGroupBox);
        fpal->setObjectName(QString::fromUtf8("fpal"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fpal->sizePolicy().hasHeightForWidth());
        fpal->setSizePolicy(sizePolicy);
        fpal->setMaximumSize(QSize(80, 16777215));
        fpal->setLayoutDirection(Qt::LeftToRight);
        fpal->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(fpal, 1, 4, 1, 1);

        label_15 = new QLabel(ObstGroupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_15, 1, 0, 1, 1);

        removeSiblings = new QToolButton(ObstGroupBox);
        removeSiblings->setObjectName(QString::fromUtf8("removeSiblings"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Graphics/minus"), QSize(), QIcon::Normal, QIcon::Off);
        removeSiblings->setIcon(icon);
        removeSiblings->setAutoRaise(true);

        gridLayout_12->addWidget(removeSiblings, 1, 12, 1, 1);

        siblings = new mSiblings(ObstGroupBox);
        siblings->setObjectName(QString::fromUtf8("siblings"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(siblings->sizePolicy().hasHeightForWidth());
        siblings->setSizePolicy(sizePolicy1);
        siblings->setEditTriggers(QAbstractItemView::NoEditTriggers);
        siblings->setAlternatingRowColors(true);
        siblings->setSelectionMode(QAbstractItemView::SingleSelection);
        siblings->setSelectionBehavior(QAbstractItemView::SelectRows);
        siblings->setShowGrid(true);
        siblings->setGridStyle(Qt::DotLine);
        siblings->setSortingEnabled(false);
        siblings->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        siblings->horizontalHeader()->setStretchLastSection(true);
        siblings->verticalHeader()->setDefaultSectionSize(23);
        siblings->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        siblings->verticalHeader()->setStretchLastSection(false);

        gridLayout_12->addWidget(siblings, 2, 1, 1, 12);

        label_13 = new QLabel(ObstGroupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_13, 1, 13, 1, 1);

        husband = new TextEdit(ObstGroupBox);
        husband->setObjectName(QString::fromUtf8("husband"));
        husband->setMaximumSize(QSize(250, 16777215));

        gridLayout_12->addWidget(husband, 2, 13, 1, 1);

        label_9 = new QLabel(ObstGroupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy2);

        gridLayout_12->addWidget(label_9, 1, 3, 1, 1);

        addSiblings = new QToolButton(ObstGroupBox);
        addSiblings->setObjectName(QString::fromUtf8("addSiblings"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Graphics/add"), QSize(), QIcon::Normal, QIcon::Off);
        addSiblings->setIcon(icon1);
        addSiblings->setAutoRaise(true);

        gridLayout_12->addWidget(addSiblings, 1, 11, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        gpa = new xLineEdit(ObstGroupBox);
        gpa->setObjectName(QString::fromUtf8("gpa"));
        sizePolicy.setHeightForWidth(gpa->sizePolicy().hasHeightForWidth());
        gpa->setSizePolicy(sizePolicy);
        gpa->setMaximumSize(QSize(80, 16777215));
        gpa->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(gpa, 1, 7, 1, 1);

        editSiblingButton = new QToolButton(ObstGroupBox);
        editSiblingButton->setObjectName(QString::fromUtf8("editSiblingButton"));
        editSiblingButton->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Graphics/pencil"), QSize(), QIcon::Normal, QIcon::Off);
        editSiblingButton->setIcon(icon2);
        editSiblingButton->setAutoRaise(true);

        gridLayout_12->addWidget(editSiblingButton, 1, 10, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_7, 1, 9, 1, 1);

        label_10 = new QLabel(ObstGroupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_12->addWidget(label_10, 1, 6, 1, 1);

        MestrualHistoryWidget = new QFrame(ObstGroupBox);
        MestrualHistoryWidget->setObjectName(QString::fromUtf8("MestrualHistoryWidget"));
        MestrualHistoryWidget->setMaximumSize(QSize(250, 16777215));
        MestrualHistoryWidget->setFrameShape(QFrame::StyledPanel);
        MestrualHistoryWidget->setFrameShadow(QFrame::Raised);
        gridLayout_13 = new QGridLayout(MestrualHistoryWidget);
        gridLayout_13->setSpacing(3);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_13->setContentsMargins(3, 3, 3, 3);
        label_8 = new QLabel(MestrualHistoryWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_13->addWidget(label_8, 4, 2, 1, 1);

        label_7 = new QLabel(MestrualHistoryWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_13->addWidget(label_7, 5, 0, 1, 1);

        checkBoxCyclePain = new xCheckBox(MestrualHistoryWidget);
        checkBoxCyclePain->setObjectName(QString::fromUtf8("checkBoxCyclePain"));

        gridLayout_13->addWidget(checkBoxCyclePain, 2, 2, 1, 1);

        every = new xLineEdit(MestrualHistoryWidget);
        every->setObjectName(QString::fromUtf8("every"));
        sizePolicy.setHeightForWidth(every->sizePolicy().hasHeightForWidth());
        every->setSizePolicy(sizePolicy);

        gridLayout_13->addWidget(every, 4, 1, 1, 1);

        LMP = new QDateEdit(MestrualHistoryWidget);
        LMP->setObjectName(QString::fromUtf8("LMP"));
        LMP->setMinimumDateTime(QDateTime(QDate(2010, 1, 1), QTime(0, 0, 0)));
        LMP->setMaximumDate(QDate(2050, 12, 31));
        LMP->setCalendarPopup(true);
        LMP->setDate(QDate(2015, 1, 1));

        gridLayout_13->addWidget(LMP, 5, 1, 1, 1);

        label_3 = new QLabel(MestrualHistoryWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_13->addWidget(label_3, 4, 0, 1, 1);

        checkBoxMenoPause = new xCheckBox(MestrualHistoryWidget);
        checkBoxMenoPause->setObjectName(QString::fromUtf8("checkBoxMenoPause"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(checkBoxMenoPause->sizePolicy().hasHeightForWidth());
        checkBoxMenoPause->setSizePolicy(sizePolicy3);

        gridLayout_13->addWidget(checkBoxMenoPause, 5, 2, 1, 1);

        label_2 = new QLabel(MestrualHistoryWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);

        gridLayout_13->addWidget(label_2, 2, 0, 1, 1);

        menarche = new xLineEdit(MestrualHistoryWidget);
        menarche->setObjectName(QString::fromUtf8("menarche"));
        sizePolicy2.setHeightForWidth(menarche->sizePolicy().hasHeightForWidth());
        menarche->setSizePolicy(sizePolicy2);

        gridLayout_13->addWidget(menarche, 1, 1, 1, 1);

        label_4 = new QLabel(MestrualHistoryWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_13->addWidget(label_4, 3, 0, 1, 1);

        label = new QLabel(MestrualHistoryWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_13->addWidget(label, 1, 0, 1, 1);

        lastsfor = new xLineEdit(MestrualHistoryWidget);
        lastsfor->setObjectName(QString::fromUtf8("lastsfor"));
        sizePolicy.setHeightForWidth(lastsfor->sizePolicy().hasHeightForWidth());
        lastsfor->setSizePolicy(sizePolicy);

        gridLayout_13->addWidget(lastsfor, 3, 1, 1, 1);

        cycle = new xComboBox(MestrualHistoryWidget);
        cycle->addItem(QString());
        cycle->addItem(QString());
        cycle->setObjectName(QString::fromUtf8("cycle"));

        gridLayout_13->addWidget(cycle, 2, 1, 1, 1);

        label_11 = new QLabel(MestrualHistoryWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_13->addWidget(label_11, 1, 2, 1, 1);

        label_6 = new QLabel(MestrualHistoryWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_13->addWidget(label_6, 3, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_13->addItem(verticalSpacer, 6, 1, 1, 1);


        gridLayout_12->addWidget(MestrualHistoryWidget, 2, 0, 1, 1);

        fpalCalButton = new QToolButton(ObstGroupBox);
        fpalCalButton->setObjectName(QString::fromUtf8("fpalCalButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Graphics/puzle"), QSize(), QIcon::Normal, QIcon::Off);
        fpalCalButton->setIcon(icon3);
        fpalCalButton->setAutoRaise(true);

        gridLayout_12->addWidget(fpalCalButton, 1, 2, 1, 1);


        gridLayout->addWidget(ObstGroupBox, 0, 0, 1, 1);


        retranslateUi(w_obGyn);

        QMetaObject::connectSlotsByName(w_obGyn);
    } // setupUi

    void retranslateUi(QWidget *w_obGyn)
    {
        w_obGyn->setWindowTitle(QApplication::translate("w_obGyn", "Form", nullptr));
        ObstGroupBox->setTitle(QApplication::translate("w_obGyn", "Obstetrics ", nullptr));
        fpal->setInputMask(QApplication::translate("w_obGyn", "0-0-0-0", nullptr));
        fpal->setText(QApplication::translate("w_obGyn", "0-0-0-0", nullptr));
        label_15->setText(QApplication::translate("w_obGyn", "Menstrual History", nullptr));
        removeSiblings->setText(QApplication::translate("w_obGyn", "...", nullptr));
        label_13->setText(QApplication::translate("w_obGyn", "Husband", nullptr));
        label_9->setText(QApplication::translate("w_obGyn", "FPAL", nullptr));
        addSiblings->setText(QApplication::translate("w_obGyn", "...", nullptr));
        gpa->setInputMask(QApplication::translate("w_obGyn", "G0-P0+0", nullptr));
        editSiblingButton->setText(QApplication::translate("w_obGyn", "...", nullptr));
        label_10->setText(QApplication::translate("w_obGyn", "GPA+", nullptr));
        label_8->setText(QApplication::translate("w_obGyn", "days", nullptr));
        label_7->setText(QApplication::translate("w_obGyn", "LMP", nullptr));
        checkBoxCyclePain->setText(QApplication::translate("w_obGyn", "Pain", nullptr));
        LMP->setDisplayFormat(QApplication::translate("w_obGyn", "dd/MM/yyyy", nullptr));
        label_3->setText(QApplication::translate("w_obGyn", "Every", nullptr));
        checkBoxMenoPause->setText(QApplication::translate("w_obGyn", "MenoPause", nullptr));
        label_2->setText(QApplication::translate("w_obGyn", "Cycle", nullptr));
        label_4->setText(QApplication::translate("w_obGyn", "Lasts For", nullptr));
        label->setText(QApplication::translate("w_obGyn", "Menarche", nullptr));
        cycle->setItemText(0, QApplication::translate("w_obGyn", "Regular", nullptr));
        cycle->setItemText(1, QApplication::translate("w_obGyn", "Irregular", nullptr));

        label_11->setText(QApplication::translate("w_obGyn", "Years Old", nullptr));
        label_6->setText(QApplication::translate("w_obGyn", "days", nullptr));
#ifndef QT_NO_TOOLTIP
        fpalCalButton->setToolTip(QApplication::translate("w_obGyn", "<html><head/><body><p>Calculate FPAL</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        fpalCalButton->setText(QApplication::translate("w_obGyn", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class w_obGyn: public Ui_w_obGyn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_OBGYN_H
