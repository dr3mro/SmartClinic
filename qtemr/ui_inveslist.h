/********************************************************************************
** Form generated from reading UI file 'inveslist.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVESLIST_H
#define UI_INVESLIST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_invesList
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *ButtonNew;
    QToolButton *ButtonDel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QToolButton *closeButton;
    QTableView *tableView;

    void setupUi(QDialog *invesList)
    {
        if (invesList->objectName().isEmpty())
            invesList->setObjectName(QString::fromUtf8("invesList"));
        invesList->resize(363, 399);
        verticalLayout = new QVBoxLayout(invesList);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 9, -1, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ButtonNew = new QToolButton(invesList);
        ButtonNew->setObjectName(QString::fromUtf8("ButtonNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Graphics/add"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonNew->setIcon(icon);

        horizontalLayout->addWidget(ButtonNew);

        ButtonDel = new QToolButton(invesList);
        ButtonDel->setObjectName(QString::fromUtf8("ButtonDel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Graphics/minus"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonDel->setIcon(icon1);

        horizontalLayout->addWidget(ButtonDel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(invesList);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        closeButton = new QToolButton(invesList);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout->addWidget(closeButton);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(invesList);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setGridStyle(Qt::NoPen);
        tableView->setSortingEnabled(true);
        tableView->setCornerButtonEnabled(false);
        tableView->horizontalHeader()->setVisible(false);
        tableView->horizontalHeader()->setHighlightSections(true);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);
        tableView->verticalHeader()->setDefaultSectionSize(20);
        tableView->verticalHeader()->setHighlightSections(true);
        tableView->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(tableView);


        retranslateUi(invesList);

        QMetaObject::connectSlotsByName(invesList);
    } // setupUi

    void retranslateUi(QDialog *invesList)
    {
        invesList->setWindowTitle(QApplication::translate("invesList", "Investigations List", nullptr));
        ButtonNew->setText(QApplication::translate("invesList", "...", nullptr));
        ButtonDel->setText(QApplication::translate("invesList", "...", nullptr));
        label->setText(QApplication::translate("invesList", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Investigations List</span></p></body></html>", nullptr));
        closeButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class invesList: public Ui_invesList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVESLIST_H
