// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef SURGICALNOTES_H
#define SURGICALNOTES_H

#include <QDialog>
#include "msettings.h"
#include "dataiohelper.h"
#include "surgicalnoteeditor.h"
#include "mymessagebox.h"

namespace Ui {
class surgicalNotes;
}

class surgicalNotes : public QDialog
{
    Q_OBJECT

public:
    explicit surgicalNotes(int ID, QWidget *parent = nullptr);
    surgicalNoteEditor *addNewNote;

    int ID;
    ~surgicalNotes();

public slots:
    void reloadNotes(int ID);
private slots:
    void on_closeButton_clicked();
    void on_buttonAdd_clicked();
    void addsNote(QString surgeryID,int julianDate, QString opName, QString opReport);
    void savesNote(QString surgeryID,int julianDate, QString opName, QString opReport);
    void on_buttonDel_clicked();
    void toggleDeleteEditButtons();
    void disableDeleteEditButtons();
    void on_buttonEdit_clicked();

private:
    Ui::surgicalNotes *ui;

signals:
    void addsNoteSignal(QString,int,QString,QString);
    void savesNoteSignal(QString,int,QString,QString);
    void deleteNote(QString surgeryID);
};

#endif // SURGICALNOTES_H
