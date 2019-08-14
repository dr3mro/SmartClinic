/********************************************************************************
** Form generated from reading UI file 'richtexteditor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RICHTEXTEDITOR_H
#define UI_RICHTEXTEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "colorbutton.h"

QT_BEGIN_NAMESPACE

class Ui_richTextEditor
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter_3;
    QToolButton *alignLeft;
    QToolButton *alignCenter;
    QToolButton *alignRight;
    QSplitter *splitter_4;
    colorButton *textColor;
    colorButton *backgroundColor;
    QSplitter *splitter_5;
    QToolButton *undo;
    QToolButton *redo;
    QSplitter *splitter_6;
    QToolButton *clearFormat;
    QToolButton *clear;
    QToolButton *SelectAll;
    QSplitter *splitter_2;
    QToolButton *cut;
    QToolButton *copy;
    QToolButton *paste;
    QToolButton *toUpper;
    QSplitter *splitter;
    QToolButton *bold;
    QToolButton *italic;
    QToolButton *underline;
    QToolButton *strike;
    QToolButton *highlight;
    QComboBox *point;
    QFontComboBox *fontComboBox;
    QToolButton *serachOnline;

    void setupUi(QWidget *richTextEditor)
    {
        if (richTextEditor->objectName().isEmpty())
            richTextEditor->setObjectName(QString::fromUtf8("richTextEditor"));
        richTextEditor->resize(296, 94);
        richTextEditor->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(richTextEditor);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter_3 = new QSplitter(richTextEditor);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter_3->sizePolicy().hasHeightForWidth());
        splitter_3->setSizePolicy(sizePolicy);
        splitter_3->setOrientation(Qt::Horizontal);
        splitter_3->setOpaqueResize(false);
        splitter_3->setChildrenCollapsible(false);
        alignLeft = new QToolButton(splitter_3);
        alignLeft->setObjectName(QString::fromUtf8("alignLeft"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Graphics/alignLeft"), QSize(), QIcon::Normal, QIcon::Off);
        alignLeft->setIcon(icon);
        alignLeft->setCheckable(false);
        alignLeft->setAutoRaise(true);
        splitter_3->addWidget(alignLeft);
        alignCenter = new QToolButton(splitter_3);
        alignCenter->setObjectName(QString::fromUtf8("alignCenter"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Graphics/alignCenter"), QSize(), QIcon::Normal, QIcon::Off);
        alignCenter->setIcon(icon1);
        alignCenter->setCheckable(false);
        alignCenter->setAutoRaise(true);
        splitter_3->addWidget(alignCenter);
        alignRight = new QToolButton(splitter_3);
        alignRight->setObjectName(QString::fromUtf8("alignRight"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Graphics/alignRight"), QSize(), QIcon::Normal, QIcon::Off);
        alignRight->setIcon(icon2);
        alignRight->setCheckable(false);
        alignRight->setAutoRaise(true);
        splitter_3->addWidget(alignRight);

        gridLayout->addWidget(splitter_3, 2, 2, 1, 1);

        splitter_4 = new QSplitter(richTextEditor);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        sizePolicy.setHeightForWidth(splitter_4->sizePolicy().hasHeightForWidth());
        splitter_4->setSizePolicy(sizePolicy);
        splitter_4->setOrientation(Qt::Horizontal);
        splitter_4->setOpaqueResize(false);
        splitter_4->setChildrenCollapsible(false);
        textColor = new colorButton(splitter_4);
        textColor->setObjectName(QString::fromUtf8("textColor"));
        textColor->setStyleSheet(QString::fromUtf8(""));
        textColor->setAutoRaise(true);
        splitter_4->addWidget(textColor);
        backgroundColor = new colorButton(splitter_4);
        backgroundColor->setObjectName(QString::fromUtf8("backgroundColor"));
        backgroundColor->setStyleSheet(QString::fromUtf8(""));
        backgroundColor->setAutoRaise(true);
        splitter_4->addWidget(backgroundColor);

        gridLayout->addWidget(splitter_4, 2, 3, 1, 1);

        splitter_5 = new QSplitter(richTextEditor);
        splitter_5->setObjectName(QString::fromUtf8("splitter_5"));
        sizePolicy.setHeightForWidth(splitter_5->sizePolicy().hasHeightForWidth());
        splitter_5->setSizePolicy(sizePolicy);
        splitter_5->setOrientation(Qt::Horizontal);
        splitter_5->setOpaqueResize(false);
        splitter_5->setChildrenCollapsible(false);
        undo = new QToolButton(splitter_5);
        undo->setObjectName(QString::fromUtf8("undo"));
        undo->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Graphics/undo"), QSize(), QIcon::Normal, QIcon::Off);
        undo->setIcon(icon3);
        undo->setAutoRaise(true);
        splitter_5->addWidget(undo);
        redo = new QToolButton(splitter_5);
        redo->setObjectName(QString::fromUtf8("redo"));
        redo->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Graphics/redo"), QSize(), QIcon::Normal, QIcon::Off);
        redo->setIcon(icon4);
        redo->setAutoRaise(true);
        splitter_5->addWidget(redo);

        gridLayout->addWidget(splitter_5, 1, 3, 1, 1);

        splitter_6 = new QSplitter(richTextEditor);
        splitter_6->setObjectName(QString::fromUtf8("splitter_6"));
        sizePolicy.setHeightForWidth(splitter_6->sizePolicy().hasHeightForWidth());
        splitter_6->setSizePolicy(sizePolicy);
        splitter_6->setOrientation(Qt::Horizontal);
        splitter_6->setOpaqueResize(false);
        splitter_6->setChildrenCollapsible(false);
        clearFormat = new QToolButton(splitter_6);
        clearFormat->setObjectName(QString::fromUtf8("clearFormat"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Graphics/brush"), QSize(), QIcon::Normal, QIcon::Off);
        clearFormat->setIcon(icon5);
        clearFormat->setAutoRaise(true);
        splitter_6->addWidget(clearFormat);
        clear = new QToolButton(splitter_6);
        clear->setObjectName(QString::fromUtf8("clear"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Graphics/clear"), QSize(), QIcon::Normal, QIcon::Off);
        clear->setIcon(icon6);
        clear->setAutoRaise(true);
        splitter_6->addWidget(clear);
        SelectAll = new QToolButton(splitter_6);
        SelectAll->setObjectName(QString::fromUtf8("SelectAll"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Graphics/selectall"), QSize(), QIcon::Normal, QIcon::Off);
        SelectAll->setIcon(icon7);
        SelectAll->setAutoRaise(true);
        splitter_6->addWidget(SelectAll);

        gridLayout->addWidget(splitter_6, 1, 2, 1, 1);

        splitter_2 = new QSplitter(richTextEditor);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_2->setOpaqueResize(false);
        splitter_2->setChildrenCollapsible(false);
        cut = new QToolButton(splitter_2);
        cut->setObjectName(QString::fromUtf8("cut"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Graphics/cut"), QSize(), QIcon::Normal, QIcon::Off);
        cut->setIcon(icon8);
        cut->setAutoRaise(true);
        splitter_2->addWidget(cut);
        copy = new QToolButton(splitter_2);
        copy->setObjectName(QString::fromUtf8("copy"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Graphics/copy"), QSize(), QIcon::Normal, QIcon::Off);
        copy->setIcon(icon9);
        copy->setAutoRaise(true);
        splitter_2->addWidget(copy);
        paste = new QToolButton(splitter_2);
        paste->setObjectName(QString::fromUtf8("paste"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Graphics/paste"), QSize(), QIcon::Normal, QIcon::Off);
        paste->setIcon(icon10);
        paste->setAutoRaise(true);
        splitter_2->addWidget(paste);
        toUpper = new QToolButton(splitter_2);
        toUpper->setObjectName(QString::fromUtf8("toUpper"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Graphics/capsLock"), QSize(), QIcon::Normal, QIcon::Off);
        toUpper->setIcon(icon11);
        toUpper->setCheckable(true);
        toUpper->setAutoRaise(true);
        splitter_2->addWidget(toUpper);

        gridLayout->addWidget(splitter_2, 2, 0, 1, 1);

        splitter = new QSplitter(richTextEditor);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(false);
        splitter->setChildrenCollapsible(false);
        bold = new QToolButton(splitter);
        bold->setObjectName(QString::fromUtf8("bold"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Graphics/bold"), QSize(), QIcon::Normal, QIcon::Off);
        bold->setIcon(icon12);
        bold->setCheckable(true);
        bold->setAutoRaise(true);
        splitter->addWidget(bold);
        italic = new QToolButton(splitter);
        italic->setObjectName(QString::fromUtf8("italic"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Graphics/italic"), QSize(), QIcon::Normal, QIcon::Off);
        italic->setIcon(icon13);
        italic->setCheckable(true);
        italic->setAutoRaise(true);
        splitter->addWidget(italic);
        underline = new QToolButton(splitter);
        underline->setObjectName(QString::fromUtf8("underline"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Graphics/underline"), QSize(), QIcon::Normal, QIcon::Off);
        underline->setIcon(icon14);
        underline->setCheckable(true);
        underline->setAutoRaise(true);
        splitter->addWidget(underline);
        strike = new QToolButton(splitter);
        strike->setObjectName(QString::fromUtf8("strike"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Graphics/strike"), QSize(), QIcon::Normal, QIcon::Off);
        strike->setIcon(icon15);
        strike->setCheckable(true);
        strike->setAutoRaise(true);
        splitter->addWidget(strike);
        highlight = new QToolButton(splitter);
        highlight->setObjectName(QString::fromUtf8("highlight"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/Graphics/highlight"), QSize(), QIcon::Normal, QIcon::Off);
        highlight->setIcon(icon16);
        highlight->setCheckable(true);
        highlight->setAutoRaise(true);
        splitter->addWidget(highlight);

        gridLayout->addWidget(splitter, 1, 0, 1, 2);

        point = new QComboBox(richTextEditor);
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->addItem(QString());
        point->setObjectName(QString::fromUtf8("point"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(point->sizePolicy().hasHeightForWidth());
        point->setSizePolicy(sizePolicy1);
        point->setMaximumSize(QSize(50, 16777215));
        point->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(point, 0, 3, 1, 1);

        fontComboBox = new QFontComboBox(richTextEditor);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));
        sizePolicy1.setHeightForWidth(fontComboBox->sizePolicy().hasHeightForWidth());
        fontComboBox->setSizePolicy(sizePolicy1);
        fontComboBox->setMaximumSize(QSize(250, 16777215));
        fontComboBox->setStyleSheet(QString::fromUtf8(""));
        fontComboBox->setEditable(false);
        fontComboBox->setFrame(false);
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        font.setPointSize(10);
        fontComboBox->setCurrentFont(font);

        gridLayout->addWidget(fontComboBox, 0, 0, 1, 3);

        serachOnline = new QToolButton(richTextEditor);
        serachOnline->setObjectName(QString::fromUtf8("serachOnline"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/ionicons/earth"), QSize(), QIcon::Normal, QIcon::Off);
        serachOnline->setIcon(icon17);
        serachOnline->setAutoRaise(true);

        gridLayout->addWidget(serachOnline, 2, 1, 1, 1);


        retranslateUi(richTextEditor);

        QMetaObject::connectSlotsByName(richTextEditor);
    } // setupUi

    void retranslateUi(QWidget *richTextEditor)
    {
        richTextEditor->setWindowTitle(QApplication::translate("richTextEditor", "Form", nullptr));
#ifndef QT_NO_TOOLTIP
        alignLeft->setToolTip(QApplication::translate("richTextEditor", "Align Left", nullptr));
#endif // QT_NO_TOOLTIP
        alignLeft->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        alignCenter->setToolTip(QApplication::translate("richTextEditor", "Align Center", nullptr));
#endif // QT_NO_TOOLTIP
        alignCenter->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        alignRight->setToolTip(QApplication::translate("richTextEditor", "Align Right", nullptr));
#endif // QT_NO_TOOLTIP
        alignRight->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        textColor->setToolTip(QApplication::translate("richTextEditor", "Text Color", nullptr));
#endif // QT_NO_TOOLTIP
        textColor->setText(QString());
#ifndef QT_NO_TOOLTIP
        backgroundColor->setToolTip(QApplication::translate("richTextEditor", "Background Color", nullptr));
#endif // QT_NO_TOOLTIP
        backgroundColor->setText(QString());
#ifndef QT_NO_TOOLTIP
        undo->setToolTip(QApplication::translate("richTextEditor", "Undo", nullptr));
#endif // QT_NO_TOOLTIP
        undo->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        undo->setShortcut(QApplication::translate("richTextEditor", "Ctrl+Z", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        redo->setToolTip(QApplication::translate("richTextEditor", "Redo", nullptr));
#endif // QT_NO_TOOLTIP
        redo->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        redo->setShortcut(QApplication::translate("richTextEditor", "Ctrl+Y", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        clearFormat->setToolTip(QApplication::translate("richTextEditor", "<html><head/><body><p>Clear Formatting[ALT+R]</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        clearFormat->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        clearFormat->setShortcut(QApplication::translate("richTextEditor", "Alt+R", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        clear->setToolTip(QApplication::translate("richTextEditor", "Delete Selected Text", nullptr));
#endif // QT_NO_TOOLTIP
        clear->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        SelectAll->setToolTip(QApplication::translate("richTextEditor", "Select All", nullptr));
#endif // QT_NO_TOOLTIP
        SelectAll->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        SelectAll->setShortcut(QApplication::translate("richTextEditor", "Ctrl+A", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        cut->setToolTip(QApplication::translate("richTextEditor", "Cut [CTRL+X]", nullptr));
#endif // QT_NO_TOOLTIP
        cut->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        cut->setShortcut(QApplication::translate("richTextEditor", "Ctrl+X", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        copy->setToolTip(QApplication::translate("richTextEditor", "Copy [CTRL+C]", nullptr));
#endif // QT_NO_TOOLTIP
        copy->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        copy->setShortcut(QApplication::translate("richTextEditor", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        paste->setToolTip(QApplication::translate("richTextEditor", "Paste [CTRL+V]", nullptr));
#endif // QT_NO_TOOLTIP
        paste->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        paste->setShortcut(QApplication::translate("richTextEditor", "Ctrl+V", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        toUpper->setToolTip(QApplication::translate("richTextEditor", "<html><head/><body><p>Toggle selected text upper / lower case letters. [ALT+C]</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        toUpper->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        toUpper->setShortcut(QApplication::translate("richTextEditor", "Alt+C", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        bold->setToolTip(QApplication::translate("richTextEditor", "Bold [ALT+B]", nullptr));
#endif // QT_NO_TOOLTIP
        bold->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        bold->setShortcut(QApplication::translate("richTextEditor", "Alt+B", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        italic->setToolTip(QApplication::translate("richTextEditor", "Italic [ALT+I]", nullptr));
#endif // QT_NO_TOOLTIP
        italic->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        italic->setShortcut(QApplication::translate("richTextEditor", "Alt+I", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        underline->setToolTip(QApplication::translate("richTextEditor", "Underline [ALT+U]", nullptr));
#endif // QT_NO_TOOLTIP
        underline->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        underline->setShortcut(QApplication::translate("richTextEditor", "Alt+U", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        strike->setToolTip(QApplication::translate("richTextEditor", "Strike [ALT+S]", nullptr));
#endif // QT_NO_TOOLTIP
        strike->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        strike->setShortcut(QApplication::translate("richTextEditor", "Alt+S", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        highlight->setToolTip(QApplication::translate("richTextEditor", "Highlight [ALT+H]", nullptr));
#endif // QT_NO_TOOLTIP
        highlight->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        highlight->setShortcut(QApplication::translate("richTextEditor", "Alt+H", nullptr));
#endif // QT_NO_SHORTCUT
        point->setItemText(0, QApplication::translate("richTextEditor", "8", nullptr));
        point->setItemText(1, QApplication::translate("richTextEditor", "9", nullptr));
        point->setItemText(2, QApplication::translate("richTextEditor", "10", nullptr));
        point->setItemText(3, QApplication::translate("richTextEditor", "11", nullptr));
        point->setItemText(4, QApplication::translate("richTextEditor", "12", nullptr));
        point->setItemText(5, QApplication::translate("richTextEditor", "14", nullptr));
        point->setItemText(6, QApplication::translate("richTextEditor", "16", nullptr));
        point->setItemText(7, QApplication::translate("richTextEditor", "18", nullptr));
        point->setItemText(8, QApplication::translate("richTextEditor", "20", nullptr));
        point->setItemText(9, QApplication::translate("richTextEditor", "22", nullptr));
        point->setItemText(10, QApplication::translate("richTextEditor", "24", nullptr));
        point->setItemText(11, QApplication::translate("richTextEditor", "36", nullptr));

#ifndef QT_NO_TOOLTIP
        serachOnline->setToolTip(QApplication::translate("richTextEditor", "<html><head/><body><p>Search selected on scholar.Google.com [ALT+G]</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        serachOnline->setText(QApplication::translate("richTextEditor", "...", nullptr));
#ifndef QT_NO_SHORTCUT
        serachOnline->setShortcut(QApplication::translate("richTextEditor", "Alt+G", nullptr));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class richTextEditor: public Ui_richTextEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RICHTEXTEDITOR_H
