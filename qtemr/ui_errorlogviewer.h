/********************************************************************************
** Form generated from reading UI file 'errorlogviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORLOGVIEWER_H
#define UI_ERRORLOGVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_errorLogViewer
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *delButton;
    QToolButton *playPause;
    QToolButton *refresh;
    QToolButton *sendReport;
    QLabel *status;
    QSpacerItem *horizontalSpacer;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *errorLogViewer)
    {
        if (errorLogViewer->objectName().isEmpty())
            errorLogViewer->setObjectName(QString::fromUtf8("errorLogViewer"));
        errorLogViewer->setWindowModality(Qt::NonModal);
        errorLogViewer->resize(627, 383);
        gridLayout = new QGridLayout(errorLogViewer);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        delButton = new QToolButton(errorLogViewer);
        delButton->setObjectName(QString::fromUtf8("delButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ionicons/trash"), QSize(), QIcon::Normal, QIcon::Off);
        delButton->setIcon(icon);

        horizontalLayout->addWidget(delButton);

        playPause = new QToolButton(errorLogViewer);
        playPause->setObjectName(QString::fromUtf8("playPause"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ionicons/pause"), QSize(), QIcon::Normal, QIcon::Off);
        playPause->setIcon(icon1);
        playPause->setCheckable(false);
        playPause->setAutoRaise(false);

        horizontalLayout->addWidget(playPause);

        refresh = new QToolButton(errorLogViewer);
        refresh->setObjectName(QString::fromUtf8("refresh"));
        refresh->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Graphics/refresh"), QSize(), QIcon::Normal, QIcon::Off);
        refresh->setIcon(icon2);

        horizontalLayout->addWidget(refresh);

        sendReport = new QToolButton(errorLogViewer);
        sendReport->setObjectName(QString::fromUtf8("sendReport"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Graphics/message"), QSize(), QIcon::Normal, QIcon::Off);
        sendReport->setIcon(icon3);

        horizontalLayout->addWidget(sendReport);

        status = new QLabel(errorLogViewer);
        status->setObjectName(QString::fromUtf8("status"));

        horizontalLayout->addWidget(status);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(errorLogViewer);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setStyleSheet(QString::fromUtf8("font: 11pt \"Consolas\";"));
        plainTextEdit->setUndoRedoEnabled(false);
        plainTextEdit->setReadOnly(true);
        plainTextEdit->setCenterOnScroll(false);

        gridLayout->addWidget(plainTextEdit, 1, 0, 1, 2);


        retranslateUi(errorLogViewer);

        QMetaObject::connectSlotsByName(errorLogViewer);
    } // setupUi

    void retranslateUi(QWidget *errorLogViewer)
    {
        errorLogViewer->setWindowTitle(QApplication::translate("errorLogViewer", "System Messages Viewer", nullptr));
#ifndef QT_NO_TOOLTIP
        delButton->setToolTip(QApplication::translate("errorLogViewer", "<html><head/><body><p>Clear Log</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        delButton->setText(QApplication::translate("errorLogViewer", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        playPause->setToolTip(QApplication::translate("errorLogViewer", "<html><head/><body><p>Pause</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        playPause->setText(QString());
#ifndef QT_NO_TOOLTIP
        refresh->setToolTip(QApplication::translate("errorLogViewer", "<html><head/><body><p>Refresh</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        refresh->setText(QString());
#ifndef QT_NO_TOOLTIP
        sendReport->setToolTip(QApplication::translate("errorLogViewer", "<html><head/><body><p>Send the text below to Smart Clinic developer</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        sendReport->setText(QApplication::translate("errorLogViewer", "...", nullptr));
        status->setText(QString());
        plainTextEdit->setPlaceholderText(QApplication::translate("errorLogViewer", "Hoarrrrray no errors...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class errorLogViewer: public Ui_errorLogViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORLOGVIEWER_H
