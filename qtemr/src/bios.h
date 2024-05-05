#ifndef BIOS_H
#define BIOS_H

#include <QObject>

class Bios : public QObject
{
  Q_OBJECT
public:
  static Bios &instance();
  QString getDeviceID();
private:
  Bios();
  Bios(const Bios&);
  ~Bios();
  Bios & operator = (const Bios&);
  QString DeviceID;
signals:

};

#endif // BIOS_H
