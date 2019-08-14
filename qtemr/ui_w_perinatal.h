/********************************************************************************
** Form generated from reading UI file 'w_perinatal.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_PERINATAL_H
#define UI_W_PERINATAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "xlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_w_perinatal
{
public:
    QGridLayout *gridLayout;
    QGroupBox *natalBox;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_12;
    QLabel *pregLabel;
    xLineEdit *pregLine;
    QHBoxLayout *horizontalLayout_13;
    QLabel *Laborlabel;
    xLineEdit *laborLine;
    QHBoxLayout *horizontalLayout_14;
    QLabel *NICUlabel;
    xLineEdit *NICUline;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_15;
    QLabel *GAlabel;
    xLineEdit *GAline;
    QWidget *Gl;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_5;
    xLineEdit *Gline;
    QLabel *PL;
    xLineEdit *Pline;
    QLabel *LL;
    xLineEdit *Lline;
    QHBoxLayout *horizontalLayout_17;
    QLabel *deitLabel;
    xLineEdit *dietLine;

    void setupUi(QWidget *w_perinatal)
    {
        if (w_perinatal->objectName().isEmpty())
            w_perinatal->setObjectName(QString::fromUtf8("w_perinatal"));
        w_perinatal->resize(400, 128);
        gridLayout = new QGridLayout(w_perinatal);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        natalBox = new QGroupBox(w_perinatal);
        natalBox->setObjectName(QString::fromUtf8("natalBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(natalBox->sizePolicy().hasHeightForWidth());
        natalBox->setSizePolicy(sizePolicy);
        natalBox->setMinimumSize(QSize(0, 110));
        gridLayout_4 = new QGridLayout(natalBox);
        gridLayout_4->setSpacing(3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(3, 3, 3, 3);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        pregLabel = new QLabel(natalBox);
        pregLabel->setObjectName(QString::fromUtf8("pregLabel"));

        horizontalLayout_12->addWidget(pregLabel);

        pregLine = new xLineEdit(natalBox);
        pregLine->setObjectName(QString::fromUtf8("pregLine"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pregLine->sizePolicy().hasHeightForWidth());
        pregLine->setSizePolicy(sizePolicy1);

        horizontalLayout_12->addWidget(pregLine);


        verticalLayout_5->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        Laborlabel = new QLabel(natalBox);
        Laborlabel->setObjectName(QString::fromUtf8("Laborlabel"));

        horizontalLayout_13->addWidget(Laborlabel);

        laborLine = new xLineEdit(natalBox);
        laborLine->setObjectName(QString::fromUtf8("laborLine"));
        sizePolicy1.setHeightForWidth(laborLine->sizePolicy().hasHeightForWidth());
        laborLine->setSizePolicy(sizePolicy1);

        horizontalLayout_13->addWidget(laborLine);


        verticalLayout_5->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        NICUlabel = new QLabel(natalBox);
        NICUlabel->setObjectName(QString::fromUtf8("NICUlabel"));

        horizontalLayout_14->addWidget(NICUlabel);

        NICUline = new xLineEdit(natalBox);
        NICUline->setObjectName(QString::fromUtf8("NICUline"));
        sizePolicy1.setHeightForWidth(NICUline->sizePolicy().hasHeightForWidth());
        NICUline->setSizePolicy(sizePolicy1);

        horizontalLayout_14->addWidget(NICUline);


        verticalLayout_5->addLayout(horizontalLayout_14);


        gridLayout_4->addLayout(verticalLayout_5, 0, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        GAlabel = new QLabel(natalBox);
        GAlabel->setObjectName(QString::fromUtf8("GAlabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(GAlabel->sizePolicy().hasHeightForWidth());
        GAlabel->setSizePolicy(sizePolicy2);

        horizontalLayout_15->addWidget(GAlabel);

        GAline = new xLineEdit(natalBox);
        GAline->setObjectName(QString::fromUtf8("GAline"));
        sizePolicy1.setHeightForWidth(GAline->sizePolicy().hasHeightForWidth());
        GAline->setSizePolicy(sizePolicy1);

        horizontalLayout_15->addWidget(GAline);


        verticalLayout_4->addLayout(horizontalLayout_15);

        Gl = new QWidget(natalBox);
        Gl->setObjectName(QString::fromUtf8("Gl"));
        horizontalLayout_16 = new QHBoxLayout(Gl);
        horizontalLayout_16->setSpacing(0);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(Gl);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);

        horizontalLayout_16->addWidget(label_5);

        Gline = new xLineEdit(Gl);
        Gline->setObjectName(QString::fromUtf8("Gline"));
        sizePolicy1.setHeightForWidth(Gline->sizePolicy().hasHeightForWidth());
        Gline->setSizePolicy(sizePolicy1);
        Gline->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_16->addWidget(Gline);

        PL = new QLabel(Gl);
        PL->setObjectName(QString::fromUtf8("PL"));
        sizePolicy2.setHeightForWidth(PL->sizePolicy().hasHeightForWidth());
        PL->setSizePolicy(sizePolicy2);

        horizontalLayout_16->addWidget(PL);

        Pline = new xLineEdit(Gl);
        Pline->setObjectName(QString::fromUtf8("Pline"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(Pline->sizePolicy().hasHeightForWidth());
        Pline->setSizePolicy(sizePolicy3);
        Pline->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_16->addWidget(Pline);

        LL = new QLabel(Gl);
        LL->setObjectName(QString::fromUtf8("LL"));
        sizePolicy2.setHeightForWidth(LL->sizePolicy().hasHeightForWidth());
        LL->setSizePolicy(sizePolicy2);

        horizontalLayout_16->addWidget(LL);

        Lline = new xLineEdit(Gl);
        Lline->setObjectName(QString::fromUtf8("Lline"));
        sizePolicy3.setHeightForWidth(Lline->sizePolicy().hasHeightForWidth());
        Lline->setSizePolicy(sizePolicy3);
        Lline->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_16->addWidget(Lline);


        verticalLayout_4->addWidget(Gl);


        gridLayout_4->addLayout(verticalLayout_4, 0, 1, 1, 1);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        deitLabel = new QLabel(natalBox);
        deitLabel->setObjectName(QString::fromUtf8("deitLabel"));
        sizePolicy2.setHeightForWidth(deitLabel->sizePolicy().hasHeightForWidth());
        deitLabel->setSizePolicy(sizePolicy2);

        horizontalLayout_17->addWidget(deitLabel);

        dietLine = new xLineEdit(natalBox);
        dietLine->setObjectName(QString::fromUtf8("dietLine"));
        sizePolicy1.setHeightForWidth(dietLine->sizePolicy().hasHeightForWidth());
        dietLine->setSizePolicy(sizePolicy1);

        horizontalLayout_17->addWidget(dietLine);


        gridLayout_4->addLayout(horizontalLayout_17, 1, 0, 1, 2);


        gridLayout->addWidget(natalBox, 0, 0, 1, 1);


        retranslateUi(w_perinatal);

        QMetaObject::connectSlotsByName(w_perinatal);
    } // setupUi

    void retranslateUi(QWidget *w_perinatal)
    {
        w_perinatal->setWindowTitle(QApplication::translate("w_perinatal", "Form", nullptr));
        natalBox->setTitle(QApplication::translate("w_perinatal", "Perinatal", nullptr));
        pregLabel->setText(QApplication::translate("w_perinatal", "Pregnancy", nullptr));
        Laborlabel->setText(QApplication::translate("w_perinatal", "Labor", nullptr));
        NICUlabel->setText(QApplication::translate("w_perinatal", "NICU", nullptr));
        GAlabel->setText(QApplication::translate("w_perinatal", "GA", nullptr));
        label_5->setText(QApplication::translate("w_perinatal", "G", nullptr));
        PL->setText(QApplication::translate("w_perinatal", "P", nullptr));
        LL->setText(QApplication::translate("w_perinatal", "L", nullptr));
        deitLabel->setText(QApplication::translate("w_perinatal", "Diet", nullptr));
    } // retranslateUi

};

namespace Ui {
    class w_perinatal: public Ui_w_perinatal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_PERINATAL_H
