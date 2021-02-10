// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>

namespace Ui {
class colorPicker;
}

class colorPicker : public QWidget
{
    Q_OBJECT

public:
    explicit colorPicker(QWidget *parent = nullptr);
    ~colorPicker();
public slots:

private:
    Ui::colorPicker *ui;
    void setColors();
signals:
    void newColor(QColor);
protected:
    void showEvent(QShowEvent *e);

};

#endif // COLORPICKER_H
