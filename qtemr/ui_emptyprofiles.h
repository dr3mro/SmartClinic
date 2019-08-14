/********************************************************************************
** Form generated from reading UI file 'emptyprofiles.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPTYPROFILES_H
#define UI_EMPTYPROFILES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EmptyProfiles
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *closeButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *checkBox;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonOk;
    QPushButton *buttonClose;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *EmptyProfiles)
    {
        if (EmptyProfiles->objectName().isEmpty())
            EmptyProfiles->setObjectName(QString::fromUtf8("EmptyProfiles"));
        EmptyProfiles->setWindowModality(Qt::ApplicationModal);
        EmptyProfiles->resize(362, 156);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EmptyProfiles->sizePolicy().hasHeightForWidth());
        EmptyProfiles->setSizePolicy(sizePolicy);
        EmptyProfiles->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(EmptyProfiles);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 9, -1, 9);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(EmptyProfiles);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(379, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        closeButton = new QToolButton(EmptyProfiles);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout_3->addWidget(closeButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(EmptyProfiles);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        spinBox = new QSpinBox(EmptyProfiles);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy1);
        spinBox->setMaximum(9999);

        horizontalLayout_4->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(EmptyProfiles);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        checkBox = new QCheckBox(EmptyProfiles);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        sizePolicy1.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(checkBox);


        verticalLayout->addLayout(horizontalLayout);

        progressBar = new QProgressBar(EmptyProfiles);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        buttonOk = new QPushButton(EmptyProfiles);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setEnabled(false);

        horizontalLayout_2->addWidget(buttonOk);

        buttonClose = new QPushButton(EmptyProfiles);
        buttonClose->setObjectName(QString::fromUtf8("buttonClose"));

        horizontalLayout_2->addWidget(buttonClose);

        horizontalSpacer_2 = new QSpacerItem(82, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(EmptyProfiles);

        QMetaObject::connectSlotsByName(EmptyProfiles);
    } // setupUi

    void retranslateUi(QDialog *EmptyProfiles)
    {
        EmptyProfiles->setWindowTitle(QApplication::translate("EmptyProfiles", "Dialog", nullptr));
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("EmptyProfiles", "<html><head/><body><p align=\"justify\">This Features enables you to create a predefinded number of empty records so in case of you already has other types of patients filing system eg. patients files (printed) then you can create them in one touch and then fill them later when ever you want</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("EmptyProfiles", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Patients Generator</span></p></body></html>", nullptr));
        closeButton->setText(QString());
        label_2->setText(QApplication::translate("EmptyProfiles", "Specify the Total number of  Records you want to Generate", nullptr));
        label->setText(QApplication::translate("EmptyProfiles", "Number of Patient Records", nullptr));
        checkBox->setText(QApplication::translate("EmptyProfiles", "Accept", nullptr));
        buttonOk->setText(QApplication::translate("EmptyProfiles", "Generate", nullptr));
        buttonClose->setText(QApplication::translate("EmptyProfiles", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmptyProfiles: public Ui_EmptyProfiles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPTYPROFILES_H
