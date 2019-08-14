#ifndef SINGLEINSTANCE_H
#define SINGLEINSTANCE_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include "mdebug.h"

class SingleInstance : public QObject
{
    Q_OBJECT
public:
    explicit SingleInstance(QObject *parent = nullptr);
    ~SingleInstance();
    void listen(QString name);
    bool hasPrevious(QString name, QStringList arg);

signals:

    void newInstance();
    void doAction();


public slots:

    void newConnection();
    void readyRead();

private:
    QLocalSocket* mSocket;
    QLocalServer mServer;
};

#endif // SINGLEINSTANCE_H
