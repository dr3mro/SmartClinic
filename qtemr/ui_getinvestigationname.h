/********************************************************************************
** Form generated from reading UI file 'getinvestigationname.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETINVESTIGATIONNAME_H
#define UI_GETINVESTIGATIONNAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_getInvestigationName
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QToolButton *closeButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *Name;
    QLabel *label_2;
    QLineEdit *Path;
    QGridLayout *gridLayout_4;
    QPushButton *OK;
    QPushButton *Close;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *getInvestigationName)
    {
        if (getInvestigationName->objectName().isEmpty())
            getInvestigationName->setObjectName(QString::fromUtf8("getInvestigationName"));
        getInvestigationName->resize(297, 145);
        gridLayout = new QGridLayout(getInvestigationName);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        closeButton = new QToolButton(getInvestigationName);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        gridLayout_2->addWidget(closeButton, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        label_3 = new QLabel(getInvestigationName);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 2);

        label = new QLabel(getInvestigationName);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(35, 0));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        Name = new QLineEdit(getInvestigationName);
        Name->setObjectName(QString::fromUtf8("Name"));

        gridLayout->addWidget(Name, 1, 1, 1, 1);

        label_2 = new QLabel(getInvestigationName);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(35, 0));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        Path = new QLineEdit(getInvestigationName);
        Path->setObjectName(QString::fromUtf8("Path"));
        Path->setReadOnly(true);

        gridLayout->addWidget(Path, 2, 1, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        OK = new QPushButton(getInvestigationName);
        OK->setObjectName(QString::fromUtf8("OK"));

        gridLayout_4->addWidget(OK, 0, 0, 1, 1);

        Close = new QPushButton(getInvestigationName);
        Close->setObjectName(QString::fromUtf8("Close"));

        gridLayout_4->addWidget(Close, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 2, 1, 1);


        gridLayout->addLayout(gridLayout_4, 3, 0, 1, 2);

        QWidget::setTabOrder(OK, Close);
        QWidget::setTabOrder(Close, closeButton);
        QWidget::setTabOrder(closeButton, Path);

        retranslateUi(getInvestigationName);

        QMetaObject::connectSlotsByName(getInvestigationName);
    } // setupUi

    void retranslateUi(QDialog *getInvestigationName)
    {
        getInvestigationName->setWindowTitle(QApplication::translate("getInvestigationName", "Dialog", nullptr));
        closeButton->setText(QString());
        label_3->setText(QApplication::translate("getInvestigationName", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600;\">Add Media</span></p></body></html>", nullptr));
        label->setText(QApplication::translate("getInvestigationName", "Name:", nullptr));
        label_2->setText(QApplication::translate("getInvestigationName", "Path:", nullptr));
        OK->setText(QApplication::translate("getInvestigationName", "OK", nullptr));
        Close->setText(QApplication::translate("getInvestigationName", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class getInvestigationName: public Ui_getInvestigationName {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETINVESTIGATIONNAME_H
