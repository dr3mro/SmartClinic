/********************************************************************************
** Form generated from reading UI file 'userpass.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERPASS_H
#define UI_USERPASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_userpass
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *submit_button;
    QSpacerItem *horizontalSpacer;
    QLineEdit *passwordLine;

    void setupUi(QDialog *userpass)
    {
        if (userpass->objectName().isEmpty())
            userpass->setObjectName(QString::fromUtf8("userpass"));
        userpass->setWindowModality(Qt::ApplicationModal);
        userpass->resize(196, 95);
        userpass->setFocusPolicy(Qt::StrongFocus);
        userpass->setContextMenuPolicy(Qt::NoContextMenu);
        userpass->setWindowOpacity(1.000000000000000);
        userpass->setModal(true);
        gridLayout = new QGridLayout(userpass);
        gridLayout->setSpacing(9);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout->setContentsMargins(-1, 9, -1, -1);
        label = new QLabel(userpass);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        submit_button = new QPushButton(userpass);
        submit_button->setObjectName(QString::fromUtf8("submit_button"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(submit_button->sizePolicy().hasHeightForWidth());
        submit_button->setSizePolicy(sizePolicy);

        gridLayout->addWidget(submit_button, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

        passwordLine = new QLineEdit(userpass);
        passwordLine->setObjectName(QString::fromUtf8("passwordLine"));
        passwordLine->setEchoMode(QLineEdit::Password);
        passwordLine->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(passwordLine, 1, 0, 1, 2);


        retranslateUi(userpass);

        QMetaObject::connectSlotsByName(userpass);
    } // setupUi

    void retranslateUi(QDialog *userpass)
    {
        userpass->setWindowTitle(QApplication::translate("userpass", "Password", nullptr));
        label->setText(QApplication::translate("userpass", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt;\">Please Enter your </span><span style=\" font-size:10pt; font-weight:600;\">PASSWORD</span></p></body></html>", nullptr));
        submit_button->setText(QApplication::translate("userpass", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userpass: public Ui_userpass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPASS_H
