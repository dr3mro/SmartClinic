#include "patientlist.h"
#include "ui_patientlist.h"

PatientList::PatientList(QWidget *parent):
    mDialog(parent),
    ui(new Ui::PatientList)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setLocale(QLocale("en_US"));
    setMinimumHeight(parent->window()->height() - (parent->height()/10) );
    setFixedSize(size());
    move(parent->window()->frameGeometry().topLeft() + parent->window()->rect().center() - rect().center());
    connect (ui->searchWidgetx,SIGNAL (loadPatient(int) ),parent->window(),SLOT(on_PatientSelected(int)) );
    connect (ui->searchWidgetx,SIGNAL (closePatientList()),this,SLOT(close()));
    ui->searchWidgetx->focusFilter();
 }

void PatientList::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    if (e->key() == Qt::Key_F2)
        ui->searchWidgetx->focusFilter();
    QWidget::keyPressEvent(e);
}

PatientList::~PatientList()
{
    delete ui;
}

void PatientList::on_closeButton_clicked()
{
    this->close();
}
