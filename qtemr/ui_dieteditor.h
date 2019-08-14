/********************************************************************************
** Form generated from reading UI file 'dieteditor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIETEDITOR_H
#define UI_DIETEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "textedit.h"

QT_BEGIN_NAMESPACE

class Ui_DietEditor
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QToolButton *closeButton;
    QTableView *dietList;
    QLineEdit *lineEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QToolButton *buttonAdd;
    QToolButton *buttonDelete;
    QToolButton *buttonEdit;
    QToolButton *ButtonSave;
    TextEdit *dietEdit;

    void setupUi(QDialog *DietEditor)
    {
        if (DietEditor->objectName().isEmpty())
            DietEditor->setObjectName(QString::fromUtf8("DietEditor"));
        DietEditor->resize(638, 427);
        gridLayout = new QGridLayout(DietEditor);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(DietEditor);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(478, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        closeButton = new QToolButton(DietEditor);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout_2->addWidget(closeButton);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 2);

        dietList = new QTableView(DietEditor);
        dietList->setObjectName(QString::fromUtf8("dietList"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dietList->sizePolicy().hasHeightForWidth());
        dietList->setSizePolicy(sizePolicy);
        dietList->setMinimumSize(QSize(140, 0));
        dietList->setMaximumSize(QSize(140, 16777215));
        dietList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        dietList->setAlternatingRowColors(false);
        dietList->setWordWrap(false);
        dietList->setCornerButtonEnabled(false);
        dietList->horizontalHeader()->setVisible(false);
        dietList->horizontalHeader()->setHighlightSections(false);
        dietList->verticalHeader()->setVisible(false);
        dietList->verticalHeader()->setMinimumSectionSize(21);
        dietList->verticalHeader()->setDefaultSectionSize(21);
        dietList->verticalHeader()->setHighlightSections(false);

        gridLayout->addWidget(dietList, 1, 0, 1, 1);

        lineEdit = new QLineEdit(DietEditor);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMaximumSize(QSize(140, 16777215));

        gridLayout->addWidget(lineEdit, 2, 0, 1, 1);

        widget = new QWidget(DietEditor);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        buttonAdd = new QToolButton(widget);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Graphics/add"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAdd->setIcon(icon);

        horizontalLayout->addWidget(buttonAdd);

        buttonDelete = new QToolButton(widget);
        buttonDelete->setObjectName(QString::fromUtf8("buttonDelete"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Graphics/minus"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDelete->setIcon(icon1);

        horizontalLayout->addWidget(buttonDelete);

        buttonEdit = new QToolButton(widget);
        buttonEdit->setObjectName(QString::fromUtf8("buttonEdit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Graphics/pencil"), QSize(), QIcon::Normal, QIcon::Off);
        buttonEdit->setIcon(icon2);
        buttonEdit->setCheckable(true);

        horizontalLayout->addWidget(buttonEdit);

        ButtonSave = new QToolButton(widget);
        ButtonSave->setObjectName(QString::fromUtf8("ButtonSave"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Graphics/ok"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonSave->setIcon(icon3);

        horizontalLayout->addWidget(ButtonSave);


        gridLayout->addWidget(widget, 3, 0, 1, 1);

        dietEdit = new TextEdit(DietEditor);
        dietEdit->setObjectName(QString::fromUtf8("dietEdit"));

        gridLayout->addWidget(dietEdit, 1, 1, 3, 1);


        retranslateUi(DietEditor);

        QMetaObject::connectSlotsByName(DietEditor);
    } // setupUi

    void retranslateUi(QDialog *DietEditor)
    {
        DietEditor->setWindowTitle(QApplication::translate("DietEditor", "Dialog", nullptr));
        label_2->setText(QApplication::translate("DietEditor", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Diet Editor</span></p></body></html>", nullptr));
        closeButton->setText(QString());
        buttonAdd->setText(QApplication::translate("DietEditor", "...", nullptr));
        buttonDelete->setText(QApplication::translate("DietEditor", "...", nullptr));
        buttonEdit->setText(QApplication::translate("DietEditor", "...", nullptr));
        ButtonSave->setText(QApplication::translate("DietEditor", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DietEditor: public Ui_DietEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIETEDITOR_H
