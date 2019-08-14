/********************************************************************************
** Form generated from reading UI file 'backup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKUP_H
#define UI_BACKUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_backup
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QToolButton *closeButton;
    QLabel *label;
    QPushButton *buttonNew;
    QPushButton *buttonRestore;
    QTableView *listOfAvailableBackUps;
    QProgressBar *progressBar;
    QPushButton *buttonDelete;
    QLabel *compatibility;

    void setupUi(QWidget *backup)
    {
        if (backup->objectName().isEmpty())
            backup->setObjectName(QString::fromUtf8("backup"));
        backup->resize(313, 383);
        gridLayout = new QGridLayout(backup);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(backup);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        closeButton = new QToolButton(backup);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout->addWidget(closeButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 3);

        label = new QLabel(backup);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 3);

        buttonNew = new QPushButton(backup);
        buttonNew->setObjectName(QString::fromUtf8("buttonNew"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonNew->sizePolicy().hasHeightForWidth());
        buttonNew->setSizePolicy(sizePolicy);

        gridLayout->addWidget(buttonNew, 5, 0, 1, 1);

        buttonRestore = new QPushButton(backup);
        buttonRestore->setObjectName(QString::fromUtf8("buttonRestore"));
        sizePolicy.setHeightForWidth(buttonRestore->sizePolicy().hasHeightForWidth());
        buttonRestore->setSizePolicy(sizePolicy);

        gridLayout->addWidget(buttonRestore, 5, 1, 1, 1);

        listOfAvailableBackUps = new QTableView(backup);
        listOfAvailableBackUps->setObjectName(QString::fromUtf8("listOfAvailableBackUps"));
        listOfAvailableBackUps->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listOfAvailableBackUps->setAlternatingRowColors(true);
        listOfAvailableBackUps->setSelectionMode(QAbstractItemView::SingleSelection);
        listOfAvailableBackUps->setSelectionBehavior(QAbstractItemView::SelectRows);
        listOfAvailableBackUps->setShowGrid(true);
        listOfAvailableBackUps->setCornerButtonEnabled(false);
        listOfAvailableBackUps->horizontalHeader()->setVisible(false);
        listOfAvailableBackUps->horizontalHeader()->setHighlightSections(false);
        listOfAvailableBackUps->verticalHeader()->setVisible(false);
        listOfAvailableBackUps->verticalHeader()->setHighlightSections(false);

        gridLayout->addWidget(listOfAvailableBackUps, 2, 0, 1, 3);

        progressBar = new QProgressBar(backup);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 4, 0, 1, 3);

        buttonDelete = new QPushButton(backup);
        buttonDelete->setObjectName(QString::fromUtf8("buttonDelete"));
        sizePolicy.setHeightForWidth(buttonDelete->sizePolicy().hasHeightForWidth());
        buttonDelete->setSizePolicy(sizePolicy);

        gridLayout->addWidget(buttonDelete, 5, 2, 1, 1);

        compatibility = new QLabel(backup);
        compatibility->setObjectName(QString::fromUtf8("compatibility"));
        compatibility->setWordWrap(true);

        gridLayout->addWidget(compatibility, 1, 0, 1, 3);


        retranslateUi(backup);

        QMetaObject::connectSlotsByName(backup);
    } // setupUi

    void retranslateUi(QWidget *backup)
    {
        backup->setWindowTitle(QApplication::translate("backup", "Form", nullptr));
        label_2->setText(QApplication::translate("backup", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Back up and Restore</span></p></body></html>", nullptr));
        closeButton->setText(QString());
        label->setText(QString());
        buttonNew->setText(QApplication::translate("backup", "Back Up", nullptr));
        buttonRestore->setText(QApplication::translate("backup", "Restore", nullptr));
        buttonDelete->setText(QApplication::translate("backup", "Delete", nullptr));
        compatibility->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class backup: public Ui_backup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKUP_H
