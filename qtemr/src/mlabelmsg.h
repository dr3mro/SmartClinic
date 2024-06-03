// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MLABELMSG_H
#define MLABELMSG_H

#include "mdebug.h"
#include "windowmanager.h"
#include <QApplication>
#include <QFont>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QObject>
#include <QString>

class mLabelMsg : public QLabel {
  Q_OBJECT
 public:
   explicit mLabelMsg (QWidget *parent = nullptr);
   ~mLabelMsg ();
   void show ();
   void setMessage (QString msg);

 private:
   QGraphicsDropShadowEffect *effect;
   WindowManager wm;
 signals:
   void escKeyPressed ();
};

#endif  // MLABELMSG_H
