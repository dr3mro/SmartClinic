// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef LIST_STYLE_WIDGET_H
#define LIST_STYLE_WIDGET_H

#include "mstyler.h"
#include "styleeditorwidget.h"
namespace Ui {
class List_style_widget;
}

class List_style_widget : public StyleEditorWidget {
  Q_OBJECT

 public:
  explicit List_style_widget(QWidget *parent = nullptr);
  ~List_style_widget();
  mStyler::List getStyle();
  void putStyle(const mStyler::List &list);

 private:
  Ui::List_style_widget *ui;
};

#endif  // LIST_STYLE_WIDGET_H
