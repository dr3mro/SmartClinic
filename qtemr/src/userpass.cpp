// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "userpass.h"

#include "ui_userpass.h"

userpass::userpass(QWidget *parent) : QDialog(parent), ui(new Ui::userpass) {
  ui->setupUi(this);
  sqlbase = new sqlBase(this, "qt_sql_base_userpass", false);
  passwdEnterCount = 0;
  passwordaccepted = false;
  wm.centerOnScreen(this);
  setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
  ui->passwordLine->setFocus(Qt::OtherFocusReason);
}

void userpass::closeEvent(QCloseEvent *) {
  if (!passwordaccepted) {
    emit quitme();
  }
}

void userpass::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape) {
    emit quitme();
  } else {
    QWidget::keyPressEvent(e);
  }
}

userpass::~userpass() {
  sqlbase->optimize();
  delete sqlbase;
  QSqlDatabase::removeDatabase("qt_sql_base_userpass");
  delete ui;
}

void userpass::on_submit_button_clicked() {
  passwordaccepted = compare_pass();
  decide_what_to_do();
}

bool userpass::compare_pass() {
  QByteArray passArray = ui->passwordLine->text().toUtf8();
  QString password = QString(
      QCryptographicHash::hash((passArray), QCryptographicHash::Md5).toHex());
  if (password == sqlbase->getUserPasswordHash("doktor")) {
    emit newMessage("information", "Access Granted");
    return true;
  } else {
    emit newMessage("information", "Access Denied");
    return false;
  }
}

void userpass::on_passwordLine_returnPressed() { on_submit_button_clicked(); }

void userpass::decide_what_to_do() {
  if (passwordaccepted) {
    this->close();
  } else {
    ui->passwordLine->clear();
    passwdEnterCount += 1;
  }
  if (passwdEnterCount > 3) {
    emit newMessage("information", "Access Denied , Now Exiting");
    this->close();
  }
}
