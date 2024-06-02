// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "window_subwindow_widget.h"

#include "ui_window_subwindow_widget.h"

window_subwindow_widget::window_subwindow_widget(QWidget *parent)
    : StyleEditorWidget(parent), ui(new Ui::window_subwindow_widget) {
  ui->setupUi(this);
  ui->top_color_button->m_connect(this, ui->top_color_text);
  ui->bottom_color_button->m_connect(this, ui->bottom_color_text);
  ui->border_color_button->m_connect(this, ui->border_color_text);
}

window_subwindow_widget::~window_subwindow_widget() { delete ui; }

mStyler::Window window_subwindow_widget::getStyle() {
  mStyler::Window window;
  window.top_color = ui->top_color_text->text();
  window.bottom_color = ui->bottom_color_text->text();
  window.border_color = ui->border_color_text->text();
  window.border_width = ui->border_width->value();
  window.border_radius = ui->border_radius->value();
  return window;
}

void window_subwindow_widget::putStyle(const mStyler::Window &window) {
  ui->top_color_text->setText(window.top_color);
  ui->bottom_color_text->setText(window.bottom_color);
  ui->border_color_text->setText(window.border_color);
  ui->border_width->setValue(window.border_width);
  ui->border_radius->setValue(window.border_radius);
}
