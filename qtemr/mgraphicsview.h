#ifndef MGRAPHICSVIEW_H
#define MGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QFile>
#include "mdebug.h"


class mGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit mGraphicsView(QWidget *parent=nullptr);
    void setRequest(QGraphicsItem *item);
private:
    int m_originX;
    int m_originY;
    bool leftMousePressed;
    void rotate90();
    QGraphicsItem *request;
    qreal rotation=0;
    bool isRequestUnderMouse();


protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void showEvent(QShowEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:
    void closeViewer();
    void loadPreviousRequest();
    void loadNextRequest();
    void deleteRequest();
    void saveRotation(qreal &);
    void openInWinPhotoViewer();
};

#endif // MGRAPHICSVIEW_H
