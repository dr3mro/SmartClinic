#include "vtypecombobox.h"

vTypeComboBox::vTypeComboBox(QWidget* )
{

}

void vTypeComboBox::fillContent(int maxFollow)
{
    clear();
    addItem("New Visit");
    for (int x = 1 ; x <= maxFollow; x++)
        addItem(QString("Follow Up %1").arg(x));
    addItem("Free");
}

