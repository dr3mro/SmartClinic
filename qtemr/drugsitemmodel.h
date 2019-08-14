#ifndef DRUGSITEMMODEL_H
#define DRUGSITEMMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include "mdebug.h"

class DrugsItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit DrugsItemModel(QObject *parent=nullptr);
    ~DrugsItemModel();
    bool isThereActiveDrugs();
    bool isThereInactiveDrugs();
    int getPrintableDrugsCount();
};

#endif // DRUGSITEMMODEL_H
