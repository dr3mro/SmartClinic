#include "mdialog.h"

mDialog::mDialog(QWidget *parent):QDialog(parent), mResult( 0 )
{

    mpFadeIn = new QPropertyAnimation( this, "windowOpacity" );
    mpFadeIn->setDuration(375);
    mpFadeIn->setStartValue(0.0);
    mpFadeIn->setEndValue(1.0);
    mpFadeIn->setEasingCurve(QEasingCurve::InSine);

    mpFadeOut = new QPropertyAnimation( this, "windowOpacity" );
    mpFadeOut->setDuration(250);
    mpFadeOut->setStartValue(1.0);
    mpFadeOut->setEndValue(0.0);
    mpFadeOut->setEasingCurve(QEasingCurve::OutSine);

    connect(mpFadeOut,SIGNAL(finished()),this,SLOT(onFadeOutFinished()));
}

void mDialog::toggleVisualEffects(bool b)
{
    enableVisualEffects = b;
}

bool mDialog::getVisualEffectStatus()
{
    return enableVisualEffects;
}



int mDialog::exec()
{
    if(enableVisualEffects)
        mpFadeIn->start();
    else
        setWindowOpacity(1.00);
    return QDialog::exec();
}

mDialog::~mDialog()
{
    delete mpFadeIn;
    delete mpFadeOut;
}

void mDialog::done(int result)
{
    mResult = result;
    if(!enableVisualEffects)
        QDialog::done(mResult);
    else
        mpFadeOut->start();
}

void mDialog::show()
{
    if(!enableVisualEffects)
    {
        QDialog::show();
        setWindowOpacity(1.00);
    }
    else
    {
        QDialog::show();
        mpFadeIn->start();
    }
}

void mDialog::onFadeOutFinished()
{
    QDialog::done(mResult);
}

void mDialog::closeEvent(QCloseEvent *e)
{
    if(enableVisualEffects)
    {
        mpFadeOut->start();
        e->ignore();
    }
}

void mDialog::showEvent(QShowEvent *e)
{
     wm.centerOnScreen(this);
     QDialog::showEvent(e);
}
