/********************************************************************************
** Form generated from reading UI file 'w_development.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_DEVELOPMENT_H
#define UI_W_DEVELOPMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>
#include "xcheckbox.h"

QT_BEGIN_NAMESPACE

class Ui_w_development
{
public:
    QGridLayout *gridLayout;
    QGroupBox *devBox;
    QGridLayout *gridLayout_9;
    xCheckBox *devCrawlCB;
    xCheckBox *devTeethCB;
    xCheckBox *devSmileCB;
    xCheckBox *devLightCB;
    QFrame *line;
    xCheckBox *devSpeechCB;
    xCheckBox *devHeadCB;
    xCheckBox *devWalkCB;
    xCheckBox *devStandCB;
    xCheckBox *devMotherCB;
    xCheckBox *devSitCB;
    xCheckBox *devSoundCB;

    void setupUi(QWidget *w_development)
    {
        if (w_development->objectName().isEmpty())
            w_development->setObjectName(QString::fromUtf8("w_development"));
        w_development->resize(449, 149);
        gridLayout = new QGridLayout(w_development);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        devBox = new QGroupBox(w_development);
        devBox->setObjectName(QString::fromUtf8("devBox"));
        devBox->setMinimumSize(QSize(0, 110));
        gridLayout_9 = new QGridLayout(devBox);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        devCrawlCB = new xCheckBox(devBox);
        devCrawlCB->setObjectName(QString::fromUtf8("devCrawlCB"));

        gridLayout_9->addWidget(devCrawlCB, 0, 2, 1, 1);

        devTeethCB = new xCheckBox(devBox);
        devTeethCB->setObjectName(QString::fromUtf8("devTeethCB"));

        gridLayout_9->addWidget(devTeethCB, 1, 2, 1, 1);

        devSmileCB = new xCheckBox(devBox);
        devSmileCB->setObjectName(QString::fromUtf8("devSmileCB"));

        gridLayout_9->addWidget(devSmileCB, 3, 1, 1, 1);

        devLightCB = new xCheckBox(devBox);
        devLightCB->setObjectName(QString::fromUtf8("devLightCB"));

        gridLayout_9->addWidget(devLightCB, 4, 0, 1, 1);

        line = new QFrame(devBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_9->addWidget(line, 2, 0, 1, 3);

        devSpeechCB = new xCheckBox(devBox);
        devSpeechCB->setObjectName(QString::fromUtf8("devSpeechCB"));

        gridLayout_9->addWidget(devSpeechCB, 4, 1, 1, 1);

        devHeadCB = new xCheckBox(devBox);
        devHeadCB->setObjectName(QString::fromUtf8("devHeadCB"));

        gridLayout_9->addWidget(devHeadCB, 0, 0, 1, 1);

        devWalkCB = new xCheckBox(devBox);
        devWalkCB->setObjectName(QString::fromUtf8("devWalkCB"));

        gridLayout_9->addWidget(devWalkCB, 1, 1, 1, 1);

        devStandCB = new xCheckBox(devBox);
        devStandCB->setObjectName(QString::fromUtf8("devStandCB"));

        gridLayout_9->addWidget(devStandCB, 1, 0, 1, 1);

        devMotherCB = new xCheckBox(devBox);
        devMotherCB->setObjectName(QString::fromUtf8("devMotherCB"));

        gridLayout_9->addWidget(devMotherCB, 3, 0, 1, 1);

        devSitCB = new xCheckBox(devBox);
        devSitCB->setObjectName(QString::fromUtf8("devSitCB"));

        gridLayout_9->addWidget(devSitCB, 0, 1, 1, 1);

        devSoundCB = new xCheckBox(devBox);
        devSoundCB->setObjectName(QString::fromUtf8("devSoundCB"));

        gridLayout_9->addWidget(devSoundCB, 3, 2, 1, 1);


        gridLayout->addWidget(devBox, 0, 0, 1, 1);


        retranslateUi(w_development);

        QMetaObject::connectSlotsByName(w_development);
    } // setupUi

    void retranslateUi(QWidget *w_development)
    {
        w_development->setWindowTitle(QApplication::translate("w_development", "Form", nullptr));
        devBox->setTitle(QApplication::translate("w_development", "Developmental", nullptr));
        devCrawlCB->setText(QApplication::translate("w_development", "Crawl", nullptr));
        devTeethCB->setText(QApplication::translate("w_development", "Teeth", nullptr));
        devSmileCB->setText(QApplication::translate("w_development", "Smile", nullptr));
        devLightCB->setText(QApplication::translate("w_development", "Light", nullptr));
        devSpeechCB->setText(QApplication::translate("w_development", "Speech", nullptr));
        devHeadCB->setText(QApplication::translate("w_development", "Head", nullptr));
        devWalkCB->setText(QApplication::translate("w_development", "Walk", nullptr));
        devStandCB->setText(QApplication::translate("w_development", "Stand", nullptr));
        devMotherCB->setText(QApplication::translate("w_development", "Mother", nullptr));
        devSitCB->setText(QApplication::translate("w_development", "Sit", nullptr));
        devSoundCB->setText(QApplication::translate("w_development", "Sound", nullptr));
    } // retranslateUi

};

namespace Ui {
    class w_development: public Ui_w_development {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_DEVELOPMENT_H
