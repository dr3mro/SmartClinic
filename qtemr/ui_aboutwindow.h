/********************************************************************************
** Form generated from reading UI file 'aboutwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWINDOW_H
#define UI_ABOUTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutWindow
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *labelRegistered;
    QLabel *label_code;
    QWidget *widget_reg;
    QGridLayout *gridLayout_3;
    QPushButton *regButton;
    QLabel *unique_id_label;
    QLineEdit *serialNumber;
    QWidget *widgetAppName;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *label_copyright;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *closeButton;
    QLabel *technology;
    QWidget *widget;
    QGridLayout *gridLayout_4;
    QLabel *label_buildtime;
    QLabel *label_version;
    QLabel *label_builddate;
    QLabel *label_developer;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_buildNbr;
    QWidget *widget_about;
    QGridLayout *gridLayout_5;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_6;
    QLabel *label_11;
    QLabel *label_12;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *AboutWindow)
    {
        if (AboutWindow->objectName().isEmpty())
            AboutWindow->setObjectName(QString::fromUtf8("AboutWindow"));
        AboutWindow->setWindowModality(Qt::NonModal);
        AboutWindow->resize(492, 442);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Graphics/applogo"), QSize(), QIcon::Normal, QIcon::Off);
        AboutWindow->setWindowIcon(icon);
        AboutWindow->setWindowOpacity(1.000000000000000);
        AboutWindow->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(AboutWindow);
        gridLayout_2->setSpacing(1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(3, 0, 3, 3);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(20, 5, 20, 5);
        labelRegistered = new QLabel(AboutWindow);
        labelRegistered->setObjectName(QString::fromUtf8("labelRegistered"));
        labelRegistered->setEnabled(true);

        gridLayout->addWidget(labelRegistered, 3, 0, 1, 1);

        label_code = new QLabel(AboutWindow);
        label_code->setObjectName(QString::fromUtf8("label_code"));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        label_code->setFont(font);
        label_code->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_code, 1, 0, 1, 1);

        widget_reg = new QWidget(AboutWindow);
        widget_reg->setObjectName(QString::fromUtf8("widget_reg"));
        gridLayout_3 = new QGridLayout(widget_reg);
        gridLayout_3->setSpacing(1);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(1, 1, 1, 1);
        regButton = new QPushButton(widget_reg);
        regButton->setObjectName(QString::fromUtf8("regButton"));
        regButton->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(regButton->sizePolicy().hasHeightForWidth());
        regButton->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(12);
        regButton->setFont(font1);
        regButton->setFlat(false);

        gridLayout_3->addWidget(regButton, 0, 0, 1, 1);


        gridLayout->addWidget(widget_reg, 6, 0, 1, 1);

        unique_id_label = new QLabel(AboutWindow);
        unique_id_label->setObjectName(QString::fromUtf8("unique_id_label"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Consolas"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        unique_id_label->setFont(font2);
        unique_id_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(unique_id_label, 2, 0, 1, 1);

        serialNumber = new QLineEdit(AboutWindow);
        serialNumber->setObjectName(QString::fromUtf8("serialNumber"));
        serialNumber->setMaxLength(39);
        serialNumber->setAlignment(Qt::AlignCenter);
        serialNumber->setCursorMoveStyle(Qt::LogicalMoveStyle);

        gridLayout->addWidget(serialNumber, 5, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 4);

        widgetAppName = new QWidget(AboutWindow);
        widgetAppName->setObjectName(QString::fromUtf8("widgetAppName"));
        formLayout_2 = new QFormLayout(widgetAppName);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setLabelAlignment(Qt::AlignCenter);
        formLayout_2->setFormAlignment(Qt::AlignHCenter|Qt::AlignTop);
        formLayout_2->setHorizontalSpacing(2);
        formLayout_2->setVerticalSpacing(2);
        formLayout_2->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(widgetAppName);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Times New Roman"));
        font3.setPointSize(28);
        font3.setBold(true);
        font3.setWeight(75);
        font3.setKerning(false);
        label->setFont(font3);
        label->setFrameShadow(QFrame::Plain);
        label->setTextFormat(Qt::RichText);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        formLayout_2->setWidget(1, QFormLayout::SpanningRole, label);

        label_copyright = new QLabel(widgetAppName);
        label_copyright->setObjectName(QString::fromUtf8("label_copyright"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_copyright->sizePolicy().hasHeightForWidth());
        label_copyright->setSizePolicy(sizePolicy2);
        QFont font4;
        font4.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font4.setPointSize(11);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(9);
        label_copyright->setFont(font4);
        label_copyright->setStyleSheet(QString::fromUtf8("font: 75 11pt \"MS Shell Dlg 2\";"));
        label_copyright->setAlignment(Qt::AlignCenter);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, label_copyright);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        closeButton = new QToolButton(widgetAppName);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout->addWidget(closeButton);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, horizontalLayout);

        technology = new QLabel(widgetAppName);
        technology->setObjectName(QString::fromUtf8("technology"));
        QFont font5;
        font5.setBold(true);
        font5.setWeight(75);
        technology->setFont(font5);
        technology->setAlignment(Qt::AlignCenter);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, technology);


        gridLayout_2->addWidget(widgetAppName, 0, 0, 1, 4);

        widget = new QWidget(AboutWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_4 = new QGridLayout(widget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setVerticalSpacing(1);
        label_buildtime = new QLabel(widget);
        label_buildtime->setObjectName(QString::fromUtf8("label_buildtime"));
        label_buildtime->setFont(font2);
        label_buildtime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_buildtime, 3, 0, 1, 1);

        label_version = new QLabel(widget);
        label_version->setObjectName(QString::fromUtf8("label_version"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_version->sizePolicy().hasHeightForWidth());
        label_version->setSizePolicy(sizePolicy3);
        QFont font6;
        font6.setFamily(QString::fromUtf8("Consolas"));
        font6.setPointSize(12);
        font6.setBold(true);
        font6.setWeight(75);
        font6.setKerning(true);
        label_version->setFont(font6);
        label_version->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_version, 0, 0, 1, 1);

        label_builddate = new QLabel(widget);
        label_builddate->setObjectName(QString::fromUtf8("label_builddate"));
        label_builddate->setFont(font2);
        label_builddate->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_builddate, 2, 0, 1, 1);

        label_developer = new QLabel(widget);
        label_developer->setObjectName(QString::fromUtf8("label_developer"));
        label_developer->setFont(font2);
        label_developer->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_developer, 4, 0, 1, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        QFont font7;
        font7.setFamily(QString::fromUtf8("Arial Rounded MT Bold"));
        font7.setPointSize(10);
        font7.setBold(false);
        font7.setItalic(true);
        font7.setWeight(50);
        font7.setKerning(false);
        label_5->setFont(font7);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_5, 5, 0, 1, 1);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font2);
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_7, 6, 0, 1, 1);

        label_buildNbr = new QLabel(widget);
        label_buildNbr->setObjectName(QString::fromUtf8("label_buildNbr"));
        label_buildNbr->setFont(font2);

        gridLayout_4->addWidget(label_buildNbr, 1, 0, 1, 1);


        gridLayout_2->addWidget(widget, 1, 2, 1, 2);

        widget_about = new QWidget(AboutWindow);
        widget_about->setObjectName(QString::fromUtf8("widget_about"));
        gridLayout_5 = new QGridLayout(widget_about);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setVerticalSpacing(1);
        label_4 = new QLabel(widget_about);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        label_2 = new QLabel(widget_about);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_2, 1, 0, 1, 1);

        label_8 = new QLabel(widget_about);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font2);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_8, 2, 0, 1, 1);

        label_9 = new QLabel(widget_about);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font2);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_9, 3, 0, 1, 1);

        label_6 = new QLabel(widget_about);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        QFont font8;
        font8.setFamily(QString::fromUtf8("Consolas"));
        font8.setPointSize(12);
        font8.setBold(true);
        font8.setWeight(75);
        font8.setKerning(false);
        label_6->setFont(font8);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_6, 4, 0, 1, 1);

        label_11 = new QLabel(widget_about);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font2);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_11, 5, 0, 1, 1);

        label_12 = new QLabel(widget_about);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font2);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_12, 6, 0, 1, 1);


        gridLayout_2->addWidget(widget_about, 1, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 3);


        retranslateUi(AboutWindow);

        regButton->setDefault(true);


        QMetaObject::connectSlotsByName(AboutWindow);
    } // setupUi

    void retranslateUi(QDialog *AboutWindow)
    {
        AboutWindow->setWindowTitle(QApplication::translate("AboutWindow", "About", nullptr));
        labelRegistered->setText(QApplication::translate("AboutWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:26pt; font-weight:600; color:#00aa00;\">REGISTERED</span></p></body></html>", nullptr));
        label_code->setText(QApplication::translate("AboutWindow", "<html><head/><body><p>Unique Device ID</p></body></html>", nullptr));
        regButton->setText(QApplication::translate("AboutWindow", "Register", nullptr));
        unique_id_label->setText(QApplication::translate("AboutWindow", "<html><head/><body><p align=\"center\">XX-XX-XX-XX</p></body></html>", nullptr));
        serialNumber->setText(QString());
        label->setText(QApplication::translate("AboutWindow", "<html><head/><body><p><span style=\" font-size:48pt; color:#aa0000;\">Smart Clinic</span></p></body></html>", nullptr));
        label_copyright->setText(QApplication::translate("AboutWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600; color:#0055ff;\">\302\2512017</span></p></body></html>", nullptr));
        closeButton->setText(QString());
        technology->setText(QApplication::translate("AboutWindow", "Using Qt 5.12.x Technology", nullptr));
        label_buildtime->setText(QApplication::translate("AboutWindow", "00:00:00", nullptr));
        label_version->setText(QApplication::translate("AboutWindow", "2.2.2.2", nullptr));
        label_builddate->setText(QApplication::translate("AboutWindow", "25 jan 2011", nullptr));
        label_developer->setText(QApplication::translate("AboutWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Dr. Amr Osman</span></p></body></html>", nullptr));
        label_5->setText(QApplication::translate("AboutWindow", "<html><head/><body><p><span style=\" text-decoration: underline; color:#5500ff;\">dr3mro@gmail.com</span></p></body></html>", nullptr));
        label_7->setText(QApplication::translate("AboutWindow", "<html><head/><body><p>(+2) 01288864274</p></body></html>", nullptr));
        label_buildNbr->setText(QApplication::translate("AboutWindow", "1", nullptr));
        label_4->setText(QApplication::translate("AboutWindow", "Version  :", nullptr));
        label_2->setText(QApplication::translate("AboutWindow", "Build Number  :", nullptr));
        label_8->setText(QApplication::translate("AboutWindow", "Build Date  :", nullptr));
        label_9->setText(QApplication::translate("AboutWindow", "Build Time  :", nullptr));
        label_6->setText(QApplication::translate("AboutWindow", "Developer  :", nullptr));
        label_11->setText(QApplication::translate("AboutWindow", "email  :", nullptr));
        label_12->setText(QApplication::translate("AboutWindow", "Phone  :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutWindow: public Ui_AboutWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWINDOW_H
