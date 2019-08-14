#ifndef XCHECKBOX_H
#define XCHECKBOX_H

#include <QObject>
#include <QCheckBox>

class xCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit xCheckBox(QWidget *parent=nullptr);
public slots:
    void makeEditable(bool b);
};

#endif // XCHECKBOX_H
