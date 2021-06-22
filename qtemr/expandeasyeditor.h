#ifndef EXPANDEASYEDITOR_H
#define EXPANDEASYEDITOR_H

#include <QDialog>

namespace Ui {
class ExpandEasyEditor;
}

class ExpandEasyEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ExpandEasyEditor(QString & expandShortcut, QString & expandContents,bool & save, QWidget *parent = nullptr);
    ~ExpandEasyEditor();


signals:
   void loadCompleters();  //dummy not used
   void reloadCompleter();  //dummy not used
   void setReadWrite(bool);   //dummy not used

private slots:
   void save();
private:
    QString & m_ExpandShortcut;
    QString & m_ExpandContents;
    bool &m_Save;
    Ui::ExpandEasyEditor *ui;
};

#endif // EXPANDEASYEDITOR_H
