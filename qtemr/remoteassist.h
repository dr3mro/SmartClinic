#ifndef REMOTEASSIST_H
#define REMOTEASSIST_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFile>
#include "sqlbase.h"
#include "mdebug.h"

namespace Ui {
class remoteAssist;
}


class remoteAssist : public QDialog
{
    Q_OBJECT

public:
    struct Visitor{
        QString name;
        QString ID;
        int sex;
        int marital;
        int age;
        QString residence;
        QString placeofbirth;
        QString job;
        QString tel;
        int visitType;
    };
    explicit remoteAssist(QWidget *parent = nullptr);
    ~remoteAssist();

public slots:
    void loadVisitors();

private slots:
    void on_visitorsTableView_clicked(const QModelIndex &index);
    void searchByID();
    void searchByName();
    void searchByTel();
    void on_visitorsTableView_doubleClicked(const QModelIndex &index);
    void on_loadID_clicked();
    void on_loadName_clicked();

private:
    QJsonDocument getJsonDocument();
    QStandardItemModel *model;
    remoteAssist::Visitor getVisitor(const int & row);
    void showVisitor(const QModelIndex &current, const QModelIndex &previous);
    void tweakTable();
    sqlBase *sqlbase;
    Ui::remoteAssist *ui;

signals:
    void search(const QString & str);
    void createVisitor(const Visitor &visitor);
};

#endif // REMOTEASSIST_H
