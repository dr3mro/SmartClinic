#include "mgraphicsview.h"

mGraphicsView::mGraphicsView(QWidget *parent):QGraphicsView(parent)
{
   //setRenderHints(QPainter::Antialiasing  | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform );


}

void mGraphicsView::setRequest(QGraphicsItem *item)
{
    request = item;
    rotation=0;
    request->setToolTip("◾ Space Key  : Rotate +90°.<br/>"
                        "◾ Enter key  : Save.<br/>"
                        "◾ Right-Left : Navigate.<br/>"
                        "◾ Mouse Wheel: Zoom in/out <br/>");
}

void mGraphicsView::rotate90()
{
    double deg = request->rotation();
    deg += 90;

    if(deg>=360)
        deg=0;

    QPointF center = request->boundingRect().center();
    request->setTransformOriginPoint(center);
    request->setRotation(deg);
    request->update();
    rotation = deg;
}

bool mGraphicsView::isRequestUnderMouse()
{
    if(request)
        return request->isUnderMouse();

    return false;
}

void mGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton)
    {
        if(isRequestUnderMouse())
            setCursor(Qt::OpenHandCursor);
        else
            emit closeViewer();
    }
    QGraphicsView::mousePressEvent(event);
}


void mGraphicsView::mouseReleaseEvent (QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton )
        setCursor(Qt::ArrowCursor);

    QGraphicsView::mouseReleaseEvent(event);
}

void mGraphicsView::wheelEvent(QWheelEvent *event)
{
    double scaleFactor = 1.05;

    if(event->delta() > 0)
        scale(scaleFactor, scaleFactor);
    else
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    return;
}

void mGraphicsView::showEvent(QShowEvent *event)
{
    fitInView(scene()->itemsBoundingRect() ,Qt::KeepAspectRatio);
    QGraphicsView::showEvent(event);
}

void mGraphicsView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        emit loadPreviousRequest();
        break;
    case Qt::Key_Right:
        emit loadNextRequest();
        break;
    case Qt::Key_Delete:
        emit deleteRequest();
        break;
    case Qt::Key_Space:
        rotate90();
        break;
    case Qt::Key_Return:
        emit saveRotation(rotation);
        break;
    default:
        break;
    }

    QGraphicsView::keyPressEvent(event);
}

void mGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton && isRequestUnderMouse())
        emit openInWinPhotoViewer();

    QGraphicsView::mouseDoubleClickEvent(event);
}
