/********************************************************************************
** Form generated from reading UI file 'miniupdater.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINIUPDATER_H
#define UI_MINIUPDATER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_miniUpdater
{
public:
    QGridLayout *gridLayout;
    QLabel *speed;
    QTextEdit *textEdit;
    QPushButton *doButton;
    QProgressBar *progressBar;
    QPushButton *closeButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *miniUpdater)
    {
        if (miniUpdater->objectName().isEmpty())
            miniUpdater->setObjectName(QString::fromUtf8("miniUpdater"));
        miniUpdater->setWindowModality(Qt::NonModal);
        miniUpdater->resize(353, 330);
        miniUpdater->setContextMenuPolicy(Qt::NoContextMenu);
        miniUpdater->setModal(true);
        gridLayout = new QGridLayout(miniUpdater);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        speed = new QLabel(miniUpdater);
        speed->setObjectName(QString::fromUtf8("speed"));
        speed->setMinimumSize(QSize(80, 0));
        speed->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(speed, 3, 0, 1, 5);

        textEdit = new QTextEdit(miniUpdater);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setReadOnly(true);

        gridLayout->addWidget(textEdit, 1, 0, 1, 5);

        doButton = new QPushButton(miniUpdater);
        doButton->setObjectName(QString::fromUtf8("doButton"));
        doButton->setEnabled(false);
        doButton->setMinimumSize(QSize(90, 0));

        gridLayout->addWidget(doButton, 5, 2, 1, 1);

        progressBar = new QProgressBar(miniUpdater);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);
        progressBar->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(progressBar, 2, 0, 1, 5);

        closeButton = new QPushButton(miniUpdater);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setMinimumSize(QSize(90, 0));

        gridLayout->addWidget(closeButton, 5, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 5, 4, 1, 1);


        retranslateUi(miniUpdater);

        QMetaObject::connectSlotsByName(miniUpdater);
    } // setupUi

    void retranslateUi(QDialog *miniUpdater)
    {
        miniUpdater->setWindowTitle(QApplication::translate("miniUpdater", "Software update", nullptr));
        speed->setText(QString());
        doButton->setText(QApplication::translate("miniUpdater", "Update Now", nullptr));
        closeButton->setText(QApplication::translate("miniUpdater", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class miniUpdater: public Ui_miniUpdater {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIUPDATER_H
