#ifndef VITALBOX_H
#define VITALBOX_H

#include <QObject>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QString>
#include <datahelper.h>
#include <msettings.h>

class vitalBox : public QLineEdit
{

    Q_OBJECT
public:
    explicit vitalBox(QWidget *parent=nullptr);
    ~vitalBox();
    void setRegExpValidator(QString regExpString);
    void setVitalType(int vt, int sp);

private:
    QRegExpValidator *validator;
    int speciality;
    int vitaltype;
    mSettings::lineStyle style;

private slots:
    void pulseRate(QString pulserate);
    void bloodpressure(QString bloodpressure);
    void respiratoryRate(QString respiratoryrate);
    void temperature(QString temperature);
    void createStyles(mSettings & settings);
public slots:
    void makeEditable(bool b);
};

#endif // VITALBOX_H
