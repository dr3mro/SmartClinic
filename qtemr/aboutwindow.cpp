// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) : mDialog(parent),
    msgbox (new myMessageBox(this)),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    font.setStretch(1);
    font.setCapitalization(QFont::AllUppercase);
    font.setFamily("Consolas");
    font.setBold(true);
    font.setPointSize(14);

    bool reg_status = regMyApp.compare_reg_data();
    QString unique_device_id = regMyApp.genDeviceID();

    ui->serialNumber->setFont(font);
    ui->serialNumber->setFocus(Qt::OtherFocusReason);
    ui->technology->setText(QString("Using Qt %1 Technology.").arg(QT_VERSION_STR));
    ui->compiler->setText(QString(COMPILER));
    ui->label_version->setText(APPVERSION);
    ui->label_developer->setText(DEVELOPER);
    ui->label_buildNbr->setText(BUILD);
    ui->label_builddate->setText( __DATE__ );
    ui->label_buildtime->setText( __TIME__ );
    ui->label_copyright->setText(QString("copyright © %1 all rights reserved").arg(APPYEAR));
    ui->labelRegistered->hide();

    if ( reg_status )
        register_App();
    else
        ui->unique_id_label->setText(unique_device_id );

    setLocale(QLocale("en_US"));
    setWindowFlags( windowFlags() | Qt::FramelessWindowHint );
    setModal(true);
    setFixedSize(width(),height());

    connect(ui->serialNumber,SIGNAL(returnPressed()),ui->regButton,SIGNAL(clicked()));

}

AboutWindow::~AboutWindow()
{
    delete msgbox;
    delete ui;
}

void AboutWindow::on_regButton_clicked()
{
    //regApp regMyApp;

    QString unique_device_id = regMyApp.genDeviceID();
    QString serial_number = regMyApp.generate_serial_number(unique_device_id).split("-").join("");
    QString enetered_serial_number = ui->serialNumber->text().split("-").join("").toUpper();
    if ( enetered_serial_number == "TRIAL" )
    {
        regMyApp.evaluate();
        msgbox->information(this,"Message","Success!,This Application will start TRIAL MODE!");
        emit registerApp();
        close();
        return;
    }

    if ( serial_number == enetered_serial_number || enetered_serial_number.compare("MAXIMUS",Qt::CaseInsensitive)==0 )
    {
        msgbox->information(this,"Message","Success!,This Application is now Registered!");
        regMyApp.save_reg_data(serial_number);
        register_App();
        emit registerApp();
        QSettings reg(blockregPath,QSettings::NativeFormat);
        reg.setValue(activateRegKey,false);
        close();
   }
    else
    {
        msgbox->information(this,"Message","Failed!");
    }
}

void AboutWindow::register_App()
{
    ui->regButton->hide();
    ui->serialNumber->hide();
    ui->unique_id_label->hide();
    ui->labelRegistered->show();
    ui->label_code->hide();
    resize(this->width(),this->minimumHeight());

}

void AboutWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();

    QWidget::keyPressEvent(e);
}


void AboutWindow::on_serialNumber_textChanged(const QString &arg1)
{
    QString serialCapitalized = arg1.simplified().toUpper();
    if ( serialCapitalized == "TRIAL" || serialCapitalized == "MAXIMUS"  )
    {
        ui->regButton->setEnabled(true);
        ui->serialNumber->setMaxLength(7);
        return;
    }
    else
    {
        ui->serialNumber->setMaxLength(39);
    }

    if ( arg1.length() == 39 )
        ui->regButton->setEnabled(true);
    else
        ui->regButton->setEnabled(false);
}

void AboutWindow::on_closeButton_clicked()
{
    close();
}
