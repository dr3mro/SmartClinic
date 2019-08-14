/********************************************************************************
** Form generated from reading UI file 'massistant.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASSISTANT_H
#define UI_MASSISTANT_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "mcashtableview.h"
#include "switch.h"

QT_BEGIN_NAMESPACE

class Ui_mAssistant
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QToolButton *closeButton;
    QTabWidget *mAssistantTabWidget;
    QWidget *agenda;
    QGridLayout *gridLayout_3;
    QCalendarWidget *agendaCalendar;
    QTableView *agendaTableView;
    QLabel *percentage;
    QSpacerItem *verticalSpacer_2;
    QWidget *cash;
    QGridLayout *gridLayout_6;
    QWidget *widget;
    QGridLayout *gridLayout_4;
    QTimeEdit *fromTime;
    QDateEdit *toDate;
    QLabel *fromLabel;
    QToolButton *goButton;
    QTimeEdit *toTime;
    QLabel *toLabel;
    QDateEdit *fromDate;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QCalendarWidget *cashCalendar;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QLineEdit *SUMlineEdit;
    QLabel *label;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QTableView *calcTableView;
    QLabel *label_4;
    QPushButton *btnCheckout;
    QSpacerItem *horizontalSpacer_6;
    mCashTableView *cashTableView;
    Switch *cbSinceLastCheckout;

    void setupUi(QDialog *mAssistant)
    {
        if (mAssistant->objectName().isEmpty())
            mAssistant->setObjectName(QString::fromUtf8("mAssistant"));
        mAssistant->resize(800, 560);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mAssistant->sizePolicy().hasHeightForWidth());
        mAssistant->setSizePolicy(sizePolicy);
        mAssistant->setMinimumSize(QSize(800, 560));
        mAssistant->setMaximumSize(QSize(1024, 16777215));
        gridLayout = new QGridLayout(mAssistant);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(mAssistant);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        closeButton = new QToolButton(mAssistant);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout->addWidget(closeButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        mAssistantTabWidget = new QTabWidget(mAssistant);
        mAssistantTabWidget->setObjectName(QString::fromUtf8("mAssistantTabWidget"));
        mAssistantTabWidget->setTabShape(QTabWidget::Rounded);
        mAssistantTabWidget->setTabBarAutoHide(false);
        agenda = new QWidget();
        agenda->setObjectName(QString::fromUtf8("agenda"));
        gridLayout_3 = new QGridLayout(agenda);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        agendaCalendar = new QCalendarWidget(agenda);
        agendaCalendar->setObjectName(QString::fromUtf8("agendaCalendar"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(agendaCalendar->sizePolicy().hasHeightForWidth());
        agendaCalendar->setSizePolicy(sizePolicy1);
        agendaCalendar->setStyleSheet(QString::fromUtf8("font: 8pt \"MS Shell Dlg 2\";"));
        agendaCalendar->setMinimumDate(QDate(2000, 1, 1));
        agendaCalendar->setMaximumDate(QDate(2100, 12, 31));
        agendaCalendar->setFirstDayOfWeek(Qt::Saturday);
        agendaCalendar->setGridVisible(true);
        agendaCalendar->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
        agendaCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        gridLayout_3->addWidget(agendaCalendar, 0, 0, 1, 1);

        agendaTableView = new QTableView(agenda);
        agendaTableView->setObjectName(QString::fromUtf8("agendaTableView"));
        agendaTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        agendaTableView->setTabKeyNavigation(true);
        agendaTableView->setProperty("showDropIndicator", QVariant(false));
        agendaTableView->setAlternatingRowColors(true);
        agendaTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        agendaTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        agendaTableView->setGridStyle(Qt::DotLine);
        agendaTableView->setSortingEnabled(true);
        agendaTableView->setWordWrap(false);
        agendaTableView->setCornerButtonEnabled(true);
        agendaTableView->horizontalHeader()->setVisible(false);
        agendaTableView->horizontalHeader()->setMinimumSectionSize(20);
        agendaTableView->verticalHeader()->setVisible(false);
        agendaTableView->verticalHeader()->setMinimumSectionSize(20);
        agendaTableView->verticalHeader()->setDefaultSectionSize(20);
        agendaTableView->verticalHeader()->setHighlightSections(true);

        gridLayout_3->addWidget(agendaTableView, 0, 1, 4, 1);

        percentage = new QLabel(agenda);
        percentage->setObjectName(QString::fromUtf8("percentage"));
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        percentage->setFont(font);
        percentage->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(percentage, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 1, 0, 1, 1);

        mAssistantTabWidget->addTab(agenda, QString());
        cash = new QWidget();
        cash->setObjectName(QString::fromUtf8("cash"));
        gridLayout_6 = new QGridLayout(cash);
        gridLayout_6->setSpacing(1);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(3, 3, 3, 3);
        widget = new QWidget(cash);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        widget->setStyleSheet(QString::fromUtf8("font: 10pt \"MS Shell Dlg 2\";"));
        gridLayout_4 = new QGridLayout(widget);
        gridLayout_4->setSpacing(1);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(1, 1, 1, 1);
        fromTime = new QTimeEdit(widget);
        fromTime->setObjectName(QString::fromUtf8("fromTime"));
        fromTime->setButtonSymbols(QAbstractSpinBox::PlusMinus);

        gridLayout_4->addWidget(fromTime, 0, 3, 1, 1);

        toDate = new QDateEdit(widget);
        toDate->setObjectName(QString::fromUtf8("toDate"));
        toDate->setProperty("showGroupSeparator", QVariant(false));
        toDate->setMinimumDate(QDate(2010, 1, 1));
        toDate->setCalendarPopup(true);

        gridLayout_4->addWidget(toDate, 0, 7, 1, 1);

        fromLabel = new QLabel(widget);
        fromLabel->setObjectName(QString::fromUtf8("fromLabel"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        fromLabel->setFont(font1);
        fromLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(fromLabel, 0, 1, 1, 1);

        goButton = new QToolButton(widget);
        goButton->setObjectName(QString::fromUtf8("goButton"));

        gridLayout_4->addWidget(goButton, 0, 9, 1, 1);

        toTime = new QTimeEdit(widget);
        toTime->setObjectName(QString::fromUtf8("toTime"));
        toTime->setButtonSymbols(QAbstractSpinBox::PlusMinus);

        gridLayout_4->addWidget(toTime, 0, 8, 1, 1);

        toLabel = new QLabel(widget);
        toLabel->setObjectName(QString::fromUtf8("toLabel"));
        toLabel->setFont(font1);
        toLabel->setStyleSheet(QString::fromUtf8(""));
        toLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(toLabel, 0, 5, 1, 1);

        fromDate = new QDateEdit(widget);
        fromDate->setObjectName(QString::fromUtf8("fromDate"));
        fromDate->setMinimumDate(QDate(2010, 1, 1));
        fromDate->setCalendarPopup(true);

        gridLayout_4->addWidget(fromDate, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 0, 4, 1, 1);


        gridLayout_6->addWidget(widget, 0, 1, 1, 5);

        frame = new QFrame(cash);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(250, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(1, 1, 1, 1);
        cashCalendar = new QCalendarWidget(frame);
        cashCalendar->setObjectName(QString::fromUtf8("cashCalendar"));
        sizePolicy1.setHeightForWidth(cashCalendar->sizePolicy().hasHeightForWidth());
        cashCalendar->setSizePolicy(sizePolicy1);
        cashCalendar->setStyleSheet(QString::fromUtf8("font: 8pt \"MS Shell Dlg 2\";"));
        cashCalendar->setMinimumDate(QDate(2000, 1, 1));
        cashCalendar->setMaximumDate(QDate(2100, 1, 1));
        cashCalendar->setFirstDayOfWeek(Qt::Saturday);
        cashCalendar->setGridVisible(true);
        cashCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        cashCalendar->setNavigationBarVisible(true);
        cashCalendar->setDateEditEnabled(false);

        gridLayout_2->addWidget(cashCalendar, 1, 0, 1, 1);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setSpacing(1);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        SUMlineEdit = new QLineEdit(groupBox);
        SUMlineEdit->setObjectName(QString::fromUtf8("SUMlineEdit"));
        sizePolicy1.setHeightForWidth(SUMlineEdit->sizePolicy().hasHeightForWidth());
        SUMlineEdit->setSizePolicy(sizePolicy1);
        SUMlineEdit->setMaximumSize(QSize(75, 16777215));
        SUMlineEdit->setAlignment(Qt::AlignCenter);
        SUMlineEdit->setReadOnly(true);

        gridLayout_5->addWidget(SUMlineEdit, 1, 3, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_5->addWidget(label, 1, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(12, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_5, 1, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(35, 0));
        label_2->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_5->addWidget(label_2, 1, 5, 1, 1);

        calcTableView = new QTableView(groupBox);
        calcTableView->setObjectName(QString::fromUtf8("calcTableView"));
        sizePolicy3.setHeightForWidth(calcTableView->sizePolicy().hasHeightForWidth());
        calcTableView->setSizePolicy(sizePolicy3);
        calcTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        calcTableView->setSelectionMode(QAbstractItemView::NoSelection);
        calcTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        calcTableView->setGridStyle(Qt::DotLine);
        calcTableView->horizontalHeader()->setMinimumSectionSize(20);
        calcTableView->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        calcTableView->verticalHeader()->setMinimumSectionSize(20);
        calcTableView->verticalHeader()->setDefaultSectionSize(23);

        gridLayout_5->addWidget(calcTableView, 0, 0, 1, 6);


        gridLayout_2->addWidget(groupBox, 2, 0, 1, 1);


        gridLayout_6->addWidget(frame, 0, 0, 4, 1);

        label_4 = new QLabel(cash);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_6->addWidget(label_4, 3, 3, 1, 1);

        btnCheckout = new QPushButton(cash);
        btnCheckout->setObjectName(QString::fromUtf8("btnCheckout"));
        sizePolicy1.setHeightForWidth(btnCheckout->sizePolicy().hasHeightForWidth());
        btnCheckout->setSizePolicy(sizePolicy1);
        btnCheckout->setCheckable(false);
        btnCheckout->setFlat(false);

        gridLayout_6->addWidget(btnCheckout, 3, 5, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_6, 3, 4, 1, 1);

        cashTableView = new mCashTableView(cash);
        cashTableView->setObjectName(QString::fromUtf8("cashTableView"));
        sizePolicy3.setHeightForWidth(cashTableView->sizePolicy().hasHeightForWidth());
        cashTableView->setSizePolicy(sizePolicy3);
        cashTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        cashTableView->setAlternatingRowColors(true);
        cashTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        cashTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        cashTableView->setGridStyle(Qt::DotLine);
        cashTableView->setSortingEnabled(true);
        cashTableView->horizontalHeader()->setMinimumSectionSize(20);
        cashTableView->verticalHeader()->setMinimumSectionSize(20);
        cashTableView->verticalHeader()->setDefaultSectionSize(20);

        gridLayout_6->addWidget(cashTableView, 1, 1, 2, 5);

        cbSinceLastCheckout = new Switch(cash);
        cbSinceLastCheckout->setObjectName(QString::fromUtf8("cbSinceLastCheckout"));

        gridLayout_6->addWidget(cbSinceLastCheckout, 3, 2, 1, 1);

        mAssistantTabWidget->addTab(cash, QString());

        gridLayout->addWidget(mAssistantTabWidget, 1, 0, 1, 1);


        retranslateUi(mAssistant);

        mAssistantTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mAssistant);
    } // setupUi

    void retranslateUi(QDialog *mAssistant)
    {
        mAssistant->setWindowTitle(QApplication::translate("mAssistant", "Dialog", nullptr));
        label_3->setText(QApplication::translate("mAssistant", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">My Assistant</span></p></body></html>", nullptr));
        closeButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        closeButton->setShortcut(QApplication::translate("mAssistant", "Esc", nullptr));
#endif // QT_NO_SHORTCUT
        percentage->setText(QApplication::translate("mAssistant", "0.00%", nullptr));
        mAssistantTabWidget->setTabText(mAssistantTabWidget->indexOf(agenda), QApplication::translate("mAssistant", "Agenda", nullptr));
        fromTime->setDisplayFormat(QApplication::translate("mAssistant", "hh:mm AP", nullptr));
        toDate->setDisplayFormat(QApplication::translate("mAssistant", "dd/MM/yyyy", nullptr));
        fromLabel->setText(QApplication::translate("mAssistant", "<html><head/><body><p><span style=\" font-weight:600;\">From:</span></p></body></html>", nullptr));
        goButton->setText(QApplication::translate("mAssistant", "Go!", nullptr));
        toTime->setDisplayFormat(QApplication::translate("mAssistant", "hh:mm AP", nullptr));
        toLabel->setText(QApplication::translate("mAssistant", "<html><head/><body><p><span style=\" font-weight:600;\">To:</span></p></body></html>", nullptr));
        fromDate->setDisplayFormat(QApplication::translate("mAssistant", "dd/MM/yyyy", nullptr));
        groupBox->setTitle(QApplication::translate("mAssistant", "Calculations", nullptr));
        label->setText(QApplication::translate("mAssistant", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">TOTAL</span></p></body></html>", nullptr));
        label_2->setText(QApplication::translate("mAssistant", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">    EGP</span></p></body></html>", nullptr));
        label_4->setText(QApplication::translate("mAssistant", "View Register since last check out point", nullptr));
        btnCheckout->setText(QApplication::translate("mAssistant", "Check out", nullptr));
#ifndef QT_NO_TOOLTIP
        cashTableView->setToolTip(QApplication::translate("mAssistant", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        cbSinceLastCheckout->setText(QString());
        mAssistantTabWidget->setTabText(mAssistantTabWidget->indexOf(cash), QApplication::translate("mAssistant", "My Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mAssistant: public Ui_mAssistant {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASSISTANT_H
