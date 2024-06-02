// This is an open source non-commercial project. Dear PVS-Studio, please check
// it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MMESSAGEBOX_H
#define MMESSAGEBOX_H

#include <QApplication>
#include <QCloseEvent>
#include <QMessageBox>
#include <QObject>
#include <QPropertyAnimation>
#include <QWidget>

class mMessageBox : public QMessageBox {
  Q_OBJECT
 public:
  explicit mMessageBox(QWidget *parent = nullptr);
  //    void toggleVisualEffects(bool b);
  //    bool getVisualEffectStatus();
  int exec();
  ~mMessageBox();

 public slots:
  void done(int result);
  void show();
  void onFadeOutFinished();

 protected:
  bool enableVisualEffects = true;
  void closeEvent(QCloseEvent *e);

 private:
  QPropertyAnimation *mpFadeIn;
  QPropertyAnimation *mpFadeOut;
  int mResult;
};

#endif  // MMESSAGEBOX_H
