#ifndef TOAST_H
#define TOAST_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QSound>
#include <QApplication>
#include <QMouseEvent>
#include <QShowEvent>
#include <QDesktopWidget>
class toast : public QLabel
{
    Q_OBJECT
public:
    explicit toast(QWidget *parent=nullptr);
    void setCenterPos(int pos);
    void setMessage(QString title,QString msg);
    void setMessageType(QString title);

private slots:
    void moveToastin();
    void moveToastout();
private:
    void moveCenter();
    QRect getScreenRect();
    int centerPos;
    int horizontalPos;
    int verticalPos;
    QTimer miTimer;
    QTimer moTimer;
    QTimer fTimer;
    QTimer wait;
protected:
    void mousePressEvent(QMouseEvent *e);
    void showEvent(QShowEvent *e);
};

#endif // TOAST_H
