#ifndef XDATETIMEEDIT_H
#define XDATETIMEEDIT_H

#include <QObject>
#include <QDateTimeEdit>

class xDateTimeEdit : public QDateTimeEdit
{
    Q_OBJECT
public:
    explicit xDateTimeEdit(QWidget *parent=nullptr);
public slots:
    void makeReadWrite(bool rw);
};

#endif // XDATETIMEEDIT_H
