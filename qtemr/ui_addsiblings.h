/********************************************************************************
** Form generated from reading UI file 'addsiblings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSIBLINGS_H
#define UI_ADDSIBLINGS_H

#include <QtCore/QDate>
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

class Ui_addSiblings
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QPushButton *closeButton;
    QPushButton *addSibling;
    QPushButton *editSibling;
    QDateEdit *dateOfBirth;
    QLabel *label;
    QLabel *label_2;
    QComboBox *gender;
    QComboBox *typeOfDelivery;
    QLabel *label_5;
    QLabel *label_3;
    genericLineEdit *placeOfBirth;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QLabel *label_6;
    QComboBox *state;
    TextEdit *complications;

    void setupUi(QDialog *addSiblings)
    {
        if (addSiblings->objectName().isEmpty())
            addSiblings->setObjectName(QString::fromUtf8("addSiblings"));
        addSiblings->resize(309, 369);
        gridLayout = new QGridLayout(addSiblings);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(addSiblings);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        closeButton = new QPushButton(splitter);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(closeButton->sizePolicy().hasHeightForWidth());
        closeButton->setSizePolicy(sizePolicy);
        splitter->addWidget(closeButton);
        addSibling = new QPushButton(splitter);
        addSibling->setObjectName(QString::fromUtf8("addSibling"));
        sizePolicy.setHeightForWidth(addSibling->sizePolicy().hasHeightForWidth());
        addSibling->setSizePolicy(sizePolicy);
        splitter->addWidget(addSibling);
        editSibling = new QPushButton(splitter);
        editSibling->setObjectName(QString::fromUtf8("editSibling"));
        splitter->addWidget(editSibling);

        gridLayout->addWidget(splitter, 9, 0, 1, 3);

        dateOfBirth = new QDateEdit(addSiblings);
        dateOfBirth->setObjectName(QString::fromUtf8("dateOfBirth"));
        dateOfBirth->setAlignment(Qt::AlignCenter);
        dateOfBirth->setAccelerated(true);
        dateOfBirth->setMaximumDate(QDate(2100, 12, 31));
        dateOfBirth->setMinimumDate(QDate(1900, 9, 14));
        dateOfBirth->setCalendarPopup(true);

        gridLayout->addWidget(dateOfBirth, 0, 1, 1, 1);

        label = new QLabel(addSiblings);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(addSiblings);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        gender = new QComboBox(addSiblings);
        gender->addItem(QString());
        gender->addItem(QString());
        gender->addItem(QString());
        gender->setObjectName(QString::fromUtf8("gender"));

        gridLayout->addWidget(gender, 2, 1, 1, 1);

        typeOfDelivery = new QComboBox(addSiblings);
        typeOfDelivery->addItem(QString());
        typeOfDelivery->addItem(QString());
        typeOfDelivery->addItem(QString());
        typeOfDelivery->setObjectName(QString::fromUtf8("typeOfDelivery"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(typeOfDelivery->sizePolicy().hasHeightForWidth());
        typeOfDelivery->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(typeOfDelivery, 1, 1, 1, 1);

        label_5 = new QLabel(addSiblings);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 7, 0, 1, 1);

        label_3 = new QLabel(addSiblings);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        placeOfBirth = new genericLineEdit(addSiblings);
        placeOfBirth->setObjectName(QString::fromUtf8("placeOfBirth"));

        gridLayout->addWidget(placeOfBirth, 6, 1, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        label_4 = new QLabel(addSiblings);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 6, 0, 1, 1);

        label_6 = new QLabel(addSiblings);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        state = new QComboBox(addSiblings);
        state->addItem(QString());
        state->addItem(QString());
        state->addItem(QString());
        state->addItem(QString());
        state->setObjectName(QString::fromUtf8("state"));
        sizePolicy.setHeightForWidth(state->sizePolicy().hasHeightForWidth());
        state->setSizePolicy(sizePolicy);

        gridLayout->addWidget(state, 3, 1, 1, 1);

        complications = new TextEdit(addSiblings);
        complications->setObjectName(QString::fromUtf8("complications"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(complications->sizePolicy().hasHeightForWidth());
        complications->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(complications, 7, 1, 1, 2);


        retranslateUi(addSiblings);

        QMetaObject::connectSlotsByName(addSiblings);
    } // setupUi

    void retranslateUi(QDialog *addSiblings)
    {
        addSiblings->setWindowTitle(QApplication::translate("addSiblings", "Add Siblings", nullptr));
        closeButton->setText(QApplication::translate("addSiblings", "Close", nullptr));
        addSibling->setText(QApplication::translate("addSiblings", "Add", nullptr));
        editSibling->setText(QApplication::translate("addSiblings", "Apply", nullptr));
        dateOfBirth->setDisplayFormat(QApplication::translate("addSiblings", "dd/MM/yyyy", nullptr));
        label->setText(QApplication::translate("addSiblings", "Date of birth:", nullptr));
        label_2->setText(QApplication::translate("addSiblings", "Type of Delivery", nullptr));
        gender->setItemText(0, QApplication::translate("addSiblings", "Male", nullptr));
        gender->setItemText(1, QApplication::translate("addSiblings", "Female", nullptr));
        gender->setItemText(2, QApplication::translate("addSiblings", "Twins", nullptr));

        typeOfDelivery->setItemText(0, QApplication::translate("addSiblings", "Vaginal", nullptr));
        typeOfDelivery->setItemText(1, QApplication::translate("addSiblings", "C/S", nullptr));
        typeOfDelivery->setItemText(2, QApplication::translate("addSiblings", "D&C", nullptr));

        label_5->setText(QApplication::translate("addSiblings", "Complications", nullptr));
        label_3->setText(QApplication::translate("addSiblings", "Gender", nullptr));
        label_4->setText(QApplication::translate("addSiblings", "Place of Birth", nullptr));
        label_6->setText(QApplication::translate("addSiblings", "Term", nullptr));
        state->setItemText(0, QApplication::translate("addSiblings", "FullTerm", nullptr));
        state->setItemText(1, QApplication::translate("addSiblings", "PreTerm", nullptr));
        state->setItemText(2, QApplication::translate("addSiblings", "Abortion", nullptr));
        state->setItemText(3, QApplication::translate("addSiblings", "IUFD", nullptr));

    } // retranslateUi

};

namespace Ui {
    class addSiblings: public Ui_addSiblings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSIBLINGS_H
