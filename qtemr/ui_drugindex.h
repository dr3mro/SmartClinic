/********************************************************************************
** Form generated from reading UI file 'drugindex.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRUGINDEX_H
#define UI_DRUGINDEX_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_drugIndex
{
public:
    QGridLayout *gridLayout;
    QLabel *title;
    QComboBox *manufacturer;
    QHBoxLayout *horizontalLayout;
    QLineEdit *search;
    QRadioButton *tradeName;
    QRadioButton *genericName;
    QRadioButton *indication;
    QComboBox *form;
    QTableView *indexTable;
    QComboBox *categories;
    QLabel *results;
    QLabel *resultsCount;
    QLabel *drugs;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *resetButton;
    QToolButton *closeButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QLabel *updated;

    void setupUi(QDialog *drugIndex)
    {
        if (drugIndex->objectName().isEmpty())
            drugIndex->setObjectName(QString::fromUtf8("drugIndex"));
        drugIndex->resize(692, 472);
        gridLayout = new QGridLayout(drugIndex);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        title = new QLabel(drugIndex);
        title->setObjectName(QString::fromUtf8("title"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        title->setFont(font);

        gridLayout->addWidget(title, 0, 0, 1, 1);

        manufacturer = new QComboBox(drugIndex);
        manufacturer->setObjectName(QString::fromUtf8("manufacturer"));
        manufacturer->setEditable(false);

        gridLayout->addWidget(manufacturer, 4, 0, 1, 3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        search = new QLineEdit(drugIndex);
        search->setObjectName(QString::fromUtf8("search"));
        search->setClearButtonEnabled(true);

        horizontalLayout->addWidget(search);

        tradeName = new QRadioButton(drugIndex);
        tradeName->setObjectName(QString::fromUtf8("tradeName"));

        horizontalLayout->addWidget(tradeName);

        genericName = new QRadioButton(drugIndex);
        genericName->setObjectName(QString::fromUtf8("genericName"));

        horizontalLayout->addWidget(genericName);

        indication = new QRadioButton(drugIndex);
        indication->setObjectName(QString::fromUtf8("indication"));

        horizontalLayout->addWidget(indication);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 11);

        form = new QComboBox(drugIndex);
        form->setObjectName(QString::fromUtf8("form"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(form->sizePolicy().hasHeightForWidth());
        form->setSizePolicy(sizePolicy);
        form->setMinimumSize(QSize(90, 0));
        form->setEditable(false);

        gridLayout->addWidget(form, 4, 3, 1, 1);

        indexTable = new QTableView(drugIndex);
        indexTable->setObjectName(QString::fromUtf8("indexTable"));
        indexTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        indexTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        indexTable->setGridStyle(Qt::DotLine);
        indexTable->setSortingEnabled(true);
        indexTable->setCornerButtonEnabled(false);
        indexTable->horizontalHeader()->setCascadingSectionResizes(true);
        indexTable->verticalHeader()->setVisible(false);

        gridLayout->addWidget(indexTable, 2, 0, 1, 11);

        categories = new QComboBox(drugIndex);
        categories->setObjectName(QString::fromUtf8("categories"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(categories->sizePolicy().hasHeightForWidth());
        categories->setSizePolicy(sizePolicy1);
        categories->setEditable(false);

        gridLayout->addWidget(categories, 3, 0, 1, 11);

        results = new QLabel(drugIndex);
        results->setObjectName(QString::fromUtf8("results"));

        gridLayout->addWidget(results, 4, 6, 1, 1);

        resultsCount = new QLabel(drugIndex);
        resultsCount->setObjectName(QString::fromUtf8("resultsCount"));
        resultsCount->setMinimumSize(QSize(40, 0));

        gridLayout->addWidget(resultsCount, 4, 7, 1, 2);

        drugs = new QLabel(drugIndex);
        drugs->setObjectName(QString::fromUtf8("drugs"));

        gridLayout->addWidget(drugs, 4, 9, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 5, 1, 1);

        resetButton = new QToolButton(drugIndex);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Graphics/ex"), QSize(), QIcon::Normal, QIcon::Off);
        resetButton->setIcon(icon);
        resetButton->setAutoRaise(true);

        gridLayout->addWidget(resetButton, 4, 4, 1, 1);

        closeButton = new QToolButton(drugIndex);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        gridLayout->addWidget(closeButton, 0, 10, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(37, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 8, 1, 2);

        horizontalSpacer = new QSpacerItem(284, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 6);

        updated = new QLabel(drugIndex);
        updated->setObjectName(QString::fromUtf8("updated"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        updated->setFont(font1);

        gridLayout->addWidget(updated, 0, 1, 1, 1);


        retranslateUi(drugIndex);

        QMetaObject::connectSlotsByName(drugIndex);
    } // setupUi

    void retranslateUi(QDialog *drugIndex)
    {
        drugIndex->setWindowTitle(QApplication::translate("drugIndex", "Dialog", nullptr));
        title->setText(QApplication::translate("drugIndex", "Egypt's Drugs Index", nullptr));
        tradeName->setText(QApplication::translate("drugIndex", "Trade Name", nullptr));
        genericName->setText(QApplication::translate("drugIndex", "Generic Name", nullptr));
        indication->setText(QApplication::translate("drugIndex", "Indication", nullptr));
        results->setText(QApplication::translate("drugIndex", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Results: </span></p></body></html>", nullptr));
        resultsCount->setText(QApplication::translate("drugIndex", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">00000</span></p></body></html>", nullptr));
        drugs->setText(QApplication::translate("drugIndex", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\"> Drugs</span></p></body></html>", nullptr));
#ifndef QT_NO_TOOLTIP
        resetButton->setToolTip(QApplication::translate("drugIndex", "Reset Filters", nullptr));
#endif // QT_NO_TOOLTIP
        resetButton->setText(QApplication::translate("drugIndex", "...", nullptr));
        closeButton->setText(QString());
        updated->setText(QApplication::translate("drugIndex", "Jan,2011", nullptr));
    } // retranslateUi

};

namespace Ui {
    class drugIndex: public Ui_drugIndex {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRUGINDEX_H
