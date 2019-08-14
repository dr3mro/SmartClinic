#include "patientnumber.h"

patientNumber::patientNumber(QWidget *parent):QLCDNumber(parent)
{

}

void patientNumber::setMax(int max)
{
    maxValue = max;
}

void patientNumber::display(int value)
{
    if ( value == 1  )
    {
        emit enableGoLower(false);
        emit enableGoHigher(true);

    }
    else if ( value >= maxValue)
    {
        emit enableGoLower(true);
        emit enableGoHigher(false);
    }
    else if ( value > 1 && value < maxValue)
    {
        emit enableGoLower(true);
        emit enableGoHigher(true);
    }
    if ( maxValue <= 1 )
    {
        enableGoHigher(false);
        enableGoLower(false);
    }

    QLCDNumber::display(value);
}
