#ifndef MPATIENTFILTER_H
#define MPATIENTFILTER_H

#include <QObject>
#include <QLineEdit>
#include <QKeyEvent>
#include <QIcon>
#include <QAction>
#include <QRegExpValidator>

class mPatientFilter : public QLineEdit
{
    Q_OBJECT
public:
    explicit mPatientFilter(QWidget *parent=nullptr);
protected:
    void keyPressEvent(QKeyEvent *ke);
signals:
    void focusPatientTable();
    void toggleFilters(bool);
private:
    QRegExpValidator validator;
};

#endif // MPATIENTFILTER_H
