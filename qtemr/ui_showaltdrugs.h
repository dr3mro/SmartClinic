/********************************************************************************
** Form generated from reading UI file 'showaltdrugs.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWALTDRUGS_H
#define UI_SHOWALTDRUGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_showAltDrugs
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QTableView *tableView;
    QLineEdit *lineEdit;
    QLabel *filters;

    void setupUi(QWidget *showAltDrugs)
    {
        if (showAltDrugs->objectName().isEmpty())
            showAltDrugs->setObjectName(QString::fromUtf8("showAltDrugs"));
        showAltDrugs->setWindowModality(Qt::ApplicationModal);
        showAltDrugs->resize(533, 304);
        gridLayout = new QGridLayout(showAltDrugs);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(showAltDrugs);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        tableView = new QTableView(showAltDrugs);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);
        tableView->horizontalHeader()->setMinimumSectionSize(250);
        tableView->verticalHeader()->setCascadingSectionResizes(true);
        tableView->verticalHeader()->setMinimumSectionSize(20);
        tableView->verticalHeader()->setDefaultSectionSize(20);

        gridLayout->addWidget(tableView, 1, 0, 1, 3);

        lineEdit = new QLineEdit(showAltDrugs);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setClearButtonEnabled(true);

        gridLayout->addWidget(lineEdit, 2, 1, 1, 2);

        filters = new QLabel(showAltDrugs);
        filters->setObjectName(QString::fromUtf8("filters"));
        filters->setWordWrap(true);

        gridLayout->addWidget(filters, 0, 0, 1, 3);


        retranslateUi(showAltDrugs);

        QMetaObject::connectSlotsByName(showAltDrugs);
    } // setupUi

    void retranslateUi(QWidget *showAltDrugs)
    {
        showAltDrugs->setWindowTitle(QApplication::translate("showAltDrugs", "Drug Finder", nullptr));
        label->setText(QApplication::translate("showAltDrugs", "Filters:", nullptr));
        lineEdit->setPlaceholderText(QApplication::translate("showAltDrugs", "Search here ...", nullptr));
        filters->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class showAltDrugs: public Ui_showAltDrugs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWALTDRUGS_H
