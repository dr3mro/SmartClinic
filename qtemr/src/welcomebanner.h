// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef WELCOMEBANNER_H
#define WELCOMEBANNER_H

#include <QDialog>
#include <QMovie>
#include <QProgressBar>
#include "mdebug.h"
#include "globalvariables.h"
#include "datahelper.h"

namespace Ui {
class welcomeBanner;
}

class welcomeBanner : public QDialog
{
    Q_OBJECT

public:
    explicit welcomeBanner(QWidget *parent = nullptr);
    void updateprogress(const QString &op_name);
    void setProgress(const int &perc);
    void close_later();
    ~welcomeBanner();
private:
    QMovie *movie;
    int percent=0;
    Ui::welcomeBanner *ui;

protected:
    void showEvent(QShowEvent *e) override;

};

#endif // WELCOMEBANNER_H
