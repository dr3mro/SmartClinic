// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "mfontcombobox.h"

mFontComboBox::mFontComboBox(QWidget *parent) : QFontComboBox(parent) {
  setFontFilters(FontFilter::ScalableFonts | FontFilter::ProportionalFonts |
                 FontFilter::MonospacedFonts);
}
