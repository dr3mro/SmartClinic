#ifndef CONDITIONSWIDGET_H
#define CONDITIONSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QList>
#include "mcheckbox.h"
#include "sqlbase.h"

class conditionsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit conditionsWidget(QWidget *parent = nullptr);
    void fillConditions(int ID);
    void clear();
    QList<QPair<QString, int> > getConditionsState();
    bool isConditionsModified();
    void setID(int id);
    bool editMode=true;
    ~conditionsWidget();
signals:

public slots:
    void load();
    void reload();
private:
    void loadCheckboxes();
    void setConditionsCount();
    void setConditions();

    int ID;
    int conditionsCount=0;
    int columns = 5;
    int rows;

    QList<QPair<int,QString> > conditions;
    QList<mCheckBox*> cbList;
    QList<mCheckBox*> getCheckboxList();
    sqlBase *sqlbase;
    QGridLayout layout;
};

#endif // CONDITIONSWIDGET_H
