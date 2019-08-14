/********************************************************************************
** Form generated from reading UI file 'stylewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STYLEWIDGET_H
#define UI_STYLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>
#include "button_input_widget.h"
#include "list_style_widget.h"
#include "text_style_editor_widget.h"
#include "window_subwindow_widget.h"

QT_BEGIN_NAMESPACE

class Ui_StyleWidget
{
public:
    QGridLayout *gridLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_4;
    QToolBox *styleEditor;
    QWidget *WindowStyle;
    QGridLayout *gridLayout;
    window_subwindow_widget *windowStyleEditor;
    QWidget *subwindowStyle;
    QGridLayout *gridLayout_2;
    window_subwindow_widget *subwindowStyleEditor;
    QWidget *ButtonsStyle;
    QGridLayout *gridLayout_5;
    button_input_widget *buttonStyleEditor;
    QWidget *inputStyles;
    QGridLayout *gridLayout_6;
    button_input_widget *inputStyleEditor;
    QWidget *elementTextStyles;
    QGridLayout *gridLayout_7;
    text_style_editor_widget *elementTextStylesEditor;
    QWidget *inputTextStyles;
    QGridLayout *gridLayout_9;
    text_style_editor_widget *inputTextStylesEditor;
    QWidget *ListStyles;
    QGridLayout *gridLayout_8;
    List_style_widget *ListStylesEditor;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_save_as;
    QPushButton *btn_apply;
    QPushButton *btn_Delete;
    QSpacerItem *horizontalSpacer;
    QComboBox *Styles;

    void setupUi(QWidget *StyleWidget)
    {
        if (StyleWidget->objectName().isEmpty())
            StyleWidget->setObjectName(QString::fromUtf8("StyleWidget"));
        StyleWidget->resize(453, 474);
        gridLayout_3 = new QGridLayout(StyleWidget);
        gridLayout_3->setSpacing(3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(3, 3, 3, 3);
        scrollArea = new QScrollArea(StyleWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 445, 438));
        gridLayout_4 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        styleEditor = new QToolBox(scrollAreaWidgetContents);
        styleEditor->setObjectName(QString::fromUtf8("styleEditor"));
        styleEditor->setStyleSheet(QString::fromUtf8("QToolBox::tab {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"    border-radius: 5px;\n"
"    color: black;\n"
"}\n"
"QToolBox::tab:selected { /* italicize selected tabs */\n"
"    font:bold;\n"
"    color: black;\n"
"}"));
        WindowStyle = new QWidget();
        WindowStyle->setObjectName(QString::fromUtf8("WindowStyle"));
        WindowStyle->setGeometry(QRect(0, 0, 427, 231));
        gridLayout = new QGridLayout(WindowStyle);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        windowStyleEditor = new window_subwindow_widget(WindowStyle);
        windowStyleEditor->setObjectName(QString::fromUtf8("windowStyleEditor"));

        gridLayout->addWidget(windowStyleEditor, 0, 0, 1, 1);

        styleEditor->addItem(WindowStyle, QString::fromUtf8("Window"));
        subwindowStyle = new QWidget();
        subwindowStyle->setObjectName(QString::fromUtf8("subwindowStyle"));
        subwindowStyle->setGeometry(QRect(0, 0, 427, 231));
        gridLayout_2 = new QGridLayout(subwindowStyle);
        gridLayout_2->setSpacing(3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(3, 3, 3, 3);
        subwindowStyleEditor = new window_subwindow_widget(subwindowStyle);
        subwindowStyleEditor->setObjectName(QString::fromUtf8("subwindowStyleEditor"));

        gridLayout_2->addWidget(subwindowStyleEditor, 0, 0, 1, 1);

        styleEditor->addItem(subwindowStyle, QString::fromUtf8("SubWindow"));
        ButtonsStyle = new QWidget();
        ButtonsStyle->setObjectName(QString::fromUtf8("ButtonsStyle"));
        ButtonsStyle->setGeometry(QRect(0, 0, 427, 231));
        gridLayout_5 = new QGridLayout(ButtonsStyle);
        gridLayout_5->setSpacing(3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(3, 3, 3, 3);
        buttonStyleEditor = new button_input_widget(ButtonsStyle);
        buttonStyleEditor->setObjectName(QString::fromUtf8("buttonStyleEditor"));

        gridLayout_5->addWidget(buttonStyleEditor, 0, 0, 1, 1);

        styleEditor->addItem(ButtonsStyle, QString::fromUtf8("Buttons"));
        inputStyles = new QWidget();
        inputStyles->setObjectName(QString::fromUtf8("inputStyles"));
        inputStyles->setGeometry(QRect(0, 0, 427, 231));
        gridLayout_6 = new QGridLayout(inputStyles);
        gridLayout_6->setSpacing(3);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(3, 3, 3, 3);
        inputStyleEditor = new button_input_widget(inputStyles);
        inputStyleEditor->setObjectName(QString::fromUtf8("inputStyleEditor"));

        gridLayout_6->addWidget(inputStyleEditor, 0, 0, 1, 1);

        styleEditor->addItem(inputStyles, QString::fromUtf8("Inputs"));
        elementTextStyles = new QWidget();
        elementTextStyles->setObjectName(QString::fromUtf8("elementTextStyles"));
        elementTextStyles->setGeometry(QRect(0, 0, 427, 231));
        gridLayout_7 = new QGridLayout(elementTextStyles);
        gridLayout_7->setSpacing(3);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(3, 3, 3, 3);
        elementTextStylesEditor = new text_style_editor_widget(elementTextStyles);
        elementTextStylesEditor->setObjectName(QString::fromUtf8("elementTextStylesEditor"));

        gridLayout_7->addWidget(elementTextStylesEditor, 0, 0, 1, 1);

        styleEditor->addItem(elementTextStyles, QString::fromUtf8("Elements Text"));
        inputTextStyles = new QWidget();
        inputTextStyles->setObjectName(QString::fromUtf8("inputTextStyles"));
        gridLayout_9 = new QGridLayout(inputTextStyles);
        gridLayout_9->setSpacing(3);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(3, 3, 3, 3);
        inputTextStylesEditor = new text_style_editor_widget(inputTextStyles);
        inputTextStylesEditor->setObjectName(QString::fromUtf8("inputTextStylesEditor"));

        gridLayout_9->addWidget(inputTextStylesEditor, 0, 0, 1, 1);

        styleEditor->addItem(inputTextStyles, QString::fromUtf8("Inputs Text"));
        ListStyles = new QWidget();
        ListStyles->setObjectName(QString::fromUtf8("ListStyles"));
        ListStyles->setGeometry(QRect(0, 0, 427, 231));
        gridLayout_8 = new QGridLayout(ListStyles);
        gridLayout_8->setSpacing(3);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(3, 3, 3, 3);
        ListStylesEditor = new List_style_widget(ListStyles);
        ListStylesEditor->setObjectName(QString::fromUtf8("ListStylesEditor"));

        gridLayout_8->addWidget(ListStylesEditor, 0, 0, 1, 1);

        styleEditor->addItem(ListStyles, QString::fromUtf8("Misc."));

        gridLayout_4->addWidget(styleEditor, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(scrollArea, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btn_save_as = new QPushButton(StyleWidget);
        btn_save_as->setObjectName(QString::fromUtf8("btn_save_as"));

        horizontalLayout->addWidget(btn_save_as);

        btn_apply = new QPushButton(StyleWidget);
        btn_apply->setObjectName(QString::fromUtf8("btn_apply"));

        horizontalLayout->addWidget(btn_apply);

        btn_Delete = new QPushButton(StyleWidget);
        btn_Delete->setObjectName(QString::fromUtf8("btn_Delete"));

        horizontalLayout->addWidget(btn_Delete);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Styles = new QComboBox(StyleWidget);
        Styles->setObjectName(QString::fromUtf8("Styles"));
        Styles->setMinimumSize(QSize(120, 0));

        horizontalLayout->addWidget(Styles);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 1);


        retranslateUi(StyleWidget);

        styleEditor->setCurrentIndex(5);
        styleEditor->layout()->setSpacing(6);


        QMetaObject::connectSlotsByName(StyleWidget);
    } // setupUi

    void retranslateUi(QWidget *StyleWidget)
    {
        StyleWidget->setWindowTitle(QApplication::translate("StyleWidget", "Form", nullptr));
        styleEditor->setItemText(styleEditor->indexOf(WindowStyle), QApplication::translate("StyleWidget", "Window", nullptr));
        styleEditor->setItemText(styleEditor->indexOf(subwindowStyle), QApplication::translate("StyleWidget", "SubWindow", nullptr));
        styleEditor->setItemText(styleEditor->indexOf(ButtonsStyle), QApplication::translate("StyleWidget", "Buttons", nullptr));
        styleEditor->setItemText(styleEditor->indexOf(inputStyles), QApplication::translate("StyleWidget", "Inputs", nullptr));
        styleEditor->setItemText(styleEditor->indexOf(elementTextStyles), QApplication::translate("StyleWidget", "Elements Text", nullptr));
        styleEditor->setItemText(styleEditor->indexOf(inputTextStyles), QApplication::translate("StyleWidget", "Inputs Text", nullptr));
        styleEditor->setItemText(styleEditor->indexOf(ListStyles), QApplication::translate("StyleWidget", "Misc.", nullptr));
        btn_save_as->setText(QApplication::translate("StyleWidget", "Save as", nullptr));
        btn_apply->setText(QApplication::translate("StyleWidget", "apply", nullptr));
        btn_Delete->setText(QApplication::translate("StyleWidget", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StyleWidget: public Ui_StyleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STYLEWIDGET_H
