/********************************************************************************
** Form generated from reading UI file 'window_subwindow_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_SUBWINDOW_WIDGET_H
#define UI_WINDOW_SUBWINDOW_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "m_scolorbutton.h"

QT_BEGIN_NAMESPACE

class Ui_window_subwindow_widget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *top_color_text;
    m_sColorButton *top_color_button;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *bottom_color_text;
    m_sColorButton *bottom_color_button;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer;
    QSpinBox *border_width;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLineEdit *border_color_text;
    m_sColorButton *border_color_button;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *border_radius;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *window_subwindow_widget)
    {
        if (window_subwindow_widget->objectName().isEmpty())
            window_subwindow_widget->setObjectName(QString::fromUtf8("window_subwindow_widget"));
        window_subwindow_widget->resize(368, 186);
        gridLayout = new QGridLayout(window_subwindow_widget);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(window_subwindow_widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        top_color_text = new QLineEdit(window_subwindow_widget);
        top_color_text->setObjectName(QString::fromUtf8("top_color_text"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(top_color_text->sizePolicy().hasHeightForWidth());
        top_color_text->setSizePolicy(sizePolicy);
        top_color_text->setMaximumSize(QSize(80, 16777215));
        top_color_text->setReadOnly(true);

        horizontalLayout->addWidget(top_color_text);

        top_color_button = new m_sColorButton(window_subwindow_widget);
        top_color_button->setObjectName(QString::fromUtf8("top_color_button"));
        top_color_button->setMinimumSize(QSize(50, 0));
        top_color_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        top_color_button->setAutoRaise(true);

        horizontalLayout->addWidget(top_color_button);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(window_subwindow_widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        bottom_color_text = new QLineEdit(window_subwindow_widget);
        bottom_color_text->setObjectName(QString::fromUtf8("bottom_color_text"));
        sizePolicy.setHeightForWidth(bottom_color_text->sizePolicy().hasHeightForWidth());
        bottom_color_text->setSizePolicy(sizePolicy);
        bottom_color_text->setMaximumSize(QSize(80, 16777215));
        bottom_color_text->setReadOnly(true);

        horizontalLayout_2->addWidget(bottom_color_text);

        bottom_color_button = new m_sColorButton(window_subwindow_widget);
        bottom_color_button->setObjectName(QString::fromUtf8("bottom_color_button"));
        bottom_color_button->setMinimumSize(QSize(50, 0));
        bottom_color_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        bottom_color_button->setAutoRaise(true);

        horizontalLayout_2->addWidget(bottom_color_button);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_7 = new QLabel(window_subwindow_widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_4->addWidget(label_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        border_width = new QSpinBox(window_subwindow_widget);
        border_width->setObjectName(QString::fromUtf8("border_width"));

        horizontalLayout_4->addWidget(border_width);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(window_subwindow_widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        border_color_text = new QLineEdit(window_subwindow_widget);
        border_color_text->setObjectName(QString::fromUtf8("border_color_text"));
        sizePolicy.setHeightForWidth(border_color_text->sizePolicy().hasHeightForWidth());
        border_color_text->setSizePolicy(sizePolicy);
        border_color_text->setMaximumSize(QSize(80, 16777215));
        border_color_text->setReadOnly(true);

        horizontalLayout_3->addWidget(border_color_text);

        border_color_button = new m_sColorButton(window_subwindow_widget);
        border_color_button->setObjectName(QString::fromUtf8("border_color_button"));
        border_color_button->setMinimumSize(QSize(50, 0));
        border_color_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        border_color_button->setAutoRaise(true);

        horizontalLayout_3->addWidget(border_color_button);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_12 = new QLabel(window_subwindow_widget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_9->addWidget(label_12);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);

        border_radius = new QSpinBox(window_subwindow_widget);
        border_radius->setObjectName(QString::fromUtf8("border_radius"));

        horizontalLayout_9->addWidget(border_radius);


        gridLayout->addLayout(horizontalLayout_9, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);


        retranslateUi(window_subwindow_widget);

        QMetaObject::connectSlotsByName(window_subwindow_widget);
    } // setupUi

    void retranslateUi(QWidget *window_subwindow_widget)
    {
        window_subwindow_widget->setWindowTitle(QApplication::translate("window_subwindow_widget", "Form", nullptr));
        label_4->setText(QApplication::translate("window_subwindow_widget", "Top-color", nullptr));
        top_color_text->setText(QString());
        top_color_button->setText(QString());
        label_5->setText(QApplication::translate("window_subwindow_widget", "Bottom-color", nullptr));
        bottom_color_text->setText(QString());
        bottom_color_button->setText(QString());
        label_7->setText(QApplication::translate("window_subwindow_widget", "border-width", nullptr));
        label_6->setText(QApplication::translate("window_subwindow_widget", "Border-color", nullptr));
        border_color_text->setText(QString());
        border_color_button->setText(QString());
        label_12->setText(QApplication::translate("window_subwindow_widget", "border-radius", nullptr));
    } // retranslateUi

};

namespace Ui {
    class window_subwindow_widget: public Ui_window_subwindow_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_SUBWINDOW_WIDGET_H
