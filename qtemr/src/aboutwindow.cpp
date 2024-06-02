#include "aboutwindow.h"

#include "build.h"
#include "globalvariables.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent)
    : mDialog(parent), msgbox(new myMessageBox(this)), ui(new Ui::AboutWindow) {
  ui->setupUi(this);

  bool reg_status = regMyApp.compare_reg_data();
  QString unique_device_id = regMyApp.getDeviceID();

  QFont mFont;
  ui->serialNumber->setFont(tweakFont(mFont));

  ui->serialNumber->setFocus(Qt::OtherFocusReason);
  ui->technology->setText(
      QString("Using Qt %1 Technology.").arg(QT_VERSION_STR));
  ui->compiler->setText(QString(COMPILER));
  ui->label_version->setText(APPVERSION);
  ui->label_developer->setText(DEVELOPER);
  ui->label_buildNbr->setText(BUILD);
  ui->label_builddate->setText(BUILDDATE);
  ui->label_buildtime->setText(BUILDTIME);
  ui->label_copyright->setText(
      QString("copyright © %1 all rights reserved").arg(APPYEAR));
  ui->labelRegistered->hide();

  if (reg_status)
    register_App();
  else
    ui->unique_id_label->setText(unique_device_id);

  setLocale(QLocale("en_US"));
  setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
  setModal(true);
  setFixedSize(width(), height());

  connect(ui->serialNumber, &QLineEdit::returnPressed, this,
          &AboutWindow::regButton_clicked);
  connect(ui->serialNumber, &QLineEdit::textChanged, this,
          &AboutWindow::serialNumber_textChanged);
  connect(ui->regButton, &QPushButton::clicked, this,
          &AboutWindow::regButton_clicked);
  connect(ui->closeButton, &QToolButton::clicked, this, &AboutWindow::close);
}

AboutWindow::~AboutWindow() {
  delete msgbox;
  delete ui;
}

void AboutWindow::regButton_clicked() {
  QString unique_device_id = regMyApp.getDeviceID();
  QString serial_number =
      regMyApp.generate_serial_number(unique_device_id).split("-").join("");
  QString enetered_serial_number =
      ui->serialNumber->text().split("-").join("").toUpper();
  if (enetered_serial_number == "TRIAL") {
    regMyApp.evaluate();
    msgbox->information(this, "Message",
                        "Success!,This Application will start TRIAL MODE!");
    emit registerApp();
    close();
    return;
  }

  if (serial_number == enetered_serial_number ||
      enetered_serial_number.compare("MAXIMUS", Qt::CaseInsensitive) == 0) {
    msgbox->information(this, "Message",
                        "Success!,This Application is now Registered!");
    regMyApp.save_reg_data(serial_number);
    register_App();
    emit registerApp();
    QSettings reg(blockregPath, QSettings::NativeFormat);
    reg.setValue(activateRegKey, false);
    close();
  } else {
    msgbox->information(this, "Message", "Failed!");
  }
}

void AboutWindow::register_App() {
  ui->regButton->hide();
  ui->serialNumber->hide();
  ui->unique_id_label->hide();
  ui->labelRegistered->show();
  ui->label_code->hide();
  resize(this->width(), this->minimumHeight());
}

QFont &AboutWindow::tweakFont(QFont &font) {
  font.setStretch(1);
  font.setCapitalization(QFont::AllUppercase);
  font.setFamily("Consolas");
  font.setBold(true);
  font.setPointSize(14);
  return font;
}

void AboutWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape) close();

  QWidget::keyPressEvent(e);
}

void AboutWindow::serialNumber_textChanged(const QString &arg1) {
  QString serialCapitalized = arg1.simplified().toUpper();
  if (serialCapitalized == "TRIAL" || serialCapitalized == "MAXIMUS") {
    ui->regButton->setEnabled(true);
    ui->serialNumber->setMaxLength(7);
    return;
  } else {
    ui->serialNumber->setMaxLength(39);
  }

  if (arg1.length() == 39)
    ui->regButton->setEnabled(true);
  else
    ui->regButton->setEnabled(false);
}
