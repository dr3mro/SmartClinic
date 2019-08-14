#ifndef XLINEEDIT_H
#define XLINEEDIT_H

#include <QObject>
#include <QLineEdit>


class xLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit xLineEdit(QWidget *parent=nullptr);
public slots:
    void makeReadWrite(bool rw);
};

#endif // XLINEEDIT_H
