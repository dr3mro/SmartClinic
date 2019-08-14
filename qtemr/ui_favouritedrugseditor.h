/********************************************************************************
** Form generated from reading UI file 'favouritedrugseditor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAVOURITEDRUGSEDITOR_H
#define UI_FAVOURITEDRUGSEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "genericlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_favouriteDrugsEditor
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    genericLineEdit *dose;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *rowsCount;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *closeButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *ButtonNew;
    QToolButton *ButtonDel;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    genericLineEdit *tradeName;
    QTableView *tableView;

    void setupUi(QDialog *favouriteDrugsEditor)
    {
        if (favouriteDrugsEditor->objectName().isEmpty())
            favouriteDrugsEditor->setObjectName(QString::fromUtf8("favouriteDrugsEditor"));
        favouriteDrugsEditor->resize(640, 480);
        favouriteDrugsEditor->setModal(true);
        gridLayout = new QGridLayout(favouriteDrugsEditor);
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(favouriteDrugsEditor);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        dose = new genericLineEdit(favouriteDrugsEditor);
        dose->setObjectName(QString::fromUtf8("dose"));
        dose->setEnabled(false);
        dose->setReadOnly(false);
        dose->setClearButtonEnabled(true);

        horizontalLayout_2->addWidget(dose);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(favouriteDrugsEditor);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setPointSize(10);
        label_3->setFont(font);

        horizontalLayout_3->addWidget(label_3);

        rowsCount = new QLabel(favouriteDrugsEditor);
        rowsCount->setObjectName(QString::fromUtf8("rowsCount"));

        horizontalLayout_3->addWidget(rowsCount);

        label_5 = new QLabel(favouriteDrugsEditor);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        closeButton = new QToolButton(favouriteDrugsEditor);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout_3->addWidget(closeButton);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 2, 3);

        widget = new QWidget(favouriteDrugsEditor);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        ButtonNew = new QToolButton(widget);
        ButtonNew->setObjectName(QString::fromUtf8("ButtonNew"));
        ButtonNew->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ionicons/add"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonNew->setIcon(icon);

        horizontalLayout_4->addWidget(ButtonNew);

        ButtonDel = new QToolButton(widget);
        ButtonDel->setObjectName(QString::fromUtf8("ButtonDel"));
        ButtonDel->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ionicons/rm"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonDel->setIcon(icon1);

        horizontalLayout_4->addWidget(ButtonDel);


        gridLayout->addWidget(widget, 3, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(favouriteDrugsEditor);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        tradeName = new genericLineEdit(favouriteDrugsEditor);
        tradeName->setObjectName(QString::fromUtf8("tradeName"));
        tradeName->setClearButtonEnabled(true);

        horizontalLayout->addWidget(tradeName);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 2);

        tableView = new QTableView(favouriteDrugsEditor);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setGridStyle(Qt::DotLine);
        tableView->setSortingEnabled(true);
        tableView->setWordWrap(false);
        tableView->setCornerButtonEnabled(true);
        tableView->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);
        tableView->verticalHeader()->setMinimumSectionSize(20);
        tableView->verticalHeader()->setDefaultSectionSize(20);
        tableView->verticalHeader()->setHighlightSections(false);

        gridLayout->addWidget(tableView, 4, 0, 1, 3);

        QWidget::setTabOrder(tradeName, dose);
        QWidget::setTabOrder(dose, ButtonNew);
        QWidget::setTabOrder(ButtonNew, ButtonDel);
        QWidget::setTabOrder(ButtonDel, tableView);

        retranslateUi(favouriteDrugsEditor);

        QMetaObject::connectSlotsByName(favouriteDrugsEditor);
    } // setupUi

    void retranslateUi(QDialog *favouriteDrugsEditor)
    {
        favouriteDrugsEditor->setWindowTitle(QApplication::translate("favouriteDrugsEditor", "Dialog", nullptr));
        label_2->setText(QApplication::translate("favouriteDrugsEditor", "Default Dose", nullptr));
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("favouriteDrugsEditor", "<html><head/><body><p>Here you can add more drugs to your favourites and set its default dose.</p><p align=\"justify\">Any drug you enter in patient list will be added here automatically with its dose.</p><p align=\"justify\">You can toggle between all drugs mode and favourite mode by clicking Middle mouse click over drugs input line in either main window or visits window</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("favouriteDrugsEditor", "<html><head/><body><p><span style=\" font-weight:600;\">Favourite drugs and default doses: currently (</span></p></body></html>", nullptr));
        rowsCount->setText(QApplication::translate("favouriteDrugsEditor", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">0</span></p></body></html>", nullptr));
        label_5->setText(QApplication::translate("favouriteDrugsEditor", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">) Items</span></p></body></html>", nullptr));
        closeButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        ButtonNew->setToolTip(QApplication::translate("favouriteDrugsEditor", "<html><head/><body><p>Add Drug</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        ButtonNew->setText(QApplication::translate("favouriteDrugsEditor", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        ButtonDel->setToolTip(QApplication::translate("favouriteDrugsEditor", "<html><head/><body><p>Delete Row</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        ButtonDel->setText(QApplication::translate("favouriteDrugsEditor", "...", nullptr));
        label->setText(QApplication::translate("favouriteDrugsEditor", "Trade Name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class favouriteDrugsEditor: public Ui_favouriteDrugsEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAVOURITEDRUGSEDITOR_H
