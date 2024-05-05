#include "bios.h"
#include <QString>
#include <QProcess>
#include <QSettings>

Bios &Bios::instance()
{
  static Bios _instance;
  return _instance;
}

QString Bios::getDeviceID()
{
  return DeviceID;
}

Bios::Bios()
{
  QProcess p1;
  QString bios_serial;

  QSettings settings1("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\Bios",QSettings::NativeFormat);
  QString key1 = settings1.value("BaseBoardManufacturer","0").toString().split(" ").at(0);
  QString key2 = settings1.value("BaseBoardProduct","0").toString().split(" ").at(0);


  if (QSysInfo::productVersion().toInt() <= 10){
    p1.start("wmic",QStringList({"bios", "get", "serialnumber"}));
    p1.waitForStarted();
    p1.waitForFinished();
    bios_serial = QString::fromLocal8Bit( p1.readAll()).split("\n").at(1).simplified();
    }else{
    p1.start("powershell",QStringList({"-c","$bios=Get-WmiObject", "win32_bios;", "Write-Host", "$bios.SerialNumber"}));
    p1.waitForStarted();
    p1.waitForFinished();
    bios_serial = QString::fromLocal8Bit( p1.readAll()).split("\n").at(0).simplified();
  }

  if ( bios_serial.length() < 4)
  {
      bios_serial = QString("ABCD");
  }

  DeviceID = QString("%1-%2-%3-%4").arg(key1.left(2),key2.right(2),bios_serial.left(2),bios_serial.right(2)).toUpper();
}

Bios::~Bios()
{

}
