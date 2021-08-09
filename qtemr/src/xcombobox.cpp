// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "xcombobox.h"

xComboBox::xComboBox(QWidget *parent) //-V730
{
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeReadWrite(bool)));
}

void xComboBox::setUserSpeciality(int us)
{
    userSpeciality = us;
}

void xComboBox::setComboName(QString cn)
{
    comboName = cn;
}

void xComboBox::makeReadWrite(bool rw)
{
    if (comboName == "Gender")
        setEnabled((userSpeciality == dataHelper::Speciality::ObGyn)?  false:rw);
    else if (comboName == "MaritalStatus")
        setEnabled( (userSpeciality != dataHelper::Speciality::Paediatrics) && rw);
    else
        setEnabled(rw);
}
