/********************************************************************************
** Form generated from reading UI file 'expecteddeliveries.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPECTEDDELIVERIES_H
#define UI_EXPECTEDDELIVERIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExpectedDeliveries
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *Month;
    QComboBox *Year;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView;

    void setupUi(QWidget *ExpectedDeliveries)
    {
        if (ExpectedDeliveries->objectName().isEmpty())
            ExpectedDeliveries->setObjectName(QString::fromUtf8("ExpectedDeliveries"));
        ExpectedDeliveries->resize(514, 421);
        gridLayout = new QGridLayout(ExpectedDeliveries);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Month = new QComboBox(ExpectedDeliveries);
        Month->setObjectName(QString::fromUtf8("Month"));

        horizontalLayout->addWidget(Month);

        Year = new QComboBox(ExpectedDeliveries);
        Year->setObjectName(QString::fromUtf8("Year"));

        horizontalLayout->addWidget(Year);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        tableView = new QTableView(ExpectedDeliveries);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setMinimumSectionSize(20);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setMinimumSectionSize(20);
        tableView->verticalHeader()->setDefaultSectionSize(20);
        tableView->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(tableView, 1, 0, 1, 1);


        retranslateUi(ExpectedDeliveries);

        QMetaObject::connectSlotsByName(ExpectedDeliveries);
    } // setupUi

    void retranslateUi(QWidget *ExpectedDeliveries)
    {
        ExpectedDeliveries->setWindowTitle(QApplication::translate("ExpectedDeliveries", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExpectedDeliveries: public Ui_ExpectedDeliveries {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPECTEDDELIVERIES_H
