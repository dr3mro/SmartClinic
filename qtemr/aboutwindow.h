#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QMessageBox>
#include <QKeyEvent>

#include "mymessagebox.h"
#include "globalvariables.h"
#include "regapp.h"
#include "mdialog.h"
#include "build.h"

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

class AboutWindow : public mDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();

private slots:
    void on_regButton_clicked();
    void keyPressEvent(QKeyEvent *e);
    void on_serialNumber_textChanged(const QString &arg1);
    void on_closeButton_clicked();

signals:
    void registerApp();

private:
    myMessageBox *msgbox;
    Ui::AboutWindow *ui;
    regApp regMyApp;
    QFont font;
    void register_App();
};

#endif // ABOUTWINDOW_H
