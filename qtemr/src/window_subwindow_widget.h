// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef WINDOW_SUBWINDOW_WIDGET_H
#define WINDOW_SUBWINDOW_WIDGET_H

#include "mstyler.h"
#include "styleeditorwidget.h"

namespace Ui {
class window_subwindow_widget;
}

class window_subwindow_widget : public StyleEditorWidget {
  Q_OBJECT

 public:
  explicit window_subwindow_widget(QWidget *parent = nullptr);
  ~window_subwindow_widget();
  mStyler::Window getStyle();
  void putStyle(const mStyler::Window &window);

 private:
  Ui::window_subwindow_widget *ui;
};

#endif  // WINDOW_SUBWINDOW_WIDGET_H
