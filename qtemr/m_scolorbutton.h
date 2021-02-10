// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef M_SCOLORBUTTON_H
#define M_SCOLORBUTTON_H

#include <QObject>
#include <QToolButton>
#include <QLineEdit>

class m_sColorButton : public QToolButton
{
    Q_OBJECT
public:
    explicit m_sColorButton(QWidget *parent=nullptr);
    QColor getSelectedColor();
    void m_connect(QWidget *w, QLineEdit *cBox);
    QLineEdit *colorBox;

private:
    QString selectedColor;
public slots:
    void m_setStyleSheet(QString c);
};

#endif // M_SCOLORBUTTON_H
