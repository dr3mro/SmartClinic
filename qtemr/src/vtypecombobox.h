// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef VTYPECOMBOBOX_H
#define VTYPECOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include "visittypes.h"


class vTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit vTypeComboBox(QWidget *parent=nullptr);
    void fillContent(int maxFollow);
private:
    VisitTypes & visitTypes = VisitTypes::instance();
public slots:
    void goUp();
    void goDown();
};

#endif // VTYPECOMBOBOX_H
