/********************************************************************************
** Form generated from reading UI file 'welcomebanner.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEBANNER_H
#define UI_WELCOMEBANNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_welcomeBanner
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QWidget *data;
    QGridLayout *gridLayout_2;
    QLabel *appName;
    QLabel *appVer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *progress;
    QSpacerItem *horizontalSpacer_3;
    QLabel *message;
    QSpacerItem *horizontalSpacer;
    QProgressBar *progressBar;
    QLabel *current_stage;

    void setupUi(QDialog *welcomeBanner)
    {
        if (welcomeBanner->objectName().isEmpty())
            welcomeBanner->setObjectName(QString::fromUtf8("welcomeBanner"));
        welcomeBanner->resize(501, 207);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(welcomeBanner->sizePolicy().hasHeightForWidth());
        welcomeBanner->setSizePolicy(sizePolicy);
        welcomeBanner->setModal(true);
        gridLayout = new QGridLayout(welcomeBanner);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(welcomeBanner);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget\n"
"{\n"
"image: url(:/banner/banner3);\n"
"}"));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        data = new QWidget(widget);
        data->setObjectName(QString::fromUtf8("data"));
        gridLayout_2 = new QGridLayout(data);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        appName = new QLabel(data);
        appName->setObjectName(QString::fromUtf8("appName"));
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        appName->setFont(font);
        appName->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(appName, 0, 0, 1, 3);

        appVer = new QLabel(data);
        appVer->setObjectName(QString::fromUtf8("appVer"));
        QFont font1;
        font1.setPointSize(11);
        appVer->setFont(font1);
        appVer->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(appVer, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(77, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        progress = new QLabel(data);
        progress->setObjectName(QString::fromUtf8("progress"));
        progress->setMinimumSize(QSize(48, 48));
        progress->setMaximumSize(QSize(48, 48));
        progress->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(progress, 2, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(77, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 2, 2, 1, 1);

        message = new QLabel(data);
        message->setObjectName(QString::fromUtf8("message"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Consolas"));
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setItalic(true);
        font2.setWeight(50);
        message->setFont(font2);

        gridLayout_2->addWidget(message, 3, 0, 1, 3);


        gridLayout_3->addWidget(data, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(236, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 0, 1, 1);

        progressBar = new QProgressBar(widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout_3->addWidget(progressBar, 2, 0, 1, 2);

        current_stage = new QLabel(widget);
        current_stage->setObjectName(QString::fromUtf8("current_stage"));
        QFont font3;
        font3.setPointSize(10);
        current_stage->setFont(font3);
        current_stage->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(current_stage, 1, 1, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(welcomeBanner);

        QMetaObject::connectSlotsByName(welcomeBanner);
    } // setupUi

    void retranslateUi(QDialog *welcomeBanner)
    {
        welcomeBanner->setWindowTitle(QApplication::translate("welcomeBanner", "Smart Clinic", nullptr));
        appName->setText(QApplication::translate("welcomeBanner", "appName", nullptr));
        appVer->setText(QApplication::translate("welcomeBanner", "appVer", nullptr));
        progress->setText(QString());
        message->setText(QApplication::translate("welcomeBanner", "Loading, Please wait.", nullptr));
        current_stage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class welcomeBanner: public Ui_welcomeBanner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEBANNER_H
