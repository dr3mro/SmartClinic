// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "windowmanager.h"

WindowManager::WindowManager(QWidget *parent) : QWidget(parent)
{

}

void WindowManager::centerOnScreen(QWidget *widget)
{
    QRect desktop = getDesktop();

    if (desktop.size() == QSize(800,600))
    {
        move(0,0);
    }
    else
    {
        int width = widget->width();
        int height = widget->height();
        int screenWidth = desktop.width();
        int screenHeight = desktop.height() * 0.95;
        widget->move(screenWidth / 2 - width / 2 + desktop.left(), screenHeight / 2 - height / 2 + desktop.top());
    }
}

QRect WindowManager::getDesktop()
{
    return qApp->topLevelWindows().at(0)->screen()->geometry();
}
