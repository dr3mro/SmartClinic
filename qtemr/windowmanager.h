#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>
class WindowManager : public QWidget
{
    Q_OBJECT
public:
    explicit WindowManager(QWidget *parent = nullptr);
    void centerOnScreen(QWidget *widget);
    QRect getDesktop();

signals:

public slots:
};

#endif // WINDOWMANAGER_H
