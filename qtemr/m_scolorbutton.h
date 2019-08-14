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
