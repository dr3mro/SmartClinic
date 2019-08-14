#ifndef W_DEVELOPMENT_H
#define W_DEVELOPMENT_H

#include <QWidget>
#include "sqlbase.h"
#include <QSqlDatabase>
#include "mdebug.h"


namespace Ui {
class w_development;
}

class w_development : public QWidget
{
    Q_OBJECT

public:
    explicit w_development(QWidget *parent = nullptr);
    void clear();
    void load(int id);
    sqlBase::development getDevelopment(int id);
    bool isDevelopmentModified();
    void setID(int id);
    ~w_development();

private:
    Ui::w_development *ui;
    sqlBase *sqlbase;
    int ID;
};

#endif // W_DEVELOPMENT_H
