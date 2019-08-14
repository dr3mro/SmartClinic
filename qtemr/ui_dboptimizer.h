/********************************************************************************
** Form generated from reading UI file 'dboptimizer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBOPTIMIZER_H
#define UI_DBOPTIMIZER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "switch.h"

QT_BEGIN_NAMESPACE

class Ui_dbOptimizer
{
public:
    QGridLayout *gridLayout_6;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QGroupBox *prefBox;
    QGridLayout *gridLayout_2;
    QCheckBox *cb_clean;
    QCheckBox *cb_quick;
    QGroupBox *dbBox;
    QGridLayout *gridLayout;
    QCheckBox *cb_patients;
    QCheckBox *cb_drugsindex;
    QCheckBox *cb_core;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_2;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QComboBox *autoVcuum;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *lockingMode;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *tempStore;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_13;
    QSpinBox *pageSize;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *synchronous;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_7;
    QSpinBox *cacheSize;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_12;
    Switch *sw_optimize;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *journalMode;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_6;
    QComboBox *sharedCache;
    QPushButton *resetTweaks;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_16;
    Switch *sw_shrinkMemory;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_11;
    QComboBox *WAL_CheckPoint_Mode;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_14;
    QLabel *loading;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *verticalSpacer;
    QSplitter *splitter_2;
    QPushButton *buttonClose;
    QPushButton *buttonOptimize;
    QTextEdit *status;

    void setupUi(QDialog *dbOptimizer)
    {
        if (dbOptimizer->objectName().isEmpty())
            dbOptimizer->setObjectName(QString::fromUtf8("dbOptimizer"));
        dbOptimizer->resize(750, 486);
        gridLayout_6 = new QGridLayout(dbOptimizer);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        tabWidget = new QTabWidget(dbOptimizer);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setSpacing(1);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(3, 3, 3, 3);
        prefBox = new QGroupBox(tab);
        prefBox->setObjectName(QString::fromUtf8("prefBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(prefBox->sizePolicy().hasHeightForWidth());
        prefBox->setSizePolicy(sizePolicy1);
        prefBox->setMaximumSize(QSize(200, 16777215));
        gridLayout_2 = new QGridLayout(prefBox);
        gridLayout_2->setSpacing(3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(3, 3, 3, 3);
        cb_clean = new QCheckBox(prefBox);
        cb_clean->setObjectName(QString::fromUtf8("cb_clean"));
        cb_clean->setChecked(true);

        gridLayout_2->addWidget(cb_clean, 2, 0, 1, 1);

        cb_quick = new QCheckBox(prefBox);
        cb_quick->setObjectName(QString::fromUtf8("cb_quick"));
        cb_quick->setChecked(true);

        gridLayout_2->addWidget(cb_quick, 1, 0, 1, 1);


        gridLayout_3->addWidget(prefBox, 0, 0, 1, 1);

        dbBox = new QGroupBox(tab);
        dbBox->setObjectName(QString::fromUtf8("dbBox"));
        sizePolicy1.setHeightForWidth(dbBox->sizePolicy().hasHeightForWidth());
        dbBox->setSizePolicy(sizePolicy1);
        dbBox->setMaximumSize(QSize(200, 16777215));
        gridLayout = new QGridLayout(dbBox);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        cb_patients = new QCheckBox(dbBox);
        cb_patients->setObjectName(QString::fromUtf8("cb_patients"));
        cb_patients->setEnabled(false);
        cb_patients->setChecked(true);

        gridLayout->addWidget(cb_patients, 0, 0, 1, 1);

        cb_drugsindex = new QCheckBox(dbBox);
        cb_drugsindex->setObjectName(QString::fromUtf8("cb_drugsindex"));
        cb_drugsindex->setChecked(true);

        gridLayout->addWidget(cb_drugsindex, 2, 0, 1, 1);

        cb_core = new QCheckBox(dbBox);
        cb_core->setObjectName(QString::fromUtf8("cb_core"));
        cb_core->setChecked(true);

        gridLayout->addWidget(cb_core, 1, 0, 1, 1);


        gridLayout_3->addWidget(dbBox, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 54, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 2, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_5 = new QGridLayout(tab_2);
        gridLayout_5->setSpacing(3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(3, 3, 3, 3);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        autoVcuum = new QComboBox(tab_2);
        autoVcuum->addItem(QString());
        autoVcuum->addItem(QString());
        autoVcuum->addItem(QString());
        autoVcuum->setObjectName(QString::fromUtf8("autoVcuum"));
        autoVcuum->setMinimumSize(QSize(90, 0));
        autoVcuum->setMaximumSize(QSize(90, 16777215));

        horizontalLayout->addWidget(autoVcuum);


        gridLayout_5->addLayout(horizontalLayout, 4, 0, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        lockingMode = new QComboBox(tab_2);
        lockingMode->addItem(QString());
        lockingMode->setObjectName(QString::fromUtf8("lockingMode"));
        lockingMode->setEnabled(true);
        lockingMode->setMinimumSize(QSize(90, 0));
        lockingMode->setMaximumSize(QSize(90, 16777215));

        horizontalLayout_5->addWidget(lockingMode);


        gridLayout_5->addLayout(horizontalLayout_5, 10, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 48, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_2, 14, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(34, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        tempStore = new QComboBox(tab_2);
        tempStore->addItem(QString());
        tempStore->addItem(QString());
        tempStore->addItem(QString());
        tempStore->setObjectName(QString::fromUtf8("tempStore"));
        tempStore->setMinimumSize(QSize(90, 0));
        tempStore->setMaximumSize(QSize(90, 16777215));

        horizontalLayout_2->addWidget(tempStore);


        gridLayout_5->addLayout(horizontalLayout_2, 6, 0, 1, 2);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_13 = new QLabel(tab_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_13->addWidget(label_13);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_13);

        pageSize = new QSpinBox(tab_2);
        pageSize->setObjectName(QString::fromUtf8("pageSize"));
        pageSize->setMaximum(999999999);

        horizontalLayout_13->addWidget(pageSize);


        gridLayout_5->addLayout(horizontalLayout_13, 12, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        synchronous = new QComboBox(tab_2);
        synchronous->addItem(QString());
        synchronous->addItem(QString());
        synchronous->addItem(QString());
        synchronous->addItem(QString());
        synchronous->setObjectName(QString::fromUtf8("synchronous"));
        synchronous->setMinimumSize(QSize(90, 0));
        synchronous->setMaximumSize(QSize(90, 16777215));

        horizontalLayout_3->addWidget(synchronous);


        gridLayout_5->addLayout(horizontalLayout_3, 7, 0, 1, 2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        cacheSize = new QSpinBox(tab_2);
        cacheSize->setObjectName(QString::fromUtf8("cacheSize"));
        cacheSize->setMinimum(-99999999);
        cacheSize->setMaximum(999999999);
        cacheSize->setSingleStep(1);

        horizontalLayout_7->addWidget(cacheSize);


        gridLayout_5->addLayout(horizontalLayout_7, 11, 0, 1, 2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_12 = new QLabel(tab_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_12->addWidget(label_12);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_12);

        sw_optimize = new Switch(tab_2);
        sw_optimize->setObjectName(QString::fromUtf8("sw_optimize"));

        horizontalLayout_12->addWidget(sw_optimize);


        gridLayout_5->addLayout(horizontalLayout_12, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        journalMode = new QComboBox(tab_2);
        journalMode->addItem(QString());
        journalMode->addItem(QString());
        journalMode->addItem(QString());
        journalMode->addItem(QString());
        journalMode->addItem(QString());
        journalMode->addItem(QString());
        journalMode->setObjectName(QString::fromUtf8("journalMode"));
        journalMode->setMinimumSize(QSize(90, 0));
        journalMode->setMaximumSize(QSize(90, 16777215));

        horizontalLayout_4->addWidget(journalMode);


        gridLayout_5->addLayout(horizontalLayout_4, 8, 0, 1, 2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        sharedCache = new QComboBox(tab_2);
        sharedCache->addItem(QString());
        sharedCache->addItem(QString());
        sharedCache->setObjectName(QString::fromUtf8("sharedCache"));
        sharedCache->setMinimumSize(QSize(90, 0));
        sharedCache->setMaximumSize(QSize(90, 16777215));

        horizontalLayout_6->addWidget(sharedCache);


        gridLayout_5->addLayout(horizontalLayout_6, 5, 0, 1, 2);

        resetTweaks = new QPushButton(tab_2);
        resetTweaks->setObjectName(QString::fromUtf8("resetTweaks"));
        sizePolicy.setHeightForWidth(resetTweaks->sizePolicy().hasHeightForWidth());
        resetTweaks->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(resetTweaks, 13, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_14 = new QLabel(tab_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_14->addWidget(label_14);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_16);

        sw_shrinkMemory = new Switch(tab_2);
        sw_shrinkMemory->setObjectName(QString::fromUtf8("sw_shrinkMemory"));
        sw_shrinkMemory->setEnabled(false);

        horizontalLayout_14->addWidget(sw_shrinkMemory);


        gridLayout_5->addLayout(horizontalLayout_14, 2, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_11 = new QLabel(tab_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_11->addWidget(label_11);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_11);

        WAL_CheckPoint_Mode = new QComboBox(tab_2);
        WAL_CheckPoint_Mode->addItem(QString());
        WAL_CheckPoint_Mode->addItem(QString());
        WAL_CheckPoint_Mode->addItem(QString());
        WAL_CheckPoint_Mode->addItem(QString());
        WAL_CheckPoint_Mode->addItem(QString());
        WAL_CheckPoint_Mode->addItem(QString());
        WAL_CheckPoint_Mode->setObjectName(QString::fromUtf8("WAL_CheckPoint_Mode"));
        WAL_CheckPoint_Mode->setMinimumSize(QSize(90, 0));
        WAL_CheckPoint_Mode->setMaximumSize(QSize(90, 16777215));

        horizontalLayout_11->addWidget(WAL_CheckPoint_Mode);


        gridLayout_5->addLayout(horizontalLayout_11, 9, 0, 1, 2);

        tabWidget->addTab(tab_2, QString());

        gridLayout_6->addWidget(tabWidget, 0, 1, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer_14 = new QSpacerItem(57, 17, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_14, 0, 0, 1, 1);

        loading = new QLabel(dbOptimizer);
        loading->setObjectName(QString::fromUtf8("loading"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(loading->sizePolicy().hasHeightForWidth());
        loading->setSizePolicy(sizePolicy2);
        loading->setMinimumSize(QSize(48, 48));
        loading->setMaximumSize(QSize(48, 48));

        gridLayout_4->addWidget(loading, 0, 1, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(68, 17, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_15, 0, 2, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(17, 371, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 2, 1, 1, 1);

        splitter_2 = new QSplitter(dbOptimizer);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setOrientation(Qt::Horizontal);
        buttonClose = new QPushButton(splitter_2);
        buttonClose->setObjectName(QString::fromUtf8("buttonClose"));
        splitter_2->addWidget(buttonClose);
        buttonOptimize = new QPushButton(splitter_2);
        buttonOptimize->setObjectName(QString::fromUtf8("buttonOptimize"));
        splitter_2->addWidget(buttonOptimize);

        gridLayout_6->addWidget(splitter_2, 3, 1, 1, 1);

        status = new QTextEdit(dbOptimizer);
        status->setObjectName(QString::fromUtf8("status"));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        status->setFont(font);
        status->setReadOnly(true);

        gridLayout_6->addWidget(status, 0, 0, 4, 1);


        retranslateUi(dbOptimizer);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(dbOptimizer);
    } // setupUi

    void retranslateUi(QDialog *dbOptimizer)
    {
        dbOptimizer->setWindowTitle(QApplication::translate("dbOptimizer", "Data Optimizer", nullptr));
        prefBox->setTitle(QApplication::translate("dbOptimizer", "Preferences", nullptr));
        cb_clean->setText(QApplication::translate("dbOptimizer", "Clean up database", nullptr));
        cb_quick->setText(QApplication::translate("dbOptimizer", "Quick mode.", nullptr));
        dbBox->setTitle(QApplication::translate("dbOptimizer", "Databases", nullptr));
        cb_patients->setText(QApplication::translate("dbOptimizer", "Patients database", nullptr));
        cb_drugsindex->setText(QApplication::translate("dbOptimizer", "drugs index database", nullptr));
        cb_core->setText(QApplication::translate("dbOptimizer", "corecomponents database", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("dbOptimizer", "settings", nullptr));
        label->setText(QApplication::translate("dbOptimizer", "Auto VACUUM", nullptr));
        autoVcuum->setItemText(0, QApplication::translate("dbOptimizer", "NONE", nullptr));
        autoVcuum->setItemText(1, QApplication::translate("dbOptimizer", "FULL", nullptr));
        autoVcuum->setItemText(2, QApplication::translate("dbOptimizer", "INCREMENTAL", nullptr));

        label_5->setText(QApplication::translate("dbOptimizer", "Locking mode", nullptr));
        lockingMode->setItemText(0, QApplication::translate("dbOptimizer", "NORMAL", nullptr));

        label_2->setText(QApplication::translate("dbOptimizer", "Temp Store", nullptr));
        tempStore->setItemText(0, QApplication::translate("dbOptimizer", "DEFAULT", nullptr));
        tempStore->setItemText(1, QApplication::translate("dbOptimizer", "MEMORY", nullptr));
        tempStore->setItemText(2, QApplication::translate("dbOptimizer", "FILE", nullptr));

        label_13->setText(QApplication::translate("dbOptimizer", "Page size", nullptr));
        label_3->setText(QApplication::translate("dbOptimizer", "Synchronous", nullptr));
        synchronous->setItemText(0, QApplication::translate("dbOptimizer", "OFF", nullptr));
        synchronous->setItemText(1, QApplication::translate("dbOptimizer", "NORMAL", nullptr));
        synchronous->setItemText(2, QApplication::translate("dbOptimizer", "FULL", nullptr));
        synchronous->setItemText(3, QApplication::translate("dbOptimizer", "EXTRA", nullptr));

        label_7->setText(QApplication::translate("dbOptimizer", "Cache size", nullptr));
        label_12->setText(QApplication::translate("dbOptimizer", "Optimize", nullptr));
        sw_optimize->setText(QString());
        label_4->setText(QApplication::translate("dbOptimizer", "Journal mode", nullptr));
        journalMode->setItemText(0, QApplication::translate("dbOptimizer", "DELETE", nullptr));
        journalMode->setItemText(1, QApplication::translate("dbOptimizer", "TRUNCATE", nullptr));
        journalMode->setItemText(2, QApplication::translate("dbOptimizer", "PERSIST", nullptr));
        journalMode->setItemText(3, QApplication::translate("dbOptimizer", "MEMORY", nullptr));
        journalMode->setItemText(4, QApplication::translate("dbOptimizer", "WAL", nullptr));
        journalMode->setItemText(5, QApplication::translate("dbOptimizer", "OFF", nullptr));

        label_6->setText(QApplication::translate("dbOptimizer", "Shared cache", nullptr));
        sharedCache->setItemText(0, QApplication::translate("dbOptimizer", "SHARED", nullptr));
        sharedCache->setItemText(1, QApplication::translate("dbOptimizer", "PRIVATE", nullptr));

        resetTweaks->setText(QApplication::translate("dbOptimizer", "Restore Defaults", nullptr));
        label_14->setText(QApplication::translate("dbOptimizer", "Shrink Memory", nullptr));
        sw_shrinkMemory->setText(QString());
        label_11->setText(QApplication::translate("dbOptimizer", "WAL CheckPoint", nullptr));
        WAL_CheckPoint_Mode->setItemText(0, QApplication::translate("dbOptimizer", "OFF", nullptr));
        WAL_CheckPoint_Mode->setItemText(1, QApplication::translate("dbOptimizer", "DEFAULT", nullptr));
        WAL_CheckPoint_Mode->setItemText(2, QApplication::translate("dbOptimizer", "PASSIVE", nullptr));
        WAL_CheckPoint_Mode->setItemText(3, QApplication::translate("dbOptimizer", "FULL", nullptr));
        WAL_CheckPoint_Mode->setItemText(4, QApplication::translate("dbOptimizer", "RESTART", nullptr));
        WAL_CheckPoint_Mode->setItemText(5, QApplication::translate("dbOptimizer", "TRUNCATE", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("dbOptimizer", "Tweaks", nullptr));
        loading->setText(QString());
        buttonClose->setText(QApplication::translate("dbOptimizer", "Close", nullptr));
        buttonOptimize->setText(QApplication::translate("dbOptimizer", "Optimize", nullptr));
        status->setPlaceholderText(QString());
    } // retranslateUi

};

namespace Ui {
    class dbOptimizer: public Ui_dbOptimizer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBOPTIMIZER_H
