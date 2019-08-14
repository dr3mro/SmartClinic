#include "m_scolorbutton.h"

m_sColorButton::m_sColorButton(QWidget *)
{

}

void m_sColorButton::m_setStyleSheet(QString c)
{
    setStyleSheet(QString("background-color: %1;"
                          "border-radius:4px;"
                          "border: 1px; "
                          "border-color: black; "
                          "border-style: outset;")
                  .arg(c));
    selectedColor = c;
}

void m_sColorButton::m_connect(QWidget *w,QLineEdit *cBox)
{
    colorBox = cBox;
    connect ( this,SIGNAL(clicked(bool)),w,SLOT(buttonSetColor()));
    connect ( colorBox,SIGNAL(textChanged(QString)),this,SLOT(m_setStyleSheet(QString)));
}

QColor m_sColorButton::getSelectedColor()
{
    return QColor(selectedColor);
}

