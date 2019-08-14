#include "surgicalnoteeditor.h"
#include "ui_surgicalnoteeditor.h"

surgicalNoteEditor::surgicalNoteEditor(bool editMode, QString surgeryID, QString date, QString opName, QString opReport, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::surgicalNoteEditor)
{
    ui->setupUi(this);
    mEditMode = editMode;
    if (mEditMode)
    {
        ui->OperationDate->setDate(QDate::fromString(date,"dd/MM/yyyy"));
        ui->operation->setText(opName);
        ui->report->setHtml(opReport);
        uID  = surgeryID;
    }
    else
    {
        ui->OperationDate->setDate(QDate::currentDate());
        ui->operation->setText("");
        ui->report->setHtml("");
        uID = uniqueID();
    }
    emit loadCompleters();
    setMinimumSize(300,400);
}

surgicalNoteEditor::~surgicalNoteEditor()
{
    delete ui;
}

void surgicalNoteEditor::on_buttonClear_clicked()
{
    ui->report->clear();
    ui->Templates->setCurrentIndex(0);
    ui->operation->setText("");
    ui->OperationDate->setDate(QDate::currentDate());
}

void surgicalNoteEditor::on_Templates_activated(int index)
{
    QString CS;
    switch (index)
    {
    case 0:
        CS = "" ;
        ui->report->setText(CS);
        break;
    case 1:
        CS ="Caesarian section. Under spinal anesthesia, abdomen was opened "
            "by pfennesteil incision, sheath, muscles and parietal proton were "
            "opened. Visceral proton was opened and bladder was dissected downward."
            "Uterus was opened by transverse lower segment incision. Baby boy "
            "was delivered in good condition and was take cared by neonatologist."
            "Placenta was delivered completely, and homeostasis was secured."
            "Uterus was closed in tow layers, proton was closed, sheath and "
            "subcutaneous were closed. Skin was closed by vicryl.";
        ui->report->setText(CS);
        ui->operation->setText("Caeserian Section");
        break;
    default:
        break;
    }
}

void surgicalNoteEditor::on_buttonClose_clicked()
{
    this->close();
}

void surgicalNoteEditor::on_buttonSave_clicked()
{
    int opDate = ui->OperationDate->date().toJulianDay();
    QString op = ui->operation->text().simplified();
    QString report = ui->report->toHtml();
    if ( mEditMode )
    {
        emit saveSurgicalNote(uID,opDate,op,report);
    }
    else
    {
        emit addSurgicalNote(uID,opDate,op,report);
    }

    this->close();
}

QString surgicalNoteEditor::uniqueID()
{
    int a = QDate::currentDate().toJulianDay();
    int b = QTime::currentTime().msecsSinceStartOfDay()/1000;
    return QString("%1%2").arg(a).arg(b);
}
