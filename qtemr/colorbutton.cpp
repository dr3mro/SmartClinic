#include "colorbutton.h"

colorButton::colorButton(QWidget *parent):QToolButton(parent)
{}

void colorButton::setColor(QColor c)
{
    setText("");
    color = c;
    setbackgroundColor();
}

void colorButton::setbackgroundColor()
{
    setStyleSheet(QString("background-color: %1;").arg(color.name()));
}

QColor colorButton::getColor()
{
    return color;
}

void colorButton::colorSelected()
{
    emit newColorSelected(color);
}

void colorButton::mousePressEvent(QMouseEvent *e)
{
    if (! colorPicker )
    {
        if ( e->button() == Qt::LeftButton)
            emit leftButtonClicked();
        else if ( e->button() == Qt::MiddleButton)
            emit midButtonClicked(color);
    }
    else if ( e->modifiers() == Qt::CTRL && color == Qt::white)
    {
        emit newColorSelected(Qt::transparent);
        parentWidget()->hide();
    }
    QToolButton::mousePressEvent(e);
}

