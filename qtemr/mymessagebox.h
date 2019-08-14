#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include "mmessagebox.h"
#include "dataiohelper.h"
#include "msettings.h"
#include <QCheckBox>
#include <QObject>


class myMessageBox : public mMessageBox
{
    Q_OBJECT
public:
    explicit myMessageBox(QWidget *parent = nullptr);
    mMessageBox *messagebox;
    int question(QWidget *parent, const QString &title, const QString &text,  const StandardButton button0, const StandardButton button1, bool DefaultNo=false);
    int question(QWidget *parent ,const QString &title, const QString &text, const StandardButton button0, const StandardButton button1,const StandardButton button2);
    int information(QWidget *parent, const QString &title, const QString &text);
signals:

public slots:

};

#endif // MYMESSAGEBOX_H
