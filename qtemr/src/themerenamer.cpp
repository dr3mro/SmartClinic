// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "themerenamer.h"
#include "ui_themerenamer.h"

ThemeRenamer::ThemeRenamer(bool& ok, QString& name, QStringList &themes, QWidget *parent):
    QDialog(parent),
    ui(new Ui::ThemeRenamer),
    Ok(ok),
    Themes(themes),
    Name(name)
{
    ui->setupUi(this);
    setMinimumSize(200,105);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->inputThemeName->setFocus(Qt::OtherFocusReason);
}

ThemeRenamer::~ThemeRenamer()
{
    delete ui;
}

void ThemeRenamer::on_btn_Cancel_clicked()
{
    Ok = false;
    close();
}

void ThemeRenamer::on_btn_Ok_clicked()
{
    Ok = true;
    Name =  ui->inputThemeName->text().simplified();
    close();
}

void ThemeRenamer::on_inputThemeName_textChanged(const QString &arg1)
{
    ui->btn_Ok->setDisabled(arg1.simplified().isEmpty()|| Themes.contains(arg1));
}
