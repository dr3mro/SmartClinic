/********************************************************************************
** Form generated from reading UI file 'mrequestviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MREQUESTVIEWER_H
#define UI_MREQUESTVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "mgraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_mRequestViewer
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    mGraphicsView *graphicsView;

    void setupUi(QWidget *mRequestViewer)
    {
        if (mRequestViewer->objectName().isEmpty())
            mRequestViewer->setObjectName(QString::fromUtf8("mRequestViewer"));
        mRequestViewer->setWindowModality(Qt::ApplicationModal);
        mRequestViewer->resize(378, 244);
        mRequestViewer->setWindowOpacity(1.000000000000000);
        mRequestViewer->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0);"));
        gridLayout_2 = new QGridLayout(mRequestViewer);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new mGraphicsView(mRequestViewer);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setFrameShape(QFrame::NoFrame);
        graphicsView->setLineWidth(0);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(mRequestViewer);

        QMetaObject::connectSlotsByName(mRequestViewer);
    } // setupUi

    void retranslateUi(QWidget *mRequestViewer)
    {
        mRequestViewer->setWindowTitle(QApplication::translate("mRequestViewer", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mRequestViewer: public Ui_mRequestViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MREQUESTVIEWER_H
