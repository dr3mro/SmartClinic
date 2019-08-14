#include "mrequestviewer.h"
#include "ui_mrequestviewer.h"

mRequestViewer::mRequestViewer(QWidget *parent) :
    mDialog(parent),
    ui(new Ui::mRequestViewer)
{
    ui->setupUi(this);
    QRect screenres = QApplication::desktop()->screenGeometry(QCursor::pos());
    resize(screenres.width(),screenres.height());
    setStyleSheet("background-color: rgba(0, 0, 0, 196);");
    //setAttribute(Qt::WA_NoSystemBackground, true);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setStyleSheet("background:transparent");
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::SplashScreen);
    //setWindowState(Qt::WindowFullScreen);
    ui->graphicsView->setScene(&scene);
    connect(ui->graphicsView,SIGNAL(closeViewer()),this,SLOT(close()),Qt::QueuedConnection);
    connect(ui->graphicsView,SIGNAL(loadPreviousRequest()),this,SLOT(loadPreviousRequest()),Qt::QueuedConnection);
    connect(ui->graphicsView,SIGNAL(loadNextRequest()),this,SLOT(loadNextRequest()),Qt::QueuedConnection);
    connect(ui->graphicsView,SIGNAL(deleteRequest()),this,SLOT(deleteRequestMedia()));
    connect(ui->graphicsView,SIGNAL(saveRotation(qreal&)),this,SLOT(saveRotation(qreal&)));
    connect(ui->graphicsView,SIGNAL(openInWinPhotoViewer()),this,SLOT(openInWinPhotoViewer()));
}

void mRequestViewer::loadRequest(QString &path)
{
    scene.clear();
    media = scene.addPixmap(QPixmap::fromImage(readImage(path)));
    media->setFlag(QGraphicsItem::ItemIsMovable);
    scene.setSceneRect(media->sceneBoundingRect());
    ui->graphicsView->setRequest(media);
    ui->graphicsView->fitInView(scene.sceneRect(),Qt::KeepAspectRatio);
    //ui->graphicsView->fitInView(this->rect(),Qt::AspectRatioMode::KeepAspectRatio);
    iReader.device()->close();
    emit repaint();
}

void mRequestViewer::setRequests(QVector<QVector <QString> > &vector, int &i)
{
    requests = vector;
    index = i;
    requestLength = vector.at(0).length();
    Go();
}

void mRequestViewer::loadPreviousRequest()
{

    index -=1;

    if(index<=0)
        index = 0;

    Go();

}

void mRequestViewer::loadNextRequest()
{
    index +=1;

    if(index >= requestLength )
        index = requestLength-1;

    Go();
}

void mRequestViewer::deleteRequestMedia()
{
    bool b;
    int reply = QMessageBox::question(nullptr,tr("Warning"),tr("Are you sure that you want to delete this request media file? "
                                                         "This can not be undone."),QMessageBox::Yes,QMessageBox::No);
    if ( reply == QMessageBox::Yes)
    {
        QFile file(request);
        b = file.remove();
        close();
        if(b)
            QMessageBox::information(nullptr,tr("infromation"),tr("Media file deleted successfuly."));
        else
            QMessageBox::information(nullptr,tr("infromation"),tr("Media file deletion failed."));

    }
}

void mRequestViewer::saveRotation(qreal &r)
{
    bool b;
    int reply = QMessageBox::question(nullptr,tr("Warning"),tr("Are you sure that you want to save rotation to media file? "
                                                         "This can not be undone."),QMessageBox::Yes,QMessageBox::No);
    if ( reply == QMessageBox::Yes)
    {
        QTransform transform;
        transform.rotate(r);
        b = writeImage(request,readImage(request).transformed(transform,Qt::SmoothTransformation));
        if(b)
            QMessageBox::information(nullptr,tr("infromation"),tr("Media file saved successfuly."));
        else
            QMessageBox::information(nullptr,tr("infromation"),tr("Media file save failed."));

    }


}

void mRequestViewer::openInWinPhotoViewer()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(request));
    close();
}

void mRequestViewer::Go()
{
    title = requests.at(0).at(index);
    request = requests.at(1).at(index);
    setBanner();
    loadRequest(request);
}

void mRequestViewer::setBanner()
{
    if(requestLength ==1 )
        banner = title;
    else if (requestLength > 1)
        banner = QString("%1 (%2/%3)").arg(title).arg(index+1).arg(requestLength);
    else
        banner = QString();
}

QImage mRequestViewer::readImage(QString &path)
{
    iReader.setFileName(path);
    iReader.setAutoTransform(true);
    return iReader.read();
}

bool mRequestViewer::writeImage(QString path,QImage pic)
{
    QImageWriter writer(path,"jpeg");
    return writer.write(pic);
}

mRequestViewer::~mRequestViewer()
{
    delete ui;
}

void mRequestViewer::hideEvent(QHideEvent *event)
{
    scene.clear();
    mDialog::hideEvent(event);
}

void mRequestViewer::closeEvent(QCloseEvent *event)
{
    scene.clear();
    mDialog::closeEvent(event);
}

void mRequestViewer::paintEvent(QPaintEvent *event)
{
    mDialog::paintEvent(event);
    QPainter painter(this);
    painter.save();
    QFont font;
    font.setFamily("Calibri");
    font.setPointSize(20);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(QPen(Qt::black));
    painter.drawText(42,42,banner);
    painter.setPen(QPen(Qt::white));
    painter.drawText(40,40,banner);
    painter.restore();
}
