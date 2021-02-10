// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef W_PERINATAL_H
#define W_PERINATAL_H

#include <QWidget>
#include "sqlbase.h"

namespace Ui {
class w_perinatal;
}

class w_perinatal : public QWidget
{
    Q_OBJECT

public:
    explicit w_perinatal(QWidget *parent = nullptr);
    void clear();
    void load(int id);
    sqlBase::perinatal getPerinatal(int id);
    bool isPnatalModified();
    void setID(int id);
    ~w_perinatal();

private:
    Ui::w_perinatal *ui;
    sqlBase *sqlbase;
    int ID;
};

#endif // W_PERINATAL_H
