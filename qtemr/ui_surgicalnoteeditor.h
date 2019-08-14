/********************************************************************************
** Form generated from reading UI file 'surgicalnoteeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SURGICALNOTEEDITOR_H
#define UI_SURGICALNOTEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include "genericlineedit.h"
#include "textedit.h"

QT_BEGIN_NAMESPACE

class Ui_surgicalNoteEditor
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QDateEdit *OperationDate;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    genericLineEdit *operation;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QSplitter *splitter;
    QLabel *label_4;
    QComboBox *Templates;
    QSpacerItem *horizontalSpacer_5;
    TextEdit *report;
    QPushButton *buttonSave;
    QPushButton *buttonClose;
    QPushButton *buttonClear;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *surgicalNoteEditor)
    {
        if (surgicalNoteEditor->objectName().isEmpty())
            surgicalNoteEditor->setObjectName(QString::fromUtf8("surgicalNoteEditor"));
        surgicalNoteEditor->resize(368, 425);
        gridLayout = new QGridLayout(surgicalNoteEditor);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(surgicalNoteEditor);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        OperationDate = new QDateEdit(surgicalNoteEditor);
        OperationDate->setObjectName(QString::fromUtf8("OperationDate"));
        OperationDate->setCalendarPopup(true);

        gridLayout->addWidget(OperationDate, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 3);

        label_2 = new QLabel(surgicalNoteEditor);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        operation = new genericLineEdit(surgicalNoteEditor);
        operation->setObjectName(QString::fromUtf8("operation"));

        gridLayout->addWidget(operation, 1, 1, 1, 2);

        label_3 = new QLabel(surgicalNoteEditor);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(163, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 1, 1, 2);

        splitter = new QSplitter(surgicalNoteEditor);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(splitter);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        splitter->addWidget(label_4);
        Templates = new QComboBox(splitter);
        Templates->addItem(QString());
        Templates->addItem(QString());
        Templates->setObjectName(QString::fromUtf8("Templates"));
        splitter->addWidget(Templates);

        gridLayout->addWidget(splitter, 2, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(26, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 4, 1, 1);

        report = new TextEdit(surgicalNoteEditor);
        report->setObjectName(QString::fromUtf8("report"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        report->setFont(font);

        gridLayout->addWidget(report, 3, 0, 1, 5);

        buttonSave = new QPushButton(surgicalNoteEditor);
        buttonSave->setObjectName(QString::fromUtf8("buttonSave"));

        gridLayout->addWidget(buttonSave, 4, 0, 1, 1);

        buttonClose = new QPushButton(surgicalNoteEditor);
        buttonClose->setObjectName(QString::fromUtf8("buttonClose"));

        gridLayout->addWidget(buttonClose, 4, 1, 1, 1);

        buttonClear = new QPushButton(surgicalNoteEditor);
        buttonClear->setObjectName(QString::fromUtf8("buttonClear"));

        gridLayout->addWidget(buttonClear, 4, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 3, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(98, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 3, 1, 2);


        retranslateUi(surgicalNoteEditor);

        QMetaObject::connectSlotsByName(surgicalNoteEditor);
    } // setupUi

    void retranslateUi(QDialog *surgicalNoteEditor)
    {
        surgicalNoteEditor->setWindowTitle(QApplication::translate("surgicalNoteEditor", "Add New Surgical Note", nullptr));
        label->setText(QApplication::translate("surgicalNoteEditor", "Date:", nullptr));
        OperationDate->setDisplayFormat(QApplication::translate("surgicalNoteEditor", "dd/MM/yyyy", nullptr));
        label_2->setText(QApplication::translate("surgicalNoteEditor", "Operation:", nullptr));
        label_3->setText(QApplication::translate("surgicalNoteEditor", "Report:", nullptr));
        label_4->setText(QApplication::translate("surgicalNoteEditor", "templates", nullptr));
        Templates->setItemText(0, QApplication::translate("surgicalNoteEditor", "-", nullptr));
        Templates->setItemText(1, QApplication::translate("surgicalNoteEditor", "C/S", nullptr));

        buttonSave->setText(QApplication::translate("surgicalNoteEditor", "Save", nullptr));
        buttonClose->setText(QApplication::translate("surgicalNoteEditor", "Close", nullptr));
        buttonClear->setText(QApplication::translate("surgicalNoteEditor", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class surgicalNoteEditor: public Ui_surgicalNoteEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SURGICALNOTEEDITOR_H
