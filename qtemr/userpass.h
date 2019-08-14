#ifndef USERPASS_H
#define USERPASS_H

#include <QDialog>
#include <QKeyEvent>
#include <QDesktopWidget>
#include "msettings.h"
#include "dataiohelper.h"
#include "sqlbase.h"
#include "windowmanager.h"

namespace Ui {
class userpass;
}

class userpass : public QDialog
{
    Q_OBJECT
    bool passwordaccepted;
    int passwdEnterCount;
    sqlBase *sqlbase;

public:
    explicit userpass(QWidget *parent = 0);
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *e);
    bool compare_pass();
    void decide_what_to_do();
    ~userpass();

signals:
    void quitme();
    void newMessage(QString,QString);

private slots:
    void on_submit_button_clicked();
    void on_passwordLine_returnPressed();

private:
    Ui::userpass *ui;
    WindowManager wm;
};

#endif // USERPASS_H
