// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <QApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QLocale>
#include <QTextStream>
#include <QTime>

#include "dataiohelper.h"
#include "globalvariables.h"
#include "mainwindow.h"
#include "msettings.h"
#include "singleinstance.h"
#include "sqlbase.h"
#include "sqlcore.h"
#include "sqlextra.h"
#include "welcomebanner.h"

#ifndef GITMESSAGE
#define GITMESSAGE ""
#endif

// #define VLD_FORCE_ENABLE
// #include <vld.h>

#if MEMLEAK == 1 && defined(QT_DEBUG) && defined(_MSC_VER)
#include <vld.h>
#endif

static bool r_p, r_c;
static bool isSharedMemoryCreated = false;

void myMessageLogger(QtMsgType type, const QMessageLogContext &context,
                     const QString &msg) {
  QString txt;
  QString dateTime =
      QDateTime::currentDateTime().toString("yyyy-MM-yy hh:mm AP");
  switch (type) {
    case QtDebugMsg:
      txt = QString("Debug:[%1] %2 (%3:%4) %5 ")
                .arg(dateTime)
                .arg(msg)
                .arg(context.file)
                .arg(context.line)
                .arg(context.function);
      break;
    case QtWarningMsg:
      txt = QString("Debug:[%1] %2 (%3:%4) %5 ")
                .arg(dateTime)
                .arg(msg)
                .arg(context.file)
                .arg(context.line)
                .arg(context.function);
      break;
    case QtCriticalMsg:
      txt = QString("Debug:[%1] %2 (%3:%4) %5 ")
                .arg(dateTime)
                .arg(msg)
                .arg(context.file)
                .arg(context.line)
                .arg(context.function);
      break;
    case QtFatalMsg:
      txt = QString("Debug:[%1] %2 (%3:%4) %5 ")
                .arg(dateTime)
                .arg(msg)
                .arg(context.file)
                .arg(context.line)
                .arg(context.function);
      break;
    default:
      break;
  }
  QFile outFile("./error.log");
  outFile.open(QIODevice::WriteOnly | QIODevice::Append);
  QTextStream ts(&outFile);
  ts << txt << '\n';
  outFile.close();
}

void createFolders() {
  QStringList dirs = QStringList() << "data/media/"
                                   << "update"
                                   << "backup"
                                   << "themes";
  foreach (QString d, dirs) {
    QDir dir(d);
    if (!dir.exists()) {
      dir.mkpath(".");
    }
  }
}

void dumpDrugsDatabase() {
  QFile resDrugsdb(":/databases/db");
  QFile drugsdb("./data/drugs.db");
  resDrugsdb.open(QIODevice::ReadOnly);
  QByteArray dbArray = resDrugsdb.readAll();
  drugsdb.open(QIODevice::WriteOnly);
  drugsdb.write(dbArray);
  drugsdb.close();
  resDrugsdb.close();
}

void copyDrugsDatabase2LocalDataFolder() {
  QFile drugsdb("./data/drugs.db");

  int currentLocalVersion;
  int latestAvailableVersion;

  if (drugsdb.exists()) {
    sqlCore sqlcore;

    currentLocalVersion = sqlcore.getDrugsDatabaseVersion();
    latestAvailableVersion = drugsDatabaseVer;
    sqlcore.closeDataBase();

    if (latestAvailableVersion > currentLocalVersion) {
      dumpDrugsDatabase();
      return;
    }
  }

  if (!drugsdb.exists()) {
    dumpDrugsDatabase();
    return;
  }
}

bool isAppClosedNormaly() {
  QFile lockFile(".lock");
  bool lockexists = lockFile.exists();
  lockFile.close();

  if (!lockexists) return true;
  return false;
}

void createLockFile(welcomeBanner *banner) {
  banner->updateprogress(QString("creating lock file"));

  QFile lockFile(".lock");

  lockFile.open(QFile::WriteOnly);
  lockFile.close();
}

