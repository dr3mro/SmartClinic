#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QMessageBox>
#include <QKeyEvent>

#include "build.h"
#include "mymessagebox.h"
#include "globalvariables.h"
#include "regapp.h"
#include "mdialog.h"


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
