// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BUTTON_INPUT_WIDGET_H
#define BUTTON_INPUT_WIDGET_H

#include "mstyler.h"
#include "styleeditorwidget.h"

namespace Ui {
class button_input_widget;
}

class button_input_widget : public StyleEditorWidget {
  Q_OBJECT

 public:
  explicit button_input_widget(QWidget *parent = nullptr);
  ~button_input_widget();
  mStyler::Element getStyle();
  void putStyle(const mStyler::Element &element);

 private:
  Ui::button_input_widget *ui;
};

#endif  // BUTTON_INPUT_WIDGET_H
