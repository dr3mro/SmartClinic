#ifndef ADDSIBLINGS_H
#define ADDSIBLINGS_H

#include <QDialog>
#include "datahelper.h"
#include "sqlextra.h"
#include "sqlbase.h"
#include "msettings.h"
#include "wm_add2completer.h"

namespace Ui {
class addSiblings;
}

class addSiblings : public QDialog
{
    Q_OBJECT

public:
    explicit addSiblings(int row, sqlBase::Sibling sibling, QWidget *parent = nullptr, bool edit=false);
    ~addSiblings();
public slots:
private:
    void clean();
    void completer();
    sqlExtra *sqlextra;
    int selectedRow;
    Ui::addSiblings *ui;
    mSettings& settings=mSettings::instance();
    sqlBase::Sibling getSibling();

signals:
    void addSibling(sqlBase::Sibling);
    void editSibling(int,sqlBase::Sibling);
    void loadCompleters();
    void setReadWrite(bool);
    void reloadCompleter();
    void updateTextFont();

private slots:
    void on_addSibling_clicked();
    void on_closeButton_clicked();
    void on_editSibling_clicked();
    void makeReadWrite(bool rw);
};

#endif // ADDSIBLINGS_H
