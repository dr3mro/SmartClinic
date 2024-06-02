// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef REGAPP_H
#define REGAPP_H
#include <QFile>
#include <QList>
#include <QObject>
#include <QProcess>
#include <QSettings>
#include <QtCore>
#include <QtNetwork/QNetworkInterface>

class regApp : public QObject {
  Q_OBJECT

 public:
  explicit regApp(QObject *parent = nullptr);
  QString generate_serial_number(QString unique_device_id);
  bool save_reg_data(QString enetered_serial_number);
  QStringList read_reg_data();
  bool compare_reg_data();
  bool check_eval_copy();
  void evaluate();
  QString md5Crypt(QByteArray &code);
  QString trialCrypted();
  QByteArray smuggle14(QString &str);
  void toggleBlock(bool b);
  int eval_max();
  QString getDeviceID();

  ~regApp();

 private:
  QString DeviceID;

 signals:

 public slots:
};

#endif  // REGAPP_H
