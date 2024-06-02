// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "colorpicker.h"

#include "ui_colorpicker.h"

colorPicker::colorPicker(QWidget *parent)
    : QWidget(parent), ui(new Ui::colorPicker) {
  ui->setupUi(this);
  setColors();
  setWindowFlags(Qt::Popup);
  setWindowOpacity(0.9);
}

colorPicker::~colorPicker() { delete ui; }

void colorPicker::setColors() {
  ui->white->setColor(QColor(Qt::white));
  ui->black->setColor(Qt::black);
  ui->red->setColor(Qt::red);
  ui->darkRed->setColor(Qt::darkRed);
  ui->green->setColor(Qt::green);
  ui->darkGreen->setColor(Qt::darkGreen);
  ui->blue->setColor(Qt::blue);
  ui->darkBlue->setColor(Qt::darkBlue);
  ui->cyan->setColor(Qt::cyan);
  ui->darkCyan->setColor(Qt::darkCyan);
  ui->magenta->setColor(Qt::magenta);
  ui->darkMagenta->setColor(Qt::darkMagenta);
  ui->yellow->setColor(Qt::yellow);
  ui->darkYellow->setColor(Qt::darkYellow);
  ui->grey->setColor(Qt::gray);
  ui->lightGrey->setColor(Qt::lightGray);
}

void colorPicker::showEvent(QShowEvent *e) {
  move(QCursor::pos());
  QWidget::showEvent(e);
}
