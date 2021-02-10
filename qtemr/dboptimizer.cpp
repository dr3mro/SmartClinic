// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "dboptimizer.h"
#include "ui_dboptimizer.h"

dbOptimizer::dbOptimizer(QWidget *parent) :
    QDialog(parent),
    movie (new QMovie(":/Graphics/loadanimation")),
    ui(new Ui::dbOptimizer)
{
    ui->setupUi(this);
    setFixedSize(this->size());
    connect(&opt,SIGNAL(status(QString,bool)),this,SLOT(status(QString,bool)));
    connect(&opt,SIGNAL(toggleProgress(bool)),this,SLOT(toggleAnimation(bool)));
    connect(ui->sw_optimize,SIGNAL(toggled(bool)),ui->sw_shrinkMemory,SLOT(setEnabled(bool)));
    movie->setScaledSize(ui->loading->size());
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    //qRegisterMetaType<QTextCursor>("QTextCursor");
    initialDbOptions = settings.readDbOptions();
    putDbOptions(initialDbOptions);
}

dbOptimizer::~dbOptimizer()
{
    future1.waitForFinished();
    future2.waitForFinished();
    opt.WAL_CheckPoint(ui->WAL_CheckPoint_Mode->currentText());
    delete movie;
    delete ui;
}

void dbOptimizer::on_buttonOptimize_clicked()
{
    if(working)
        abort();
    else
        doOptimize();
}

void dbOptimizer::toggleAnimation(bool t)
{
    if (t)
    {
        ui->loading->setMovie(movie);
        ui->buttonOptimize->setText("Abort");
        movie->start();
    }
    else
    {
        ui->buttonOptimize->setText("Optimize");
        movie->stop();
        ui->loading->clear();
    }

    togglecb(t);
    working = t;
}

void dbOptimizer::togglecb(bool t)
{
    ui->cb_quick->setEnabled(!t);
    ui->cb_clean->setEnabled(!t);
    ui->cb_core->setEnabled(!t);
    ui->cb_drugsindex->setEnabled(!t);
}

void dbOptimizer::readPrefs()
{
    clean = ui->cb_clean->isChecked();
    bool quick = ui->cb_quick->isChecked();
    bool db_patients = ui->cb_patients->isChecked();
    bool db_core = ui->cb_core->isChecked();
    bool db_drugsindex = ui->cb_drugsindex->isChecked();
    opt.setDatabases(db_patients,db_core,db_drugsindex);
    opt.setQuick(quick);
}

void dbOptimizer::abort()
{
    ui->buttonOptimize->setText("Aborting..");
    aborted=true;
    opt.terminate(true);
}

void dbOptimizer::doOptimize()
{
    aborted = false;
    opt.terminate(false);
    ui->status->clear();
    readPrefs();

    message("Initializing database integrity check ...");

    future1 = QtConcurrent::run(&opt,&optimizer::integrityCheck);
    while(future1.isRunning())
        qApp->processEvents();

    if(aborted)
        message("Integrity check Terminated.");
    else
        message("Integrity check Completed.");


    if(clean)
    {
        message("Initializing database Optimization ...");
        future2 = QtConcurrent::run(&opt,&optimizer::vacuum);
        while(future2.isRunning())
           qApp->processEvents();

        if(aborted)
            message("Optimization Terminated.");
        else
            message("Optimization completed.");
    }
}

mSettings::dbOptions dbOptimizer::getDbOptions()
{
    mSettings::dbOptions options;
    options.autovacuum = ui->autoVcuum->currentText();
    options.optimize = ui->sw_optimize->isChecked();
    options.shrinkMem = ui->sw_shrinkMemory->isChecked();
    options.WAL_CheckPoint = ui->WAL_CheckPoint_Mode->currentText();
    options.shared_cache = ui->sharedCache->currentText();
    options.temp_store= ui->tempStore->currentText();
    options.synchronous=ui->synchronous->currentText();
    options.journal_mode=ui->journalMode->currentText();
    options.locking_mode=ui->lockingMode->currentText();
    options.cache_size=ui->cacheSize->value();
    options.page_size=ui->pageSize->value();
    return options;
}

void dbOptimizer::putDbOptions(const mSettings::dbOptions &options)
{
    ui->autoVcuum->setCurrentText(options.autovacuum);
    ui->sw_optimize->setChecked(options.optimize);
    ui->sw_shrinkMemory->setChecked(options.shrinkMem);
    ui->WAL_CheckPoint_Mode->setCurrentText(options.WAL_CheckPoint);
    ui->sharedCache->setCurrentText(options.shared_cache);
    ui->tempStore->setCurrentText(options.temp_store);
    ui->synchronous->setCurrentText(options.synchronous);
    ui->journalMode->setCurrentText(options.journal_mode);
    ui->lockingMode->setCurrentText(options.locking_mode);
    ui->cacheSize->setValue(options.cache_size);
    ui->pageSize->setValue(options.page_size);
}

bool dbOptimizer::saveDbOptions(const mSettings::dbOptions &options)
{
    bool tweaks_changed = (options!=initialDbOptions);
    if(tweaks_changed)
        settings.saveDbOptions(options);
    return tweaks_changed;
}

void dbOptimizer::closeEvent(QCloseEvent *e)
{
    if (!working)
    {
        bool s = saveDbOptions(getDbOptions());
        if(s)
            QMessageBox::information(nullptr,"Alert!",
                                     "Database options has been changed, please restart application to avoid crashes.",
                                     QMessageBox::Ok);
        e->accept();

    }
    while (working)
    {
        abort();
        e->ignore();
        QApplication::processEvents();
    }

    e->accept();

}

void dbOptimizer::status(QString operation,bool state)
{
    QApplication::processEvents();
    ui->status->append(QString ("<b>%1</b> : %2").arg(operation).arg(state? "<b style='color:green;'>OK</b>":"<b style='color:red;'>FAIL</b>"));
}

void dbOptimizer::message(QString msg)
{
    QApplication::processEvents();
    ui->status->append(QString ("<b style='color:blue;'>%1</b>").arg(msg));
}

void dbOptimizer::on_buttonClose_clicked()
{
    abort();
    close();
}

void dbOptimizer::on_resetTweaks_clicked()
{
    int reply = QMessageBox::question(nullptr,"Alert!",
                                      "This will restore database settings to default values, Are you sure?",
                                      QMessageBox::Yes,
                                      QMessageBox::No);
    if(reply==QMessageBox::No)
        return;

    mSettings::dbOptions options;
    options.clear();
    settings.saveDbOptions(options);
    putDbOptions(options);
}

void dbOptimizer::on_journalMode_currentIndexChanged(int index)
{
    int i = ui->WAL_CheckPoint_Mode->currentIndex();
    ui->WAL_CheckPoint_Mode->setCurrentIndex((index!=4)? 0:i);
    ui->WAL_CheckPoint_Mode->setEnabled((index==4));
}

void dbOptimizer::show()
{
    wm.centerOnScreen(this);
}
