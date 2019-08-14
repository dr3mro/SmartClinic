#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QToolButton>
#include <QColor>
#include <QObject>
#include <QMouseEvent>

class colorButton : public QToolButton
{
    Q_OBJECT
public:
    explicit colorButton(QWidget *parent=nullptr);
    void setbackgroundColor();
    QColor getColor();
    bool colorPicker=false;
public slots:
    void setColor(QColor c);
private:
    QColor color;
private slots:
    void colorSelected();
signals:
    void newColorSelected(QColor);
    void leftButtonClicked();
    void midButtonClicked(QColor);
protected:
    void mousePressEvent(QMouseEvent *e);

};

#endif // COLORBUTTON_H
