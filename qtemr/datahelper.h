// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
#ifndef DATAHELPER_H
#define DATAHELPER_H

#include <QObject>
#include <QTextDocument>
#include <QDate>
#include <QCoreApplication>
#include <QEventLoop>
#include "mdebug.h"
#include "msettings.h"

class mSettings;

class dataHelper : public QObject
{
    Q_OBJECT
public:
    enum AgeStyle{compact,expanded,normal,printable};
    enum Speciality{InternalMedicine=0,
                    Paediatrics=1,
                    Orthopaedics=2,
                    Surgery=3,
                    ObGyn=4,
                    FamilyMedicine=5,
                    PhysicalTherapy=6};

    explicit dataHelper(QObject *parent = nullptr);
    static QString cleanHTML(QString string);
    static QString julianToAge(int totalDays=0, AgeStyle style=AgeStyle::normal);
    static QString daysToAge(int totalDays = 0);
    static int ageToYear(int totalDays = 0);
    static int julianToYear(int totalDays);
//    static QString numericToVisitType(int x);
    static bool str2bool(QString string);
    static QString bool2String(bool b);
    static int appversiontoint(QByteArray ba);
    static void switchToEasternArabic(QString &str);
    static void delay(const int &delay_msec);
    static bool doubleEqual(double a,double b);
    static QString getVisitType(int visitType,mSettings &settings);
    static void cleanExpanderHTML(QString &expander);
    static void cleanDrugName(QString &drug);
    ~dataHelper();

signals:

public slots:
};

#endif // DATAHELPER_H
