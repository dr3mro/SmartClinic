#ifndef GENERICONLINESEARCH_H
#define GENERICONLINESEARCH_H

#include "mDialog.h"
#include <QStringListModel>
#include <QDesktopServices>
#include <QUrl>
#include <QMouseEvent>


namespace Ui {
class genericOnlineSearch;
}

class genericOnlineSearch : public mDialog
{
    Q_OBJECT

public:
    explicit genericOnlineSearch(QWidget *parent = nullptr);
    void setModel(QStringList drugs);
    void setTradeName(QString tname);
    ~genericOnlineSearch();

private slots:
    void on_listView_activated(const QModelIndex &index);
    void on_buttonSearch_clicked();
    void on_listView_clicked(const QModelIndex &index);
    void tradeNameDoubleClicked();
    void searchGoogle();

private:
    Ui::genericOnlineSearch *ui;
    QStringListModel *model;
    QString rawTradeName;
    int x_cord;
    int y_cord;
    QString searchEngine();
    void openUrl(QString generic,QString engine);
    void doOpen(const QModelIndex &index);

protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // GENERICONLINESEARCH_H
