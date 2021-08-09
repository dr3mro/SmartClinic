// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QWidget>
#include <QDesktopWidget>
#include <QScreen>
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
