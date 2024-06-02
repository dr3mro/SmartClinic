// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QColor>
#include <QMouseEvent>
#include <QObject>
#include <QToolButton>

class colorButton : public QToolButton {
  Q_OBJECT
 public:
  explicit colorButton(QWidget *parent = nullptr);
  void setbackgroundColor();
  QColor getColor();
  bool colorPicker = false;
 public slots:
  void setColor(const QColor &c);

 private:
  QColor color;
 private slots:
  void colorSelected();
 signals:
  void newColorSelected(const QColor &);
  void leftButtonClicked();
  void midButtonClicked(const QColor &);

 protected:
  void mousePressEvent(QMouseEvent *e);
};

#endif  // COLORBUTTON_H
