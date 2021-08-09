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
    void on_closeButton_clicked();
    void on_buttonNew_clicked();
    void on_buttonDelete_clicked();
    void on_listOfAvailableBackUps_clicked(const QModelIndex &index);
    void on_buttonRestore_clicked();
    bool createBackup();
protected:
    void closeEvent(QCloseEvent *e) override;
    void keyPressEvent(QKeyEvent *e);
private:
    Ui::backup *ui;
    mSettings& settings=mSettings::instance();
    QString getZipMD5(QString zipFile);
    void makeList();
    bool clearFolders();
    QByteArray getFileContents(QString fileName);
    QStringList getMediaDirList(QStringList mediaFiles);
    int indexLENGTH;
    QString ZipName;
    QStandardItemModel *model;
    QString selectedZip,savedMD5;
    int MaxBackUP;
    bool Working;
    myMessageBox msg;
    sqlBase *sqlbase;
    double databaseVersion;

signals:
    void closeDataBase();
    void reOpenDataBase();
    void loadFirstPatient();
};

#endif // BACKUP_H
