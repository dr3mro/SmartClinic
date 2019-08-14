#ifndef MPUSHBUTTON_H
#define MPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

class mPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit mPushButton(QWidget *parent=nullptr);
private slots:
    void makeReadWrite(bool rw);
};

#endif // MPUSHBUTTON_H
