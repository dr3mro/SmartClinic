/********************************************************************************
** Form generated from reading UI file 'notifications.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTIFICATIONS_H
#define UI_NOTIFICATIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_notifications
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget;

    void setupUi(QDialog *notifications)
    {
        if (notifications->objectName().isEmpty())
            notifications->setObjectName(QString::fromUtf8("notifications"));
        notifications->resize(239, 424);
        gridLayout = new QGridLayout(notifications);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(notifications);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setAlternatingRowColors(false);
        listWidget->setProperty("isWrapping", QVariant(false));
        listWidget->setWordWrap(false);

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);


        retranslateUi(notifications);

        QMetaObject::connectSlotsByName(notifications);
    } // setupUi

    void retranslateUi(QDialog *notifications)
    {
        notifications->setWindowTitle(QApplication::translate("notifications", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class notifications: public Ui_notifications {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTIFICATIONS_H
