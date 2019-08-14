/********************************************************************************
** Form generated from reading UI file 'list_style_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIST_STYLE_WIDGET_H
#define UI_LIST_STYLE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "m_scolorbutton.h"
#include "switch.h"

QT_BEGIN_NAMESPACE

class Ui_List_style_widget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *selected_item_color_text;
    m_sColorButton *selected_item_color_button;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLineEdit *selected_item_text_color_text;
    m_sColorButton *selected_item_text_color_button;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QLineEdit *messagebox_background_color_text;
    m_sColorButton *messagebox_background_color_button;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QLineEdit *messagebox_text_color_text;
    m_sColorButton *messagebox_text_color_button;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QLineEdit *toolbutton_background_color_text;
    m_sColorButton *toolbutton_background_color_button;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    Switch *enable3D;

    void setupUi(QWidget *List_style_widget)
    {
        if (List_style_widget->objectName().isEmpty())
            List_style_widget->setObjectName(QString::fromUtf8("List_style_widget"));
        List_style_widget->resize(362, 349);
        gridLayout = new QGridLayout(List_style_widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(List_style_widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        selected_item_color_text = new QLineEdit(List_style_widget);
        selected_item_color_text->setObjectName(QString::fromUtf8("selected_item_color_text"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(selected_item_color_text->sizePolicy().hasHeightForWidth());
        selected_item_color_text->setSizePolicy(sizePolicy);
        selected_item_color_text->setMaximumSize(QSize(80, 16777215));
        selected_item_color_text->setReadOnly(true);

        horizontalLayout_2->addWidget(selected_item_color_text);

        selected_item_color_button = new m_sColorButton(List_style_widget);
        selected_item_color_button->setObjectName(QString::fromUtf8("selected_item_color_button"));
        selected_item_color_button->setMinimumSize(QSize(50, 0));
        selected_item_color_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        selected_item_color_button->setAutoRaise(true);

        horizontalLayout_2->addWidget(selected_item_color_button);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(List_style_widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_3->addWidget(label_6);

        selected_item_text_color_text = new QLineEdit(List_style_widget);
        selected_item_text_color_text->setObjectName(QString::fromUtf8("selected_item_text_color_text"));
        sizePolicy.setHeightForWidth(selected_item_text_color_text->sizePolicy().hasHeightForWidth());
        selected_item_text_color_text->setSizePolicy(sizePolicy);
        selected_item_text_color_text->setMaximumSize(QSize(80, 16777215));
        selected_item_text_color_text->setReadOnly(true);

        horizontalLayout_3->addWidget(selected_item_text_color_text);

        selected_item_text_color_button = new m_sColorButton(List_style_widget);
        selected_item_text_color_button->setObjectName(QString::fromUtf8("selected_item_text_color_button"));
        selected_item_text_color_button->setMinimumSize(QSize(50, 0));
        selected_item_text_color_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        selected_item_text_color_button->setAutoRaise(true);

        horizontalLayout_3->addWidget(selected_item_text_color_button);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_7 = new QLabel(List_style_widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_4->addWidget(label_7);

        messagebox_background_color_text = new QLineEdit(List_style_widget);
        messagebox_background_color_text->setObjectName(QString::fromUtf8("messagebox_background_color_text"));
        sizePolicy.setHeightForWidth(messagebox_background_color_text->sizePolicy().hasHeightForWidth());
        messagebox_background_color_text->setSizePolicy(sizePolicy);
        messagebox_background_color_text->setMaximumSize(QSize(80, 16777215));
        messagebox_background_color_text->setReadOnly(true);

        horizontalLayout_4->addWidget(messagebox_background_color_text);

        messagebox_background_color_button = new m_sColorButton(List_style_widget);
        messagebox_background_color_button->setObjectName(QString::fromUtf8("messagebox_background_color_button"));
        messagebox_background_color_button->setMinimumSize(QSize(50, 0));
        messagebox_background_color_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        messagebox_background_color_button->setAutoRaise(true);

        horizontalLayout_4->addWidget(messagebox_background_color_button);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_9 = new QLabel(List_style_widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_6->addWidget(label_9);

        messagebox_text_color_text = new QLineEdit(List_style_widget);
        messagebox_text_color_text->setObjectName(QString::fromUtf8("messagebox_text_color_text"));
        sizePolicy.setHeightForWidth(messagebox_text_color_text->sizePolicy().hasHeightForWidth());
        messagebox_text_color_text->setSizePolicy(sizePolicy);
        messagebox_text_color_text->setMaximumSize(QSize(80, 16777215));
        messagebox_text_color_text->setReadOnly(true);

        horizontalLayout_6->addWidget(messagebox_text_color_text);

        messagebox_text_color_button = new m_sColorButton(List_style_widget);
        messagebox_text_color_button->setObjectName(QString::fromUtf8("messagebox_text_color_button"));
        messagebox_text_color_button->setMinimumSize(QSize(50, 0));
        messagebox_text_color_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        messagebox_text_color_button->setAutoRaise(true);

        horizontalLayout_6->addWidget(messagebox_text_color_button);


        gridLayout->addLayout(horizontalLayout_6, 3, 0, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_8 = new QLabel(List_style_widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_5->addWidget(label_8);

        toolbutton_background_color_text = new QLineEdit(List_style_widget);
        toolbutton_background_color_text->setObjectName(QString::fromUtf8("toolbutton_background_color_text"));
        sizePolicy.setHeightForWidth(toolbutton_background_color_text->sizePolicy().hasHeightForWidth());
        toolbutton_background_color_text->setSizePolicy(sizePolicy);
        toolbutton_background_color_text->setMaximumSize(QSize(80, 16777215));
        toolbutton_background_color_text->setReadOnly(true);

        horizontalLayout_5->addWidget(toolbutton_background_color_text);

        toolbutton_background_color_button = new m_sColorButton(List_style_widget);
        toolbutton_background_color_button->setObjectName(QString::fromUtf8("toolbutton_background_color_button"));
        toolbutton_background_color_button->setMinimumSize(QSize(50, 0));
        toolbutton_background_color_button->setStyleSheet(QString::fromUtf8("border:1px solid black;\n"
"border-radius:4px;"));
        toolbutton_background_color_button->setAutoRaise(true);

        horizontalLayout_5->addWidget(toolbutton_background_color_button);


        gridLayout->addLayout(horizontalLayout_5, 4, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(List_style_widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        enable3D = new Switch(List_style_widget);
        enable3D->setObjectName(QString::fromUtf8("enable3D"));

        horizontalLayout->addWidget(enable3D);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 2);


        retranslateUi(List_style_widget);

        QMetaObject::connectSlotsByName(List_style_widget);
    } // setupUi

    void retranslateUi(QWidget *List_style_widget)
    {
        List_style_widget->setWindowTitle(QApplication::translate("List_style_widget", "Form", nullptr));
        label_5->setText(QApplication::translate("List_style_widget", "selected-item-color", nullptr));
        selected_item_color_text->setText(QString());
        selected_item_color_button->setText(QString());
        label_6->setText(QApplication::translate("List_style_widget", "selected-item-text-color", nullptr));
        selected_item_text_color_text->setText(QString());
        selected_item_text_color_button->setText(QString());
        label_7->setText(QApplication::translate("List_style_widget", "Messagebox-background-color", nullptr));
        messagebox_background_color_text->setText(QString());
        messagebox_background_color_button->setText(QString());
        label_9->setText(QApplication::translate("List_style_widget", "Messagebox-text-color", nullptr));
        messagebox_text_color_text->setText(QString());
        messagebox_text_color_button->setText(QString());
        label_8->setText(QApplication::translate("List_style_widget", "toolButton-background-color", nullptr));
        toolbutton_background_color_text->setText(QString());
        toolbutton_background_color_button->setText(QString());
        label->setText(QApplication::translate("List_style_widget", "Enable 3D", nullptr));
        enable3D->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class List_style_widget: public Ui_List_style_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIST_STYLE_WIDGET_H
