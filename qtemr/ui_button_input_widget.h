/********************************************************************************
** Form generated from reading UI file 'button_input_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTON_INPUT_WIDGET_H
#define UI_BUTTON_INPUT_WIDGET_H

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

class Ui_button_input_widget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *color_normal_text;
    m_sColorButton *color_normal_button;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_12;
    QLineEdit *border_color_focus_text;
    m_sColorButton *border_color_focus_button;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QLineEdit *color_disabled_text;
    m_sColorButton *color_disabled_button;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *border_radius;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_10;
    QLineEdit *border_color_normal_text;
    m_sColorButton *border_color_normal_button;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *color_hover_text;
    m_sColorButton *color_hover_button;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLineEdit *color_focus_text;
    m_sColorButton *color_focus_button;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QLineEdit *color_warning_text;
    m_sColorButton *color_warning_button;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_11;
    QLineEdit *border_color_hover_text;
    m_sColorButton *border_color_hover_button;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_15;
    QSpacerItem *horizontalSpacer;
    QSpinBox *border_width;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_13;
    QLineEdit *border_color_diabled_text;
    m_sColorButton *border_color_diabled_button;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QLineEdit *color_error_text;
    m_sColorButton *color_error_button;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *button_input_widget)
    {
        if (button_input_widget->objectName().isEmpty())
            button_input_widget->setObjectName(QString::fromUtf8("button_input_widget"));
        button_input_widget->resize(348, 403);
        gridLayout = new QGridLayout(button_input_widget);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(button_input_widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        color_normal_text = new QLineEdit(button_input_widget);
        color_normal_text->setObjectName(QString::fromUtf8("color_normal_text"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(color_normal_text->sizePolicy().hasHeightForWidth());
        color_normal_text->setSizePolicy(sizePolicy);
        color_normal_text->setMaximumSize(QSize(80, 16777215));
        color_normal_text->setReadOnly(true);

        horizontalLayout->addWidget(color_normal_text);

        color_normal_button = new m_sColorButton(button_input_widget);
        color_normal_button->setObjectName(QString::fromUtf8("color_normal_button"));
        color_normal_button->setMinimumSize(QSize(50, 0));
        color_normal_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        color_normal_button->setAutoRaise(true);

        horizontalLayout->addWidget(color_normal_button);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_12 = new QLabel(button_input_widget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_9->addWidget(label_12);

        border_color_focus_text = new QLineEdit(button_input_widget);
        border_color_focus_text->setObjectName(QString::fromUtf8("border_color_focus_text"));
        sizePolicy.setHeightForWidth(border_color_focus_text->sizePolicy().hasHeightForWidth());
        border_color_focus_text->setSizePolicy(sizePolicy);
        border_color_focus_text->setMaximumSize(QSize(80, 16777215));
        border_color_focus_text->setReadOnly(true);

        horizontalLayout_9->addWidget(border_color_focus_text);

        border_color_focus_button = new m_sColorButton(button_input_widget);
        border_color_focus_button->setObjectName(QString::fromUtf8("border_color_focus_button"));
        border_color_focus_button->setMinimumSize(QSize(50, 0));
        border_color_focus_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        border_color_focus_button->setAutoRaise(true);

        horizontalLayout_9->addWidget(border_color_focus_button);


        gridLayout->addLayout(horizontalLayout_9, 8, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_7 = new QLabel(button_input_widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_4->addWidget(label_7);

        color_disabled_text = new QLineEdit(button_input_widget);
        color_disabled_text->setObjectName(QString::fromUtf8("color_disabled_text"));
        sizePolicy.setHeightForWidth(color_disabled_text->sizePolicy().hasHeightForWidth());
        color_disabled_text->setSizePolicy(sizePolicy);
        color_disabled_text->setMaximumSize(QSize(80, 16777215));
        color_disabled_text->setReadOnly(true);

        horizontalLayout_4->addWidget(color_disabled_text);

        color_disabled_button = new m_sColorButton(button_input_widget);
        color_disabled_button->setObjectName(QString::fromUtf8("color_disabled_button"));
        color_disabled_button->setMinimumSize(QSize(50, 0));
        color_disabled_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        color_disabled_button->setAutoRaise(true);

        horizontalLayout_4->addWidget(color_disabled_button);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_16 = new QLabel(button_input_widget);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_13->addWidget(label_16);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_2);

        border_radius = new QSpinBox(button_input_widget);
        border_radius->setObjectName(QString::fromUtf8("border_radius"));

        horizontalLayout_13->addWidget(border_radius);


        gridLayout->addLayout(horizontalLayout_13, 11, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_10 = new QLabel(button_input_widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_7->addWidget(label_10);

        border_color_normal_text = new QLineEdit(button_input_widget);
        border_color_normal_text->setObjectName(QString::fromUtf8("border_color_normal_text"));
        sizePolicy.setHeightForWidth(border_color_normal_text->sizePolicy().hasHeightForWidth());
        border_color_normal_text->setSizePolicy(sizePolicy);
        border_color_normal_text->setMaximumSize(QSize(80, 16777215));
        border_color_normal_text->setReadOnly(true);

        horizontalLayout_7->addWidget(border_color_normal_text);

        border_color_normal_button = new m_sColorButton(button_input_widget);
        border_color_normal_button->setObjectName(QString::fromUtf8("border_color_normal_button"));
        border_color_normal_button->setMinimumSize(QSize(50, 0));
        border_color_normal_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        border_color_normal_button->setAutoRaise(true);

        horizontalLayout_7->addWidget(border_color_normal_button);


        gridLayout->addLayout(horizontalLayout_7, 6, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(button_input_widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        color_hover_text = new QLineEdit(button_input_widget);
        color_hover_text->setObjectName(QString::fromUtf8("color_hover_text"));
        sizePolicy.setHeightForWidth(color_hover_text->sizePolicy().hasHeightForWidth());
        color_hover_text->setSizePolicy(sizePolicy);
        color_hover_text->setMaximumSize(QSize(80, 16777215));
        color_hover_text->setReadOnly(true);

        horizontalLayout_2->addWidget(color_hover_text);

        color_hover_button = new m_sColorButton(button_input_widget);
        color_hover_button->setObjectName(QString::fromUtf8("color_hover_button"));
        color_hover_button->setMinimumSize(QSize(50, 0));
        color_hover_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        color_hover_button->setAutoRaise(true);

        horizontalLayout_2->addWidget(color_hover_button);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(button_input_widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        color_focus_text = new QLineEdit(button_input_widget);
        color_focus_text->setObjectName(QString::fromUtf8("color_focus_text"));
        sizePolicy.setHeightForWidth(color_focus_text->sizePolicy().hasHeightForWidth());
        color_focus_text->setSizePolicy(sizePolicy);
        color_focus_text->setMaximumSize(QSize(80, 16777215));
        color_focus_text->setReadOnly(true);

        horizontalLayout_3->addWidget(color_focus_text);

        color_focus_button = new m_sColorButton(button_input_widget);
        color_focus_button->setObjectName(QString::fromUtf8("color_focus_button"));
        color_focus_button->setMinimumSize(QSize(50, 0));
        color_focus_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        color_focus_button->setAutoRaise(true);

        horizontalLayout_3->addWidget(color_focus_button);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_8 = new QLabel(button_input_widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_5->addWidget(label_8);

        color_warning_text = new QLineEdit(button_input_widget);
        color_warning_text->setObjectName(QString::fromUtf8("color_warning_text"));
        sizePolicy.setHeightForWidth(color_warning_text->sizePolicy().hasHeightForWidth());
        color_warning_text->setSizePolicy(sizePolicy);
        color_warning_text->setMaximumSize(QSize(80, 16777215));
        color_warning_text->setReadOnly(true);

        horizontalLayout_5->addWidget(color_warning_text);

        color_warning_button = new m_sColorButton(button_input_widget);
        color_warning_button->setObjectName(QString::fromUtf8("color_warning_button"));
        color_warning_button->setMinimumSize(QSize(50, 0));
        color_warning_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        color_warning_button->setAutoRaise(true);

        horizontalLayout_5->addWidget(color_warning_button);


        gridLayout->addLayout(horizontalLayout_5, 4, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_11 = new QLabel(button_input_widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_8->addWidget(label_11);

        border_color_hover_text = new QLineEdit(button_input_widget);
        border_color_hover_text->setObjectName(QString::fromUtf8("border_color_hover_text"));
        sizePolicy.setHeightForWidth(border_color_hover_text->sizePolicy().hasHeightForWidth());
        border_color_hover_text->setSizePolicy(sizePolicy);
        border_color_hover_text->setMaximumSize(QSize(80, 16777215));
        border_color_hover_text->setReadOnly(true);

        horizontalLayout_8->addWidget(border_color_hover_text);

        border_color_hover_button = new m_sColorButton(button_input_widget);
        border_color_hover_button->setObjectName(QString::fromUtf8("border_color_hover_button"));
        border_color_hover_button->setMinimumSize(QSize(50, 0));
        border_color_hover_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        border_color_hover_button->setAutoRaise(true);

        horizontalLayout_8->addWidget(border_color_hover_button);


        gridLayout->addLayout(horizontalLayout_8, 7, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_15 = new QLabel(button_input_widget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_12->addWidget(label_15);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer);

        border_width = new QSpinBox(button_input_widget);
        border_width->setObjectName(QString::fromUtf8("border_width"));

        horizontalLayout_12->addWidget(border_width);


        gridLayout->addLayout(horizontalLayout_12, 10, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_13 = new QLabel(button_input_widget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_10->addWidget(label_13);

        border_color_diabled_text = new QLineEdit(button_input_widget);
        border_color_diabled_text->setObjectName(QString::fromUtf8("border_color_diabled_text"));
        sizePolicy.setHeightForWidth(border_color_diabled_text->sizePolicy().hasHeightForWidth());
        border_color_diabled_text->setSizePolicy(sizePolicy);
        border_color_diabled_text->setMaximumSize(QSize(80, 16777215));
        border_color_diabled_text->setReadOnly(true);

        horizontalLayout_10->addWidget(border_color_diabled_text);

        border_color_diabled_button = new m_sColorButton(button_input_widget);
        border_color_diabled_button->setObjectName(QString::fromUtf8("border_color_diabled_button"));
        border_color_diabled_button->setMinimumSize(QSize(50, 0));
        border_color_diabled_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        border_color_diabled_button->setAutoRaise(true);

        horizontalLayout_10->addWidget(border_color_diabled_button);


        gridLayout->addLayout(horizontalLayout_10, 9, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_9 = new QLabel(button_input_widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_6->addWidget(label_9);

        color_error_text = new QLineEdit(button_input_widget);
        color_error_text->setObjectName(QString::fromUtf8("color_error_text"));
        sizePolicy.setHeightForWidth(color_error_text->sizePolicy().hasHeightForWidth());
        color_error_text->setSizePolicy(sizePolicy);
        color_error_text->setMaximumSize(QSize(80, 16777215));
        color_error_text->setReadOnly(true);

        horizontalLayout_6->addWidget(color_error_text);

        color_error_button = new m_sColorButton(button_input_widget);
        color_error_button->setObjectName(QString::fromUtf8("color_error_button"));
        color_error_button->setMinimumSize(QSize(50, 0));
        color_error_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        color_error_button->setAutoRaise(true);

        horizontalLayout_6->addWidget(color_error_button);


        gridLayout->addLayout(horizontalLayout_6, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 12, 0, 1, 1);


        retranslateUi(button_input_widget);

        QMetaObject::connectSlotsByName(button_input_widget);
    } // setupUi

    void retranslateUi(QWidget *button_input_widget)
    {
        button_input_widget->setWindowTitle(QApplication::translate("button_input_widget", "Form", nullptr));
        label_4->setText(QApplication::translate("button_input_widget", "color-normal", nullptr));
        color_normal_text->setText(QString());
        color_normal_button->setText(QString());
        label_12->setText(QApplication::translate("button_input_widget", "border-color-focus", nullptr));
        border_color_focus_text->setText(QString());
        border_color_focus_button->setText(QString());
        label_7->setText(QApplication::translate("button_input_widget", "color-disabled", nullptr));
        color_disabled_text->setText(QString());
        color_disabled_button->setText(QString());
        label_16->setText(QApplication::translate("button_input_widget", "border-radius", nullptr));
        label_10->setText(QApplication::translate("button_input_widget", "border-color-normal", nullptr));
        border_color_normal_text->setText(QString());
        border_color_normal_button->setText(QString());
        label_5->setText(QApplication::translate("button_input_widget", "color-hover", nullptr));
        color_hover_text->setText(QString());
        color_hover_button->setText(QString());
        label_6->setText(QApplication::translate("button_input_widget", "color-focus", nullptr));
        color_focus_text->setText(QString());
        color_focus_button->setText(QString());
        label_8->setText(QApplication::translate("button_input_widget", "color-warning", nullptr));
        color_warning_text->setText(QString());
        color_warning_button->setText(QString());
        label_11->setText(QApplication::translate("button_input_widget", "border-color-hover", nullptr));
        border_color_hover_text->setText(QString());
        border_color_hover_button->setText(QString());
        label_15->setText(QApplication::translate("button_input_widget", "border-width", nullptr));
        label_13->setText(QApplication::translate("button_input_widget", "boder-color-disabled", nullptr));
        border_color_diabled_text->setText(QString());
        border_color_diabled_button->setText(QString());
        label_9->setText(QApplication::translate("button_input_widget", "color-error", nullptr));
        color_error_text->setText(QString());
        color_error_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class button_input_widget: public Ui_button_input_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTON_INPUT_WIDGET_H
