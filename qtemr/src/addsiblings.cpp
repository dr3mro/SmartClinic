// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "addsiblings.h"
#include "ui_addsiblings.h"

addSiblings::addSiblings(int row, sqlBase::Sibling sibling, QWidget *parent, bool edit) :
    QDialog(parent),
    sqlextra (new sqlExtra(this,"qt_sql_extra_siblings",false)),
    selectedRow(row),
    ui(new Ui::addSiblings)
{
    ui->setupUi(this);
    connect(ui->addSibling,&QPushButton::clicked,this,&addSiblings::onAddSibling_clicked);
    connect(ui->editSibling,&QPushButton::clicked,this,&addSiblings::onEditSibling_clicked);
    connect(ui->closeButton,&QPushButton::clicked,this,&addSiblings::onCloseButton_clicked);
    clean();
    ui->addSibling->setHidden(edit);
    ui->editSibling->setVisible(edit);
    if (edit)
    {
        ui->dateOfBirth->setDate(QDate::fromString(sibling.DateOfBirth,"dd/MM/yyyy"));
        ui->typeOfDelivery->setCurrentText(sibling.TypeOfDelivery);
        ui->gender->setCurrentText(sibling.Gender);
        ui->placeOfBirth->setText(sibling.PlaceOfBirth);
        ui->complications->setText(sibling.Complications);
        ui->term->setCurrentText(sibling.Term);

    }
    setMinimumSize(300,400);
}

addSiblings::~addSiblings()
{
    sqlextra->optimize();
    delete sqlextra;
    QSqlDatabase::removeDatabase("qt_sql_extra_siblings");
    delete ui;
}

void addSiblings::clean()
{
    completer();
    ui->dateOfBirth->setDate(QDate::currentDate());
    ui->typeOfDelivery->setCurrentIndex(0);
    ui->gender->setCurrentIndex(0);
    ui->placeOfBirth->clear();
    ui->complications->clear();
    ui->term->setCurrentIndex(0);
}

void addSiblings::completer()
{
    QString placeOfBirth = ui->placeOfBirth->text();
    QString complications = ui->complications->toHtml();
    sqlextra->addToAutoComplete("placeOfBirth",placeOfBirth);
    wm_add2Completer wmac;
    QStringList dictList = QStringList() << complications;
    wmac.save2Dict(dictList);
    emit loadCompleters();
}

sqlBase::Sibling addSiblings::getSibling()
{
    sqlBase::Sibling sibling;
    QLocale locale = QLocale(QLocale::English , QLocale::UnitedStates );
    sibling.DateOfBirth = locale.toString(ui->dateOfBirth->date(),"dd/MM/yyyy");
    sibling.TypeOfDelivery = ui->typeOfDelivery->currentText();
    sibling.Gender = ui->gender->currentText();
    sibling.PlaceOfBirth = ui->placeOfBirth->text();
    sibling.Complications = ui->complications->toPlainText();
    sibling.Term = ui->term->currentText();
    return sibling;
}

void addSiblings::onAddSibling_clicked()
{

    emit addSibling(getSibling());
    clean();
}


void addSiblings::onCloseButton_clicked()
{
    clean();
    close();
}

void addSiblings::onEditSibling_clicked()
{
    emit editSibling(selectedRow,getSibling());
    clean();
    close();
}

void addSiblings::makeReadWrite(bool rw)
{
    setEnabled(rw);
}
