/********************************************************************************
** Form generated from reading UI file 'colorpicker.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORPICKER_H
#define UI_COLORPICKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "mcolorpicker.h"

QT_BEGIN_NAMESPACE

class Ui_colorPicker
{
public:
    QGridLayout *gridLayout;
    mColorPicker *black;
    mColorPicker *red;
    mColorPicker *darkRed;
    mColorPicker *green;
    mColorPicker *darkGreen;
    mColorPicker *blue;
    mColorPicker *darkBlue;
    mColorPicker *cyan;
    mColorPicker *darkCyan;
    mColorPicker *magenta;
    mColorPicker *darkMagenta;
    mColorPicker *yellow;
    mColorPicker *darkYellow;
    mColorPicker *grey;
    mColorPicker *lightGrey;
    mColorPicker *white;

    void setupUi(QWidget *colorPicker)
    {
        if (colorPicker->objectName().isEmpty())
            colorPicker->setObjectName(QString::fromUtf8("colorPicker"));
        colorPicker->resize(112, 88);
        gridLayout = new QGridLayout(colorPicker);
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        black = new mColorPicker(colorPicker);
        black->setObjectName(QString::fromUtf8("black"));
        black->setAutoRaise(true);

        gridLayout->addWidget(black, 0, 1, 1, 1);

        red = new mColorPicker(colorPicker);
        red->setObjectName(QString::fromUtf8("red"));
        red->setAutoRaise(true);

        gridLayout->addWidget(red, 0, 2, 1, 1);

        darkRed = new mColorPicker(colorPicker);
        darkRed->setObjectName(QString::fromUtf8("darkRed"));
        darkRed->setAutoRaise(true);

        gridLayout->addWidget(darkRed, 0, 3, 1, 1);

        green = new mColorPicker(colorPicker);
        green->setObjectName(QString::fromUtf8("green"));
        green->setAutoRaise(true);

        gridLayout->addWidget(green, 1, 0, 1, 1);

        darkGreen = new mColorPicker(colorPicker);
        darkGreen->setObjectName(QString::fromUtf8("darkGreen"));
        darkGreen->setAutoRaise(true);

        gridLayout->addWidget(darkGreen, 1, 1, 1, 1);

        blue = new mColorPicker(colorPicker);
        blue->setObjectName(QString::fromUtf8("blue"));
        blue->setAutoRaise(true);

        gridLayout->addWidget(blue, 1, 2, 1, 1);

        darkBlue = new mColorPicker(colorPicker);
        darkBlue->setObjectName(QString::fromUtf8("darkBlue"));
        darkBlue->setAutoRaise(true);

        gridLayout->addWidget(darkBlue, 1, 3, 1, 1);

        cyan = new mColorPicker(colorPicker);
        cyan->setObjectName(QString::fromUtf8("cyan"));
        cyan->setAutoRaise(true);

        gridLayout->addWidget(cyan, 2, 0, 1, 1);

        darkCyan = new mColorPicker(colorPicker);
        darkCyan->setObjectName(QString::fromUtf8("darkCyan"));
        darkCyan->setAutoRaise(true);

        gridLayout->addWidget(darkCyan, 2, 1, 1, 1);

        magenta = new mColorPicker(colorPicker);
        magenta->setObjectName(QString::fromUtf8("magenta"));
        magenta->setAutoRaise(true);

        gridLayout->addWidget(magenta, 2, 2, 1, 1);

        darkMagenta = new mColorPicker(colorPicker);
        darkMagenta->setObjectName(QString::fromUtf8("darkMagenta"));
        darkMagenta->setAutoRaise(true);

        gridLayout->addWidget(darkMagenta, 2, 3, 1, 1);

        yellow = new mColorPicker(colorPicker);
        yellow->setObjectName(QString::fromUtf8("yellow"));
        yellow->setAutoRaise(true);

        gridLayout->addWidget(yellow, 3, 0, 1, 1);

        darkYellow = new mColorPicker(colorPicker);
        darkYellow->setObjectName(QString::fromUtf8("darkYellow"));
        darkYellow->setStyleSheet(QString::fromUtf8(""));
        darkYellow->setAutoRaise(true);

        gridLayout->addWidget(darkYellow, 3, 1, 1, 1);

        grey = new mColorPicker(colorPicker);
        grey->setObjectName(QString::fromUtf8("grey"));
        grey->setAutoRaise(true);

        gridLayout->addWidget(grey, 3, 2, 1, 1);

        lightGrey = new mColorPicker(colorPicker);
        lightGrey->setObjectName(QString::fromUtf8("lightGrey"));
        lightGrey->setAutoRaise(true);

        gridLayout->addWidget(lightGrey, 3, 3, 1, 1);

        white = new mColorPicker(colorPicker);
        white->setObjectName(QString::fromUtf8("white"));
        white->setAutoRaise(true);

        gridLayout->addWidget(white, 0, 0, 1, 1);


        retranslateUi(colorPicker);

        QMetaObject::connectSlotsByName(colorPicker);
    } // setupUi

    void retranslateUi(QWidget *colorPicker)
    {
        colorPicker->setWindowTitle(QApplication::translate("colorPicker", "Form", nullptr));
        black->setText(QApplication::translate("colorPicker", "...", nullptr));
        red->setText(QApplication::translate("colorPicker", "...", nullptr));
        darkRed->setText(QApplication::translate("colorPicker", "...", nullptr));
        green->setText(QApplication::translate("colorPicker", "...", nullptr));
        darkGreen->setText(QApplication::translate("colorPicker", "...", nullptr));
        blue->setText(QApplication::translate("colorPicker", "...", nullptr));
        darkBlue->setText(QApplication::translate("colorPicker", "...", nullptr));
        cyan->setText(QApplication::translate("colorPicker", "...", nullptr));
        darkCyan->setText(QApplication::translate("colorPicker", "...", nullptr));
        magenta->setText(QApplication::translate("colorPicker", "...", nullptr));
        darkMagenta->setText(QApplication::translate("colorPicker", "...", nullptr));
        yellow->setText(QApplication::translate("colorPicker", "...", nullptr));
        darkYellow->setText(QApplication::translate("colorPicker", "...", nullptr));
        grey->setText(QApplication::translate("colorPicker", "...", nullptr));
        lightGrey->setText(QApplication::translate("colorPicker", "...", nullptr));
        white->setText(QApplication::translate("colorPicker", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class colorPicker: public Ui_colorPicker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORPICKER_H
