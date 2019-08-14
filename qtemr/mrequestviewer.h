#ifndef MREQUESTVIEWER_H
#define MREQUESTVIEWER_H

#include <QKeyEvent>
#include <QImageReader>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPaintEvent>
#include <QTextDocument>
#include <QTextCursor>
#include <QPixmap>
#include <QVector>
#include <QImageWriter>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include "mdialog.h"
#include "mdebug.h"


namespace Ui {
class mRequestViewer;
}

class mRequestViewer : public mDialog
{
    Q_OBJECT

public:
    explicit mRequestViewer(QWidget *parent = nullptr);
    void loadRequest(QString &path);
    void setRequests(QVector<QVector<QString> > &vector, int &i);
    ~mRequestViewer();

private slots:
    void loadPreviousRequest();
    void loadNextRequest();
    void deleteRequestMedia();
    void saveRotation(qreal &r);
    void openInWinPhotoViewer();

private:
    void Go();
    void setBanner();
    Ui::mRequestViewer *ui;
    QGraphicsScene scene;
    QImageReader iReader;
    QVector<QVector<QString> >  requests;
    QGraphicsPixmapItem *media;
    int requestLength;
    int index;
    QString banner;
    QString title;
    QString request;
    QImage readImage(QString &path);
    bool writeImage(QString path, QImage pic);

protected:
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);

};

#endif // MREQUESTVIEWER_H
