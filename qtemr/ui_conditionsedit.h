/********************************************************************************
** Form generated from reading UI file 'conditionsedit.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONDITIONSEDIT_H
#define UI_CONDITIONSEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_conditionsEdit
{
public:
    QGridLayout *gridLayout;
    QPushButton *buttonAdd;
    QTableView *tableView;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QWidget *conditionsEdit)
    {
        if (conditionsEdit->objectName().isEmpty())
            conditionsEdit->setObjectName(QString::fromUtf8("conditionsEdit"));
        conditionsEdit->resize(389, 538);
        gridLayout = new QGridLayout(conditionsEdit);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonAdd = new QPushButton(conditionsEdit);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));
        buttonAdd->setAutoDefault(true);

        gridLayout->addWidget(buttonAdd, 0, 2, 1, 1);

        tableView = new QTableView(conditionsEdit);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableView->setShowGrid(false);
        tableView->setGridStyle(Qt::NoPen);
        tableView->setCornerButtonEnabled(false);
        tableView->horizontalHeader()->setVisible(false);
        tableView->horizontalHeader()->setHighlightSections(false);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setMinimumSectionSize(20);
        tableView->verticalHeader()->setDefaultSectionSize(20);

        gridLayout->addWidget(tableView, 1, 0, 1, 3);

        lineEdit = new QLineEdit(conditionsEdit);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setClearButtonEnabled(true);

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label = new QLabel(conditionsEdit);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(conditionsEdit);

        buttonAdd->setDefault(true);


        QMetaObject::connectSlotsByName(conditionsEdit);
    } // setupUi

    void retranslateUi(QWidget *conditionsEdit)
    {
        conditionsEdit->setWindowTitle(QApplication::translate("conditionsEdit", "Conditions Editor", nullptr));
        buttonAdd->setText(QApplication::translate("conditionsEdit", "Add", nullptr));
        label->setText(QApplication::translate("conditionsEdit", "Add:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class conditionsEdit: public Ui_conditionsEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONDITIONSEDIT_H
