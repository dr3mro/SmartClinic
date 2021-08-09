// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "getinvestigationname.h"
#include "ui_getinvestigationname.h"

getInvestigationName::getInvestigationName(QWidget *parent) :
    mDialog(parent),
    ui(new Ui::getInvestigationName)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowFlags(windowFlags() | Qt::Window | Qt::FramelessWindowHint);
    ui->OK->setEnabled(false);

    QAction *selectResourceAction =
        ui->Path->addAction(QIcon(":/ionicons/more"), QLineEdit::ActionPosition::TrailingPosition);
    connect(selectResourceAction,&QAction::triggered,this,&getInvestigationName::setPath);
}


int getInvestigationName::exec()
{
    emit hideParentWindow();
    return mDialog::exec();
}

getInvestigationName::~getInvestigationName()
{
    delete ui;
}

void getInvestigationName::show()
{
    emit hideParentWindow();
    mDialog::show();
}

void getInvestigationName::on_closeButton_clicked()
{
    close();
}

void getInvestigationName::setPath()
{
    QFileDialog fileDialog;
    QString desktop = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString selectedImagePath = fileDialog.getOpenFileName(this,"Select Photo Copy",desktop, "*.jpg *.jpeg");
    ui->Path->setText(selectedImagePath);
}


void getInvestigationName::close()
{
    ui->Name->clear();
    ui->Path->clear();
    emit showParentWindow();
    mDialog::close();
}

void getInvestigationName::on_OK_clicked()
{
    QString Name = ui->Name->text().simplified();
    QString Path = ui->Path->text().simplified();
    QImage img;
    if (!img.load(Path))
    {
        emit popUpMessage("Error","Invalid File Selected!");
        return;
    }
    else
    {
        emit investigationAccepted(Name,Path);
        close();
    }
}

void getInvestigationName::on_Close_clicked()
{
    close();
}

void getInvestigationName::on_Name_textChanged(const QString &arg1)
{
    ui->OK->setEnabled( arg1.length() > 0  && ui->Path->text().length() >0);
}

void getInvestigationName::on_Path_textChanged(const QString &arg1)
{
     ui->OK->setEnabled( arg1.length() > 0  && ui->Name->text().length() >0);
}
