/********************************************************************************
** Form generated from reading UI file 'surgicalnotes.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SURGICALNOTES_H
#define UI_SURGICALNOTES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include "msurgicalnotes.h"

QT_BEGIN_NAMESPACE

class Ui_surgicalNotes
{
public:
    QGridLayout *gridLayout;
    QLabel *label_3;
    QToolButton *closeButton;
    QToolButton *buttonAdd;
    QToolButton *buttonDel;
    QToolButton *buttonEdit;
    mSurgicalNotes *notes;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *surgicalNotes)
    {
        if (surgicalNotes->objectName().isEmpty())
            surgicalNotes->setObjectName(QString::fromUtf8("surgicalNotes"));
        surgicalNotes->resize(542, 378);
        gridLayout = new QGridLayout(surgicalNotes);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 3, -1, -1);
        label_3 = new QLabel(surgicalNotes);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 4);

        closeButton = new QToolButton(surgicalNotes);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        gridLayout->addWidget(closeButton, 0, 4, 1, 1);

        buttonAdd = new QToolButton(surgicalNotes);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Graphics/add"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAdd->setIcon(icon);

        gridLayout->addWidget(buttonAdd, 1, 0, 1, 1);

        buttonDel = new QToolButton(surgicalNotes);
        buttonDel->setObjectName(QString::fromUtf8("buttonDel"));
        buttonDel->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Graphics/minus"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDel->setIcon(icon1);

        gridLayout->addWidget(buttonDel, 1, 1, 1, 1);

        buttonEdit = new QToolButton(surgicalNotes);
        buttonEdit->setObjectName(QString::fromUtf8("buttonEdit"));
        buttonEdit->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Graphics/pencil"), QSize(), QIcon::Normal, QIcon::Off);
        buttonEdit->setIcon(icon2);

        gridLayout->addWidget(buttonEdit, 1, 2, 1, 1);

        notes = new mSurgicalNotes(surgicalNotes);
        notes->setObjectName(QString::fromUtf8("notes"));
        notes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        notes->setAlternatingRowColors(true);
        notes->setSelectionMode(QAbstractItemView::SingleSelection);
        notes->setSelectionBehavior(QAbstractItemView::SelectRows);
        notes->setGridStyle(Qt::DotLine);
        notes->setWordWrap(false);
        notes->setCornerButtonEnabled(false);
        notes->horizontalHeader()->setStretchLastSection(true);
        notes->verticalHeader()->setDefaultSectionSize(23);

        gridLayout->addWidget(notes, 2, 0, 1, 5);

        horizontalSpacer = new QSpacerItem(434, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 2);


        retranslateUi(surgicalNotes);

        QMetaObject::connectSlotsByName(surgicalNotes);
    } // setupUi

    void retranslateUi(QDialog *surgicalNotes)
    {
        surgicalNotes->setWindowTitle(QApplication::translate("surgicalNotes", "Dialog", nullptr));
        label_3->setText(QApplication::translate("surgicalNotes", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Surgical Notes</span></p></body></html>", nullptr));
        closeButton->setText(QString());
        buttonAdd->setText(QApplication::translate("surgicalNotes", "...", nullptr));
        buttonDel->setText(QApplication::translate("surgicalNotes", "...", nullptr));
        buttonEdit->setText(QApplication::translate("surgicalNotes", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class surgicalNotes: public Ui_surgicalNotes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SURGICALNOTES_H
