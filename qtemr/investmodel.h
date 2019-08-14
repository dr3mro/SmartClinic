#ifndef INVESTMODEL_H
#define INVESTMODEL_H

#include <QStandardItemModel>
#include <QVector>
#include <QString>
#include "mdebug.h"

class InvestModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit InvestModel(QObject *parent=nullptr);
    QVector<QVector <QString> > getMediaVector();
    void clear();
    ~InvestModel();
    enum InvestigationsStates{normal=0,hasMedia=1,isPaid=2,wasPaid=3,nonPrintable=4,PrintableWithMedia=5};
private:
signals:
    void modelAboutToBeClear();
};

#endif // INVESTMODEL_H
