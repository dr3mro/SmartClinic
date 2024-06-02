#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QKeyEvent>
#include <QMessageBox>

#include "mdialog.h"
#include "mymessagebox.h"
#include "regapp.h"

#ifdef __GNUC__
#define COMPILER "GCC Compiler"
#elif __clang__
#define COMPILER "CLANG Compiler"
#elif _MSC_VER
#define COMPILER "MSVC Compiler"
#endif

namespace Ui {
class AboutWindow;
}

class AboutWindow : public mDialog {
  Q_OBJECT

 public:
  explicit AboutWindow(QWidget *parent = nullptr);
  ~AboutWindow();

 private slots:
  void regButton_clicked();
  void keyPressEvent(QKeyEvent *e);
  void serialNumber_textChanged(const QString &arg1);

 signals:
  void registerApp();

 private:
  myMessageBox *msgbox;
  Ui::AboutWindow *ui;
  regApp regMyApp;
  void register_App();
  QFont &tweakFont(QFont &font);
};

#endif  // ABOUTWINDOW_H
