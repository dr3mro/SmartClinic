// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef MDIALOG_H
#define MDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QTimer>
#include <QCloseEvent>
#include <QApplication>
#include <QPropertyAnimation>
#include "windowmanager.h"

class mDialog : public QDialog
{
    Q_OBJECT
public:
    explicit mDialog(QWidget * parent=nullptr);
    void toggleVisualEffects(bool b);
    bool getVisualEffectStatus();
    int exec();
    virtual ~mDialog();
    WindowManager wm;

public slots:
    void done(int result);
    void show();
    void onFadeOutFinished();

protected:
    bool enableVisualEffects;
    virtual void closeEvent(QCloseEvent *e);
    void showEvent(QShowEvent *e);

private:
    QPropertyAnimation *mpFadeIn;
    QPropertyAnimation *mpFadeOut;
    int mResult;


private slots:

};

#endif // MDIALOG_H
