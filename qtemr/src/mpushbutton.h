// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
