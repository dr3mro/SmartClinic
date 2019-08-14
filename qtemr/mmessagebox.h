#ifndef MMESSAGEBOX_H
#define MMESSAGEBOX_H

#include <QWidget>
#include <QMessageBox>
#include <QObject>
#include <QCloseEvent>
#include <QApplication>

#include <QPropertyAnimation>

class mMessageBox : public QMessageBox
{
    Q_OBJECT
public:
    explicit mMessageBox(QWidget *parent=nullptr);
//    void toggleVisualEffects(bool b);
//    bool getVisualEffectStatus();
    int exec();
    ~mMessageBox();

public slots:
    void done(int result);
    void show();
    void onFadeOutFinished();

protected:
    bool enableVisualEffects=true;
    void closeEvent(QCloseEvent *e);

private:
    QPropertyAnimation *mpFadeIn;
    QPropertyAnimation *mpFadeOut;
    int mResult;
};

#endif // MMESSAGEBOX_H
