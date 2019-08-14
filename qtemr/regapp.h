#ifndef REGAPP_H
#define REGAPP_H

#include <QObject>
#include <QtCore>
#include <QNetworkInterface>
#include <QFile>
#include <QList>
#include <QSettings>
#include "globalvariables.h"
#include "email.h"

class regApp : public QObject
{
    Q_OBJECT

public:
    explicit regApp(QObject *parent = nullptr);
    QString genDeviceID();
    QString generate_serial_number(QString unique_device_id);
    bool save_reg_data(QString enetered_serial_number);
    QString read_reg_data();
    bool compare_reg_data();
    bool check_eval_copy();
    void evaluate();
    QString md5Crypt(QByteArray &code);
    QString trialCrypted();
    QByteArray smuggle14(QString &str);
    void toggleBlock(bool b);
    int eval_max();

    ~regApp();
private:

signals:

public slots:



};

#endif // REGAPP_H
