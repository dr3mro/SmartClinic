/********************************************************************************
** Form generated from reading UI file 'genericonlinesearch.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERICONLINESEARCH_H
#define UI_GENERICONLINESEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_genericOnlineSearch
{
public:
    QGridLayout *gridLayout;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonSearch;
    QListView *listView;
    clickableLabel *label;

    void setupUi(QWidget *genericOnlineSearch)
    {
        if (genericOnlineSearch->objectName().isEmpty())
            genericOnlineSearch->setObjectName(QString::fromUtf8("genericOnlineSearch"));
        genericOnlineSearch->setWindowModality(Qt::ApplicationModal);
        genericOnlineSearch->resize(308, 345);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(genericOnlineSearch->sizePolicy().hasHeightForWidth());
        genericOnlineSearch->setSizePolicy(sizePolicy);
        genericOnlineSearch->setMouseTracking(false);
        genericOnlineSearch->setFocusPolicy(Qt::NoFocus);
        gridLayout = new QGridLayout(genericOnlineSearch);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBox = new QComboBox(genericOnlineSearch);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 3, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 1, 1, 1);

        buttonSearch = new QPushButton(genericOnlineSearch);
        buttonSearch->setObjectName(QString::fromUtf8("buttonSearch"));
        buttonSearch->setEnabled(false);

        gridLayout->addWidget(buttonSearch, 3, 0, 1, 1);

        listView = new QListView(genericOnlineSearch);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView->setAlternatingRowColors(true);

        gridLayout->addWidget(listView, 2, 0, 1, 4);

        label = new clickableLabel(genericOnlineSearch);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);
        label->setOpenExternalLinks(true);

        gridLayout->addWidget(label, 1, 0, 1, 4);


        retranslateUi(genericOnlineSearch);

        QMetaObject::connectSlotsByName(genericOnlineSearch);
    } // setupUi

    void retranslateUi(QWidget *genericOnlineSearch)
    {
        genericOnlineSearch->setWindowTitle(QApplication::translate("genericOnlineSearch", "Online drug information", nullptr));
        comboBox->setItemText(0, QApplication::translate("genericOnlineSearch", "drugs.com", nullptr));
        comboBox->setItemText(1, QApplication::translate("genericOnlineSearch", "rxlist.com", nullptr));
        comboBox->setItemText(2, QApplication::translate("genericOnlineSearch", "fda.gov", nullptr));
        comboBox->setItemText(3, QApplication::translate("genericOnlineSearch", "usnlm.gov", nullptr));
        comboBox->setItemText(4, QApplication::translate("genericOnlineSearch", "wikipedia.com", nullptr));
        comboBox->setItemText(5, QApplication::translate("genericOnlineSearch", "google.com", nullptr));

        buttonSearch->setText(QApplication::translate("genericOnlineSearch", "Search", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class genericOnlineSearch: public Ui_genericOnlineSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERICONLINESEARCH_H
