// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "styleeditorwidget.h"

StyleEditorWidget::StyleEditorWidget(QWidget *parent) : QWidget(parent) {}

void StyleEditorWidget::buttonSetColor() {
  m_sColorButton *colorButton = dynamic_cast<m_sColorButton *>(sender());
  QColor c = dialog.getColor(colorButton->getSelectedColor(), this,
                             "Select Color", QColorDialog::DontUseNativeDialog);
  if (c.isValid()) {
    colorButton->colorBox->setText(c.name());
    //        colorButton->m_setStyleSheet(c.name());
    //        ui->comboBoxSelectedTheme->setCurrentIndex(0); this to set theme
    //        as custom ..
  }
}
