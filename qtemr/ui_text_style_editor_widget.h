/********************************************************************************
** Form generated from reading UI file 'text_style_editor_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXT_STYLE_EDITOR_WIDGET_H
#define UI_TEXT_STYLE_EDITOR_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "m_scolorbutton.h"

QT_BEGIN_NAMESPACE

class Ui_text_style_editor_widget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_10;
    QLineEdit *color_disabled_text;
    m_sColorButton *color_disabled_button;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_11;
    QLineEdit *color_error_text;
    m_sColorButton *color_error_button;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_12;
    QLineEdit *color_warning_text;
    m_sColorButton *color_warning_button;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *color_normal_text;
    m_sColorButton *color_normal_button;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLineEdit *color_hover_text;
    m_sColorButton *color_hover_button;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_13;
    QLineEdit *color_focus_text;
    m_sColorButton *color_focus_button;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *text_style_editor_widget)
    {
        if (text_style_editor_widget->objectName().isEmpty())
            text_style_editor_widget->setObjectName(QString::fromUtf8("text_style_editor_widget"));
        text_style_editor_widget->resize(359, 228);
        gridLayout = new QGridLayout(text_style_editor_widget);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_10 = new QLabel(text_style_editor_widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_7->addWidget(label_10);

        color_disabled_text = new QLineEdit(text_style_editor_widget);
        color_disabled_text->setObjectName(QString::fromUtf8("color_disabled_text"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(color_disabled_text->sizePolicy().hasHeightForWidth());
        color_disabled_text->setSizePolicy(sizePolicy);
        color_disabled_text->setMaximumSize(QSize(80, 16777215));
        color_disabled_text->setReadOnly(true);

        horizontalLayout_7->addWidget(color_disabled_text);

        color_disabled_button = new m_sColorButton(text_style_editor_widget);
        color_disabled_button->setObjectName(QString::fromUtf8("color_disabled_button"));
        color_disabled_button->setMinimumSize(QSize(50, 0));
        color_disabled_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        color_disabled_button->setAutoRaise(true);

        horizontalLayout_7->addWidget(color_disabled_button);


        gridLayout->addLayout(horizontalLayout_7, 3, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_11 = new QLabel(text_style_editor_widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_8->addWidget(label_11);

        color_error_text = new QLineEdit(text_style_editor_widget);
        color_error_text->setObjectName(QString::fromUtf8("color_error_text"));
        sizePolicy.setHeightForWidth(color_error_text->sizePolicy().hasHeightForWidth());
        color_error_text->setSizePolicy(sizePolicy);
        color_error_text->setMaximumSize(QSize(80, 16777215));
        color_error_text->setReadOnly(true);

        horizontalLayout_8->addWidget(color_error_text);

        color_error_button = new m_sColorButton(text_style_editor_widget);
        color_error_button->setObjectName(QString::fromUtf8("color_error_button"));
        color_error_button->setMinimumSize(QSize(50, 0));
        color_error_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        color_error_button->setAutoRaise(true);

        horizontalLayout_8->addWidget(color_error_button);


        gridLayout->addLayout(horizontalLayout_8, 5, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_12 = new QLabel(text_style_editor_widget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_9->addWidget(label_12);

        color_warning_text = new QLineEdit(text_style_editor_widget);
        color_warning_text->setObjectName(QString::fromUtf8("color_warning_text"));
        sizePolicy.setHeightForWidth(color_warning_text->sizePolicy().hasHeightForWidth());
        color_warning_text->setSizePolicy(sizePolicy);
        color_warning_text->setMaximumSize(QSize(80, 16777215));
        color_warning_text->setReadOnly(true);

        horizontalLayout_9->addWidget(color_warning_text);

        color_warning_button = new m_sColorButton(text_style_editor_widget);
        color_warning_button->setObjectName(QString::fromUtf8("color_warning_button"));
        color_warning_button->setMinimumSize(QSize(50, 0));
        color_warning_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        color_warning_button->setAutoRaise(true);

        horizontalLayout_9->addWidget(color_warning_button);


        gridLayout->addLayout(horizontalLayout_9, 4, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(text_style_editor_widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        color_normal_text = new QLineEdit(text_style_editor_widget);
        color_normal_text->setObjectName(QString::fromUtf8("color_normal_text"));
        sizePolicy.setHeightForWidth(color_normal_text->sizePolicy().hasHeightForWidth());
        color_normal_text->setSizePolicy(sizePolicy);
        color_normal_text->setMaximumSize(QSize(80, 16777215));
        color_normal_text->setReadOnly(true);

        horizontalLayout_2->addWidget(color_normal_text);

        color_normal_button = new m_sColorButton(text_style_editor_widget);
        color_normal_button->setObjectName(QString::fromUtf8("color_normal_button"));
        color_normal_button->setMinimumSize(QSize(50, 0));
        color_normal_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        color_normal_button->setAutoRaise(true);

        horizontalLayout_2->addWidget(color_normal_button);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(text_style_editor_widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        color_hover_text = new QLineEdit(text_style_editor_widget);
        color_hover_text->setObjectName(QString::fromUtf8("color_hover_text"));
        sizePolicy.setHeightForWidth(color_hover_text->sizePolicy().hasHeightForWidth());
        color_hover_text->setSizePolicy(sizePolicy);
        color_hover_text->setMaximumSize(QSize(80, 16777215));
        color_hover_text->setReadOnly(true);

        horizontalLayout_3->addWidget(color_hover_text);

        color_hover_button = new m_sColorButton(text_style_editor_widget);
        color_hover_button->setObjectName(QString::fromUtf8("color_hover_button"));
        color_hover_button->setMinimumSize(QSize(50, 0));
        color_hover_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        color_hover_button->setAutoRaise(true);

        horizontalLayout_3->addWidget(color_hover_button);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_13 = new QLabel(text_style_editor_widget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_10->addWidget(label_13);

        color_focus_text = new QLineEdit(text_style_editor_widget);
        color_focus_text->setObjectName(QString::fromUtf8("color_focus_text"));
        sizePolicy.setHeightForWidth(color_focus_text->sizePolicy().hasHeightForWidth());
        color_focus_text->setSizePolicy(sizePolicy);
        color_focus_text->setMaximumSize(QSize(80, 16777215));
        color_focus_text->setReadOnly(true);

        horizontalLayout_10->addWidget(color_focus_text);

        color_focus_button = new m_sColorButton(text_style_editor_widget);
        color_focus_button->setObjectName(QString::fromUtf8("color_focus_button"));
        color_focus_button->setMinimumSize(QSize(50, 0));
        color_focus_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        color_focus_button->setAutoRaise(true);

        horizontalLayout_10->addWidget(color_focus_button);


        gridLayout->addLayout(horizontalLayout_10, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 1);


        retranslateUi(text_style_editor_widget);

        QMetaObject::connectSlotsByName(text_style_editor_widget);
    } // setupUi

    void retranslateUi(QWidget *text_style_editor_widget)
    {
        text_style_editor_widget->setWindowTitle(QApplication::translate("text_style_editor_widget", "Form", nullptr));
        label_10->setText(QApplication::translate("text_style_editor_widget", "color-disabled", nullptr));
        color_disabled_text->setText(QString());
        color_disabled_button->setText(QString());
        label_11->setText(QApplication::translate("text_style_editor_widget", "color-error", nullptr));
        color_error_text->setText(QString());
        color_error_button->setText(QString());
        label_12->setText(QApplication::translate("text_style_editor_widget", "color-warning", nullptr));
        color_warning_text->setText(QString());
        color_warning_button->setText(QString());
        label_5->setText(QApplication::translate("text_style_editor_widget", "color-normal", nullptr));
        color_normal_text->setText(QString());
        color_normal_button->setText(QString());
        label_6->setText(QApplication::translate("text_style_editor_widget", "color-hover", nullptr));
        color_hover_text->setText(QString());
        color_hover_button->setText(QString());
        label_13->setText(QApplication::translate("text_style_editor_widget", "color-focus", nullptr));
        color_focus_text->setText(QString());
        color_focus_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class text_style_editor_widget: public Ui_text_style_editor_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXT_STYLE_EDITOR_WIDGET_H
