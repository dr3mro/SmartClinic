#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class clickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit clickableLabel(QWidget *parent=nullptr);

signals:
    void rightClicked();
    void leftClicked();
protected:
    void mousePressEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
};

#endif // CLICKABLELABEL_H
