// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef SETTINGSCLASS_H
#define SETTINGSCLASS_H


#include <QCloseEvent>
#include <QKeyEvent>
#include <QMovie>
#include <QDesktopWidget>
#include "sqlextra.h"
#include "sqlbase.h"
#include "globalvariables.h"
#include "spinboxdelegate.h"
#include "mdialog.h"
#include "msettings.h"
#include "dataiohelper.h"
#include <QFileSystemWatcher>

namespace Ui {
class settingsClass;
}

class settingsClass : public mDialog
{
    Q_OBJECT
public:
    explicit settingsClass(QWidget *parent = nullptr);
    mSettings::pSettings getValuesFromUI();
    void setValuesToUI(const mSettings::pSettings &_settings);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *e);
    int exec();
    ~settingsClass();
    bool isSettingsModified=false;

protected:

private slots:
    void on_setPasswdButton_clicked();
    void on_passwordLine_textChanged(const QString &arg1);
    void on_passwordLine_returnPressed();
    void on_autoSave_toggled(bool checked);
    void on_closeButton_clicked();
    void on_resetDrugsButton_clicked();
    void on_buttonAddService_clicked();
    void on_buttonDeleteService_clicked();
    void on_serviceLine_returnPressed();
    void addNewService();
    void on_serviceLine_textChanged(const QString &arg1);
    void on_servicesTable_clicked(const QModelIndex&);
    void on_comboBoxSpeciality_currentIndexChanged(int index);
    void shortcutChecker();
    void portabilityChecker();
    void createStartMenuShortcut(bool b);
    void createDesktopShortcut(bool b);
    void on_selectDirButton_clicked();
    void toggleEncryption(bool b);
    void on_cb_portability_clicked(bool checked);

signals:
    void newMessage(QString,QString);
    void refreshCompleter();
    void reloadMainWindow();
    void reloadTheme();
private:
    void set_clear_pass();
    void initiateWatcher();
    void mklnk(const QString &path,const bool &create);
    Ui::settingsClass *ui;
    mSettings& msettings = mSettings::instance();
    mSettings::pSettings settings;
    sqlExtra *sqlextra;
    sqlBase *sqlbase;
    QString exConName;
    QString bsConName;
    QSqlTableModel *serviceModel;
    spinBoxDelegate *spinboxdelegate;
    QString appPath;
    QString lnkDesktopPath;
    QString lnkStartMenuPath;
    QFileSystemWatcher linkWatcher;
    QFileSystemWatcher portabilityWatcher;
    QMovie *movie;
    bool working=false;
    bool encryptionToggled=false;
    
};

#endif // SETTINGSCLASS_H
