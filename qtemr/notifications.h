#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class notifications;
}

class notifications : public QDialog
{
    Q_OBJECT

public:
    explicit notifications(QWidget *parent = nullptr);
    void fillList(QStringList n);
    ~notifications();
private slots:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::notifications *ui;
};

#endif // NOTIFICATIONS_H
