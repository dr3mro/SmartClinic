/********************************************************************************
** Form generated from reading UI file 'searchwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHWIDGET_H
#define UI_SEARCHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "mpatientfilter.h"
#include "patienttable.h"

QT_BEGIN_NAMESPACE

class Ui_searchWidget
{
public:
    QGridLayout *gridLayout;
    mPatientFilter *filterLineEdit;
    QWidget *filtersWidget;
    QHBoxLayout *horizontalLayout_20;
    QSpacerItem *horizontalSpacer_9;
    QRadioButton *filterByNameRadio;
    QRadioButton *filterByIDRadio;
    QRadioButton *filterByMobileRadio;
    QSpacerItem *horizontalSpacer_10;
    patientTable *PatientListTableView;

    void setupUi(QWidget *searchWidget)
    {
        if (searchWidget->objectName().isEmpty())
            searchWidget->setObjectName(QString::fromUtf8("searchWidget"));
        searchWidget->resize(273, 480);
        gridLayout = new QGridLayout(searchWidget);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        filterLineEdit = new mPatientFilter(searchWidget);
        filterLineEdit->setObjectName(QString::fromUtf8("filterLineEdit"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        filterLineEdit->setFont(font);
        filterLineEdit->setClearButtonEnabled(true);

        gridLayout->addWidget(filterLineEdit, 0, 0, 1, 1);

        filtersWidget = new QWidget(searchWidget);
        filtersWidget->setObjectName(QString::fromUtf8("filtersWidget"));
        horizontalLayout_20 = new QHBoxLayout(filtersWidget);
        horizontalLayout_20->setSpacing(3);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        horizontalLayout_20->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_9);

        filterByNameRadio = new QRadioButton(filtersWidget);
        filterByNameRadio->setObjectName(QString::fromUtf8("filterByNameRadio"));

        horizontalLayout_20->addWidget(filterByNameRadio);

        filterByIDRadio = new QRadioButton(filtersWidget);
        filterByIDRadio->setObjectName(QString::fromUtf8("filterByIDRadio"));

        horizontalLayout_20->addWidget(filterByIDRadio);

        filterByMobileRadio = new QRadioButton(filtersWidget);
        filterByMobileRadio->setObjectName(QString::fromUtf8("filterByMobileRadio"));

        horizontalLayout_20->addWidget(filterByMobileRadio);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_10);


        gridLayout->addWidget(filtersWidget, 1, 0, 1, 1);

        PatientListTableView = new patientTable(searchWidget);
        PatientListTableView->setObjectName(QString::fromUtf8("PatientListTableView"));
        PatientListTableView->setFont(font);
        PatientListTableView->setAlternatingRowColors(true);
        PatientListTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        PatientListTableView->setGridStyle(Qt::NoPen);
        PatientListTableView->setSortingEnabled(true);
        PatientListTableView->setCornerButtonEnabled(false);
        PatientListTableView->horizontalHeader()->setMinimumSectionSize(40);
        PatientListTableView->horizontalHeader()->setDefaultSectionSize(40);
        PatientListTableView->verticalHeader()->setVisible(false);
        PatientListTableView->verticalHeader()->setMinimumSectionSize(20);
        PatientListTableView->verticalHeader()->setDefaultSectionSize(20);
        PatientListTableView->verticalHeader()->setHighlightSections(true);

        gridLayout->addWidget(PatientListTableView, 2, 0, 1, 1);


        retranslateUi(searchWidget);

        QMetaObject::connectSlotsByName(searchWidget);
    } // setupUi

    void retranslateUi(QWidget *searchWidget)
    {
        searchWidget->setWindowTitle(QApplication::translate("searchWidget", "Form", nullptr));
#ifndef QT_NO_TOOLTIP
        filterLineEdit->setToolTip(QApplication::translate("searchWidget", "<html><head/><body><p>F2</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        filterLineEdit->setPlaceholderText(QApplication::translate("searchWidget", "Search here ...", nullptr));
#ifndef QT_NO_TOOLTIP
        filterByNameRadio->setToolTip(QApplication::translate("searchWidget", "<html><head/><body><p>CTRL+1</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        filterByNameRadio->setText(QApplication::translate("searchWidget", "Name", nullptr));
#ifndef QT_NO_SHORTCUT
        filterByNameRadio->setShortcut(QApplication::translate("searchWidget", "Ctrl+1", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        filterByIDRadio->setToolTip(QApplication::translate("searchWidget", "<html><head/><body><p>CTRL+2</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        filterByIDRadio->setText(QApplication::translate("searchWidget", "ID", nullptr));
#ifndef QT_NO_SHORTCUT
        filterByIDRadio->setShortcut(QApplication::translate("searchWidget", "Ctrl+2", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        filterByMobileRadio->setToolTip(QApplication::translate("searchWidget", "<html><head/><body><p>CTRL+3</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        filterByMobileRadio->setText(QApplication::translate("searchWidget", "Mobile", nullptr));
#ifndef QT_NO_SHORTCUT
        filterByMobileRadio->setShortcut(QApplication::translate("searchWidget", "Ctrl+3", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        PatientListTableView->setToolTip(QApplication::translate("searchWidget", "<html><head/><body><p>Tab</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class searchWidget: public Ui_searchWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHWIDGET_H
