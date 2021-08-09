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
    QFile resDrugsdb(":/databases/drugsIndex.db");
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
    QFile lockFile(".lock");
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
    initializeSettings();
    banner->updateprogress(QString("initializing settings"));
    QSharedMemory sharedMemory;
    sharedMemory.setKey(singleInstance);
    banner->updateprogress(QString("initializing single Instance"));
    isSharedMemoryCreated = sharedMemory.create(1);
    banner->updateprogress(QString("initializing logger"));
    qSetMessagePattern("[%{type}] %{appname} (%{file}:%{line}) - %{message}");
    qInstallMessageHandler(myMessageLogger);
    a.setQuitOnLastWindowClosed(false);
    banner->updateprogress(QString("creating folders"));
    createFolders();
    dataIOhelper::dumpLogoNotExists();
    banner->updateprogress(QString("drugs local databse"));
    copyDrugsDatabase2LocalDataFolder();
    banner->updateprogress(QString("creating UserInterface"));
    SingleInstance cInstance;
    MainWindow w;
    banner->updateprogress(QString("Making sure only one instance is running"));
    seatBelt(cInstance,banner);
    QObject::connect(&cInstance,SIGNAL(doAction()),&w,SLOT(showMainwindowIfMinimizedToTray()));
    cInstance.listen(singleInstance);
    banner->updateprogress(QString("creating random hook"));
    QTime time = QTime::currentTime();
    qsrand((static_cast<uint>(time.msec())));
    banner->updateprogress(QString("creating application main parts"));
    w.boot();
    QRect screenres = QApplication::desktop()->screenGeometry(QCursor::pos());
    w.move(QPoint(screenres.x(), screenres.y()));
    w.showMaximized();
    banner->updateprogress(QString("Starting Application"));
    banner->setProgress(100);
    QTimer::singleShot(1000,banner,SLOT(close()));
    QTimer::singleShot(1500,banner,SLOT(deleteLater()));
    banner->close();
    delete banner;
    auto exitCode = a.exec();
    //_CrtDumpMemoryLeaks();
    
    //int* p = new int();
    //int n = 5;
    //p = &n;
    //while (n--) {
    //    new int;
    //}
    return  exitCode;// a.exec();;
}