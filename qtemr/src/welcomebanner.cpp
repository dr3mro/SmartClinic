// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "welcomebanner.h"
#include "ui_welcomebanner.h"

welcomeBanner::welcomeBanner(QWidget *parent) :
    QDialog(parent),
    movie (new QMovie(":/Graphics/loadanimation")),
    ui(new Ui::welcomeBanner)
{
    ui->setupUi(this);
    ui->progressBar->setAlignment(Qt::AlignCenter);
    setModal(true);
    setWindowFlags( Qt::SplashScreen );
    movie->setScaledSize(ui->progress->size());
    ui->progress->setMovie(movie);
    ui->appName->setText(APPNAME);
    ui->appVer->setText(APPVERSION);
    movie->start();
}

void welcomeBanner::updateprogress(const QString &op_name)
{
    //called 13 times
    percent +=7;
    ui->progressBar->setValue(percent);
    ui->current_stage->setText(op_name);
    //dataHelper::delay(100);
}

void welcomeBanner::setProgress(const int &perc)
{
    percent = perc;
    ui->progressBar->setValue(percent);
}

welcomeBanner::~welcomeBanner()
{
    delete movie;
    delete ui;
}
