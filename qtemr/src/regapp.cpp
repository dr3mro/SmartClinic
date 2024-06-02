#include "regapp.h"

#include "bios.h"
#include "globalvariables.h"

regApp::regApp(QObject *parent) : QObject(parent) {
  Bios &b = Bios::instance();
  DeviceID = b.getDeviceID();
}

QString regApp::generate_serial_number(QString unique_device_id) {
  QStringList keyList = unique_device_id.split("-");
  QStringList smugList = QString("am-na-mo-os").split("-");
  QStringList bigKey;
  for (int i = 0; i < 4; i++) {
    bigKey << keyList.at(i) << smugList.at(i);
  }
  QByteArray unique_key = bigKey.join("").toUtf8().toBase64();
  QByteArray key = unique_key.toBase64().toHex() +
                   QString("25jan,11").toUtf8().toBase64().toHex();
  QString serialNumber =
      QString(QCryptographicHash::hash((key), QCryptographicHash::Md5).toHex())
          .toUpper();

  QString SN = QString("%1-%2-%3-%4-%5-%6-%7-%8")
                   .arg(serialNumber.left(4), serialNumber.mid(4, 4),
                        serialNumber.mid(8, 4), serialNumber.mid(12, 4),
                        serialNumber.mid(16, 4), serialNumber.mid(20, 4),
                        serialNumber.mid(24, 4), serialNumber.right(4));
  // mDebug() << SN;
  return SN;
}

bool regApp::save_reg_data(QString enetered_serial_number) {
  QFile file("./license.key");
  if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
    QTextStream out(&file);
    QByteArray enetered_serial_number_array = enetered_serial_number.toUtf8();
    QString enetered_serial_number_crypted =
        md5Crypt(enetered_serial_number_array);
    out << '\n' << enetered_serial_number_crypted;
    file.close();
  }

  return true;
}

QStringList regApp::read_reg_data() {
  QStringList reg_data_list;
  QFile file("./license.key");
  if (file.exists()) {
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    while (!in.atEnd()) {
      QString line = in.readLine();
      reg_data_list << line;
    }
    file.close();
  } else {
    return QStringList() << trialCrypted();
  }
  return reg_data_list;
}

bool regApp::compare_reg_data() {
  QString serial_number = generate_serial_number(DeviceID);
  QByteArray serial_number_array = serial_number.split("-").join("").toUtf8();
  QString serial_number_crypted = md5Crypt(serial_number_array);

  QStringList saved_reg_data = read_reg_data();

  foreach (const QString &reg, saved_reg_data) {
    if (reg == "1702198590490") {
      return true;  // master liscense
    } else if (reg == serial_number_crypted) {
      return true;
    }
  }
  return false;
}

bool regApp::check_eval_copy() {
  QStringList regs = read_reg_data();
  foreach (const QString &reg, regs) {
    if (reg == trialCrypted()) {
      return true;
    }
  }
  return false;
}
void regApp::evaluate() {
  QFile file("./license.key");
  QString trial_string = QString("TRIAL");
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    QByteArray trial_array = smuggle14(trial_string);
    QString trial_crypted = md5Crypt(trial_array);
    out << trial_crypted;
    file.close();
  }
}

QString regApp::md5Crypt(QByteArray &code) {
  QString trial_crypted = QString(
      QCryptographicHash::hash((code), QCryptographicHash::Md5).toHex());
  return trial_crypted;
}

QByteArray regApp::smuggle14(QString &str) {
  QString code = str;
  QByteArray array = code.toUtf8().toHex().toBase64().left(14);
  return array;
}

void regApp::toggleBlock(bool b) {
  QSettings reg(blockregPath, QSettings::NativeFormat);
  reg.setValue(blockRegKey, b);
}

int regApp::eval_max() { return 10; }

QString regApp::getDeviceID() { return DeviceID; }

regApp::~regApp() {}

QString regApp::trialCrypted() {
  QString trial_string = QString("TRIAL");
  QByteArray Trial_code = this->smuggle14(trial_string);
  return this->md5Crypt(Trial_code);
}
