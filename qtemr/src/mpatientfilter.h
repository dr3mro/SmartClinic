// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MPATIENTFILTER_H
#define MPATIENTFILTER_H

#include <QObject>
#include <QLineEdit>
#include <QKeyEvent>
#include <QIcon>
#include <QAction>
#include <QRegularExpressionValidator>

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
    QRegularExpressionValidator validator;
};

#endif // MPATIENTFILTER_H
