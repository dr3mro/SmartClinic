// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef SHOWALTDRUGS_H
#define SHOWALTDRUGS_H

#include <QWidget>
#include <QStandardItemModel>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSortFilterProxyModel>

namespace Ui {
class showAltDrugs;
}

class showAltDrugs : public QWidget
{
    Q_OBJECT

public:
    explicit showAltDrugs(QWidget *parent = nullptr);
    void setSelectedDrugName(QString name);
    ~showAltDrugs();
public slots:
    void setModel(QStandardItemModel *model);
    void setLabel(QString label);

private slots:
    void on_tableView_activated(const QModelIndex &index);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::showAltDrugs *ui;
    QSortFilterProxyModel *proxy_model;
    QString drugsTableCurrentSelectedDrugName;

signals:
    void replaceDrug(QString tradeName);
protected:
    void keyPressEvent(QKeyEvent *keyevent);
};

#endif // SHOWALTDRUGS_H
