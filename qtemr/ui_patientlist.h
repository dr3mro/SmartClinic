/********************************************************************************
** Form generated from reading UI file 'patientlist.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTLIST_H
#define UI_PATIENTLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include "searchwidget.h"

QT_BEGIN_NAMESPACE

class Ui_PatientList
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *closeButton;
    searchWidget *searchWidgetx;

    void setupUi(QDialog *PatientList)
    {
        if (PatientList->objectName().isEmpty())
            PatientList->setObjectName(QString::fromUtf8("PatientList"));
        PatientList->setWindowModality(Qt::ApplicationModal);
        PatientList->resize(320, 458);
        PatientList->setStyleSheet(QString::fromUtf8(""));
        PatientList->setModal(true);
        gridLayout = new QGridLayout(PatientList);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(3);
        gridLayout->setContentsMargins(9, 9, 9, 9);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(PatientList);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        closeButton = new QToolButton(PatientList);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout->addWidget(closeButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        searchWidgetx = new searchWidget(PatientList);
        searchWidgetx->setObjectName(QString::fromUtf8("searchWidgetx"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(searchWidgetx->sizePolicy().hasHeightForWidth());
        searchWidgetx->setSizePolicy(sizePolicy);

        gridLayout->addWidget(searchWidgetx, 1, 0, 1, 1);


        retranslateUi(PatientList);

        QMetaObject::connectSlotsByName(PatientList);
    } // setupUi

    void retranslateUi(QDialog *PatientList)
    {
        PatientList->setWindowTitle(QApplication::translate("PatientList", "Dialog", nullptr));
        label->setText(QApplication::translate("PatientList", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600;\">Patient List</span></p></body></html>", nullptr));
        closeButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PatientList: public Ui_PatientList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTLIST_H
