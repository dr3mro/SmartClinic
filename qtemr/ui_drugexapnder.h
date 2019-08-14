/********************************************************************************
** Form generated from reading UI file 'drugexapnder.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRUGEXAPNDER_H
#define UI_DRUGEXAPNDER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include "genericlineedit.h"
#include "textedit.h"

QT_BEGIN_NAMESPACE

class Ui_drugExapnder
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *saveButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QToolButton *closeButton;
    QHBoxLayout *horizontalLayout_2;
    genericLineEdit *shortcut;
    QToolButton *buttonDel;
    QToolButton *buttonAdd;
    QHBoxLayout *horizontalLayout_4;
    QTableView *tableView;
    TextEdit *expandText;

    void setupUi(QDialog *drugExapnder)
    {
        if (drugExapnder->objectName().isEmpty())
            drugExapnder->setObjectName(QString::fromUtf8("drugExapnder"));
        drugExapnder->resize(646, 451);
        gridLayout = new QGridLayout(drugExapnder);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        saveButton = new QPushButton(drugExapnder);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(saveButton->sizePolicy().hasHeightForWidth());
        saveButton->setSizePolicy(sizePolicy);
        saveButton->setAutoDefault(false);

        horizontalLayout_3->addWidget(saveButton);


        gridLayout->addLayout(horizontalLayout_3, 6, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 0, -1, -1);
        label_4 = new QLabel(drugExapnder);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(220, 16777215));

        horizontalLayout_5->addWidget(label_4);

        label_3 = new QLabel(drugExapnder);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);


        gridLayout->addLayout(horizontalLayout_5, 4, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(drugExapnder);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(318, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        closeButton = new QToolButton(drugExapnder);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout->addWidget(closeButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        shortcut = new genericLineEdit(drugExapnder);
        shortcut->setObjectName(QString::fromUtf8("shortcut"));
        shortcut->setClearButtonEnabled(true);

        horizontalLayout_2->addWidget(shortcut);

        buttonDel = new QToolButton(drugExapnder);
        buttonDel->setObjectName(QString::fromUtf8("buttonDel"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Graphics/minus"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDel->setIcon(icon);

        horizontalLayout_2->addWidget(buttonDel);

        buttonAdd = new QToolButton(drugExapnder);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Graphics/add"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAdd->setIcon(icon1);

        horizontalLayout_2->addWidget(buttonAdd);


        gridLayout->addLayout(horizontalLayout_2, 6, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        tableView = new QTableView(drugExapnder);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy1);
        tableView->setMaximumSize(QSize(220, 16777215));
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSortingEnabled(false);
        tableView->setWordWrap(false);
        tableView->setCornerButtonEnabled(false);
        tableView->horizontalHeader()->setVisible(false);
        tableView->horizontalHeader()->setHighlightSections(false);
        tableView->verticalHeader()->setVisible(false);
        tableView->verticalHeader()->setMinimumSectionSize(20);
        tableView->verticalHeader()->setDefaultSectionSize(20);
        tableView->verticalHeader()->setHighlightSections(false);

        horizontalLayout_4->addWidget(tableView);

        expandText = new TextEdit(drugExapnder);
        expandText->setObjectName(QString::fromUtf8("expandText"));
        expandText->setEnabled(false);

        horizontalLayout_4->addWidget(expandText);


        gridLayout->addLayout(horizontalLayout_4, 5, 0, 1, 2);


        retranslateUi(drugExapnder);

        QMetaObject::connectSlotsByName(drugExapnder);
    } // setupUi

    void retranslateUi(QDialog *drugExapnder)
    {
        drugExapnder->setWindowTitle(QApplication::translate("drugExapnder", "Dialog", nullptr));
        saveButton->setText(QApplication::translate("drugExapnder", "Save", nullptr));
        label_4->setText(QApplication::translate("drugExapnder", "<html><head/><body><p><span style=\" font-weight:600;\">ShortCut:</span></p></body></html>", nullptr));
        label_3->setText(QApplication::translate("drugExapnder", "<html><head/><body><p><span style=\" font-weight:600;\">Expands to:</span></p></body></html>", nullptr));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("drugExapnder", "<html><head/><body><p>Here you can add a shortcut when you type in drugs box it will be expanded when ever you print the prescription, note that<br/>1. Duplicates are not allowed.<br/>2. You can't use Names that already on drugindex as Shortcut.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("drugExapnder", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Drugs Expander</span></p></body></html>", nullptr));
        closeButton->setText(QString());
        buttonDel->setText(QApplication::translate("drugExapnder", "...", nullptr));
        buttonAdd->setText(QApplication::translate("drugExapnder", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class drugExapnder: public Ui_drugExapnder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRUGEXAPNDER_H
