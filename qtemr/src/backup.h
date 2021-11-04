// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef BACKUP_H
#define BACKUP_H

#include <QDialog>
#include <QCryptographicHash>
#include <QEvent>
#include "mymessagebox.h"
#include "sqlbase.h"
#include "dataiohelper.h"
#include "3rdparty/zip/zipreader.h"
#include "3rdparty/zip/zipwriter.h"
#include "globalvariables.h"
#include "mdialog.h"
#include "msettings.h"

namespace Ui {
class backup;
}

class backup : public mDialog
{
    Q_OBJECT
public:
    explicit backup(QWidget *parent = nullptr);
    ~backup();

private slots:
    void onCloseButton_clicked();
    void onButtonNew_clicked();
    void onButtonDelete_clicked();
    void onListOfAvailableBackUps_clicked(const QModelIndex &index);
    void onButtonRestore_clicked();
    bool createBackup();
protected:
    void closeEvent(QCloseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
private:
    Ui::backup *ui;
    mSettings& settings=mSettings::instance();
    QString getZipMD5(const QString &zipFile);
    void makeList();
    bool clearFolders();
    void getFileContents(const QString &fileName, QByteArray *fileContents);
    QStringList getMediaDirList(QStringList mediaFiles);
    QString ZipName;
    QStandardItemModel *model;
    QString selectedZip,savedMD5;
    sqlBase *sqlbase;
    double databaseVersion;
    int MaxBackUP;
    bool Working;
    int indexLENGTH;
    myMessageBox msg;

signals:
    void closeDataBase();
    void reOpenDataBase();
    void loadFirstPatient();
    void quit_app();
};

#endif // BACKUP_H