// void dbDuplicator(QString from,QString to,welcomeBanner * banner)
//{
//     QFile destination(to);

//    if(destination.exists())
//        destination.remove();
//    banner->updateprogress(QString("backing up database"));
//    QFile::copy(from,to);
//}

// void createCopyOfPatientsDB(welcomeBanner * banner)
//{
//     QString from=QString("%1/data/patients.db").arg(QDir::currentPath());
//     QString to=QString("%1/data/~patients.db").arg(QDir::currentPath());

//    dbDuplicator(from,to,banner);
//}

// void backupLastPatientDB(welcomeBanner * banner)
//{
//     QString from=QString("%1/data/~patients.db").arg(QDir::currentPath());
//     QString to=QString("%1/backup/~patients.db").arg(QDir::currentPath());

//    dbDuplicator(from,to,banner);
//}

void dbIntegritycheck(welcomeBanner *banner) {
  banner->updateprogress(QString("database integrity check"));
  sqlExtra *sqlextra =
      new sqlExtra(nullptr, "qt_sql_extra_Main_connection", false);
  sqlBase *sqlbase = new sqlBase(nullptr, "qt_sql_base_Main_connection", false);

  r_p = sqlbase->integrityCheck(true);
  r_c = sqlextra->integrityCheck(true);

  sqlextra->optimize();
  delete sqlextra;
  sqlbase->optimize();
  delete sqlbase;
  QSqlDatabase::removeDatabase("qt_sql_base_Main_connection");
  QSqlDatabase::removeDatabase("qt_sql_extra_Main_connection");
}

void seatBelt(SingleInstance &cInstance, welcomeBanner *banner) {
  if (cInstance.hasPrevious(singleInstance, qApp->arguments())) {
    exit(1);
  }

  if (!isSharedMemoryCreated) {
    QMessageBox::warning(nullptr, "Warning!",
                         "An instance of this application is running!");
    exit(1);
  }

  if (!isAppClosedNormaly()) {
    // backupLastPatientDB(banner);
    dbIntegritycheck(banner);
    QMessageBox::information(
        nullptr, "Crash Detected!",
        QString(
            "<p align='jusify'>%1 was not closed properly last time, luckily "
            "%2 had saved the last known working copy of patients' "
            "database at the last successful application start up into "
            "backup/~patients.db.<br />"
            "Note that this database does not contain any data from last "
            "session "
            "and only use it if current database became corrupted."
            "<br />"
            "For your convenience an itegrity check was performed on current "
            "databases "
            "and the results are:</p>"
            "<ul style='list-style-type:disc'>"
            "<li>patients.db : %3</li>"
            "<li>coreComponents.db : %4</li>"
            "</ul>"
            "<p>It seams that %5</p>")
            .arg(APPNAMEVER)
            .arg(APPNAME)
            .arg(r_p ? "OK" : "Corrupted")
            .arg(r_c ? "OK" : "Corrupted")
            .arg((r_p && r_c)
                     ? "Everything is alright, Application will now continue."
                     : "There is a corruption in your Data! Application will "
                       "now close."));
    if (!r_p || !r_c) exit(1);
  } else {
    createLockFile(banner);
    // createCopyOfPatientsDB(banner);
  }
}

void initializeSettings() {
  mSettings &settings = mSettings::instance();
  settings.readSettings();
  settings.readDbOptions();
}

