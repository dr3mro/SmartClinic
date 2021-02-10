// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef DBOPTIMIZER_H
#define DBOPTIMIZER_H

#include <QDialog>
#include <QMovie>
#include <QCloseEvent>
#include <QtConcurrentRun>
#include <QFuture>
#include "msettings.h"
#include "optimizer.h"
#include "windowmanager.h"
namespace Ui {
class dbOptimizer;
}

class dbOptimizer : public QDialog
{
    Q_OBJECT

public:
    explicit dbOptimizer(QWidget *parent = nullptr);
    ~dbOptimizer();

private slots:
    void on_buttonOptimize_clicked();
    void status(QString operation , bool state);
    void message(QString msg);
    void on_buttonClose_clicked();
    void on_resetTweaks_clicked();
    void toggleAnimation(bool t);
    void on_journalMode_currentIndexChanged(int index);

public slots:
    void show();

private:
    mSettings::dbOptions getDbOptions();
    void putDbOptions(const mSettings::dbOptions &options);
    bool saveDbOptions(const mSettings::dbOptions &options);
    void togglecb(bool t);
    void readPrefs();
    void abort();
    void doOptimize();
    void closeEvent(QCloseEvent *e);
    QMovie *movie;
    QFuture<void> future1;
    QFuture<void> future2;
    mSettings::dbOptions initialDbOptions;
    mSettings& settings=mSettings::instance();
    optimizer opt;
    bool aborted=false;
    bool clean;
    bool working=false;
    Ui::dbOptimizer *ui;
    WindowManager wm;

protected:

};

#endif // DBOPTIMIZER_H
