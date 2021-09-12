// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <QApplication>
#include <QDir>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "mainwindow.h"
#include <QLocale>
#include "globalvariables.h"
#include "sqlcore.h"
#include "sqlbase.h"
#include "sqlextra.h"
#include "singleinstance.h"
#include "welcomebanner.h"
#include "dataiohelper.h"
#include "msettings.h"


//#define VLD_FORCE_ENABLE
//#include <vld.h>

#if MEMLEAK == 1 && defined(QT_DEBUG) && defined(_MSC_VER)
#include <vld.h>
#endif

static bool r_p,r_c;
static bool isSharedMemoryCreated=false;

void myMessageLogger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txt;
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-yy hh:mm AP");
    switch (type) {

    case QtDebugMsg:
        txt = QString("Debug:[%1] %2 (%3:%4) %5 ").arg(dateTime).arg(msg).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtWarningMsg:
        txt = QString("Debug:[%1] %2 (%3:%4) %5 ").arg(dateTime).arg(msg).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtCriticalMsg:
        txt = QString("Debug:[%1] %2 (%3:%4) %5 ").arg(dateTime).arg(msg).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtFatalMsg:
        txt = QString("Debug:[%1] %2 (%3:%4) %5 ").arg(dateTime).arg(msg).arg(context.file).arg(context.line).arg(context.function);
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

void createFolders()
{
    QStringList dirs = QStringList() << "data/media/" << "update" << "backup" << "themes";
    foreach (QString d,dirs)
    {
        QDir dir(d);
        if ( ! dir.exists() )
        {
            dir.mkpath(".");
        }
    }
}

void dumpDrugsDatabase()
{
    QFile resDrugsdb(":/databases/db");
    QFile drugsdb("./data/drugs.db");
    resDrugsdb.open(QIODevice::ReadOnly);
    QByteArray dbArray = resDrugsdb.readAll();
    drugsdb.open(QIODevice::WriteOnly);
    drugsdb.write(dbArray);
    drugsdb.close();
    resDrugsdb.close();
}

void copyDrugsDatabase2LocalDataFolder()
{
    QFile drugsdb("./data/drugs.db");

    int currentLocalVersion;
    int latestAvailableVersion;

    if(drugsdb.exists())
    {
        sqlCore sqlcore;

        currentLocalVersion = sqlcore.getDrugsDatabaseVersion();
        latestAvailableVersion = drugsDatabaseVer;
        sqlcore.closeDataBase();

        if(latestAvailableVersion > currentLocalVersion )
        {
            dumpDrugsDatabase();
            return;
        }
    }

    if ( !drugsdb.exists() )
    {
        dumpDrugsDatabase();
        return;
    }
}

bool isAppClosedNormaly()
{
    QFile lockFile(".lock");

    if (!lockFile.exists())
        return true;
    return false;
}

void createLockFile(welcomeBanner * banner)
{
    banner->updateprogress(QString("creating lock file"));
    QApplication::processEvents();
    QFile lockFile(".lock");
    QApplication::processEvents();
    lockFile.open(QFile::WriteOnly);
    lockFile.close();
}

//void dbDuplicator(QString from,QString to,welcomeBanner * banner)
//{
//    QFile destination(to);

//    if(destination.exists())
//        destination.remove();
//    banner->updateprogress(QString("backing up database"));
//    QFile::copy(from,to);
//}

//void createCopyOfPatientsDB(welcomeBanner * banner)
//{
//    QString from=QString("%1/data/patients.db").arg(QDir::currentPath());
//    QString to=QString("%1/data/~patients.db").arg(QDir::currentPath());

//    dbDuplicator(from,to,banner);
//}

//void backupLastPatientDB(welcomeBanner * banner)
//{
//    QString from=QString("%1/data/~patients.db").arg(QDir::currentPath());
//    QString to=QString("%1/backup/~patients.db").arg(QDir::currentPath());

//    dbDuplicator(from,to,banner);
//}

void dbIntegritycheck(welcomeBanner * banner)
{
    banner->updateprogress(QString("database integrity check"));
    sqlExtra *sqlextra = new sqlExtra(nullptr,"qt_sql_extra_Main_connection",false);
    sqlBase *sqlbase = new sqlBase(nullptr,"qt_sql_base_Main_connection",false);

    r_p = sqlbase->integrityCheck(true);
    r_c = sqlextra->integrityCheck(true);

    sqlextra->optimize();
    delete sqlextra;
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase("qt_sql_base_Main_connection");
    QSqlDatabase::removeDatabase("qt_sql_extra_Main_connection");
}

void seatBelt(SingleInstance &cInstance,welcomeBanner * banner)
{
    if(cInstance.hasPrevious(singleInstance, qApp->arguments()))
    {
        exit(1);
    }

    if (!isSharedMemoryCreated)
    {
        QMessageBox::warning(nullptr, "Warning!", "An instance of this application is running!");
        exit(1);
    }

    if (!isAppClosedNormaly())
    {
        //backupLastPatientDB(banner);
        dbIntegritycheck(banner);
        QMessageBox::information(nullptr,"Crash Detected!",
                                 QString("<p align='jusify'>%1 was not closed properly last time, luckily "
                                         "%2 had saved the last known working copy of patients' "
                                         "database at the last successful application start up into "
                                         "backup/~patients.db.<br />"
                                         "Note that this database does not contain any data from last session "
                                         "and only use it if current database became corrupted."
                                         "<br />"
                                         "For your convenience an itegrity check was performed on current databases "
                                         "and the results are:</p>"
                                         "<ul style='list-style-type:disc'>"
                                         "<li>patients.db : %3</li>"
                                         "<li>coreComponents.db : %4</li>"
                                         "</ul>"
                                         "<p>It seams that %5</p>")
                                 .arg(APPNAMEVER)
                                 .arg(APPNAME)
                                 .arg(r_p?"OK":"Corrupted")
                                 .arg(r_c?"OK":"Corrupted")
                                 .arg((r_p && r_c)? "Everything is alright, Application will now continue.":"There is a corruption in your Data! Application will now close."));
        if (!r_p || !r_c )
            exit(1);
    }
    else
    {
        QApplication::processEvents();
        createLockFile(banner);
        //createCopyOfPatientsDB(banner);
    }
}

void initializeSettings()
{
    mSettings& settings = mSettings::instance();
    settings.readSettings();
    settings.readDbOptions();
}

int main(int argc, char *argv[])
{

#if defined(_DEBUG) && MEMLEAK == 2
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif 

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // DPI support
    QApplication a(argc, argv);
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));


    QCommandLineParser clParser;
    clParser.setApplicationDescription("Smart Clinic helper");
    clParser.addHelpOption();
    clParser.addVersionOption();

    QCommandLineOption makeUpdatePkgOption("makeUpdatePackage", QCoreApplication::translate("main", "make update package"));

    clParser.addOption(makeUpdatePkgOption);
    clParser.addPositionalArgument("changes", QCoreApplication::translate("main", "Source file to copy."));
    clParser.addPositionalArgument("url", QCoreApplication::translate("main", "Destination directory."));

    clParser.process(a);

    bool makeUpdatePKG = clParser.isSet(makeUpdatePkgOption);

    if(makeUpdatePKG){
        QString changes = clParser.positionalArguments().at(0);
        QString pkgUrl = clParser.positionalArguments().at(1);

        if(!QDir("updatePKGs").exists())
            QDir().mkdir("updatePKGs");

        squeeze::compact(EXENAME,"updatePKGs/sc.pkg");
        QString md5 = QString(QCryptographicHash::hash(dataIOhelper::readFile("updatePKGs/sc.pkg"),QCryptographicHash::Md5 ).toHex());
        QByteArray updateData = QString("%1;%2;%3;%4;%5;%6;%7").arg(
                    APPVERSION,BUILD,BUILDDATE,BUILDTIME,pkgUrl,md5,changes).toUtf8();
        dataIOhelper::saveFile("updateInfo",updateData);
        exit(0);
    }

    qRegisterMetaType<QVector<int> >("QVector<int>");
    qRegisterMetaType<QTextCursor>("QTextCursor");
    qRegisterMetaType<QAbstractSocket::SocketState>();
    qRegisterMetaType<Qt::Orientation>("Qt::Orientation");
    qRegisterMetaType<QList<QPersistentModelIndex> >("QList<QPersistentModelIndex>");
    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");


    welcomeBanner *banner = new welcomeBanner;
    banner->show();

    banner->updateprogress(QString("initializing application"));
    dataIOhelper::setCurrentFolder();
    QApplication::processEvents();
    initializeSettings();
    QApplication::processEvents();
    banner->updateprogress(QString("initializing settings"));
    QSharedMemory sharedMemory;
    QApplication::processEvents();
    sharedMemory.setKey(singleInstance);
    QApplication::processEvents();
    banner->updateprogress(QString("initializing single Instance"));
    QApplication::processEvents();
    isSharedMemoryCreated = sharedMemory.create(1);
    QApplication::processEvents();
    banner->updateprogress(QString("initializing logger"));
    QApplication::processEvents();
    qSetMessagePattern("[%{type}] %{appname} (%{file}:%{line}) - %{message}");
    QApplication::processEvents();
    qInstallMessageHandler(myMessageLogger);
    a.setQuitOnLastWindowClosed(false);
    QApplication::processEvents();
    banner->updateprogress(QString("creating folders"));
    QApplication::processEvents();
    createFolders();
    QApplication::processEvents();
    dataIOhelper::dumpLogoNotExists();
    dataIOhelper::dumpBannerTemplate();
    QApplication::processEvents();
    banner->updateprogress(QString("drugs local databse"));
    QApplication::processEvents();
    copyDrugsDatabase2LocalDataFolder();
    QApplication::processEvents();
    banner->updateprogress(QString("creating UserInterface"));
    QApplication::processEvents();
    SingleInstance cInstance;
    QApplication::processEvents();
    MainWindow w;
    QApplication::processEvents();
    banner->updateprogress(QString("Making sure only one instance is running"));
    QApplication::processEvents();
    seatBelt(cInstance,banner);
    QApplication::processEvents();
    QObject::connect(&cInstance,SIGNAL(doAction()),&w,SLOT(showMainwindowIfMinimizedToTray()));
    cInstance.listen(singleInstance);
    QApplication::processEvents();
    w.boot();
    QApplication::processEvents();
    QRect screenres = qApp->screenAt(QCursor::pos())->geometry();

    w.move(QPoint(screenres.x(), screenres.y()));
    w.showMaximized();
    QApplication::processEvents();
    banner->updateprogress(QString("Starting Application"));
    banner->setProgress(100);
    QApplication::processEvents();
    banner->close();
    delete banner;
    auto exitCode = a.exec();
    //_CrtDumpMemoryLeaks();
    
    return  exitCode;// a.exec();;
}
