#include "backup.h"
#include "ui_backup.h"

backup::backup(QWidget *parent) :
    mDialog(parent),
    ui(new Ui::backup)
{
    ui->setupUi(this);
    databaseVersion = dbVersion;
    ui->compatibility->setText(QString("Only Backups compatible with database version [%1] will be displayed below.").arg(databaseVersion));
    sqlbase = new sqlBase(this,"qt_sql_base_backup",false);
    MaxBackUP =7;
    Working = false;
    indexLENGTH = sqlbase->getPatientIndexLength();
    ui->progressBar->setAlignment(Qt::AlignCenter);
    makeList();
    ui->progressBar->setValue(0);
    ui->progressBar->hide();
    ui->label->hide();
    ui->buttonDelete->setEnabled(false);
    ui->buttonRestore->setEnabled(false);
    QDir backupDir("backup/");
    if ( !backupDir.exists())
    {
        backupDir.mkpath("./");
    }
    this->setFixedSize(this->width(),this->height());
    ui->buttonNew->setEnabled((indexLENGTH>1));
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

}

backup::~backup()
{
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase("qt_sql_base_backup");
    delete model;
    delete ui;
}

void backup::on_closeButton_clicked()
{
    this->close();
}

QString backup::getZipMD5(QString zipFile)
{
    QString md5 = QString(QCryptographicHash::hash(( getFileContents(zipFile) ),QCryptographicHash::Md5 ).toHex() );
    return md5;

}

void backup::makeList()
{
    model = dataIOhelper::getBackUpModel(this);
    ui->listOfAvailableBackUps->setModel(model);
    ui->listOfAvailableBackUps->hideColumn(1);
    ui->listOfAvailableBackUps->hideColumn(2);
    ui->listOfAvailableBackUps->hideColumn(3);
    ui->listOfAvailableBackUps->horizontalHeader()->setStretchLastSection(true);
    if ( model->rowCount() > MaxBackUP )
        ui->buttonNew->setEnabled(false);
    else
        ui->buttonNew->setEnabled(true);
}

bool backup::createBackup()
{
    Working = true;
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    ui->label->show();
    ui->buttonDelete->setEnabled(false);
    ui->buttonRestore->setEnabled(false);
    ui->buttonNew->setEnabled(false);

    QDateTime dt = QDateTime::currentDateTime();
    QLocale locale(QLocale::English , QLocale::UnitedStates );
    QString dtLocalized = locale.toString(dt,"yyyyMMddHHmmss");
    QString cDT = locale.toString(dt,"ddd dd/MM/yyyy hh:mm:ss AP");

    ZipName =  QString ( "%1%2%3").arg("backup/").arg(dtLocalized).arg(".zip");
    QString cDateTime = QString ("%1 [Manual]").arg(cDT);
    ui->label->setText("Initiating .. ");
    QStringList mediaFilesList = sqlbase->getInvestigationsMediaFilesList();
    mediaFilesList.removeDuplicates();
    QStringList dbFilesList = QStringList() << "data/coreComponents.db"
                                            << "data/drugs.db"
                                            << "data/patients.db";

    QStringList mediDirList = getMediaDirList(mediaFilesList);
    QStringList AllFILES = dbFilesList << mediaFilesList;
    int hundredPercent = AllFILES.count();
    ZipWriter bZip(ZipName);
    bZip.setCompressionPolicy(ZipWriter::AlwaysCompress);
    bZip.addDirectory("data/media/");
    int x =0;
    foreach (QString d, mediDirList)
    {
        ui->label->setText(QString("creating folders...: %1").arg(d));
        bZip.addDirectory(d);
        QApplication::processEvents();
    }
    foreach (QString f,AllFILES )
    {
        x+=1;
        ui->progressBar->setValue(x*100/hundredPercent);
        ui->label->setText(QString("backing up: %1").arg(f));
        bZip.addFile(f,getFileContents(f));
        QApplication::processEvents();
    }
    bZip.close();
    QString MD5 = getZipMD5(ZipName);
    int backupcount = static_cast<int>(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000);
    dataIOhelper::add2BackUpXML(backupcount, cDateTime,ZipName,MD5);
    ui->label->setText("Done");
    ui->progressBar->setValue(100);
    Working = false;
    return true;
}

bool backup::clearFolders()
{
    QDir dir("data/");
    dir.removeRecursively();
    return true;
}

QByteArray backup::getFileContents(QString fileName)
{
    QFile f(fileName);

    if(!f.open(QIODevice::ReadOnly))
        return QByteArray();

    QByteArray ba = f.readAll();
    f.close();
    return ba;
}

QStringList backup::getMediaDirList(QStringList mediaFiles)
{
    QStringList baseDirs;
    foreach (QString mediaFile, mediaFiles)
    {
        QFileInfo ffo(mediaFile);
        baseDirs << ffo.path();

    }
    baseDirs.removeDuplicates();
    return baseDirs;
}

void backup::on_buttonNew_clicked()
{
    createBackup();
    makeList();
}

void backup::on_buttonDelete_clicked()
{
    QFile f(selectedZip);

    bool b = f.remove();
    if ( b || !f.exists() )
    {
        dataIOhelper::removeBackUpXml(selectedZip);
        makeList();
        ui->buttonDelete->setEnabled(false);
        ui->buttonRestore->setEnabled(false);
    }
}

void backup::on_listOfAvailableBackUps_clicked(const QModelIndex &index)
{
    selectedZip = model->data(index.sibling(index.row(),1)).toString();
    savedMD5 = model->data(index.sibling(index.row(),2)).toString();
    ui->progressBar->setValue(0);
    ui->progressBar->hide();
    ui->label->hide();
    ui->buttonDelete->setEnabled(true);
    ui->buttonRestore->setEnabled(true);
}

void backup::closeEvent(QCloseEvent *e)
{
    if ( Working )
    {
        e->ignore();
        msg.information(this,"Error","Can't Close Window while working !");
    }
    else
    {
        //e->accept();
        mDialog::closeEvent(e);
    }
}

void backup::keyPressEvent(QKeyEvent *e)
{
    if((e->key() == Qt::Key_Escape) || Working)
    {
        return;
    }

    QDialog::keyPressEvent(e);
}

void backup::on_buttonRestore_clicked()
{
    ui->buttonDelete->setEnabled(false);
    ui->buttonNew->setEnabled(false);
    ui->buttonRestore->setEnabled(false);
    Working = true;
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    ui->progressBar->show();
    ui->label->setText("Restoring");
    ui->label->show();
    emit closeDataBase();
    QApplication::processEvents();

    clearFolders();
    ZipReader rZip(selectedZip);

    QApplication::processEvents();

    QString zipMD5 = getZipMD5(selectedZip);
    if ( zipMD5 == savedMD5)
    {
        rZip.extractAll("./");
        ui->label->setText("Restore Finnished");
    }
    else
    {
        ui->label->setText("Error");
    }
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);
    Working = false;

    QApplication::processEvents();

    emit reOpenDataBase();
    emit loadFirstPatient();

    ui->listOfAvailableBackUps->clearSelection();
    ui->buttonNew->setEnabled(true);
}
