// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "surgicalnotes.h"
#include "ui_surgicalnotes.h"

surgicalNotes::surgicalNotes(const int &_ID,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::surgicalNotes)
{
    this->ID = _ID;
    ui->setupUi(this);
    connect(ui->notes,SIGNAL(disableDeleteEditButton()),this,SLOT(disableDeleteEditButtons()));
    connect(ui->notes,SIGNAL(clicked(QModelIndex)),this,SLOT(toggleDeleteEditButtons()));
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    ui->notes->fillTable(ID);
}

void surgicalNotes::toggleDeleteEditButtons()
{
    ui->buttonDel->setEnabled(( ui->notes->model->rowCount() > 0 ));
    ui->buttonEdit->setEnabled(( ui->notes->model->rowCount() > 0 ));
}

void surgicalNotes::disableDeleteEditButtons()
{
    ui->buttonDel->setEnabled(false);
    ui->buttonEdit->setEnabled(false);
}



surgicalNotes::~surgicalNotes()
{
    delete ui;

}

void surgicalNotes::reloadNotes(const int &_ID)
{
    ui->notes->fillTable(_ID);
}

void surgicalNotes::on_closeButton_clicked()
{
    this->close();
}

void surgicalNotes::on_buttonAdd_clicked()
{
    surgicalNoteEditor addNewNote(false,NULL,NULL,NULL,NULL,this);
    connect(&addNewNote,SIGNAL(addSurgicalNote(QString,int,QString,QString)),this,SLOT(addsNote(QString,int,QString,QString)));
    addNewNote.exec();
}

void surgicalNotes::addsNote(QString surgeryID, int julianDate, QString opName, QString opReport)
{
    emit addsNoteSignal(surgeryID,julianDate,opName,opReport);
}

void surgicalNotes::savesNote(QString surgeryID, int julianDate, QString opName, QString opReport)
{
    emit savesNoteSignal(surgeryID,julianDate,opName,opReport);
}

void surgicalNotes::on_buttonDel_clicked()
{
    myMessageBox *msgbox =  new myMessageBox(this);
    //msgbox->toggleVisualEffects(settings.isVisualEffectsEnabled());
    int reply = msgbox->question(this,"Message","This Will <b>Delete</b> the currently Selected Post-Operative Note Are you Sure?<center> <i>This Can't be undone!</i></center>",
                                  QMessageBox::Yes,QMessageBox::No);

    if (reply == QMessageBox::No) {
      return;
    }
    int row =  ui->notes->selectionModel()->currentIndex().row();
    QString uID = ui->notes->model->data(ui->notes->model->index(row,0)).toString();
    emit deleteNote(uID);
    toggleDeleteEditButtons();
    delete msgbox;
}

void surgicalNotes::on_buttonEdit_clicked()
{
    int row =  ui->notes->selectionModel()->currentIndex().row();
    QString uID = ui->notes->model->data(ui->notes->model->index(row,0)).toString();
    QString opDate = ui->notes->model->data(ui->notes->model->index(row,2)).toString();
    QString opName = ui->notes->model->data(ui->notes->model->index(row,3)).toString();
    QString opReport = ui->notes->model->data(ui->notes->model->index(row,4)).toString();
    surgicalNoteEditor *editNote = new surgicalNoteEditor(true,uID,opDate,opName,opReport,this);
    connect(editNote,SIGNAL(saveSurgicalNote(QString,int,QString,QString)),this,SLOT(savesNote(QString,int,QString,QString)));
    editNote->exec();
    delete editNote;

}
