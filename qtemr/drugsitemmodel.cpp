#include "drugsitemmodel.h"

DrugsItemModel::DrugsItemModel(QObject *parent):QStandardItemModel(parent)
{
    //mDebug() << "drugs Object Created" << this ;
}

DrugsItemModel::~DrugsItemModel()
{
    //mDebug() << "drugs Object Deleted" << this ;
}

bool DrugsItemModel::isThereActiveDrugs()
{
    for ( int i = 0 ; i < rowCount() ; i++ )
    {
         int current = item(i,5)->text().toInt();
         switch (current) {
         case 1:
             return true;
             break;
         default:
             break;
         }
    }
    return false;
}

bool DrugsItemModel::isThereInactiveDrugs()
{
    for ( int i = 0 ; i < rowCount() ; i++ )
    {
         int current = item(i,5)->text().toInt();
         switch (current) {
         case 0:
             return true;
             break;
         default:
             break;
         }
    }
    return false;
}

int DrugsItemModel::getPrintableDrugsCount()
{
    int x = 0;
    for ( int i = 0 ; i < rowCount() ; i++ )
    {
         if(item(i,5)->text().toInt() == 1)
             x++;
    }
    return x;
}
