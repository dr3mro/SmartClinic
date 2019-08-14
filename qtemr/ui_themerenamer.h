/********************************************************************************
** Form generated from reading UI file 'themerenamer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THEMERENAMER_H
#define UI_THEMERENAMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ThemeRenamer
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *btn_Ok;
    QPushButton *btn_Cancel;
    QLineEdit *inputThemeName;

    void setupUi(QDialog *ThemeRenamer)
    {
        if (ThemeRenamer->objectName().isEmpty())
            ThemeRenamer->setObjectName(QString::fromUtf8("ThemeRenamer"));
        ThemeRenamer->resize(222, 86);
        ThemeRenamer->setModal(true);
        gridLayout = new QGridLayout(ThemeRenamer);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(ThemeRenamer);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        btn_Ok = new QPushButton(ThemeRenamer);
        btn_Ok->setObjectName(QString::fromUtf8("btn_Ok"));
        btn_Ok->setEnabled(false);

        gridLayout->addWidget(btn_Ok, 2, 0, 1, 1);

        btn_Cancel = new QPushButton(ThemeRenamer);
        btn_Cancel->setObjectName(QString::fromUtf8("btn_Cancel"));

        gridLayout->addWidget(btn_Cancel, 2, 1, 1, 1);

        inputThemeName = new QLineEdit(ThemeRenamer);
        inputThemeName->setObjectName(QString::fromUtf8("inputThemeName"));

        gridLayout->addWidget(inputThemeName, 1, 0, 1, 2);


        retranslateUi(ThemeRenamer);

        QMetaObject::connectSlotsByName(ThemeRenamer);
    } // setupUi

    void retranslateUi(QDialog *ThemeRenamer)
    {
        ThemeRenamer->setWindowTitle(QApplication::translate("ThemeRenamer", "New Theme", nullptr));
        label->setText(QApplication::translate("ThemeRenamer", "Type Theme name here.", nullptr));
        btn_Ok->setText(QApplication::translate("ThemeRenamer", "Ok", nullptr));
        btn_Cancel->setText(QApplication::translate("ThemeRenamer", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThemeRenamer: public Ui_ThemeRenamer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THEMERENAMER_H
