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
    ~welcomeBanner();
private:
    QMovie *movie;
    int percent=0;
    Ui::welcomeBanner *ui;
};

#endif // WELCOMEBANNER_H
