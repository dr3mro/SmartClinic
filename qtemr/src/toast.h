// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef TOAST_H
#define TOAST_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QtMultimedia/QSound>
#include <QApplication>
#include <QMouseEvent>
#include <QShowEvent>
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
    int horizontalPos=0;
    int verticalPos=0;
    QTimer miTimer;
    QTimer moTimer;
    QTimer fTimer;
    QTimer wait;
protected:
    void mousePressEvent(QMouseEvent *e);
    void showEvent(QShowEvent *e);
};

#endif // TOAST_H
