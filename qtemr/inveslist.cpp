#include "inveslist.h"
#include "ui_inveslist.h"

invesList::invesList(QWidget *parent, int _id) :
    mDialog(parent),
    model(new InvestModel(this)),
    ui(new Ui::invesList)
{
    ui->setupUi(this);

    sqlbase = new sqlBase(this,"qt_sql_base_invList",false);
    ID = _id;

    getNameDlg = new getInvestigationName(this);
    connect (getNameDlg,SIGNAL(investigationAccepted(QString,QString)),this,SLOT(addInvestigation(QString,QString)));
    connect (getNameDlg,SIGNAL(popUpMessage(QString,QString)),parent,SLOT(popUpMessage(QString,QString)));
    connect (this,SIGNAL(popUpMessge(QString,QString)),parent,SLOT(popUpMessage(QString,QString)));
    connect (getNameDlg,SIGNAL(hideParentWindow()),this,SLOT(mHide()));
    connect (getNameDlg,SIGNAL(showParentWindow()),this,SLOT(mShow()));

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(uptodate()));
    setFixedSize(width(),height());
    ui->ButtonDel->setEnabled(false);
    ui->ButtonNew->setEnabled(sqlbase->isPatientExists(ID));
    setWindowFlags(windowFlags() | Qt::Window | Qt::FramelessWindowHint);
    worker = new wm_invModelLoader();
    worker->setInvestigationsModel(model);
    connect (&watcher,SIGNAL(finished()),this,SLOT(loadInvestigations()));
    scale = invIconHelper::getScale();

    invTooltipWorker = new wm_investTooltipLoader;
    invTooltipWorker->setScale(scale);
    invTooltipWorker->setInvestigationsModel(model);
    connect(&tooltipWatcher,SIGNAL(finished()),this,SLOT(putToolTip()));
}

invesList::~invesList()
{
    delete worker;
    delete invTooltipWorker;
    sqlbase->optimize();
    delete sqlbase;
    QSqlDatabase::removeDatabase("qt_sql_base_invList");
    delete timer;
    delete model;
    delete getNameDlg;
    delete ui;
}

void invesList::mHide()
{
    setWindowOpacity(0.00);
}

void invesList::mShow()
{
    setWindowOpacity(1.00);
}


void invesList::on_tableView_activated(const QModelIndex &index)
{
    QString mediaFileurl = model->item(index.row(),3)->text();
    QFile file(mediaFileurl);
    QImage img;
    if( file.exists()
        && ( mediaFileurl.endsWith(".jpg",Qt::CaseInsensitive)
             ||  mediaFileurl.endsWith(".jpeg",Qt::CaseInsensitive) )
        && img.load(mediaFileurl) )
    {

        if(settings.isUseNativePhotoViewer())
        {
            QVector<QVector<QString> > vector =  model->getMediaVector();
            int index = vector.at(1).indexOf(mediaFileurl);
            requestViewer.setRequests(vector,index);
            requestViewer.exec();
        }
        else
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(mediaFileurl));
        }
    }

}

void invesList::uptodate()
{
    QString mediaFileurl,name;
    int visitDate;

    for ( int i = 0 ; i < model->rowCount() ; i++ )
    {
        QApplication::processEvents();
        name = model->item(i,1)->text();
        visitDate = model->item(i,2)->text().toInt();
        mediaFileurl = model->item(i,3)->text();
        QFile file ( mediaFileurl );
        if ( ! file.exists() )
        {
            model->removeRow(i);
            sqlbase->removeMediaUrlNormalizeRequest(ID,visitDate,mediaFileurl,name);

        }
    }
    setModal(model);
}

void invesList::on_closeButton_clicked()
{
    timer->stop();
    close();
}

void invesList::loadInvestigations()
{
    model = future.result();

    QStringList label = QStringList() << "ID" << "Investigation" << "visitDate"
                                      << "PATH" << "invDate" << "invTime" ;
    model->setHorizontalHeaderLabels(label);
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(6);
    ui->tableView->hideColumn(7);
    ui->tableView->hideColumn(8);
    ui->tableView->setColumnWidth(1,160);
    ui->tableView->setColumnWidth(4,80);
    ui->tableView->setColumnWidth(5,80);
    createTooltips(model);
    timer->start();
}

void invesList::putToolTip()
{
    model = tooltipFuture.result();
    ui->tableView->setModel(model);
}

void invesList::on_ButtonNew_clicked()
{
    getNameDlg->toggleVisualEffects(this->enableVisualEffects);
    getNameDlg->show();
}

void invesList::addInvestigation(QString invName, QString selectedImagePath)
{
    QLocale locale(QLocale::English , QLocale::UnitedStates );
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dt = locale.toString(dateTime,"ddMMyyyyHHmmss");

    int visitJulianDate = 0;
    int invDate = dateTime.date().toJulianDay();
    QString invTime = QString::number(dateTime.time().msecsSinceStartOfDay()/1000);
    int invState = 1;
    int invPrice = 0;
    QString invResults = "";

    QString inv2Name = invName;
    QString localCopyPath = QString ( "data/media/%1/" ).arg(ID);
    QString localImagePath = QString("%1%2_%3.jpg").arg(localCopyPath).arg(inv2Name.replace(QRegExp("[^A-Za-z\\d\\s]"),"_")).arg(dt);
    QImage img;
    QDir mediaDir(localCopyPath);
    bool addInvBool = false;
    if ( img.load(selectedImagePath))
    {
        mediaDir.mkpath("./");
        QFile::copy(selectedImagePath,localImagePath);
        addInvBool = sqlbase->addInvestigation(ID,visitJulianDate,invName,localImagePath,invDate,invTime,invState,invPrice,invResults);
        load();
    }
    else
    {
        emit popUpMessge("Error","Invalid Photo Selected.");
    }
    if ( addInvBool )
    {
        emit popUpMessge("Message","New Investigation has been added Successfully.");
    }
    else
    {
        QFile f(localImagePath);
        if(f.open(QFile::ReadWrite))
            return;

        f.remove();
        f.close();
        emit popUpMessge("Error","Sorry, I failed to Add your Investigation.");
    }

}

void invesList::on_ButtonDel_clicked()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    int ID = model->item(row,0)->text().toInt();
    QString invName = model->item(row,1)->text();
    int visitDate = model->item(row,2)->text().toInt();
    QString path = model->item(row,3)->text();
    sqlbase->deleteInvestigation(ID,visitDate,path,invName);
    ui->ButtonDel->setEnabled(false);
    uptodate();
}

void invesList::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    if ( row < 0 )
        ui->ButtonDel->setEnabled(false);
    else
        ui->ButtonDel->setEnabled(true);
}

void invesList::load()
{
    worker->setIdJulianDate(ID);
    future = QtConcurrent::run(worker,&wm_invModelLoader::Work);
    watcher.setFuture(future);
}

void invesList::createTooltips(InvestModel *m)
{
    invTooltipWorker->setInvestigationsModel(m);
    tooltipFuture=QtConcurrent::run(invTooltipWorker,&wm_investTooltipLoader::Work);
    tooltipWatcher.setFuture(tooltipFuture);
}

void invesList::showEvent(QShowEvent *e)
{
    load();
    mDialog::showEvent(e);
}
