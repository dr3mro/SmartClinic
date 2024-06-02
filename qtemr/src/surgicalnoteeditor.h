// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef SURGICALNOTEEDITOR_H
#define SURGICALNOTEEDITOR_H

#include <QDialog>

namespace Ui {
class surgicalNoteEditor;

}

class surgicalNoteEditor : public QDialog {
  Q_OBJECT

 public:
  explicit surgicalNoteEditor(bool editMode, QString surgeryID = "",
                              QString date = "", QString opName = "",
                              QString opReport = "", QWidget *parent = nullptr);
  ~surgicalNoteEditor();

 private slots:
  void on_buttonClear_clicked();
  void on_Templates_activated(int index);
  void on_buttonClose_clicked();
  void on_buttonSave_clicked();
  QString uniqueID();

 private:
  Ui::surgicalNoteEditor *ui;
  QString uID;
  bool mEditMode;

 signals:
  void addSurgicalNote(QString surgeryID, int julianDate, QString opName,
                       QString opReport);
  void saveSurgicalNote(QString surgeryID, int julianDate, QString opName,
                        QString opReport);
  void loadCompleters();
  // unused signals
  void setReadWrite(bool);
  void reloadCompleter();
};

#endif  // SURGICALNOTEEDITOR_H
