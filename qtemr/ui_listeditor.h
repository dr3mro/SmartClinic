/********************************************************************************
** Form generated from reading UI file 'listeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTEDITOR_H
#define UI_LISTEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include "genericlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_listEditor
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QToolButton *closeButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    genericLineEdit *lineEdit;
    QToolButton *buttonDelete;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboList;
    QToolButton *buttonAdd;

    void setupUi(QDialog *listEditor)
    {
        if (listEditor->objectName().isEmpty())
            listEditor->setObjectName(QString::fromUtf8("listEditor"));
        listEditor->resize(388, 457);
        verticalLayout = new QVBoxLayout(listEditor);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(listEditor);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        closeButton = new QToolButton(listEditor);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout_4->addWidget(closeButton);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(listEditor);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lineEdit = new genericLineEdit(listEditor);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setClearButtonEnabled(true);

        horizontalLayout_3->addWidget(lineEdit);

        buttonDelete = new QToolButton(listEditor);
        buttonDelete->setObjectName(QString::fromUtf8("buttonDelete"));
        buttonDelete->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Graphics/minus"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDelete->setIcon(icon);

        horizontalLayout_3->addWidget(buttonDelete);


        verticalLayout->addLayout(horizontalLayout_3);

        tableView = new QTableView(listEditor);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setFocusPolicy(Qt::StrongFocus);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);
        tableView->horizontalHeader()->setVisible(false);
        tableView->horizontalHeader()->setHighlightSections(false);
        tableView->verticalHeader()->setVisible(false);
        tableView->verticalHeader()->setMinimumSectionSize(20);
        tableView->verticalHeader()->setDefaultSectionSize(20);
        tableView->verticalHeader()->setHighlightSections(false);

        verticalLayout->addWidget(tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(listEditor);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label);

        comboList = new QComboBox(listEditor);
        comboList->setObjectName(QString::fromUtf8("comboList"));

        horizontalLayout_2->addWidget(comboList);

        buttonAdd = new QToolButton(listEditor);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Graphics/arrow_bottom"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAdd->setIcon(icon1);

        horizontalLayout_2->addWidget(buttonAdd);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(listEditor);

        QMetaObject::connectSlotsByName(listEditor);
    } // setupUi

    void retranslateUi(QDialog *listEditor)
    {
        listEditor->setWindowTitle(QApplication::translate("listEditor", "List Editor", nullptr));
#ifndef QT_NO_TOOLTIP
        label_4->setToolTip(QApplication::translate("listEditor", "<html><head/><body><p align=\"justify\">This Feature enables you to modify the autocomplete feature of Smart Clinic so you can add and remove words from their respective lists</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("listEditor", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Typing Bird </span></p></body></html>", nullptr));
        closeButton->setText(QString());
        label_2->setText(QApplication::translate("listEditor", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Add:</span></p></body></html>", nullptr));
#ifndef QT_NO_TOOLTIP
        buttonDelete->setToolTip(QApplication::translate("listEditor", "<html><head/><body><p>remove current selection</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonDelete->setText(QApplication::translate("listEditor", "...", nullptr));
        label->setText(QApplication::translate("listEditor", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Lists:</span></p></body></html>", nullptr));
#ifndef QT_NO_TOOLTIP
        buttonAdd->setToolTip(QApplication::translate("listEditor", "<html><head/><body><p>Load items from Text File</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        buttonAdd->setText(QApplication::translate("listEditor", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class listEditor: public Ui_listEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTEDITOR_H
