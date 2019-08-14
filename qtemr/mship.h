#ifndef MSHIP_H
#define MSHIP_H

#include <QObject>
#include <QTimer>
#include <QtConcurrent>
#include "wm_mship.h"
#include "internet.h"
#include "email.h"
class mShip : public QObject
{
    Q_OBJECT
public:
    explicit mShip(QObject *parent = nullptr);
    ~mShip();
public slots:
    void run();

signals:
    void showHelloPirate();

private slots:
    void sendMail(QString subject, QString body);
    void work();
private:
    QTimer *timer;
    internet *inet;
    email *mail;
    wm_mShip *worker;
};

#endif // MSHIP_H
