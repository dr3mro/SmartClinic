#include "xcombobox.h"

xComboBox::xComboBox(QWidget *parent)
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
