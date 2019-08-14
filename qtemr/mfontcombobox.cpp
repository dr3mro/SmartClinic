#include "mfontcombobox.h"

mFontComboBox::mFontComboBox(QWidget *parent):QFontComboBox(parent)
{
    setFontFilters(FontFilter::ScalableFonts | FontFilter::ProportionalFonts | FontFilter::MonospacedFonts );
}