int main(int argc, char *argv[]) {
#if defined(_DEBUG) && MEMLEAK == 2
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);  // DPI support
#endif

  QApplication a(argc, argv);
  QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

  QFontDatabase::addApplicationFont(":/fonts/CoconNextLight");
  QFontDatabase::addApplicationFont(":/fonts/ConcoNextBold");

  if (argc > 1) {
    QCommandLineParser clParser;
    clParser.setApplicationDescription("Smart Clinic helper");
    clParser.addHelpOption();
    clParser.addVersionOption();

    QCommandLineOption makeUpdatePkgOption(
        "makeUpdatePackage",
        QCoreApplication::translate("main", "make update package"));

    clParser.addOption(makeUpdatePkgOption);
    clParser.process(a);
    bool makeUpdatePKG = clParser.isSet(makeUpdatePkgOption);
    if (makeUpdatePKG) {
      if (!QDir(updatePackageDir).exists()) QDir().mkdir(updatePackageDir);

      squeeze::compact(qApp->applicationFilePath(), updatePacakgeFile);
      QString md5 = QString(
          QCryptographicHash::hash(dataIOhelper::readFile(updatePacakgeFile),
                                   QCryptographicHash::Md5)
              .toHex());
      QByteArray updateData = QString("%1;%2;%3;%4;%5;%6;%7")
                                  .arg(APPVERSION, BUILD, BUILDDATE, BUILDTIME,
                                       pkgUrl, md5, GITMESSAGE)
                                  .toUtf8();
      dataIOhelper::saveFile(updateInfoFile, updateData);
      //        qDebug() << updateData;
      exit(0);
    }
  }

  qRegisterMetaType<QVector<int> >("QVector<int>");
  qRegisterMetaType<QTextCursor>("QTextCursor");
  qRegisterMetaType<QAbstractSocket::SocketState>();
  qRegisterMetaType<Qt::Orientation>("Qt::Orientation");
  qRegisterMetaType<QList<QPersistentModelIndex> >(
      "QList<QPersistentModelIndex>");
  qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>(
      "QAbstractItemModel::LayoutChangeHint");

  welcomeBanner *banner = new welcomeBanner;
  banner->show();
  qApp->processEvents(QEventLoop::AllEvents);

  banner->updateprogress(QString("initializing application"));
  qApp->processEvents(QEventLoop::AllEvents);
  dataIOhelper::setCurrentFolder();

  initializeSettings();

  banner->updateprogress(QString("initializing settings"));
  qApp->processEvents(QEventLoop::AllEvents);
  QSharedMemory sharedMemory;

  sharedMemory.setKey(singleInstance);

  banner->updateprogress(QString("initializing single Instance"));
  qApp->processEvents(QEventLoop::AllEvents);
  isSharedMemoryCreated = sharedMemory.create(1);

  banner->updateprogress(QString("initializing logger"));
  qApp->processEvents(QEventLoop::AllEvents);

  qSetMessagePattern("[%{type}] %{appname} (%{file}:%{line}) - %{message}");

  qInstallMessageHandler(myMessageLogger);
  a.setQuitOnLastWindowClosed(false);

  banner->updateprogress(QString("creating folders"));
  qApp->processEvents(QEventLoop::AllEvents);
  createFolders();

  dataIOhelper::dumpLogoNotExists();
  dataIOhelper::dumpTemplates();

  banner->updateprogress(QString("drugs local databse"));
  qApp->processEvents(QEventLoop::AllEvents);

  copyDrugsDatabase2LocalDataFolder();
  banner->updateprogress(QString("creating UserInterface"));
  qApp->processEvents(QEventLoop::AllEvents);

  SingleInstance cInstance;
  MainWindow w;

  banner->updateprogress(QString("Making sure only one instance is running"));
  qApp->processEvents(QEventLoop::AllEvents);

  seatBelt(cInstance, banner);
  QObject::connect(&cInstance, SIGNAL(doAction()), &w,
                   SLOT(showMainwindowIfMinimizedToTray()));
  cInstance.listen(singleInstance);
  qApp->processEvents(QEventLoop::AllEvents);
  w.boot();
  banner->updateprogress(QString("Starting Application"));
  qApp->processEvents(QEventLoop::AllEvents);

  banner->setProgress(100);
  qApp->processEvents(QEventLoop::AllEvents);

  banner->deleteLater();
  w.showMaximized();
  QRect screenres = qApp->primaryScreen()->geometry();
  w.move(QPoint(screenres.x(), screenres.y()));
  //_CrtDumpMemoryLeaks();
  return a.exec();
}
