#include "addsiblings.h"
#include "ui_addsiblings.h"

addSiblings::addSiblings(int row, sqlBase::Sibling sibling, QWidget *parent, bool edit) :
    QDialog(parent),
    sqlextra (new sqlExtra(this,"qt_sql_extra_siblings",false)),
    selectedRow(row),
    ui(new Ui::addSiblings)
{
    ui->setupUi(this);
    connect(parent->window(),SIGNAL(setReadWrite(bool)),this,SLOT(makeReadWrite(bool)));
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
        ui->state->setCurrentText(sibling.State);

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
    ui->state->setCurrentIndex(0);
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
    sibling.State = ui->state->currentText();
    return sibling;
}

void addSiblings::on_addSibling_clicked()
{

    emit addSibling(getSibling());
    clean();
}


void addSiblings::on_closeButton_clicked()
{
    clean();
    close();
}

void addSiblings::on_editSibling_clicked()
{
    emit editSibling(selectedRow,getSibling());
    clean();
    close();
}

void addSiblings::makeReadWrite(bool rw)
{
    setEnabled(rw);
}
