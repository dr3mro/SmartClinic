// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "vtypecombobox.h"

vTypeComboBox::vTypeComboBox(QWidget* parent):QComboBox(parent)
{

}

void vTypeComboBox::fillContent(int maxFollow)
{
    clear();
    int index = 0;
    QList<VisitTypes::t_visitsType> visitsList = visitTypes.getVisitTypesListByUiIndex();
    for(const VisitTypes::t_visitsType &_vt:visitsList){
        addItem(_vt.name);
        setItemData(index++,visitTypes.getVisitTypesByAlgoIndex(_vt.id).color,Qt::BackgroundRole);
    }
}

void vTypeComboBox::goUp()
{
    if(isEnabled())
        setCurrentIndex(currentIndex()>0? currentIndex()-1:0);
}

void vTypeComboBox::goDown()
{
    if(isEnabled())
        setCurrentIndex(currentIndex() < count()-1? currentIndex()+1:count()-1);
}

