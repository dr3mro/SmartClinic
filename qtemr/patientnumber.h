#ifndef PATIENTNUMBER_H
#define PATIENTNUMBER_H

#include <QObject>
#include <QLCDNumber>


class patientNumber : public QLCDNumber
{
    Q_OBJECT
public:
    explicit patientNumber(QWidget *parent=nullptr);
    void setMax(int max);

public slots:
    void display(int value);

private:
    int maxValue;

signals:
    void enableGoLower(bool);
    void enableGoHigher(bool);
};

#endif // PATIENTNUMBER_H
