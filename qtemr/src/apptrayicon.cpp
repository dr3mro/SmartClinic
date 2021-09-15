// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "apptrayicon.h"

appTrayIcon::appTrayIcon(QObject *parent) : QSystemTrayIcon(parent)
{
    setIcon(QIcon(":/Graphics/appicon"));
    trayMenu = new QMenu();
    dbSubMenu = new QMenu(trayMenu);
    easySubMenu = new QMenu(trayMenu);

    dbSubMenu->setTitle("My Data");
    dbSubMenu->setIcon(QIcon(":/Graphics/sptreadsheet"));

    easySubMenu->setTitle("Easy Typing");
    easySubMenu->setIcon(QIcon(":/Graphics/bolt"));

    a_about = new QAction("&About",this);
    connect (a_about,SIGNAL(triggered()),parent,SLOT(show_about_win()));
    a_about->setIcon(QIcon(":/Graphics/info"));

    a_settings = new QAction("&Settings",this);
    a_settings->setShortcut(QKeySequence(Qt::Key_F9));
    a_settings->setShortcutContext(Qt::ApplicationShortcut);
    connect (a_settings,SIGNAL(triggered()),parent,SLOT(show_settings_win()));
    a_settings->setIcon(QIcon(":/Graphics/settings"));

    a_expander = new QAction("&Drugs Expander",this);
    connect (a_expander,SIGNAL(triggered()),parent,SLOT(show_expand_win()));
    a_expander->setIcon(QIcon(":/Graphics/expand"));

    a_dietsEdit = new QAction("&Diet Editor",this);
    connect (a_dietsEdit,SIGNAL(triggered()),parent,SLOT(showDieteditWin()));
    a_dietsEdit->setIcon(QIcon(":/ionicons/leaf"));

    a_genRec = new QAction("&Generate",this);
    connect (a_genRec,SIGNAL(triggered()),parent,SLOT(show_gen_win()));
    a_genRec->setIcon(QIcon(":/Graphics/infinity"));

    a_backup = new QAction("&Back up",this);
    connect(a_backup,SIGNAL(triggered()),parent,SLOT(show_backup_win()));
    a_backup->setIcon(QIcon(":/Graphics/shield"));

    a_listEdit = new QAction("&Typing Bird",this);
    connect (a_listEdit,SIGNAL(triggered()),parent,SLOT(show_listEdit_win()));
    a_listEdit->setIcon(QIcon(":/Graphics/list"));

    a_favourites = new QAction("&Favourite Drugs",this);
    connect (a_favourites,SIGNAL(triggered()),parent,SLOT(show_favouritesDrugs_win()));
    a_favourites->setIcon(QIcon(":/Graphics/heart"));

    a_exit = new QAction("&Exit",this);
    a_exit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    a_exit->setShortcutContext(Qt::ApplicationShortcut);
    connect(a_exit,SIGNAL(triggered()),parent,SLOT(close()));
    a_exit->setIcon(QIcon(":/Graphics/remove"));

    a_toggle = new QAction("&Show/Hide",this);
    connect(a_toggle,SIGNAL(triggered()),parent,SLOT(toggleWindow()));
    a_toggle->setIcon(QIcon(":/Graphics/showHide"));

    a_CompactDataBase = new QAction("&Optimize",this);
    connect(a_CompactDataBase,SIGNAL(triggered()),parent,SLOT(fixDatabase()));
    a_CompactDataBase->setIcon(QIcon(":/Graphics/dash"));

    a_exportPatientList = new QAction("&Export",this);
    connect(a_exportPatientList,SIGNAL(triggered()),parent,SLOT(exportPatientList()));
    a_exportPatientList->setIcon(QIcon(":/Graphics/export"));

    a_miniUpdate = new QAction("&Update",this);
    connect(a_miniUpdate,SIGNAL(triggered()),parent,SLOT(show_update_win()));
    a_miniUpdate->setIcon(QIcon(":/ionicons/earth"));

    a_feedback = new QAction("&Feedback",this);
    connect(a_feedback,SIGNAL(triggered()),parent,SLOT(show_feedback_win()));
    a_feedback->setIcon(QIcon(":/ionicons/message"));


    a_conEdit = new QAction("&Conditions",this);
    connect(a_conEdit,SIGNAL(triggered()),parent,SLOT(show_commonConditionsEdit()));
    a_conEdit->setIcon(QIcon(":/Graphics/puzle"));


    a_merge = new QAction("&Merge Visits",this);
    connect(a_merge,SIGNAL(triggered()),parent,SLOT(showMergedlg()));
    a_merge->setIcon(QIcon(":/ionicons/merge"));

    QList<QAction*> actionsList;
    QList<QAction*> dbList;
    QList<QAction*> easyList;
    actionsList  << a_settings << a_miniUpdate << a_feedback << a_about << a_exit;
    dbList << a_CompactDataBase << a_genRec << a_backup << a_exportPatientList << a_merge;
    easyList << a_listEdit << a_favourites << a_expander << a_dietsEdit << a_conEdit ;

    dbSubMenu->addActions(dbList);
    easySubMenu->addActions(easyList);
    trayMenu->addAction(a_toggle);
    trayMenu->addMenu(dbSubMenu);
    trayMenu->addMenu(easySubMenu);
    trayMenu->addActions(actionsList);

    this->setContextMenu(trayMenu);
    this->setToolTip(QString("%1 %2").arg(APPNAME,APPVERSION));
    connect (this,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),parent,SLOT(toggleWindow(QSystemTrayIcon::ActivationReason)));
}

appTrayIcon::~appTrayIcon()
{
    delete a_about;
    delete a_settings;
    delete a_genRec;
    delete a_backup;
    delete a_listEdit;
    delete a_favourites;
    delete a_exit;
    delete a_toggle;
    delete a_exportPatientList;
    delete a_CompactDataBase;
    delete a_miniUpdate;
    delete a_feedback;
    delete a_merge;
    delete dbSubMenu;
    delete easySubMenu;
    delete trayMenu;
    delete a_conEdit;
    delete a_dietsEdit;
}

void appTrayIcon::toggleActions(bool b)
{
    a_about->setEnabled(b);
    a_settings->setEnabled(b);
    a_genRec->setEnabled(b);
    a_expander->setEnabled(b);
    a_exportPatientList->setEnabled(b);
    a_backup->setEnabled(b);
    a_listEdit->setEnabled(b);
    a_favourites->setEnabled(b);
    a_miniUpdate->setEnabled(b);
    a_feedback->setEnabled(b);
    a_conEdit->setEnabled(b);
    a_exit->setEnabled(b);
    a_toggle->setEnabled(b);
    a_CompactDataBase->setEnabled(b);
    dbSubMenu->setEnabled(b);
    easySubMenu->setEnabled(b);

}

void appTrayIcon::showMenu()
{
    contextMenu()->move(geometry().center());
    contextMenu()->exec();
}
