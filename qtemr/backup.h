#ifndef BACKUP_H
#define BACKUP_H

#include <QDialog>
#include <QCryptographicHash>
#include <QEvent>
#include "mymessagebox.h"
#include "sqlbase.h"
#include "dataiohelper.h"
#include "3rdparty/zipreader.h"
#include "3rdparty/zipwriter.h"
#include "globalvariables.h"
#include "mdialog.h"

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
    void closeEvent(QCloseEvent *e);
    void keyPressEvent(QKeyEvent *e);
private:
    Ui::backup *ui;
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
