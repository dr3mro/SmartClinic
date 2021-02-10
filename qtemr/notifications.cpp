// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "notifications.h"
#include "ui_notifications.h"

notifications::notifications(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notifications)
{
    ui->setupUi(this);
    setWindowFlags( windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setStyleSheet("background-color:black;color:white;");
    setWindowOpacity(0.95);
}

notifications::~notifications()
{
    delete ui;
}


void notifications::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_F11 || e->key() == Qt::Key_Escape )
        close();

    QWidget::keyPressEvent(e);
}

void notifications::fillList(QStringList n)
{
    ui->listWidget->clear();
    ui->listWidget->addItems(n);

}
