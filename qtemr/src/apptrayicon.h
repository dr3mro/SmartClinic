// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef APPTRAYICON_H
#define APPTRAYICON_H

#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include "globalvariables.h"

class appTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit appTrayIcon(QObject *parent = nullptr);
    bool childWindowsActive();
    ~appTrayIcon();
private:
    QAction *a_about;
    QAction *a_settings;
    QAction *a_genRec;
    QAction *a_backup;
    QAction *a_listEdit;
    QAction *a_favourites;
    QAction *a_expander;
    QAction *a_exit;
    QAction *a_toggle;
    QAction *a_CompactDataBase;
    QAction *a_exportPatientList;
    QAction *a_miniUpdate;
    QAction *a_conEdit;
    QAction *a_dietsEdit;
    QAction *a_merge;
    QAction *a_feedback;
    QMenu *trayMenu;
    QMenu *dbSubMenu;
    QMenu *easySubMenu;
    bool _mChildWindowActive=false;
signals:

public slots:
    void toggleActions(bool b);
    void showMenu();
protected:

};

#endif // APPTRAYICON_H
