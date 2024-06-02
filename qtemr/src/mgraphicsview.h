// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MGRAPHICSVIEW_H
#define MGRAPHICSVIEW_H

#include <QFile>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>

#include "mdebug.h"

class mGraphicsView : public QGraphicsView {
  Q_OBJECT
 public:
  explicit mGraphicsView(QWidget *parent = nullptr);
  void setRequest(QGraphicsItem *item);

 private:
  int m_originX;
  int m_originY;
  bool leftMousePressed;
  void rotate90();
  QGraphicsItem *request;
  qreal rotation = 0;
  bool isRequestUnderMouse();

 protected:
  void mousePressEvent(QMouseEvent *event);
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
  void saveRotation(const qreal &);
  void openInWinPhotoViewer();
};

#endif  // MGRAPHICSVIEW_H
