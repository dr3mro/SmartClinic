// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "vitalbox.h"

vitalBox::vitalBox(QWidget *parent):QLineEdit(parent),
validator(new QRegExpValidator(this))
{
   connect (parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeEditable(bool)));
   connect (parent->window(),SIGNAL(styleVitals(mSettings&)),this,SLOT(createStyles(mSettings&)));
}

vitalBox::~vitalBox()
{
    delete validator;
}

void vitalBox::setRegExpValidator(QString regExpString)
{
    QRegExp regExp(regExpString);
    validator->setRegExp(regExp);
    setValidator(validator);
}

void vitalBox::setVitalType(int vt,int sp)
{
    vitaltype = vt;
    speciality = sp;
    switch(vitaltype)
    {
    case(0):
        connect(this,SIGNAL(textChanged(QString)),this,SLOT(pulseRate(QString)));
        setStyleSheet(style.normalStylesheet);
        setRegExpValidator("^([0-9][0-9]|[1-3][0-9][0-9]?)$");
        break;
    case(1):
        connect(this,SIGNAL(textChanged(QString)),this,SLOT(bloodpressure(QString)));
        setStyleSheet(style.normalStylesheet);
        setRegExpValidator("^([1-9][0-9]|[1-2][0-9][0-9]|300?)\\/([1-9][0-9]|[1-2][0-9][0-9]?)$");
        break;
    case(2):
        connect(this,SIGNAL(textChanged(QString)),this,SLOT(respiratoryRate(QString)));
        setStyleSheet(style.normalStylesheet);
        setRegExpValidator("^(100|[1-9]?[0-9])$");
        break;
    case(3):
        connect(this,SIGNAL(textChanged(QString)),this,SLOT(temperature(QString)));
        setStyleSheet(style.normalStylesheet);
        setRegExpValidator("^3[5-9][.][0-9]|^4[0-2][.][0-9]$");
        break;
    case(4)://weight
        setRegExpValidator("^[0-9]{1,3}[.][0-9]{0,2}$");
        break;
    case(5)://height
        setRegExpValidator("^[0-9]{1,3}$");
        break;
    case(6)://spo2
        setRegExpValidator("^(100|[1-9]?[0-9])$");
        break;
    default:
        break;
    }
}

void vitalBox::pulseRate(QString pulserate)
{
    if ( speciality != dataHelper::Speciality::InternalMedicine )
        return;
    int pulseRate  = pulserate.toInt();
    if ( pulseRate == 0 )
    {
        setStyleSheet(style.normalStylesheet);
        return;
    }
    if ( pulseRate >=60 && pulseRate <= 100 )
    {
        setStyleSheet(style.normalStylesheet);
        return;
    }
    else if ((pulseRate < 60 && pulseRate > 45) || (pulseRate > 100 && pulseRate <= 150))
    {
        setStyleSheet(style.warningStylesheet);
        return;
    }
    else //if (pulseRate > 150 || pulseRate <= 45)
    {
        setStyleSheet(style.errorStylesheet);
        return;
    }
}

void vitalBox::bloodpressure(QString bloodpressure)
{
    if ( speciality != dataHelper::Speciality::InternalMedicine )
        return;

    if ( bloodpressure.split("/").count() != 2 )
    {
        setStyleSheet(style.normalStylesheet);
        return;
    }

    int systolic  = bloodpressure.split("/").at(0).toInt();
    int diastolic = bloodpressure.split("/").at(1).toInt();

    if ( systolic == 0 || diastolic == 0 )
    {
        setStyleSheet(style.normalStylesheet);
        return;
    }
    else if ( ( systolic >= 100 && systolic <= 120 ) || ( diastolic >= 60 && diastolic <= 80 ))
    {
        setStyleSheet(style.normalStylesheet);
        return;
    }
    else if ( ( systolic > 120 && systolic <= 140 ) || ( diastolic > 80 && diastolic <= 90 ))
    {
        setStyleSheet(style.warningStylesheet);
        return;
    }
    else if ( ( systolic > 140 ) || ( diastolic > 90 ))
    {
        setStyleSheet(style.errorStylesheet);
        return;
    }
    else if ( ( systolic < 100 || diastolic < 60 ) && ( ( systolic > 60 ) || ( diastolic > 50 ) ) )
    {
        setStyleSheet(style.warningStylesheet);
        return;
    }
    else if ( ( systolic < 60 ) || ( diastolic < 30 ))
    {
        setStyleSheet(style.errorStylesheet);
        return;
    }
}

void vitalBox::respiratoryRate(QString respiratoryrate)
{
    if ( speciality != dataHelper::Speciality::InternalMedicine )
        return;
    int respRate  = respiratoryrate.toInt();
    if ( respRate == 0 )
    {
        setStyleSheet(style.normalStylesheet);
        return;
    }
    if ( respRate >=16 && respRate <= 20 )
    {
        setStyleSheet(style.normalStylesheet);
        return;
    }
    else //if ( respRate <16 || respRate > 20)
    {
        setStyleSheet(style.errorStylesheet);
        return;
    }
}

void vitalBox::temperature(QString temperature)
{
    double temp = temperature.toDouble();

    if ( (temp >= 36.8 && temp <= 37.2) || dataHelper::doubleEqual(temp,0) )
    {
        setStyleSheet(style.normalStylesheet);
        return;
    }
    if ( temp > 37.2 && temp <= 38.5 )
    {
        setStyleSheet(style.warningStylesheet);
        return;
    }
    if ( temp > 35.5 && temp < 36.8)
    {
        setStyleSheet(style.warningStylesheet);
        return;
    }
    if ( temp > 38.5 || temp <= 35.5)
    {
        setStyleSheet(style.errorStylesheet);
        return;
    }
}

void vitalBox::makeEditable(bool b)
{
    setReadOnly(!b);
}

void vitalBox::createStyles(mSettings &settings)
{
    style = settings.getLineStylesheet();
}

