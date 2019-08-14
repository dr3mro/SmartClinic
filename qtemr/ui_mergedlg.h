/********************************************************************************
** Form generated from reading UI file 'mergedlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MERGEDLG_H
#define UI_MERGEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include "switch.h"

QT_BEGIN_NAMESPACE

class Ui_MergeDlg
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_6;
    QToolButton *closeButton;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *fromID;
    QSpinBox *toID;
    QLabel *label_2;
    QListWidget *visits;
    QHBoxLayout *horizontalLayout_6;
    Switch *cb_delorigin;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_3;
    Switch *cb_all;
    QLabel *mode;
    QHBoxLayout *horizontalLayout_5;
    Switch *cbAccept;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnApply;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLabel *status;

    void setupUi(QDialog *MergeDlg)
    {
        if (MergeDlg->objectName().isEmpty())
            MergeDlg->setObjectName(QString::fromUtf8("MergeDlg"));
        MergeDlg->resize(294, 425);
        gridLayout_2 = new QGridLayout(MergeDlg);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(MergeDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        closeButton = new QToolButton(MergeDlg);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout_4->addWidget(closeButton);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(MergeDlg);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        fromID = new QSpinBox(MergeDlg);
        fromID->setObjectName(QString::fromUtf8("fromID"));
        fromID->setMinimum(1);
        fromID->setMaximum(99999999);

        gridLayout->addWidget(fromID, 0, 2, 1, 1);

        toID = new QSpinBox(MergeDlg);
        toID->setObjectName(QString::fromUtf8("toID"));
        toID->setMinimum(1);
        toID->setMaximum(99999999);

        gridLayout->addWidget(toID, 1, 2, 1, 1);

        label_2 = new QLabel(MergeDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        visits = new QListWidget(MergeDlg);
        visits->setObjectName(QString::fromUtf8("visits"));
        visits->setEditTriggers(QAbstractItemView::NoEditTriggers);
        visits->setAlternatingRowColors(true);
        visits->setSelectionMode(QAbstractItemView::MultiSelection);
        visits->setSelectionBehavior(QAbstractItemView::SelectRows);
        visits->setSelectionRectVisible(true);

        gridLayout_2->addWidget(visits, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        cb_delorigin = new Switch(MergeDlg);
        cb_delorigin->setObjectName(QString::fromUtf8("cb_delorigin"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cb_delorigin->sizePolicy().hasHeightForWidth());
        cb_delorigin->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(cb_delorigin);

        label_5 = new QLabel(MergeDlg);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);


        gridLayout_2->addLayout(horizontalLayout_6, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cb_all = new Switch(MergeDlg);
        cb_all->setObjectName(QString::fromUtf8("cb_all"));
        sizePolicy.setHeightForWidth(cb_all->sizePolicy().hasHeightForWidth());
        cb_all->setSizePolicy(sizePolicy);
        cb_all->setChecked(false);

        horizontalLayout_3->addWidget(cb_all);

        mode = new QLabel(MergeDlg);
        mode->setObjectName(QString::fromUtf8("mode"));

        horizontalLayout_3->addWidget(mode);


        gridLayout_2->addLayout(horizontalLayout_3, 4, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        cbAccept = new Switch(MergeDlg);
        cbAccept->setObjectName(QString::fromUtf8("cbAccept"));
        sizePolicy.setHeightForWidth(cbAccept->sizePolicy().hasHeightForWidth());
        cbAccept->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(cbAccept);

        label_4 = new QLabel(MergeDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);


        gridLayout_2->addLayout(horizontalLayout_5, 5, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnApply = new QPushButton(MergeDlg);
        btnApply->setObjectName(QString::fromUtf8("btnApply"));
        btnApply->setEnabled(false);

        horizontalLayout->addWidget(btnApply);


        gridLayout_2->addLayout(horizontalLayout, 6, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(MergeDlg);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(label_6);

        status = new QLabel(MergeDlg);
        status->setObjectName(QString::fromUtf8("status"));

        horizontalLayout_7->addWidget(status);


        gridLayout_2->addLayout(horizontalLayout_7, 7, 0, 1, 1);


        retranslateUi(MergeDlg);

        QMetaObject::connectSlotsByName(MergeDlg);
    } // setupUi

    void retranslateUi(QDialog *MergeDlg)
    {
        MergeDlg->setWindowTitle(QApplication::translate("MergeDlg", "Dialog", nullptr));
        label_3->setText(QApplication::translate("MergeDlg", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Move Visits</span></p></body></html>", nullptr));
        closeButton->setText(QString());
        label->setText(QApplication::translate("MergeDlg", "Move  visits from patient file number", nullptr));
        label_2->setText(QApplication::translate("MergeDlg", "and add them to patient file number ", nullptr));
        cb_delorigin->setText(QString());
        label_5->setText(QApplication::translate("MergeDlg", "Delete after merge.", nullptr));
        cb_all->setText(QString());
        mode->setText(QApplication::translate("MergeDlg", "All visits.", nullptr));
        cbAccept->setText(QString());
        label_4->setText(QApplication::translate("MergeDlg", "I am sure.", nullptr));
        btnApply->setText(QApplication::translate("MergeDlg", "Apply", nullptr));
        label_6->setText(QApplication::translate("MergeDlg", "Status:", nullptr));
        status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MergeDlg: public Ui_MergeDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MERGEDLG_H
