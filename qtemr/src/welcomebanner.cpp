// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "welcomebanner.h"
#include "ui_welcomebanner.h"
#include <QTimer>

welcomeBanner::welcomeBanner(QWidget *parent) :
    QDialog(parent),
    movie (new QMovie(":/Graphics/loadanimation")),
    ui(new Ui::welcomeBanner)
{
    ui->setupUi(this);
    ui->progress->setMovie(movie);
    ui->appName->setText(APPNAME);
    ui->appVer->setText(APPVERSION);
    setModal(true);
    setWindowFlags( Qt::SplashScreen );
}

void welcomeBanner::updateprogress(const QString &op_name)
{
    percent +=9;
    ui->progressBar->setValue(percent);
    ui->current_stage->setText(op_name);
}

void welcomeBanner::setProgress(const int &perc)
{
    percent = perc;
    ui->progressBar->setValue(percent);
}

void welcomeBanner::close_later(QMainWindow *w)
{
    QTimer::singleShot(2000,this,[=]{
        if(w->isVisible())
            this->close();
    });
}

welcomeBanner::~welcomeBanner()
{
    delete movie;
    delete ui;
}
void welcomeBanner::showEvent(QShowEvent *e)
{
    QDialog::showEvent(e);
    ui->progressBar->setAlignment(Qt::AlignCenter);
    movie->setScaledSize(ui->progress->size());
    movie->start();
}
